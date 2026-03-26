#include "mqtt_manager.h"
#include "config.h"
#include "comm.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

/* 
 * Hàm xử lý dữ liệu nhận được từ Cloud (Subscribe Callback).
 * Đây là nơi nhận "phản hồi" từ Cloud để xác nhận dữ liệu đã lên thành công.
 */
static void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.println("\n-------------------------");
    Serial.printf("[MQTT][RECEIVE] Topic: %s\n", topic);
    Serial.printf("[MQTT][FEEDBACK] Giá trị từ Cloud: %s\n", message.c_str());
    Serial.println("-------------------------");
}

/* 
 * Hàm chuyên biệt để đăng ký tất cả các Feed cần theo dõi.
 * Việc tách riêng giúp code dễ quản lý khi số lượng Feed tăng lên.
 */
static void subscribe_all_feeds() {
    Serial.println("[MQTT] Đang đăng ký các Feed (Subscribe)...");
    
    client.subscribe(MQTT_FEED_TEMP);
    client.subscribe(MQTT_FEED_HUMID);
    
    /* Bạn có thể thêm các feed điều khiển khác ở đây */
    // client.subscribe(MQTT_FEED_CMD);

    Serial.println("[MQTT] Hoàn tất đăng ký Subscribe.");
}

/* 
 * Hàm thực hiện kết nối lại với Broker Adafruit IO.
 */
static void reconnect() {
    static unsigned long last_reconnect_attempt = 0;
    if (millis() - last_reconnect_attempt > 5000) {
        last_reconnect_attempt = millis();
        Serial.print("[MQTT] Đang thử kết nối lại...");
        
        if (client.connect("ESP8266_Client", MQTT_USER, MQTT_KEY)) {
            Serial.println("Đã kết nối!");
            
            /* Sau khi kết nối thành công, gọi hàm Subscribe */
            subscribe_all_feeds();
        } else {
            Serial.printf("Lỗi! (rc=%d). Thử lại sau 5s.\n", client.state());
        }
    }
}

/* 
 * Khởi tạo MQTT client và cấu hình hàm Callback.
 */
void mqtt_init() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(mqtt_callback);
    Serial.println("[MQTT] Hệ thống MQTT đã sẵn sàng.");
}

/* 
 * Duy trì kết nối, xử lý vòng lặp và gửi dữ liệu định kỳ.
 */
void mqtt_update() {
    if (WiFi.status() != WL_CONNECTED) return;

    if (!client.connected()) {
        reconnect();
    } else {
        client.loop();

        static unsigned long last_publish = 0;
        if (millis() - last_publish > MQTT_PUBLISH_INTERVAL) {
            last_publish = millis();
            
            char payload[10];
            
            /* Gửi Nhiệt độ */
            dtostrf(current_temperature, 1, 0, payload);
            client.publish(MQTT_FEED_TEMP, payload);

            /* Gửi Độ ẩm */
            dtostrf(current_humidity, 1, 0, payload);
            client.publish(MQTT_FEED_HUMID, payload);
            
            Serial.println("[MQTT][PUBLISH] Đã gửi dữ liệu Nhiệt độ & Độ ẩm lên Cloud.");
        }
    }
}

/* 
 * Gửi một giá trị bất kỳ lên Cloud một cách tức thời.
 */
void mqtt_publish(const char* feed, float value) {
    if (client.connected()) {
        char payload[10];
        dtostrf(value, 1, 1, payload);
        client.publish(feed, payload);
    }
}
