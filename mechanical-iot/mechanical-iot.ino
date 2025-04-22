#include <Servo.h>

Servo myServo;
String command = "";
bool allowMotion = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);  // Attach servo to pin 9
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "p") {
      allowMotion = true;
    } else if (command == "o") {
      allowMotion = false;
    }
  }

  if (allowMotion) {
    myServo.write(180);   // Rotate to 180°
    delay(500);           // Wait 500 ms
    myServo.write(0);     // Rotate back to 0°
    delay(100);           // Small delay to prevent flooding
  }
}
