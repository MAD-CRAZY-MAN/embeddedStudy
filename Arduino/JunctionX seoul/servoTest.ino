#include <Servo.h>

#define servoA_init 90
#define servoB_init 160
#define servoC_init 0
#define LEFT 0
#define RIGHT 1

int i = 0, j = 0, k = 0;
int mtA = 90, mtB = 160, mtC = 0;
int minA = 0, maxA = 180;
int maxB = 80, maxC = 80;

int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;

Servo servo1;
Servo servo2;
Servo servo3;

void readSerial();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(stop_btn, INPUT);
//  pinMode(init_btn, INPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo1.write(servoA_init);
  servo2.write(servoB_init);
  servo3.write(servoC_init);
}

void loop() {
  // put your main code here, to run repeatedly:
  int rotateDistance_A, turn = -1;
  readSerial();
  if(i <= 90)
  {
    turn = RIGHT;
    rotateDistance_A = i;
  }
  else 
  {
    turn = LEFT;
    rotateDistance_A = i;  
  }
//  Serial.println(i);
//  Serial.println(j);
//  Serial.println(k);
//  Serial.println("START");
  Serial.println("Processing to move ...");
  if(turn == RIGHT)
  {
    for(mtA = 90, mtB = 160, mtC = 0; 
        mtA > rotateDistance_A | mtB > (160 - j) | mtC < k;
        mtA--, mtB--, mtC++)
    {
      if(mtA > rotateDistance_A && mtA > minA)
        servo1.write(mtA);
      if(mtB > (160-j) && mtB > maxB)
        servo2.write(mtB);
      if(mtC < k && mtC < maxC)
        servo3.write(mtC);
      delay(20);
    }
    Serial.println("******Current Data******");
    Serial.println(mtA);
    Serial.println(mtB);
    Serial.println(mtC);
    Serial.println("Successfully Processed to Maximum data!");
    if(mtA < minA)  mtA = minA;
    if(mtB < maxB)  mtB = maxB;
    if(mtC > maxC)  mtC = maxC;
    Serial.println("Successfully Processed to changed data!");
    if(mtA < rotateDistance_A)         mtA = i;
    if(mtB < (160-j))   mtB = (160-j);
    if(mtC > k)         mtC = k;
  }
  else
  {
    for(mtA = 90, mtB = 160, mtC = 0; 
        mtA < rotateDistance_A | mtB > (160 - j) | mtC < k;
        mtA++, mtB--, mtC++)
    {
      if(mtA < rotateDistance_A && mtA < maxA)
        servo1.write(mtA);
      if(mtB > (160-j) && mtB > maxB)
        servo2.write(mtB);
      if(mtC < k && mtC < maxC)
        servo3.write(mtC);
      delay(20);
    }
    Serial.println("******Current Data******");
    Serial.println(mtA);
    Serial.println(mtB);
    Serial.println(mtC);
    Serial.println("Successfully Processed to Maximum data!");
    if(mtA > maxA)  mtA = maxA;
    if(mtB < maxB)  mtB = maxB;
    if(mtC > maxC)  mtC = maxC;
    Serial.println("Successfully Processed to changed data!");
    if(mtA < rotateDistance_A)         mtA = rotateDistance_A;
    if(mtB < (160-j))   mtB = (160-j);
    if(mtC > k)         mtC = k;
  }
  
  Serial.println("******Origin Data******");
  Serial.println(mtA);
  Serial.println(mtB);
  Serial.println(mtC);
  delay(3000);

  if(turn == RIGHT)
  {
    for(; 
        mtA <= servoA_init | mtB <= servoB_init | mtC >= servoC_init;
        mtA++, mtB++, mtC--)
    {
      if(mtA <= servoA_init)
        servo1.write(mtA);
      if(mtB <= servoB_init)
        servo2.write(mtB);
      if(mtC >= servoC_init)
        servo3.write(mtC);
      delay(20);
    }
  }
  else
  {
    for(; 
        mtA >= servoA_init | mtB <= servoB_init | mtC >= servoC_init;
        mtA--, mtB++, mtC--)
    {
      if(mtA >= servoA_init)
        servo1.write(mtA);
      if(mtB <= servoB_init)
        servo2.write(mtB);
      if(mtC >= servoC_init)
        servo3.write(mtC);
      delay(20);
    }
  }

}


void readSerial()
{
  String str = "";
  char ch;
  int stat = 0; 
  int value = 0;
  while(Serial.available() == 0);
  while(Serial.available() > 0)
  {
    ch = Serial.read();
    if(ch == ' ')
    {
      value = atoi(str.c_str());
      if(stat == 0) i = value;
      else if (stat == 1) j = value;
      else if (stat == 2) k = value;
      stat++;
      str = "";
    }
    else
    {
      str.concat(ch);
    }
    delay(10);
  }
}
