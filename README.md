# Akıllı Hırsız Takip Sistemi (Gömülü Sistem Tasarımı)

Arduino mikrodenetleyici tabanlı, çoklu sensör doğrulaması ve şifreli kontrol mekanizmasına sahip gerçek zamanlı güvenlik ve alarm sistemidir.

### ⚙️ Donanım Bileşenleri
- **Mikrodenetleyici:** Arduino Uno
- **Mesafe Algılama:** HC-SR04 Ultrasonik Mesafe Sensörü
- **Hareket/Kızılötesi Algılama:** IR Alıcı Modülü
- **Kullanıcı Arayüzü:** 4x4 Tuş Takımı (Keypad) ve 16x2 Karakter LCD Ekran
- **Uyarı Mekanizması:** DC Motor / Fan Alarm Modülü

### 🔄 Çalışma Mantığı
1. Sistem aktif moddayken ultrasonik sensör ve IR alıcı sürekli olarak ortam taraması yapar.
2. Belirlenen eşik mesafenin altına inildiğinde veya IR sinyali kesildiğinde ihlal algılanır ve motor/fan alarmı devreye girer.
3. Yetkili kullanıcı 4x4 tuş takımı üzerinden doğru şifreyi (`#` ile onaylayarak) girdiğinde alarm durdurulur ve sistem durumu LCD ekranda güncellenir.
