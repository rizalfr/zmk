# Copyright (c) 2024 The ZMK Contributors
# SPDX-License-Identifier: MIT

zephyr_include_directories(.)

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_PMW3610 pmw3610.c)
zephyr_library_sources_ifndef(CONFIG_PMW3610 ${ZEPHYR_BASE}/misc/empty_file.c)
