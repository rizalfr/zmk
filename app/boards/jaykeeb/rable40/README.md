# Rable40

Native board support for the nRF52840 Rable40 on this ZMK checkout with Zephyr
`4.1.0+zmk-fixes` and Zephyr SDK `0.17.0`.

The matrix wiring, battery divider, two EC11 encoder inputs, and bootloader flash
partitions come from [rizalfr/zmk, branch jaykeeb](https://github.com/rizalfr/zmk/tree/030af72434fe972cb44df5fddd20be846f757daf/app/boards/arm/rable40).
The five-layer, 41-key keymap and physical geometry come from
[rable40-remap](https://github.com/rizalfr/rable40-remap/tree/6f9ffab31695f57c475b00a7306f0f96dac681f0/config).

## Build

From the repository root in PowerShell:

```powershell
. .\tools\activate-native.ps1
west build -s app -b rable40 -d build/rable40-studio
```

The firmware is `build/rable40-studio/zephyr/zmk.uf2`. Studio, USB serial transport,
BLE transport, and keymap settings storage are enabled by the board defaults.
No additional Studio snippet is needed for this default build.

## Flash and connect

1. Enter the UF2 bootloader with the PCB reset button, or hold the base layer's
   rightmost third-row key (the modifier-layer key) and press the top-left key.
2. Copy `zmk.uf2` to the bootloader drive (`NRF52BOOT` on the original firmware).
3. Connect USB and open [ZMK Studio](https://zmk.studio/) in Chrome or Edge.
4. Hold that same modifier-layer key and press the physical `U` position to select
   USB output, then connect to the keyboard's USB serial port in Studio.

Studio locking is disabled, so it is always unlocked when connected.

If the older port only restarts when invoking `&bootloader`, double-tap the
physical RESET button with USB connected, then flash the updated UF2. This port
now uses the Zephyr retention boot-mode API and the nRF52840 UF2 magic mapper
(`0x57` in GPREGRET1) for software entry into the existing Adafruit bootloader.

BLE Studio transport is also enabled for clients that support it; select BLE
output using the modifier layer's physical `B` position when using BLE Studio.

Studio changes are saved in flash. After editing with Studio, use its **Restore
Stock Settings** action to apply later changes to the compiled `.keymap` file.
Bluetooth bonds are retained across restarts, rather than cleared on every boot
as in the original remap configuration.

## Hardware and layout notes

- The default Studio layout is **All bottom-row switches (12 matrix positions)**:
  48 electrical positions, including all 12 bottom-row circuits verified from
  the supplied Gerbers. The bottom row uses 1u boxes in column order as an
  electrical view; these boxes do not depict the installed keycap widths.
- **6.25u spacebar (5 bottom keys)** retains the original 41-key physical layout.
  Select either layout in Studio. Existing saved layout selections may need to
  be changed manually after flashing.
- The original 41 key bindings retain their indices and actions. Added circuits
  default to Alt, Ctrl, Space, Space, Space, GUI, and Ctrl on the base layer, with
  transparent bindings on the remaining layers. Previously saved Studio keymaps
  retain their saved assignments; use **Restore Stock Settings** if you want the
  updated stock defaults (this replaces saved keymap edits).
- Alternate footprints sharing a matrix circuit share one binding. They cannot
  be assigned independently. See [the verified bottom-row map](BOTTOM_ROW.md).
- Both encoder inputs retain the original four-pulse resolution. The source
  remap keymap assigns no encoder actions; this port preserves that behavior.
  Add `sensor-bindings` to the keymap to assign actions at build time. This
  checkout's Studio implementation does not support editing encoder bindings.
- Underglow and external power control are disabled. The original hardware
  definition supplies neither an RGB LED device nor an external-power GPIO.
- The firmware has been built and its UF2 structure checked on Windows. Physical
  key scanning, USB/BLE connections, and persistence still need a PCB test.

## Studio layout options

Choose the matching physical layout in Studio and save the selection. Switching
layouts retains assignments for the same electrical switch circuit, including
keys whose position or width changes. Keys absent from the selected assembly are
hidden, while their stored bindings remain available in layouts that expose them.

| Layout | Bottom-row keys | Total keys |
| --- | --- | --- |
| 6.25u spacebar | 5 | 41 |
| 6u spacebar (centered / off-center stem) | 5 | 41 |
| Split 2.75u + 3u | 8 | 44 |
| Split 2u + 3u | 9 | 45 |
| Split 2.75u + 2.25u | 9 | 45 |
| Split 2u + 2.25u | 10 | 46 |
| Split 3u + 3u | 8 | 44 |
| All bottom-row switches (electrical view) | 12 | 48 |

The split presets include non-overlapping outer modifier footprints. The 6u
preset represents the centered cap geometry; its centered and off-center stem
footprints share the same electrical circuit. The full electrical view is useful
for other supported assemblies and switch testing. The PCB back image is mirrored
relative to these layouts, so split-space sizes appear in the opposite order there.
