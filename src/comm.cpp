#include "comm.h"
#include "config.h"
#include <SoftwareSerial.h>

SoftwareSerial stmSerial(STM32_RX_PIN, STM32_TX_PIN); 

int current_temperature = 0;
int current_humidity = 0;

/* 
 * Khởi tạo giao tiếp Serial với máy tính và STM32.
 */
void comm_init() {
    Serial.begin(DEBUG_BAUDRATE);
    stmSerial.begin(STM32_BAUDRATE);
    Serial.println("[COMM] UART System Initialized.");
}

/* 
 * Xử lý dữ liệu nhận được từ STM32 theo format: !TAG:<val>#
 */
static void handle_uart_packet(String packet) {
    packet.trim();
    if (!packet.startsWith("!") || !packet.endsWith("#")) return;

    int colonIndex = packet.indexOf(':');
    if (colonIndex == -1) return;

    String tag = packet.substring(1, colonIndex); // Lấy "TEMP" hoặc "HUMID"
    String valStr = packet.substring(colonIndex + 1, packet.length() - 1); // Lấy giá trị
    int value = valStr.toInt();

    if (tag == "TEMP") {
        current_temperature = value;
        Serial.printf("[COMM] Cập nhật Nhiệt độ: %d C\n", value);
    } else if (tag == "HUMID" || tag == "HUM") {
        current_humidity = value;
        Serial.printf("[COMM] Cập nhật Độ ẩm: %d %%\n", value);
    }
}

/* 
 * Đọc dữ liệu từ UART STM32 và tách các packet.
 */
void comm_update() {
    while (stmSerial.available()) {
        /* Đọc cho đến dấu kết thúc '#' */
        String packet = stmSerial.readStringUntil('#');
        if (packet.length() > 0) {
            handle_uart_packet(packet + "#"); // Thêm lại '#' để hàm handle xử lý
        }
    }

    /* Giữ giả lập khi không có STM32 để bạn có thể test web/mqtt */
    static unsigned long last_fake = 0;
    if (millis() - last_fake > SENSOR_READ_INTERVAL) {
        last_fake = millis();
        if (current_temperature == 0) { // Chỉ giả lập nếu không nhận được dữ liệu thực
            current_temperature = random(25, 35);
            current_humidity = random(50, 70);
        }
    }
}
