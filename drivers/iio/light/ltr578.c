// SPDX-License-Identifier: GPL-2.0-only
/*
 * IIO driver for Lite-On LTR-578ALS-01 ambient light + proximity sensor
 *
 * Copyright (C) 2026 nomorecoolnicknames <78512247+nomorecoolnicknames@users.noreply.github.com>
 *
 * The LTR-578 shares its ALS data register block with the LTR-390 but adds a
 * proximity engine (IR LED + PS ADC). Polling only; the INT pad is optional
 * and not used here.
 *
 * Register map from the LTR-578ALS-01 datasheet.
 */

#include <linux/i2c.h>
#include <linux/iio/iio.h>
#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/regmap.h>

#define LTR578_MAIN_CTRL	0x00
#define LTR578_PS_LED		0x01
#define LTR578_PS_PULSES	0x02
#define LTR578_PS_MEAS_RATE	0x03
#define LTR578_ALS_MEAS_RATE	0x04
#define LTR578_ALS_GAIN		0x05
#define LTR578_PART_ID		0x06
#define LTR578_MAIN_STATUS	0x07
#define LTR578_PS_DATA		0x08	/* 2 bytes, 11 bit */
#define LTR578_ALS_DATA		0x0d	/* 3 bytes, 20 bit */

#define LTR578_PS_EN		BIT(0)
#define LTR578_ALS_EN		BIT(1)

#define LTR578_PART_ID_VAL	0xb1

/* defaults: LED 60kHz/100mA, 8 pulses, 8 bit/100ms PS; 100ms/gain-3 ALS */
#define LTR578_PS_LED_DEF	0x36
#define LTR578_PS_PULSES_DEF	0x08
#define LTR578_PS_MEAS_RATE_DEF	0x55
#define LTR578_ALS_MEAS_RATE_DEF 0x22
#define LTR578_ALS_GAIN_DEF	0x01	/* gain 3 */

struct ltr578_data {
	struct regmap *regmap;
	u32 near_level;
};

static const struct regmap_config ltr578_regmap_config = {
	.name = "ltr578",
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0x26,
};

static int ltr578_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int *val,
			   int *val2, long mask)
{
	struct ltr578_data *data = iio_priv(indio_dev);
	u8 buf[3];
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			ret = regmap_bulk_read(data->regmap, LTR578_ALS_DATA,
					       buf, 3);
			if (ret)
				return ret;
			*val = (buf[2] & 0x0f) << 16 | buf[1] << 8 | buf[0];
			return IIO_VAL_INT;
		case IIO_PROXIMITY:
			ret = regmap_bulk_read(data->regmap, LTR578_PS_DATA,
					       buf, 2);
			if (ret)
				return ret;
			*val = (buf[1] & 0x07) << 8 | buf[0];
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SCALE:
		/* lux = 0.8 * counts / (gain * integration time); 3 * 100ms */
		*val = 0;
		*val2 = 266667;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}

static const struct iio_info ltr578_info = {
	.read_raw = ltr578_read_raw,
};

static ssize_t ltr578_read_near_level(struct iio_dev *indio_dev,
				      uintptr_t priv,
				      const struct iio_chan_spec *chan,
				      char *buf)
{
	struct ltr578_data *data = iio_priv(indio_dev);

	return sysfs_emit(buf, "%u\n", data->near_level);
}

static const struct iio_chan_spec_ext_info ltr578_ext_info[] = {
	{
		.name = "nearlevel",
		.shared = IIO_SEPARATE,
		.read = ltr578_read_near_level,
	},
	{ /* sentinel */ }
};

static const struct iio_chan_spec ltr578_channels[] = {
	{
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	},
	{
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.ext_info = ltr578_ext_info,
	},
};

static void ltr578_disable(void *arg)
{
	struct ltr578_data *data = arg;

	regmap_write(data->regmap, LTR578_MAIN_CTRL, 0);
}

static int ltr578_probe(struct i2c_client *client)
{
	struct ltr578_data *data;
	struct iio_dev *indio_dev;
	unsigned int part_id;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->regmap = devm_regmap_init_i2c(client, &ltr578_regmap_config);
	if (IS_ERR(data->regmap))
		return dev_err_probe(&client->dev, PTR_ERR(data->regmap),
				     "regmap initialization failed\n");

	ret = regmap_read(data->regmap, LTR578_PART_ID, &part_id);
	if (ret)
		return ret;
	if (part_id != LTR578_PART_ID_VAL)
		dev_warn(&client->dev, "unexpected part id 0x%02x\n", part_id);

	if (device_property_read_u32(&client->dev, "proximity-near-level",
				     &data->near_level))
		data->near_level = 0;

	indio_dev->info = &ltr578_info;
	indio_dev->channels = ltr578_channels;
	indio_dev->num_channels = ARRAY_SIZE(ltr578_channels);
	indio_dev->name = "ltr578";
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = regmap_write(data->regmap, LTR578_PS_LED, LTR578_PS_LED_DEF);
	if (ret)
		return ret;
	ret = regmap_write(data->regmap, LTR578_PS_PULSES,
			   LTR578_PS_PULSES_DEF);
	if (ret)
		return ret;
	ret = regmap_write(data->regmap, LTR578_PS_MEAS_RATE,
			   LTR578_PS_MEAS_RATE_DEF);
	if (ret)
		return ret;
	ret = regmap_write(data->regmap, LTR578_ALS_MEAS_RATE,
			   LTR578_ALS_MEAS_RATE_DEF);
	if (ret)
		return ret;
	ret = regmap_write(data->regmap, LTR578_ALS_GAIN, LTR578_ALS_GAIN_DEF);
	if (ret)
		return ret;

	ret = regmap_write(data->regmap, LTR578_MAIN_CTRL,
			   LTR578_ALS_EN | LTR578_PS_EN);
	if (ret)
		return ret;

	ret = devm_add_action_or_reset(&client->dev, ltr578_disable, data);
	if (ret)
		return ret;

	return devm_iio_device_register(&client->dev, indio_dev);
}

static const struct i2c_device_id ltr578_id[] = {
	{ "ltr578" },
	{ }
};
MODULE_DEVICE_TABLE(i2c, ltr578_id);

static const struct of_device_id ltr578_of_match[] = {
	{ .compatible = "liteon,ltr578" },
	{ }
};
MODULE_DEVICE_TABLE(of, ltr578_of_match);

static struct i2c_driver ltr578_driver = {
	.driver = {
		.name = "ltr578",
		.of_match_table = ltr578_of_match,
	},
	.probe = ltr578_probe,
	.id_table = ltr578_id,
};
module_i2c_driver(ltr578_driver);

MODULE_AUTHOR("nomorecoolnicknames <78512247+nomorecoolnicknames@users.noreply.github.com>");
MODULE_DESCRIPTION("Lite-On LTR-578ALS ambient light and proximity sensor driver");
MODULE_LICENSE("GPL");
