// SPDX-License-Identifier: GPL-2.0-only
// Generated from the Meizu M6 Note (m1721) vendor DT:
//   dsi-panel-ili7807d-txdkj-1080p-video.dtsi
// Panel module: TXDKJ (Tongxingda), controller: Ilitek ILI7807D, 1080x1920 video mode.

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct ili7807d_txdkj {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator_bulk_data *supplies;
	struct gpio_desc *reset_gpio;
};

static const struct regulator_bulk_data ili7807d_txdkj_supplies[] = {
	{ .supply = "vsp" },
	{ .supply = "vsn" },
};

static inline struct ili7807d_txdkj *to_ili7807d_txdkj(struct drm_panel *panel)
{
	return container_of_const(panel, struct ili7807d_txdkj, panel);
}

static void ili7807d_txdkj_reset(struct ili7807d_txdkj *ctx)
{
	/*
	 * Vendor reset sequence <1 1 0 5 1 50>, with reset-gpios flagged
	 * GPIO_ACTIVE_LOW: physical HIGH 1 ms, LOW 5 ms, HIGH 50 ms.
	 * The panel must be left out of reset (physical HIGH) here, otherwise
	 * every init command below is ignored.
	 */
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 1100);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(5000, 5100);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(50000, 51000);
}

static int ili7807d_txdkj_on(struct ili7807d_txdkj *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x42, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x45, 0x19);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x46, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4a, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4b, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x50, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa2, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa3, 0x16);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x22, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x63, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x64, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6c, 0x45);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6d, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5a, 0x33);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x06);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x43);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x01, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x02, 0x43);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x03, 0x43);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x04, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x05, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x06, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x07, 0x0a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x08, 0x83);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x09, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0a, 0x30);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0b, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0c, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0d, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0f, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x11, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x12, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x13, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x14, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x15, 0x84);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x31, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x32, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x33, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x34, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x35, 0x13);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x37, 0x22);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x38, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x39, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3b, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3d, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3e, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3f, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x40, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x41, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x42, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x43, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x44, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x45, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x46, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x47, 0x22);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x48, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x49, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4b, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4d, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4e, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4f, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x50, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x61, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x62, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x63, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x64, 0x12);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x65, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x66, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x67, 0x22);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x68, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x69, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6b, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6d, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6e, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6f, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x70, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x71, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x72, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x73, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x74, 0x13);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x75, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x76, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x77, 0x22);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x78, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x79, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7b, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7d, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7e, 0x28);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x7f, 0x29);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x80, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd0, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd1, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd2, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd3, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd4, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd5, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd6, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd7, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd8, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xd9, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xda, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xdb, 0x47);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xdc, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xdd, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x96, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x97, 0x33);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa0, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa1, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa2, 0x08);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa3, 0x1e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa7, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa6, 0x32);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xa7, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xae, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe3, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xe5, 0x80);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb2, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xb3, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x01, 0x0f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x03, 0x31);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x05, 0x64);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x07, 0x8a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x08, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x09, 0xa7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0a, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0b, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0d, 0xd5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0f, 0xe7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x11, 0xf8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x12, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x13, 0x2d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x14, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x15, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x16, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x17, 0x8f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x18, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x19, 0xb9);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1a, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1b, 0xf6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1d, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1f, 0x27);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x20, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x21, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x22, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x23, 0x8c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x24, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x25, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x26, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x27, 0xe9);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x28, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x29, 0x0d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2b, 0x3b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2d, 0x49);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2f, 0x58);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x30, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x31, 0x69);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x32, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x33, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x34, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x35, 0x94);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x37, 0xb1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x38, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x39, 0xde);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3b, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3d, 0x0f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3f, 0x31);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x40, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x41, 0x64);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x42, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x43, 0x8a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x45, 0xa7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x46, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x47, 0xc0);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x48, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x49, 0xd5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4a, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4b, 0xe7);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4d, 0xf8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4e, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4f, 0x2d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x50, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x52, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x53, 0x8f);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x54, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x55, 0xb9);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x56, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x57, 0xf6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x58, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x59, 0x26);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5b, 0x27);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5d, 0x55);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5f, 0x8c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x60, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x61, 0xb3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x62, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x63, 0xe9);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x64, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x65, 0x0d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x66, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x67, 0x3b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x68, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x69, 0x49);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6b, 0x58);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6d, 0x69);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6f, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x70, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x71, 0x94);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x72, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x73, 0xb1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x74, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x75, 0xde);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x76, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x77, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x78, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x79, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x01, 0x21);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x03, 0x43);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x05, 0x75);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x07, 0x99);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x08, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x09, 0xb5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0a, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0b, 0xcd);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0d, 0xe1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0f, 0xf4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x10, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x11, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x12, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x13, 0x37);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x14, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x15, 0x5d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x16, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x17, 0x95);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x18, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x19, 0xbe);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1a, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1b, 0xfa);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1d, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1f, 0x2b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x20, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x21, 0x58);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x22, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x23, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x24, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x25, 0xb6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x26, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x27, 0xec);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x28, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x29, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2b, 0x3d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2d, 0x4b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2f, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x30, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x31, 0x6b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x32, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x33, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x34, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x35, 0x92);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x37, 0xac);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x38, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x39, 0xd2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3b, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3d, 0x21);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3f, 0x43);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x40, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x41, 0x75);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x42, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x43, 0x99);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x45, 0xb5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x46, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x47, 0xcd);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x48, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x49, 0xe1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4a, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4b, 0xf4);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4c, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4d, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4e, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4f, 0x37);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x50, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0x5d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x52, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x53, 0x95);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x54, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x55, 0xbe);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x56, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x57, 0xfa);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x58, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x59, 0x2a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5b, 0x2b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5d, 0x58);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5f, 0x90);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x60, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x61, 0xb6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x62, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x63, 0xec);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x64, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x65, 0x10);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x66, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x67, 0x3d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x68, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x69, 0x4b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6b, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6d, 0x6b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6f, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x70, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x71, 0x92);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x72, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x73, 0xac);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x74, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x75, 0xd2);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x76, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x77, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x78, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x79, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x04);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x01, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x03, 0x48);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x05, 0x85);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x07, 0xab);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x08, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x09, 0xc8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0a, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0b, 0xdf);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0d, 0xf3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0e, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x0f, 0x05);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x10, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x11, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x12, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x13, 0x44);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x14, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x15, 0x69);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x16, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x17, 0x9e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x18, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x19, 0xc5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1a, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1b, 0xfe);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1d, 0x2c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x1f, 0x2d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x20, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x21, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x22, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x23, 0x91);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x24, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x25, 0xb8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x26, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x27, 0xed);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x28, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x29, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2b, 0x3e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2d, 0x4b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x2f, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x30, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x31, 0x6b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x32, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x33, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x34, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x35, 0x93);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x37, 0xae);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x38, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x39, 0xd1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3b, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3c, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3d, 0x0c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3e, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x3f, 0x48);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x40, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x41, 0x85);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x42, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x43, 0xab);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x45, 0xc8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x46, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x47, 0xdf);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x48, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x49, 0xf3);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4a, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4b, 0x05);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4c, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4d, 0x14);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4e, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x4f, 0x44);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x50, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x51, 0x69);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x52, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x53, 0x9e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x54, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x55, 0xc5);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x56, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x57, 0xfe);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x58, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x59, 0x2c);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5a, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5b, 0x2d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5c, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5d, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5e, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x5f, 0x91);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x60, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x61, 0xb8);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x62, 0x02);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x63, 0xed);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x64, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x65, 0x11);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x66, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x67, 0x3e);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x68, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x69, 0x4b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6a, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6b, 0x5a);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6c, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6d, 0x6b);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6e, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x6f, 0x7d);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x70, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x71, 0x93);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x72, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x73, 0xae);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x74, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x75, 0xd1);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x76, 0x03);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x77, 0xe6);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x78, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x79, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x00);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x36, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0xc0);

	return dsi_ctx.accum_err;
}

