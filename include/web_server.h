#ifndef WEB_SERVER_H
#define WEB_SERVER_H

/*
 * Cấu hình và khởi chạy dịch vụ Web Server.
 */
void web_server_init();

/*
 * Duy trì hoạt động của Web Server bằng cách xử lý các kết nối đến.
 */
void web_server_loop();

#endif
