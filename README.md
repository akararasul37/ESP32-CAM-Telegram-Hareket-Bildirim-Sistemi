# 🛡️ ESP32-CAM & Telegram Akıllı Güvenlik Sistemi

**Işık Üniversitesi - Nesnelerin İnterneti (IoT) Dersi Final Projesi**

Bu proje, hareket algıladığında sesli uyarı veren ve anlık fotoğraf çekerek Telegram üzerinden kullanıcıya bildirim gönderen düşük maliyetli bir güvenlik kamerası prototipidir.


## ✨ Öne Çıkan Özellikler
- **Çift WiFi Tanımlama:** Ev ve okul/hotspot ağları arasında otomatik geçiş.
- **RGB565 to JPEG:** RHYX sensörler için özel yazılımsal görüntü dönüştürücü.
- **Aktif Alarm:** Hareket anında 1.5 saniyelik Buzzer uyarısı.
- **SSL Güvenliği:** Telegram API ile şifreli güvenli iletişim.

## 🛠 Donanım Listesi
- ESP32-CAM (AI-Thinker)
<img width="600" height="338" alt="image" src="https://github.com/user-attachments/assets/da1cef1e-7568-40ec-9e0a-9cc097d11a4e" />

- ESP32-CAM programlayıcı Modül (FTDI)
<img width="447" height="447" alt="image" src="https://github.com/user-attachments/assets/7de4c351-3bcb-4db1-8b21-907e9a360b12" />
 
- PIR Hareket Sensörü (HC-SR501)
<img width="225" height="225" alt="image" src="https://github.com/user-attachments/assets/4c43b1f1-66b7-4f24-92cf-7ddb061a1341" />

- Aktif Buzzer
<img width="234" height="234" alt="image" src="https://github.com/user-attachments/assets/1090ab6e-a538-4deb-baa2-07152eff8903" />

- 7.4V Pil Seti + Voltaj Düşürücü (5V)
<img width="339" height="339" alt="image" src="https://github.com/user-attachments/assets/89caace9-d68a-48c1-bac9-17f8d48d2e7d" />


<img width="1000" height="1000" alt="image" src="https://github.com/user-attachments/assets/bf992263-82fa-493b-9981-78388fbb3ca6" />

- Breadboard ve Jumper Kablolar
<img width="375" height="375" alt="image" src="https://github.com/user-attachments/assets/5aa3d825-96f5-4af5-9dd2-fe362dfb640c" />


<img width="582" height="640" alt="image" src="https://github.com/user-attachments/assets/446b210b-3872-40f4-b06c-8dcb0c7d266e" />


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

## Görseller
<img width="1530" height="2040" alt="image" src="https://github.com/user-attachments/assets/13cc7790-2e41-4423-9b71-31a0ca2aaac4" />

--- 

<img width="1530" height="2040" alt="image" src="https://github.com/user-attachments/assets/c81dafc0-104e-4467-b2b8-a6b2f6c0156b" />

---

<img width="453" height="361" alt="image" src="https://github.com/user-attachments/assets/be46b87b-d531-432f-aab8-80b30a9838a3" />

## Telegram Bildirim Ekranı Görseli

<img width="460" height="1026" alt="image" src="https://github.com/user-attachments/assets/b6c4fa69-e72c-4b34-b647-f08febddd0b6" />






