#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 2
#define SDA_PIN 10

MFRC522 mfrc522(SDA_PIN, RST_PIN);

void printByteArray(byte *, byte);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("Ready to read info");
}

void loop() {
  // put your main code here, to run repeatedly:

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  byte block;
  byte len;
  MFRC522::StatusCode status;

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  Serial.println("New Card Detected");
  Serial.println();
  printByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("PIcc_Type : ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
}

void printByteArray(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " ": " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}