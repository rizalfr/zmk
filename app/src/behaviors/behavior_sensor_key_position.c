/*
 * Copyright (c) 2026 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_sensor_key_position

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zmk/behavior.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/virtual_key_position.h>

struct sensor_key_position_config {
    uint32_t position;
};

static int emit_position(struct zmk_behavior_binding *binding,
                         struct zmk_behavior_binding_event event, bool pressed) {
    // Only accept sensor-originated events, preventing recursive keymap assignments.
    if (event.position < ZMK_VIRTUAL_KEY_POSITION_SENSOR(0) ||
        event.position >= ZMK_VIRTUAL_KEY_POSITION_SENSOR(ZMK_KEYMAP_SENSORS_LEN)) {
        return -ENOTSUP;
    }

    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct sensor_key_position_config *cfg = dev->config;
    return raise_zmk_position_state_changed((struct zmk_position_state_changed){
        .source = ZMK_POSITION_STATE_CHANGE_SOURCE_LOCAL,
        .position = cfg->position,
        .state = pressed,
        .timestamp = event.timestamp,
    });
}

static int pressed(struct zmk_behavior_binding *binding, struct zmk_behavior_binding_event event) {
    return emit_position(binding, event, true);
}

static int released(struct zmk_behavior_binding *binding, struct zmk_behavior_binding_event event) {
    return emit_position(binding, event, false);
}

static const struct behavior_driver_api driver_api = {
    .binding_pressed = pressed,
    .binding_released = released,
};

#define SENSOR_KEY_POSITION_INST(n)                                                                \
    BUILD_ASSERT(DT_INST_PROP(n, position) < ZMK_KEYMAP_LEN, "Invalid encoder key position");         \
    static const struct sensor_key_position_config config_##n = {                                   \
        .position = DT_INST_PROP(n, position),                                                      \
    };                                                                                             \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, &config_##n, POST_KERNEL,                            \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &driver_api);

DT_INST_FOREACH_STATUS_OKAY(SENSOR_KEY_POSITION_INST)
