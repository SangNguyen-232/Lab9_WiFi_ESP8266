#include "comm.h"
#include "config.h"
#include <SoftwareSerial.h>

// Khởi tạo SoftwareSerial để nhận data từ STM32 [cite: 814, 828]
SoftwareSerial stmSerial(STM32_RX_PIN, STM32_TX_PIN); 

float current_temperature = 0.0; // Đổi sang float để nhận số thập phân
uint32_t current_light = 0;

/* * Khởi tạo giao tiếp Serial với máy tính và STM32.
 * Tốc độ Baudrate nên để 115200 để đồng bộ với STM32[cite: 698, 810].
 */
void comm_init() {
    Serial.begin(DEBUG_BAUDRATE);
    stmSerial.begin(STM32_BAUDRATE);
    Serial.println("[COMM] UART System Initialized. Waiting for !TEMP:LIGHT#");
}

/* * Xử lý dữ liệu nhận được từ STM32 theo định dạng mới: !TEMP:LIGHT#
 */
static void handle_uart_packet(String packet) {
    packet.trim();
    // Kiểm tra tiền tố '!' và hậu tố '#' [cite: 524, 532]
    if (!packet.startsWith("!") || !packet.endsWith("#")) return;

    // Tìm vị trí dấu phân cách ':' giữa Temperature và Light
    int colonIndex = packet.indexOf(':');
    if (colonIndex == -1) return;

    // Tách chuỗi: ! [TEMP] : [LIGHT] #
    // substring(bắt đầu, kết thúc) - lấy từ sau '!' đến trước ':'
    String tempStr = packet.substring(1, colonIndex); 
    // lấy từ sau ':' đến trước '#'
    String lightStr = packet.substring(colonIndex + 1, packet.length() - 1); 

    // Chuyển đổi dữ liệu sang kiểu số
    current_temperature = tempStr.toFloat();
    current_light = (uint32_t)lightStr.toInt();

    // In ra Debug console để kiểm tra
    Serial.print("[COMM] Data Received -> ");
    Serial.print("Nhiệt độ: "); Serial.print(current_temperature); Serial.print(" C | ");
    Serial.print("Ánh sáng: "); Serial.println(current_light);
}

/* * Đọc dữ liệu từ UART STM32 và tách các gói tin (packets).
 */
void comm_update() {
    // Đọc dữ liệu thực từ STM32 qua UART2 (PA2/PA3) [cite: 825, 826]
    while (stmSerial.available()) {
        String packet = stmSerial.readStringUntil('#');
        if (packet.length() > 0) {
            // readStringUntil bỏ mất ký tự '#' nên cần thêm lại để handle_uart_packet nhận diện
            handle_uart_packet(packet + "#"); 
        }
    }

    /* * Phần giả lập (Fake Data) - Chỉ chạy khi không nhận được data thực
     * Ope có thể xóa phần này nếu muốn chỉ dùng data từ STM32
     */
    static unsigned long last_fake = 0;
    if (millis() - last_fake > SENSOR_READ_INTERVAL) {
        last_fake = millis();
        // Nếu STM32 chưa gửi gì (current_temperature vẫn bằng 0), tạo số ngẫu nhiên để test Web
        if (current_temperature == 0) {
            current_temperature = random(2500, 3500) / 100.0;
            current_light = random(0, 4095);
            Serial.println("[COMM] Using Fake Data for testing...");
        }
    }
}