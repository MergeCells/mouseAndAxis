#include <Mouse.h>

#define cursorMoveBtn 1 // Pro micro's TX0 is D1. Miss printed. 
#define scrollMoveBtn 3
#define pushLftBtn 6
#define pushRgtBtn 9

double vdd;
double rx, ry, rz;
double x, y, z;
double g;
double dltX = 0;
double dltY = 0;
double dltZ = 0; // scroll

void setup() {
  pinMode(cursorMoveBtn, INPUT_PULLUP);
  pinMode(scrollMoveBtn, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(pushLftBtn, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(pushRgtBtn, INPUT_PULLUP);
  //Serial.begin(9600);
  Mouse.begin();
}

void loop() {

  vdd = (float)analogRead(A3) / 205;

  rx = (float)analogRead(A0) / 205;
  ry = (float)analogRead(A1) / 205;
  rz = (float)analogRead(A2) / 205;

  x = (rx - vdd / 2) / (vdd / 10) + 0.00;
  y = (ry - vdd / 2) / (vdd / 10) - 0.00;
  z = (rz - vdd / 2) / (vdd / 10) + 0.00;

  g = sqrt(x * x + y * y + z * z);

  if ((0.9 < g) && (g < 1.1)) {
    if ( (digitalRead(cursorMoveBtn) == LOW) ) {
      dltX += asin(y) / 1.57 * 20;
      dltY += asin(x) / 1.57 * 20;
      Mouse.move((int)dltX, (int)dltY, 0);
      dltX -= (int)dltX;
      dltY -= (int)dltY;
    }
    if ( (digitalRead(scrollMoveBtn) == LOW) ) {
      dltZ += -asin(x) / 1.57 /2;
      Mouse.move(0,0,(int)dltZ);
      dltZ -= (int)dltZ;
    }
  }
  if(digitalRead(pushLftBtn) == LOW){
    Mouse.press(MOUSE_LEFT);
  }else if(Mouse.isPressed(MOUSE_LEFT)){
    Mouse.release(MOUSE_LEFT);
  }
  if(digitalRead(pushRgtBtn) == LOW){
    Mouse.press(MOUSE_RIGHT);
  }else if(Mouse.isPressed(MOUSE_RIGHT)){
    Mouse.release(MOUSE_RIGHT);
  }
  delay(5);

  /*
    Serial.print(dltX);
    Serial.println(dltY);

    Serial.print(vdd);
    Serial.print("\t");
    Serial.print(sqrt(x*x+y*y+z*z));
    Serial.print("\tx:  ");
    Serial.print(rx);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t\ty:  ");
    Serial.print(ry);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t\tz:  ");
    Serial.print(rz);
    Serial.print("\t");
    Serial.print(z);
    Serial.println("\t");
    delay(100);
  */
}
