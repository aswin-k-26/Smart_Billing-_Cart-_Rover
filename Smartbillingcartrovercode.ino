#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

// RFID setup
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// LCD setup (I2C address might be 0x27 or 0x3F based on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Motor and Buzzer setup
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 8
#define ENB 11
#define BUZZER_PIN 3
#define BUTTON_PIN 2

// RFID card UIDs
byte START_CARD[4] = {0x7A, 0xAC, 0xA9, 0xEE};  // Example start tag
byte STOP_CARD[4]  = {0xC3, 0x50, 0x13, 0x2D};  // Example stop tag

const byte products[][4] = {
  {0x73, 0x40, 0x28, 0x03},  // Product 1
  {0x73, 0xF6, 0x93, 0x28},  // Product 2
  {0x7E, 0x46, 0xD1, 0x89}   // Product 3
};

const char* productNames[] = {
  "Soap",
  "Shampoo",
  "Biscuits"
};

float productPrices[] = {
  20.0,
  65.5,
  30.0
};

float total = 0.0;
float scannedPrices[50];
uint8_t priceIndex = 0;
bool roverMoving = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready to Scan");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW && priceIndex > 0) {
    priceIndex--;
    total -= scannedPrices[priceIndex];
    buzz(2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Item Removed");
    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(total);
    delay(1500);
    lcd.clear();
    lcd.print("Ready to Scan");
    return;
  }

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  byte *readUID = rfid.uid.uidByte;

  if (compareUID(readUID, START_CARD)) {
    startRover();
  } else if (compareUID(readUID, STOP_CARD)) {
    stopRover();
  } else {
    int productIndex = getProductIndex(readUID);
    lcd.clear();
    if (productIndex != -1) {
      lcd.setCursor(0, 0);
      lcd.print(productNames[productIndex]);
      lcd.setCursor(0, 1);
      lcd.print("P:");
      lcd.print(productPrices[productIndex]);
      total += productPrices[productIndex];
      scannedPrices[priceIndex++] = productPrices[productIndex];
      lcd.print(" T:");
      lcd.print(total);
      buzz(1);
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Unknown Product");
    }
    delay(1500);
    lcd.clear();
    lcd.print("Ready to Scan");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

int getProductIndex(byte *uid) {
  for (int i = 0; i < 3; i++) {
    bool match = true;
    for (int j = 0; j < 4; j++) {
      if (products[i][j] != uid[j]) {
        match = false;
        break;
      }
    }
    if (match) return i;
  }
  return -1;
}

bool compareUID(byte *a, byte *b) {
  for (int i = 0; i < 4; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

void startRover() {
  if (!roverMoving) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
    roverMoving = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME TO STORE");
    buzz(1);
    delay(1500);
    lcd.clear();
    lcd.print("Ready to Scan");
  }
}

void stopRover() {
  if (roverMoving) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    roverMoving = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ROVER STOPS");

    lcd.setCursor(0, 1);
    lcd.print("Total: ");
    lcd.print(total);

    buzz(2);
    delay(3000); // Give more time to read total
    lcd.clear();
    lcd.print("Ready to Scan");
  }
}

void buzz(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}
