/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_mochi_node_box_display.h"
#include "esp_mochi_node.h"

/**
 * @brief Register the display-specific Mochi commands for the ESP-BOX-3.
 *
 * The helper adds the `display.show` and `display.status` commands.
 *
 * @param[in] node Mochi Node instance to extend.
 * @param[in] display Display state used by the command handlers.
 *
 * @return
 *      - `ESP_OK` on success
 *      - `ESP_ERR_INVALID_ARG` if `display` is `NULL`
 *      - an ESP-IDF error code if registration fails
 */
esp_err_t esp_mochi_node_box_register_display_node_commands(
    esp_mochi_node_handle_t node,
    esp_mochi_node_box_display_t *display);
