# Lab9: WiFi ESP8266 Enterprise Modular System

Dự án giám sát IoT chuyên nghiệp, tích hợp điều khiển thiết bị qua Web cục bộ và giám sát dữ liệu cảm biến từ xa qua Cloud (Adafruit IO). Hệ thống được thiết kế theo cấu trúc module hóa (Modular Design) và cơ chế Non-blocking hoàn toàn.

## 1. Cấu trúc Thư mục & Module
Hệ thống được chia thành các module độc lập để dễ dàng bảo trì và mở rộng:

- **`include/config.h`**: Tập trung toàn bộ cấu hình (WiFi, MQTT, Pins, Baudrate).
- **`include/index_html.h`**: Chứa toàn bộ giao diện Web Dashboard (HTML/CSS/JS).
- **`src/main.cpp`**: Bộ điều phối (Coordinator), khởi tạo và chạy vòng lặp của các module.
- **`src/mqtt_manager.cpp`**: Quản lý kết nối MQTT Adafruit IO, Publish dữ liệu định kỳ và Subscribe nhận phản hồi từ Cloud.
- **`src/comm.cpp`**: Xử lý giao tiếp UART với STM32 (D5/D6) theo giao thức chuẩn `!TAG:VALUE#`.
- **`src/wifi_manager.cpp`**: Quản lý đồng thời chế độ AP (Phát WiFi cấu hình) và STA (Kết nối Internet).
- **`src/web_server.cpp`**: Cung cấp Web UI cục bộ và các API điều khiển thiết bị.
- **`src/led.cpp`**: Quản lý trạng thái LED và hiệu ứng nháy Sin tự động.

## 2. Các tính năng cốt lõi

### 2.1. Giám sát & Điều khiển Đa nền tảng
- **Local Control:** Truy cập Dashboard qua IP `192.168.4.1` để điều khiển LED và xem sensor thời gian thực.
- **Cloud Monitoring:** Gửi dữ liệu Nhiệt độ/Độ ẩm lên Adafruit IO mỗi 30 giây.
- **Feedback Loop:** Tự động Subscribe các Feed trên Cloud để xác nhận dữ liệu đã lên thành công và đồng bộ hóa trạng thái.

### 2.2. Giao tiếp UART chuyên nghiệp (STM32)
- Sử dụng **SoftwareSerial** trên chân D5 (RX) và D6 (TX) để tránh xung đột với cổng nạp code.
- Định dạng dữ liệu: 
  - `!TEMP:25#` -> Cập nhật Nhiệt độ 25°C.
  - `!HUMID:65#` -> Cập nhật Độ ẩm 65%.

### 2.3. Hệ thống Logging (Debug)
- Toàn bộ hoạt động của hệ thống được in chi tiết ra cổng Serial (Baudrate: 115200).
- Các bản tin Log được gắn Tag phân loại: `[SYSTEM]`, `[WIFI]`, `[MQTT]`, `[COMM]`, `[HTTP]`.

## 3. Sơ đồ luồng dữ liệu
```text
[ STM32 Sensor ] --(!TAG:VAL#)--> [ COMM Module ] --(Global Var)--> [ Web UI (Local) ]
                                         |
                                         +---(Publish/30s)---> [ Adafruit IO Cloud ]
                                                                        |
                                         +---(Subscribe/Loopback)-------+
```

## 4. Hướng dẫn cấu hình & Sử dụng
1. **Cấu hình:** Mở file `include/config.h`, điền thông tin WiFi, `MQTT_USER` và `MQTT_KEY` từ tài khoản Adafruit IO của bạn.
2. **Nối dây:** 
   - ESP8266 D5 (RX) <-> STM32 TX.
   - ESP8266 D6 (TX) <-> STM32 RX.
   - Nối chung GND giữa 2 kit.
3. **Sử dụng:**
   - Kết nối vào WiFi phát ra từ ESP để vào trang cấu hình Web.
   - Mở Serial Monitor (115200) để xem log hệ thống.
   - Truy cập Adafruit IO Dashboard để giám sát biểu đồ nhiệt độ/độ ẩm từ xa.
