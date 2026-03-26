#ifndef CONFIG_H
#define CONFIG_H

/* --- CẤU HÌNH SERIAL (UART) --- */
#define DEBUG_BAUDRATE      9600  
#define STM32_BAUDRATE      9600    
#define STM32_RX_PIN        1      
#define STM32_TX_PIN        3      

/* --- CẤU HÌNH WIFI (ACCESS POINT) --- */
#define AP_SSID             "ESP8266_Config_Portal"
#define AP_PASSWORD         "12345678"
#define WEB_SERVER_PORT     80

/* --- CẤU HÌNH MQTT ADAFRUIT IO --- */
#define MQTT_SERVER         "io.adafruit.com"
#define MQTT_PORT           1883
#define MQTT_USER           "USERNAME" 
#define MQTT_KEY            "KEY"      
/* Định dạng feed trên Adafruit: username/feeds/ten-feed */
#define MQTT_FEED_TEMP      "USERNAME/feeds/iot.temp-feed"
#define MQTT_FEED_HUMID     "USERNAME/feeds/iot.humid-feed"

/* --- CẤU HÌNH ĐIỀU KHIỂN (LED/GPIO) --- */
#define LED1_PIN            2       
#define LED2_PIN            5       

/* --- THỜI GIAN CẬP NHẬT (MS) --- */
#define SENSOR_READ_INTERVAL  10000   
#define MQTT_PUBLISH_INTERVAL 10000  /* Gửi lên Adafruit mỗi 30 giây */

#endif
