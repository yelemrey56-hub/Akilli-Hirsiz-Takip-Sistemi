#include <Keypad.h>
#include <LiquidCrystal.h>

// LCD Pinleri: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ultrasonik Mesafe Sensörü (HC-SR04)
const int trigPin = 9;
const int echoPin = 10;

// IR Alıcı ve Motor/Fan Alarm Çıkışı
const int irPin = A0;
const int alarmMotorPin = 13;

// Keypad Ayarları
const byte SATIR = 4;
const byte SUTUN = 4;
char tuslar[SATIR][SUTUN] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte satirPinleri[SATIR] = {A1, A2, A3, A4};
byte sutunPinleri[SUTUN] = {6, 7, 8, A5};

Keypad keypad = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

String dogruSifre = "1234";
String girilenSifre = "";
bool sistemAktif = true;
bool alarmCalisiyor = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(alarmMotorPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Sistem Aktif");
  lcd.setCursor(0, 1);
  lcd.print("Sifre: ");
}

long mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long sure = pulseIn(echoPin, HIGH);
  return sure * 0.034 / 2;
}

void loop() {
  char tus = keypad.getKey();

  if (tus) {
    if (tus == '#') {
      if (girilenSifre == dogruSifre) {
        sistemAktif = !sistemAktif;
        alarmCalisiyor = false;
        digitalWrite(alarmMotorPin, LOW);
        lcd.clear();
        lcd.print(sistemAktif ? "Sistem Aktif" : "Sistem Devre Disi");
      } else {
        lcd.clear();
        lcd.print("Hatali Sifre!");
        delay(1000);
      }
      girilenSifre = "";
      lcd.setCursor(0, 1);
      lcd.print("Sifre:          ");
      lcd.setCursor(7, 1);
    } else if (tus == '*') {
      girilenSifre = "";
      lcd.setCursor(7, 1);
      lcd.print("         ");
      lcd.setCursor(7, 1);
    } else {
      girilenSifre += tus;
      lcd.print("*");
    }
  }

  if (sistemAktif && !alarmCalisiyor) {
    long mesafe = mesafeOlc();
    int irDurum = digitalRead(irPin);

    if ((mesafe > 0 && mesafe < 30) || irDurum == LOW) {
      alarmCalisiyor = true;
      digitalWrite(alarmMotorPin, HIGH);
      lcd.clear();
      lcd.print("IHLAL TESPITI!");
      lcd.setCursor(0, 1);
      lcd.print("Sifre Giriniz:");
    }
  }
}
