# SPDX-License-Identifier: MIT

if(CONFIG_PMW3610)
    zephyr_library()
    zephyr_library_sources(pmw3610.c)
    zephyr_library_include_directories(.)
    zephyr_library_include_directories(../../../include)
endif()
