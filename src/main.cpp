#include <Arduino.h>
#include "led.h"
#include "web_server.h"
#include "wifi_manager.h"
#include "comm.h"
#include "mqtt_manager.h"

/* 
 * Khởi tạo toàn bộ các module của hệ thống.
 */
void setup() {
    comm_init();
    led_init();
    wifi_init();
    web_server_init();
    mqtt_init();
}

/* 
 * Chạy vòng lặp của các module. Lưu ý không sử dụng delay() ở đây.
 */
void loop() {
    comm_update();      
    wifi_update();
    web_server_loop();
    led_update();
    mqtt_update();      // Cập nhật kết nối và gửi dữ liệu lên Adafruit IO
}