static int ili7807d_txdkj_off(struct ili7807d_txdkj *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0xc0);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0xff, 0x78, 0x07, 0x01);
	mipi_dsi_generic_write_seq_multi(&dsi_ctx, 0x58, 0x01);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int ili7807d_txdkj_prepare(struct drm_panel *panel)
{
	struct ili7807d_txdkj *ctx = to_ili7807d_txdkj(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ili7807d_txdkj_supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	ili7807d_txdkj_reset(ctx);

	ret = ili7807d_txdkj_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ili7807d_txdkj_supplies), ctx->supplies);
		return ret;
	}

	return 0;
}

static int ili7807d_txdkj_unprepare(struct drm_panel *panel)
{
	struct ili7807d_txdkj *ctx = to_ili7807d_txdkj(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = ili7807d_txdkj_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ili7807d_txdkj_supplies), ctx->supplies);

	return 0;
}

static const struct drm_display_mode ili7807d_txdkj_mode = {
	.clock = (1080 + 80 + 28 + 88) * (1920 + 24 + 8 + 16) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 80,
	.hsync_end = 1080 + 80 + 28,
	.htotal = 1080 + 80 + 28 + 88,
	.vdisplay = 1920,
	.vsync_start = 1920 + 24,
	.vsync_end = 1920 + 24 + 8,
	.vtotal = 1920 + 24 + 8 + 16,
	.width_mm = 68,
	.height_mm = 121,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int ili7807d_txdkj_get_modes(struct drm_panel *panel,
				    struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &ili7807d_txdkj_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	drm_mode_probed_add(connector, mode);
	return 1;
}

static const struct drm_panel_funcs ili7807d_txdkj_panel_funcs = {
	.prepare = ili7807d_txdkj_prepare,
	.unprepare = ili7807d_txdkj_unprepare,
	.get_modes = ili7807d_txdkj_get_modes,
};

static int ili7807d_txdkj_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct ili7807d_txdkj *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct ili7807d_txdkj, panel,
				   &ili7807d_txdkj_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ret = devm_regulator_bulk_get_const(dev,
					    ARRAY_SIZE(ili7807d_txdkj_supplies),
					    ili7807d_txdkj_supplies,
					    &ctx->supplies);
	if (ret < 0)
		return ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void ili7807d_txdkj_remove(struct mipi_dsi_device *dsi)
{
	struct ili7807d_txdkj *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id ili7807d_txdkj_of_match[] = {
	{ .compatible = "meizu,m1721-ili7807d-txdkj" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, ili7807d_txdkj_of_match);

static struct mipi_dsi_driver ili7807d_txdkj_driver = {
	.probe = ili7807d_txdkj_probe,
	.remove = ili7807d_txdkj_remove,
	.driver = {
		.name = "panel-ili7807d-txdkj",
		.of_match_table = ili7807d_txdkj_of_match,
	},
};
module_mipi_dsi_driver(ili7807d_txdkj_driver);

MODULE_AUTHOR("Meizu m1721 mainline port");
MODULE_DESCRIPTION("DRM driver for TXDKJ ILI7807D 1080p video mode DSI panel");
MODULE_LICENSE("GPL");
