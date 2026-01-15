#include <IRremote.h>

#define IR_PIN 11

#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 9

IRrecv irrecv(IR_PIN);
decode_results results;

int brightness = 255;  // full brightness

void setColor(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {

    uint32_t code = results.value;
    Serial.println(code, HEX);

    // ==========================
    // YOUR BUTTON CODES
    // ==========================

    if (code == 0xFF30CF) {     // Button "1" = RED
      setColor(brightness, 0, 0);
    }

    if (code == 0xFF18E7) {     // Button "2" = GREEN
      setColor(0, brightness, 0);
    }

    if (code == 0xFF7A85) {     // Button "3" = BLUE
      setColor(0, 0, brightness);
    }

    irrecv.resume();
  }
}
