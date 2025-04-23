#include <Servo.h>

Servo myServo;
String input = "";
bool personDetected = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(9); // Connect servo signal wire to pin 9
  myServo.write(0);  // Start at 0 degrees
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim(); // Clean newline or space

    if (input == "p") {
      personDetected = true;
      myServo.write(60); // Person detected -> go to 180 and stay
      Serial.println("Detected: 180°");
    }
    else if (input == "o") {
      personDetected = false;
      myServo.write(0);  // Move to 180 first
      delay(1000);         // Hold for a moment
      myServo.write(180);    // Return to 0
      Serial.println("No one: 180° -> 0°");
    }
  }
}
