cmake_minimum_required(VERSION 3.13.11)
find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})

project(zephyr_ble_sample)

set(sources     "app_sources/main.c"
                "app_sources/ble_uart_service.c"
                "app_sources/ble_application.c")

target_sources(app PRIVATE ${sources})
target_include_directories(app PRIVATE app_sources)