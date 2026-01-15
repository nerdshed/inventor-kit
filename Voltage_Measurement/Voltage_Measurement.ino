#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address if your module uses 0x3F etc.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int analogPin = A0;
const float R1 = 1000.0; // top resistor (ohms)
const float R2 = 220.0;   // bottom resistor (ohms)
const float ADC_REF = 5.00;  // ADC reference voltage (V). Use measured Vcc for better accuracy
const int ADC_MAX = 1023;    // 10-bit ADC

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.print("   VOLTAGE ");
  lcd.setCursor(0,1);
  lcd.print("  MEASUREMENT");
  delay(3000);
}

float readAverageADC(int samples = 10, int delayMs = 5) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(analogPin);
    delay(delayMs);
  }
  return (float)sum / samples;
}

void loop() {
  float adc = readAverageADC(20, 3); // average 20 readings
  float vout = (adc * ADC_REF) / ADC_MAX;      // measured at divider midpoint (node A)
  float vin = vout * (R1 + R2) / R2;           // actual input voltage

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Vin:");
  lcd.print(vin, 3);   // 3 decimal places
  lcd.print("V");

  lcd.setCursor(0,1);
  lcd.print("Vout:");
  lcd.print(vout, 2);

  // Serial debug
  Serial.print("ADC: "); Serial.print(adc);
  Serial.print("  Vout: "); Serial.print(vout,4);
  Serial.print("  Vin: "); Serial.println(vin,4);

  delay(800);
}
