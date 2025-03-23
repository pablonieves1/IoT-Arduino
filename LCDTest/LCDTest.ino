#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address of the LCD (commonly 0x27 or 0x3F)
#define LCD_ADDRESS 0x27

// Initialize the LCD object with the I2C address and size (16x2)
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  // Start I2C communication
  Wire.begin();
  // Start serial communication
  Serial.begin(9600);
  while (!Serial)
    delay(10);
  Serial.println("\nI2C Scanner");

  // Scan the I2C bus for devices
  scanI2CDevices();

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("I2C Address:");
  lcd.setCursor(0, 1);
  lcd.print("0x");
  lcd.print(LCD_ADDRESS, HEX);
}

void loop() {
  // Main code can go here
}

// Function to scan I2C devices and display addresses
void scanI2CDevices() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("Scan completed\n");
}
