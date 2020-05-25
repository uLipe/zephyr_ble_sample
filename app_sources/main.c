#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/types.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <kernel.h>
#include <ble_application.h>
#include <ble_uart_service.h>

static void on_ble_rx_data(const uint8_t *buffer, size_t len) {
    ble_uart_service_transmit(buffer, len);
}

static void on_ble_stack_ready(struct bt_conn *conn) {
    (void)conn;
    ble_uart_service_register(on_ble_rx_data);
}

void main (void) {
    ble_application_start(on_ble_stack_ready);
}