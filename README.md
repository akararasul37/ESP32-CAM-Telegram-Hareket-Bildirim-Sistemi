# 🛡️ ESP32-CAM & Telegram Akıllı Güvenlik Sistemi

**Işık Üniversitesi - Nesnelerin İnterneti (IoT) Dersi Final Projesi**

Bu proje, hareket algıladığında sesli uyarı veren ve anlık fotoğraf çekerek Telegram üzerinden kullanıcıya bildirim gönderen düşük maliyetli bir güvenlik kamerası prototipidir. Özellikle **RHYX M21-45 (GC2145)** kamera sensörü ve **ESP32 Core 3.x** güncel sürümleriyle uyumlu çalışacak şekilde optimize edilmiştir.


## ✨ Öne Çıkan Özellikler
- **Çift WiFi Tanımlama:** Ev ve okul/hotspot ağları arasında otomatik geçiş.
- **RGB565 to JPEG:** RHYX sensörler için özel yazılımsal görüntü dönüştürücü.
- **Aktif Alarm:** Hareket anında 1.5 saniyelik Buzzer uyarısı.
- **SSL Güvenliği:** Telegram API ile şifreli güvenli iletişim.

## 🛠 Donanım Listesi
- ESP32-CAM (AI-Thinker)
- RHYX M21-45 (GC2145) Kamera Sensörü
- PIR Hareket Sensörü (HC-SR501)
- Aktif Buzzer
- 7.4V Pil Seti + Voltaj Düşürücü (5V)

## 🔧 Devre Bağlantıları
| Bileşen | ESP32-CAM Pin |
| :--- | :--- |
| **PIR Sensör OUT** | GPIO 13 |
| **Buzzer (+)** | GPIO 14 |
| **GND / VCC** | GND / 5V |

## 🚀 Kurulum
1. Arduino IDE'de `ESP32` kart desteğinin yüklü olduğundan emin olun.
2. Kod içerisindeki `ssid`, `password`, `token` ve `chat_id` alanlarını kendi bilgilerinizle doldurun.
3. Kart modelini **AI Thinker ESP32-CAM** olarak seçip yüklemeyi tamamlayın.

