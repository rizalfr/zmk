---
title: ZMK Studio
sidebar_label: Studio
---

:::warning[Alpha Feature]

ZMK Studio support is in alpha. Although best efforts are being made, keeping compatibility during active development is not guaranteed.

:::

ZMK Studio provides runtime update functionality to ZMK powered devices. Studio is still under active development, and is not yet ready for casual end user use.

## Building

Building for ZMK Studio involves two main additional items.

- Build with the `studio-rpc-usb-uart` snippet to enable the endpoint used for Studio communication over USB.
- Enable the `ZMK_STUDIO` Kconfig setting.

### GitHub Actions

First add a `studio-rpc-usb-uart` to the `snippet` property of your build configuration. For a split keyboard, you should do this _only_ for your central/left side, e.g.:

```
---
include:
  - board: nice_nano_v2
    shield: corne_left
    snippet: studio-rpc-usb-uart
  - board: nice_nano_v2
    shield: corne_right
```

Next, enable the `ZMK_STUDIO` Kconfig symbol, for example by adding the following line to your .conf file:

```
CONFIG_ZMK_STUDIO=y
```

### Local Build

When building locally, use the `-S` parameter to include the `studio-rpc-usb-uart` snippet. Instead of adding it to your config file, you can also append the `ZMK_STUDIO` Kconfig as an additional CMake argument, e.g.:

```bash
west build -d build/cl_studio -b nice_nano_v2 \
  -S studio-rpc-usb-uart -- -DSHIELD=corne_left -DCONFIG_ZMK_STUDIO=y
```

## Behaviors

Normally, ZMK will only build and include behaviors that are referenced by your keymap and unused behavior will be skipped. However, Studio builds using the `studio-rpc-usb-uart` snippet will automatically define the `ZMK_BEHAVIORS_KEEP_ALL` value, which changes the approach and builds all possible behaviors into the firmware. This lets those behaviors be used in Studio.

A few controls are available to override this behavior for fine-grained control of what behaviors are built. Behaviors can be kept or omitted by defining certain values in the top of your keymap file before the standard `behaviors.dtsi` file is included.

### Omit Specific Behaviors

You can omit a specific behaviors by defining a variable like `ZMK_BEHAVIORS_OMIT_FOO` at the top of your keymap:

```dts
#define ZMK_BEHAVIORS_OMIT_KEY_TOGGLE

#include <behaviors.dtsi>
```

### Keep Only Selective Behaviors

To override the default "keep all" functionality, you can define the `ZMK_BEHAVIORS_KEEP_SELECTIVE` flag, and then keep only specific behaviors with a flag like `ZMK_BEHAVIORS_KEEP_FOO`, e.g.:

```dts
#define ZMK_BEHAVIORS_KEEP_SELECTIVE

#define ZMK_BEHAVIORS_KEEP_STICKY_KEY
#define ZMK_BEHAVIORS_KEEP_MOD_TAP

#include <behaviors.dtsi>
```

## Layers

By default, a build with ZMK Studio enabled will only allow as many layers as are defined in your standard keymap. To make additional layers available for use through Studio, you simply add new empty layers to your keymap with a status of `reserved`, e.g.:

```dts
/ {
    keymap {
        compatible = "zmk,keymap";

        base {
            display-name = "Base";
            bindings = // etc.
        };

        fn_layer {
            display-name = "Fn";
            bindings = // etc.
        };

        extra1 {
            status = "reserved";
        };

        extra2 {
            status = "reserved";
        };
    }
}
```

The reserved layers will be ignored during regular ZMK builds but will become available for ZMK Studio enabled builds.
