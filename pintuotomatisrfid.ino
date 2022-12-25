#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MFRC522.h>
 LiquidCrystal_I2C lcd(0x27, 16, 2);
 MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
 Servo myservo;
 int angle=0;
 int Led = 2;
 int buzzer = 3;
 String tagUID = "05 8F 28 83 B8 61 00"; // String to store UID of tag. Change it with your tag's UID
 
 void setup() {
 myservo.attach(6);
 lcd.begin(16,2); // LCD screen
 lcd.backlight();
 SPI.begin(); // Init SPI bus
 mfrc522.PCD_Init(); // Init MFRC522
 pinMode(Led, OUTPUT);
 pinMode(buzzer, OUTPUT);
 lcd.clear();
 }
 void loop() {
 lcd.setCursor(0, 0);
 lcd.print("PINTU KUNCI RFID");
 delay(1000);
 lcd.setCursor(0, 1);
 lcd.print("Tunjukkan Kartu");
 
 // Look for new cards
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
 return;
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
 return;
 }
 
 //Reading from the card
 String tag = "";
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
 tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
 tag.concat(String(mfrc522.uid.uidByte[i], HEX));
 }
 tag.toUpperCase();
 
 //Checking the card
 if (tag.substring(1) == tagUID) //change here the UID of the card/cards that you want to give access
 {
 // If UID of tag is matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Akses DITERIMA");
 lcd.setCursor(0, 1);
 lcd.print("Pintu TERBUKA");
 myservo.write(90);
 digitalWrite(Led, HIGH);
 delay(2000);
 digitalWrite(Led, LOW);
 myservo.write(0);
 lcd.clear();
 }
 
 else
 {
 // If UID of tag is not matched.
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Kartu Anda Salah!");
 lcd.setCursor(0, 1);
 lcd.print("Akses DITOLAK!");
 digitalWrite(buzzer, HIGH);
 delay(2000);
 digitalWrite(buzzer, LOW);
 lcd.clear();
 }
 }
