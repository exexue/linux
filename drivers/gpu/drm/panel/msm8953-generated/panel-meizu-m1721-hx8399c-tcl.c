// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 postmarketOS m1721 port
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct hx8399c_tcl {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data supplies[2];
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline struct hx8399c_tcl *to_hx8399c_tcl(struct drm_panel *panel)
{
	return container_of(panel, struct hx8399c_tcl, panel);
}

static void hx8399c_tcl_reset(struct hx8399c_tcl *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(120);
}

static int hx8399c_tcl_on(struct hx8399c_tcl *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = dsi };

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0xff, 0x83, 0x99);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x63, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x25, 0x5a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
			  0x02, 0x02, 0x6d, 0x8d, 0x01, 0x32, 0x99, 0x11, 0x11,
			  0x57, 0x4d, 0x56, 0x73, 0x02, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
			  0x00, 0x88, 0x00, 0xae, 0x05, 0x07, 0x5a, 0x14, 0x00,
			  0x10, 0x00, 0x1e, 0x70, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
			  0x04, 0xff, 0x92, 0x28, 0x00, 0xa4, 0x00, 0x00, 0x0a,
			  0x00, 0x02, 0x04, 0x00, 0x25, 0x05, 0x0c, 0x0e, 0x43,
			  0x01, 0x00, 0x00, 0x06, 0xaf, 0x88, 0x90, 0x48, 0x00,
			  0xaa, 0x00, 0x00, 0x05, 0x00, 0x02, 0x04, 0x00, 0x2c,
			  0x02, 0x04, 0x08, 0x00, 0x00, 0x02, 0xaf, 0x12, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcc, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3,
			  0x10, 0x00, 0x01, 0x01, 0x00, 0x00, 0x30, 0x30, 0x32,
			  0x10, 0x04, 0x00, 0x04, 0x32, 0x10, 0x02, 0x00, 0x02,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x02, 0x05, 0x05,
			  0x03, 0x00, 0x00, 0x00, 0x05, 0x40, 0x00, 0x00, 0x00,
			  0x05, 0x27, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd5,
			  0x18, 0x18, 0x03, 0x02, 0x01, 0x00, 0x64, 0x64, 0x18,
			  0x18, 0x19, 0x19, 0x21, 0x20, 0x18, 0x18, 0x18, 0x18,
			  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x31,
			  0x31, 0x30, 0x30, 0x2f, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6,
			  0x58, 0x58, 0x00, 0x01, 0x02, 0x03, 0x24, 0x24, 0x19,
			  0x19, 0x18, 0x18, 0x20, 0x21, 0x58, 0x58, 0x58, 0x58,
			  0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x58, 0x31,
			  0x31, 0x30, 0x30, 0x2f, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
			  0xff, 0xbf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x00, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0,
			  0x01, 0x19, 0x24, 0x1e, 0x44, 0x4c, 0x5a, 0x55, 0x5d,
			  0x66, 0x6f, 0x75, 0x7a, 0x81, 0x88, 0x8c, 0x90, 0x98,
			  0x9a, 0xa1, 0x95, 0xa1, 0xa5, 0x56, 0x52, 0x5f, 0x6d,
			  0x01, 0x19, 0x24, 0x1e, 0x44, 0x4c, 0x5a, 0x55, 0x5d,
			  0x66, 0x6f, 0x75, 0x7a, 0x81, 0x88, 0x8c, 0x90, 0x98,
			  0x9a, 0xa1, 0x95, 0xa1, 0xa5, 0x56, 0x52, 0x5f, 0x6d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
			  0x01, 0x00, 0x07, 0x0e, 0x15, 0x1d, 0x24, 0x2b, 0x33,
			  0x3a, 0x42, 0x4a, 0x52, 0x59, 0x62, 0x69, 0x71, 0x79,
			  0x83, 0x8a, 0x92, 0x9b, 0xa2, 0xab, 0xb4, 0xbc, 0xc4,
			  0xcc, 0xd5, 0xdc, 0xe4, 0xeb, 0xf3, 0xfc, 0x1b, 0x2d,
			  0x9d, 0xc4, 0x4b, 0xfc, 0x08, 0xae, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
			  0x00, 0x07, 0x0e, 0x16, 0x1d, 0x25, 0x2c, 0x33, 0x3b,
			  0x42, 0x4b, 0x52, 0x5a, 0x63, 0x6b, 0x73, 0x7b, 0x84,
			  0x8c, 0x95, 0x9d, 0xa5, 0xac, 0xb5, 0xbd, 0xc5, 0xce,
			  0xd6, 0xdd, 0xe5, 0xed, 0xf5, 0xfd, 0x2c, 0x4b, 0x3f,
			  0xe0, 0xe8, 0x4c, 0x20, 0xe9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
			  0x00, 0x07, 0x0f, 0x16, 0x1e, 0x26, 0x2e, 0x35, 0x3d,
			  0x45, 0x4e, 0x56, 0x5e, 0x66, 0x6e, 0x77, 0x80, 0x88,
			  0x91, 0x9a, 0xa2, 0xaa, 0xb2, 0xba, 0xc3, 0xcc, 0xd3,
			  0xdc, 0xe3, 0xeb, 0xf3, 0xfa, 0xff, 0x22, 0x22, 0x74,
			  0x78, 0x20, 0x5f, 0x4d, 0x97, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x85, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x88);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x00);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x01, 0xc1);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6,
			  0x00, 0x00, 0x00, 0x05, 0x05, 0x1c, 0x18, 0x1c, 0x20,
			  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 20);

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	return dsi_ctx.accum_err;
}

