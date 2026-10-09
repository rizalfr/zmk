# Verified bottom-row electrical map

The supplied `3349224A_Y139/.../yg/GerberFiles` copper and soldermask files contain
19 bottom-row switch-center positions connected to 12 independent matrix
circuits. Copper connectivity was reconstructed separately for both layers,
including clear-polarity regions, then joined at shared plated pad/via locations.
Each switch was traced to a column and a diode; all 12 diodes share the same
bottom-row net. Column order matches the original board's top-row matrix order.

Coordinates below are Gerber millimeters, not screen pixels. All listed switch
centers have Y = 19.05 mm. Gerber X increases in the front image's direction;
the supplied back image is mirrored. The column GPIO assignments are preserved
from the original board definition.

| Matrix position | Column GPIO | Switch-center X choices (mm) | Stock binding index |
| --- | --- | --- | --- |
| R3 C0 | P0.10 | 21.4313 | 36 |
| R3 C1 | P1.09 | 42.8625 | 41 (new) |
| R3 C2 | P0.17 | 59.5313, 61.9125, 64.2938 | 37 |
| R3 C3 | P0.31 | 80.9625 | 42 (new) |
| R3 C4 | P0.30 | 102.3938, 109.5375 | 43 (new) |
| R3 C5 | P0.29 | 121.4438, 130.9688 | 38 |
| R3 C6 | P0.02 | 150.0188 | 44 (new) |
| R3 C7 | P1.13 | 159.5438 | 45 (new) |
| R3 C8 | P0.28 | 180.9750, 183.3563 | 46 (new) |
| R3 C9 | P0.03 | 202.4063, 204.7875 | 39 |
| R3 C10 | P1.10 | 223.8375 | 47 (new) |
| R3 C11 | P1.11 | 240.5063, 242.8875 | 40 |

The row GPIO is P0.24. R3 and column numbers above are zero-based.

The full Studio layout exposes every circuit once, with 1u boxes ordered C0 to
C11. This supports the alternate modifier and split-space footprints electrically
without pretending their overlapping physical positions can all be populated
simultaneously. Physical presets additionally represent the 6.25u and 6u spacebars,
and split 2.75u + 3u, 2u + 3u, 2.75u + 2.25u, 2u + 2.25u, and 3u + 3u assemblies.
Every split key's center is checked against the corresponding Gerber footprint;
key widths follow the PCB's silkscreen labels. Adjacent key boxes do not overlap.

Selecting any layout preserves binding indices through explicit position maps.
Original indices 0–40 are unchanged. Indices 41–47 provide extra modifier and space
bindings on the base layer and are transparent on the other layers.
Studio locking remains disabled.

Source file SHA-256 hashes:

```text
copper_top.gbr
C7FC7D140160DAF236C9CCF3E485897D933A0CDC9B808789A7C07758E6C37DDD
copper_bottom.gbr
D8E0FFB5DFC3D4F02477C30804D77E746CC6C4381F11F5137E118D5B6CB836BB
```

Electrical connectivity and the firmware build have been checked. Physical
switch operation on the assembled PCB still needs testing.
