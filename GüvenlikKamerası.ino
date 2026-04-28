/*
 * PROJE ADI: ESP32-CAM ile Telegram’a Görüntü Gönderen Güvenlik Kamerası
 * Hazırlayan: Ahmed Kararasul
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"

// --- AYARLAR (Lütfen Kendi Bilgilerinizi Girin) ---
const char* ssid1 = "WIFI_ADINIZ";   
const char* pass1 = "WIFI_SIFRENIZ";   

const char* ssid2 = "HOTSPOT_ADINIZ"; 
const char* pass2 = "HOTSPOT_SIFRENIZ";  

String token = "BOT_TOKEN_BURAYA";
String chat_id = "CHAT_ID_BURAYA";

// CAMERA_MODEL_AI_THINKER Pin Tanımlamaları
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

int gpioPIR = 13; 
int buzzerPin = 14;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  Serial.begin(115200);
  
  pinMode(gpioPIR, INPUT_PULLDOWN);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); 

  WiFi.mode(WIFI_STA);
  Serial.print("WiFi agina baglaniliyor...");
  WiFi.begin(ssid1, pass1);
  
  long int StartTime = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - StartTime) < 10000) { 
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nİkinci aga geciliyor...");
    WiFi.begin(ssid2, pass2);
    StartTime = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - StartTime) < 10000) { 
      delay(500);
      Serial.print(".");
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nBaglandi! IP: " + WiFi.localIP().toString());
  }

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000; 
  config.pixel_format = PIXFORMAT_RGB565; // RHYX Kamera İçin

  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 12;
    config.fb_count = 1; 
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Kamera hatasi: 0x%x\n", err);
    delay(1000);
    ESP.restart();
  }
  Serial.println("Kamera hazir!");
}

void loop() {
  if (digitalRead(gpioPIR) == HIGH) { 
    Serial.println("Hareket Algilandi!");
    digitalWrite(buzzerPin, HIGH);
    delay(1500);                    
    digitalWrite(buzzerPin, LOW);  
    
    alerts2Telegram(token, chat_id);
    delay(10000); // 10 saniye bekleme
  }
  delay(500);
}

String alerts2Telegram(String token, String chat_id) {
  const char* myDomain = "api.telegram.org";
  String getBody = "";
  camera_fb_t * fb = esp_camera_fb_get();  
  if(!fb) return "Kamera hatasi";

  uint8_t * jpg_buf = NULL;
  size_t jpg_buf_len = 0;
  bool jpeg_converted = frame2jpg(fb, 20, &jpg_buf, &jpg_buf_len);
  esp_camera_fb_return(fb); 

  if(!jpeg_converted) return "Donusturme hatasi";

  WiFiClientSecure client_tcp;
  client_tcp.setInsecure(); 

  if (client_tcp.connect(myDomain, 443)) {
    String head = "--India\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + chat_id + "\r\n--India\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--India--\r\n";
    uint32_t totalLen = jpg_buf_len + head.length() + tail.length();

    client_tcp.println("POST /bot" + token + "/sendPhoto HTTP/1.1");
    client_tcp.println("Host: " + String(myDomain));
    client_tcp.println("Content-Length: " + String(totalLen));
    client_tcp.println("Content-Type: multipart/form-data; boundary=India");
    client_tcp.println();
    client_tcp.print(head);
    client_tcp.write(jpg_buf, jpg_buf_len);
    client_tcp.print(tail);
    free(jpg_buf);
    client_tcp.stop();
    Serial.println("Telegram gonderildi!");
  }
  return "Tamamlandi";
}