static int hx8399c_tcl_off(struct hx8399c_tcl *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = dsi };

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0xff, 0x83, 0x99);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x00);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 48);

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x00);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	return dsi_ctx.accum_err;
}

static int hx8399c_tcl_prepare(struct drm_panel *panel)
{
	struct hx8399c_tcl *ctx = to_hx8399c_tcl(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	hx8399c_tcl_reset(ctx);

	ret = hx8399c_tcl_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int hx8399c_tcl_unprepare(struct drm_panel *panel)
{
	struct hx8399c_tcl *ctx = to_hx8399c_tcl(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = hx8399c_tcl_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode hx8399c_tcl_mode = {
	.clock = (1080 + 27 + 35 + 35) * (1920 + 10 + 4 + 4) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 27,
	.hsync_end = 1080 + 27 + 35,
	.htotal = 1080 + 27 + 35 + 35,
	.vdisplay = 1920,
	.vsync_start = 1920 + 10,
	.vsync_end = 1920 + 10 + 4,
	.vtotal = 1920 + 10 + 4 + 4,
	.width_mm = 68,
	.height_mm = 121,
};

static int hx8399c_tcl_get_modes(struct drm_panel *panel,
				 struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &hx8399c_tcl_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs hx8399c_tcl_panel_funcs = {
	.prepare = hx8399c_tcl_prepare,
	.unprepare = hx8399c_tcl_unprepare,
	.get_modes = hx8399c_tcl_get_modes,
};

static int hx8399c_tcl_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct hx8399c_tcl *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supplies[0].supply = "vsp";
	ctx->supplies[1].supply = "vsn";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return dev_err_probe(dev, ret, "Failed to get regulators\n");

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &hx8399c_tcl_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		return ret;
	}

	return 0;
}

static void hx8399c_tcl_remove(struct mipi_dsi_device *dsi)
{
	struct hx8399c_tcl *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id hx8399c_tcl_of_match[] = {
	{ .compatible = "meizu,m1721-hx8399c-tcl" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, hx8399c_tcl_of_match);

static struct mipi_dsi_driver hx8399c_tcl_driver = {
	.probe = hx8399c_tcl_probe,
	.remove = hx8399c_tcl_remove,
	.driver = {
		.name = "panel-hx8399c-tcl",
		.of_match_table = hx8399c_tcl_of_match,
	},
};
module_mipi_dsi_driver(hx8399c_tcl_driver);

MODULE_AUTHOR("Generated with lmdpg from Meizu M6 Note vendor DT");
MODULE_DESCRIPTION("DRM driver for hx8399c tcl 1080p video mode dsi panel");
MODULE_LICENSE("GPL v2");
