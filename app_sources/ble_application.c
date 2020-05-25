
#include <ble_application.h>

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0x0d, 0x18, 0x0f, 0x18, 0x0a, 0x18),
};

static struct bt_conn *ble_connection = NULL;
static ble_ready_callback ready_callback = NULL;
static struct bt_conn_cb conn_callbacks;
static ble_status status = kBleDisconnected;

static uint32_t ble_start_advertise(void)  {
	return (bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad),NULL, 0));
}

static void ble_connected(struct bt_conn *conn, u8_t err) {
    if (err) {
        printk(" BLE connection failed (err %u)\n",err);
    } else {
        ble_connection = bt_conn_ref(conn);
        status = kBleConnected;
        printk(" BLE connected! \n");
    }
}

static void ble_disconnected(struct bt_conn *conn, u8_t reason) {
	printk(" BLE disconnected, reason: %u \n", reason);
	if (ble_connection) {
		bt_conn_unref(ble_connection);
		ble_connection = NULL;
	}
    status = kBleDisconnected;
    ble_start_advertise();
    printk(" ble re-started to advertise ! \n");
}

static void ble_stack_ready(int err) {
    (void)err;
    if(ready_callback) {
        ready_callback(ble_connection);
    }

    //Stack initialized, so start advertisement:
    ble_start_advertise();
    printk(" ble started to advertise ! \n");
}

uint32_t ble_application_start(ble_ready_callback callback) {
    if(!callback) 
        return (-1);

    conn_callbacks.connected = ble_connected;
    conn_callbacks.disconnected = ble_disconnected;
    ready_callback = callback;
    
	bt_conn_cb_register(&conn_callbacks);
    return((uint32_t)bt_enable(ble_stack_ready));
}

struct bt_conn *ble_get_connection_ref() {
	return ble_connection;
}