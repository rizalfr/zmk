# REVIUNG5

Five-key macropad with an optional rotary encoder, ported from the
[QMK REVIUNG5 definition](https://github.com/rizalfr/qmk_firmware/tree/master/keyboards/reviung/reviung5).
Use a ZMK-supported Pro Micro-compatible controller; the original ATmega32U4
Pro Micro cannot run this firmware.

Like Corne, hardware is defined in `reviung5.dtsi`, included by the shield
overlay, with a separate physical layout under `app/dts/layouts/gtips/` and a
controller-specific RGB overlay under `boards/`. This is a single shield,
so it does not need left/right variants or split configuration.

## Wiring

| Function | QMK AVR pin | Pro Micro connector pin |
| --- | --- | --- |
| Row | F4 | 21 (A3) |
| Columns, left to right | D4, C6, D7, E6, B4 | 4, 5, 6, 7, 8 |
| Encoder A / B | D0 / D1 | 3 / 2 |
| Four WS2812 LEDs | D3 | 1 (TX) |

Diodes are COL2ROW. The nice!nano RGB overlay uses P0.06 for connector pin 1.
Encoder support is enabled by default. RGB is optional: uncomment
`CONFIG_ZMK_RGB_UNDERGLOW=y` in `reviung5.conf` when using the supplied
nice!nano overlay. Other controllers need their own RGB driver overlay.

## Keymap

The Base and Lower actions follow QMK, with extra Bluetooth controls:

| Layer | Key 1 | Key 2 | Key 3 | Key 4 | Key 5 |
| --- | --- | --- | --- | --- | --- |
| Base | Volume down / hold Lower | Previous track | Play/pause | Next track | Volume up |
| Lower | Transparent | Hue up | Next RGB effect | RGB toggle | Mute / hold Bluetooth |
| Bluetooth | Transparent | Toggle USB/BLE | Previous profile | Next profile | Transparent |

Hold key 1, then hold key 5 to reach Bluetooth. On that layer, press keys
2+3 together to clear the current Bluetooth profile, or keys 3+4 together
to unlock Studio (when built with Studio support). Two small virtual keys appear to the right of key 5 in Studio: the upper
key is counterclockwise (Page Up), and the lower key is clockwise (Page Down).
Select either virtual key in Studio and change its binding, then save. Lower
and Bluetooth inherit these bindings via transparent keys; they can also be
remapped independently per layer. The fifth physical key remains the encoder
push switch when an encoder is installed there. RGB actions require RGB underglow to be enabled.

## Build

From the repository root, for nice!nano v2:

```sh
west build -b nice_nano@2.0.0/nrf52840/zmk -d build/reviung5 app -- -DSHIELD=reviung5
```

For RGB and Studio over USB:

```sh
west build -b nice_nano@2.0.0/nrf52840/zmk -d build/reviung5-studio -S studio-rpc-usb-uart app -- -DSHIELD=reviung5 -DCONFIG_ZMK_STUDIO=y -DCONFIG_ZMK_RGB_UNDERGLOW=y
```

Flash `build/reviung5/zephyr/zmk.uf2` (or the Studio build's equivalent)
by copying it to the controller's UF2 bootloader drive.

## nRFMicro 1.3 with unlocked Studio

```sh
west build -b nrfmicro@1.3.0/nrf52840/zmk -d build/reviung5-nrfmicro_13-studio -S studio-rpc-usb-uart app -- -DSHIELD=reviung5 -DCONFIG_ZMK_STUDIO=y -DCONFIG_ZMK_STUDIO_LOCKING=n
```

The encoder uses a local `zmk,behavior-sensor-key-position` bridge, since this
version of Studio edits key positions rather than sensor bindings. Each encoder
detent queues a press/release at virtual key position 5 (CCW) or 6 (CW), using
the currently active keymap, including bindings saved by Studio. The two extra
matrix entries are virtual and do not require additional wiring. Keep the
`encoder_keys` sensor binding when customizing the keymap source.
