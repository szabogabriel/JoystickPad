#include <Mouse.h>

#define reactionSpeed 20
#define movementSpeed 0.005
#define joyX 1
#define joyY 2
#define but 3

int isMousePressed = 0;

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  pinMode(but, INPUT);
}

int getMovement(int base, int value) {
  double delta = base - (value / 10);
  double movementDirection = (delta < 0) ? -1.0 : 1.0;
  int movement = (int)(delta * delta * movementSpeed * movementDirection);
  return movement;
}

void loop() {
  int moveX = getMovement(51, analogRead(joyX));
  int moveY = getMovement(49, analogRead(joyY));
  int button = analogRead(but);

  Mouse.move(moveX, moveY, 0);

  if (isMousePressed && button > 0) {
    Mouse.release();
    isMousePressed = 0;
  } else
  if (!isMousePressed && button == 0) {
    Mouse.press();
    isMousePressed = 1;
  }

  Serial.print("Button: "); Serial.print(button); Serial.print(", X: "); Serial.print(moveX); Serial.print(", Y: "); Serial.println(moveY);

  delay(reactionSpeed);
}
