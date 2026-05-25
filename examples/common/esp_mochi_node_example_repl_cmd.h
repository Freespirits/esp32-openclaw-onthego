/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "esp_mochi_node.h"

/**
 * @brief Register the common REPL commands used by the examples.
 *
 * @param[in] node Mochi Node instance targeted by REPL actions.
 *
 * @return
 *      - `ESP_OK` on success
 *      - an ESP-IDF error code if registration fails
 */
esp_err_t esp_mochi_node_example_repl_register_commands(esp_mochi_node_handle_t node);
