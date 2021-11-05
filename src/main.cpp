#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 2
#define SS_PIN 8

#define lockPin 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

void printByteArray(byte *, byte);
bool UIDisEqual(MFRC522::Uid, MFRC522::Uid);

MFRC522::Uid card = {0x4, {0x2A, 0xB1, 0xF7, 0x56}, 0x8};

Servo lock;
bool lockState = false;

void setup() {
  // put your setup code here, to run once:
  //card.size = 0x4;
  //card.sak = 0x8;
  //card.uidByte = {0x2A, 0xB1, 0xF7, 0x56};
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("Ready to read info");
  lock.attach(lockPin);
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
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  printByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("PIcc_Type : ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  Serial.print("SAK : ");
  Serial.println(mfrc522.uid.sak, HEX);
  Serial.print("size : ");
  Serial.println(mfrc522.uid.size, HEX);

  Serial.println(UIDisEqual(mfrc522.uid, card) ? "Match" : "No match");


}

void printByteArray(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}

bool UIDisEqual(MFRC522::Uid uid1, MFRC522::Uid uid2)  {


  if (uid1.sak != uid2.sak || uid1.size != uid2.size) {
    return false;
  }

  bool result = true;
  for (byte i = 0; i < uid1.size; i++) {
    if (uid1.uidByte[i] != uid2.uidByte[i]) {
      result = false;
    }
  }
  
  return result;
}

void toggle() {
  if (lockState) {
    lock.write(0);
  } else {
    lock.write(90);
  }
  lockState = !lockState;
}