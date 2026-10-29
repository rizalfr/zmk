# Arble V2

Native Zephyr 4.1 board definition for the nRF52840 Arble V2, with the existing
66-key Alice split-backspace layout and 22-LED RGB strip.

Build from the workspace root:

```powershell
. ./tools/activate-native.ps1
west build -s app -b arble_v2 -d build/arble_v2-studio -S studio-rpc-usb-uart
```

Firmware: `build/arble_v2-studio/zephyr/zmk.uf2`.

- Studio is always unlocked. The build snippet enables USB Studio transport and
  retains behaviors for remapping; BLE Studio support is also enabled.
- The bootloader behavior uses the retained Adafruit UF2 boot-mode request.
  Hold the rightmost layer key (layer 2) and press Tab to enter the bootloader.
- On battery, automatic deep sleep starts after 15 minutes of inactivity.
  The physical G switch wakes the board, matching Rable65's wake policy.
- For manual power-off, hold layer 1 and Backspace for more than two seconds,
  then release Backspace. Press physical G to wake.
- BLE transmit power is +8 dBm. DCDC regulation is enabled.
- Hold bottom-row MO(1) and H/J/K/L to move the mouse left/down/up/right.
  N/M press the left/right mouse buttons on the same layer.
  The space keys' layer-1 hold actions also access these bindings.
- RGB data uses P0.09 with NFC disabled on that pin. RGB remains enabled with
  the existing brightness and effect defaults.

Wake, RGB, and bootloader-drive behavior require verification on the keyboard.
