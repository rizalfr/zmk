---
title: Studio Setup
---

:::warning[Alpha Feature]

ZMK Studio support is in alpha. Although best efforts are being made, backwards compatibility during active development is not guaranteed.

:::

This guide will walk you through enabling ZMK Studio support for a keyboard.

The main additional pieces needed for Studio support involve additional metadata needed in order
to properly to display the physical layouts available for the particular keyboard.

# Physical Layout Positions

Physical layouts are described as part of the [new shield guide](./new-shield.mdx#physical-layouts) with the exception of the `keys` property that is required for Studio support. This is used to describe the physical attributes of each key position present in that layout and its items are listed in the same order as keymap bindings, matrix transforms, etc. The properties available are:

- Width
- Height
- X
- Y
- Rotation
- Rotation X
- Rotation Y

All X/Y/Width/Height values are in "key unit" units, with a 100th of a key unit resolution. Rotations are in degrees, with a 100th of a degree resolution. Due to the nature of devicetree, all values are stored in the devicetree without decimals as hundredths of a value, e.g. one key unit is represented as `100`, twenty degrees is represented as `2000`, etc.

Width/Height values should be positive and X/Y should be nonnegative.
If the Rotation value is non-zero, the key will be rotated by that angle around the coordinates specified by Rotation X/Y values, after it is translated to X/Y coordinates. Rotation is clockwise for positive values and counterclockwise otherwise.

:::note
You can specify negative values in devicetree using parentheses around it, e.g. `(-3000)` for a 30 degree counterclockwise rotation.
:::

Here is an example physical layout for a 2x2 macropad:

```
    macropad_physical_layout: macropad_physical_layout {
        compatible = "zmk,physical-layout";
        display-name = "Macro Pad";

        keys  //                     w   h    x    y     rot    rx    ry
            = <&key_physical_attrs 100 100    0    0       0     0     0>
            , <&key_physical_attrs 100 100  100    0       0     0     0>
            , <&key_physical_attrs 100 100    0  100       0     0     0>
            , <&key_physical_attrs 100 100  100  100       0     0     0>
            ;
    };
```

# Position Map

When switching between layouts with ZMK Studio, the keymap of the previously selected layout is used to populate the keymap in the new layout. To determine which keymap entry maps to which entry in the new layout, keys between the two layouts that share the exact same physical attributes are matched.

However, keys between layouts might not be in exactly the same positions, in which case a position map can be used. The position map includes a sequence for every relevant layout, and the corresponding entries in `positions` property will be used to determine the mapping between layouts.

For example, the following position map correctly maps the 5-column and 6-column Corne keymap layouts.

```dts
    foostan_corne_position_map {
        compatible = "zmk,physical-layout-position-map";

        complete;

        twelve {
            physical-layout = <&foostan_corne_6col_layout>;
            positions
                = < 1  2  3  4  5  6  7  8  9 10>
                , <13 14 15 16 17 18 19 20 21 22>
                , <25 26 27 28 29 30 31 32 33 34>
                , <      36 37 38 39 40 41      >;
        };

        ten {
            physical-layout = <&foostan_corne_5col_layout>;
            positions
                = < 0  1  2  3  4  5  6  7  8  9>
                , <10 11 12 13 14 15 16 17 18 19>
                , <20 21 22 23 24 25 26 27 28 29>
                , <      30 31 32 33 34 35      >;
        };
    };
```

The first entries in the two mappings have values `1` and `0` respectively, which means that the zero-th entry in the 5-column will map to the first entry in the 6-column layout, the second entries show that the second 6-column keymap entry corresponds to the first 5-column entry, etc.
