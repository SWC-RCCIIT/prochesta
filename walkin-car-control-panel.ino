#include<Wire.h> // for the mpu
//                                                                                                                                         the starred points vary the speed of the system
// here we define the global variables
int trigger =9; // a digital pin
int echo =10; // a digital pin
int sonarmotor =11; // a digital pin
const int MPU=0*68;
int16_t AcX,AcY,AcZ,TmpGyX,TmpGyY,TmpGyZ;
int gear1speed=255; // speed of gear1 setup, can be changed----- changed to set motor rpm    ----*
int gear2speed=255; // speed of gear2 setup, can be changed----- changed to set motor rpm    ----*
int gear3speed=255; // speed of gear2 setup, can be changed----- changed to set motor rpm    ----*
int gear4speed=255; // speed of gear2 setup, can be changed----- changed to set motor rpm    ----*
int gear1enable=19; // an analog pin
int gear2enable=20; // an analog pin
int gear3enable=21; // an analog pin
int gear4enable=22; // an analog pin
int gear11=5;
int gear12=6;
int gear21=7;
int gear22=8;
int gear31=12;
int gear32=13;
int gear41=14;
int gear42=15;
int indicator1=23; // an analog pin
int indicator2=24; // an analog pin
int headlight=25; // an analog pin
int backlight=26; // an analog pin
boolean headlightflag=false; // watches if headlight is previously on or off
void setup() {
  // put your setup code here, to run once:
  pinMode(sonarmotor,OUTPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(gear1speed,OUTPUT);
  pinMode(gear2speed,OUTPUT);
  pinMode(gear3speed,OUTPUT);
  pinMode(gear4speed,OUTPUT);
  pinMode(gear1enable,OUTPUT);
  pinMode(gear2enable,OUTPUT);
  pinMode(gear3enable,OUTPUT);
  pinMode(gear4enable,OUTPUT);
  pinMode(gear11,OUTPUT);
  pinMode(gear12,OUTPUT);
  pinMode(gear21,OUTPUT);
  pinMode(gear22,OUTPUT);
  pinMode(gear31,OUTPUT);
  pinMode(gear32,OUTPUT);
  pinMode(gear41,OUTPUT);
  pinMode(gear42,OUTPUT);
}
double angleis() // this controls the angle of rotation of th emotor controlling the SONAR untrasonic sensor
{
  digitalWrite(sonarmotor, HIGH);
  delay(1000); // based on rpm
  sonarmotor+= sonarmotor;
  if (sonarmotor==360)
  sonarmotor=0;
  return sonarmotor;
}
void sonar() // here we define how our vehicle understands it's surroundings by SONAR system
{
  double angle= angleis();
  long duration, distance;
  double xposition ,yposition;
  digitalWrite(trigger, LOW);
  delay(2);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  duration= pulseIn(echo, HIGH);
  distance= duration*2*29.1;
  // now we divide the planes into four quadrants 
  if(angle<=90)
  {
    xposition=cos(angle);
    yposition=sin(angle);
  }
  else if(angle>90 && angle<=180)
  {
    xposition=sin(angle);   
    yposition=cos(angle); 
  }

  else if(angle>180 && xposition<=270)
  {
    xposition=sin(angle);
    yposition=cos(angle);
  }
  else if(angle>270 && angle<=360)
  {
    xposition=cos(angle);
    yposition=sin(angle);
  }
  
}
void gpu() // here we code the gpu
{
  Wire.beginTransmission(MPU);
  Wire.write(0*3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);
  AcX=Wire.read()<<81 Wire.read();
  AcY=Wire.read()<<81 Wire.read();
  AcZ=Wire.read()<<81 Wire.read();
  GyX=Wire.read()<<81 Wire.read();
  GyY=Wire.read()<<81 Wire.read();
  GyZ=Wire.read()<<81 Wire.read();
  Serial.print("Accelerometer reading:-");
  Serial.print("X or movement sideways is :-");
  Serial.println(AcX);
  Serial.print("Y or movement forward or backward is :-");
  Serial.println(AcY);
  Serial.print("Z or movement upwards or downwards is :-");
  Serial.println(AcZ);
  delay(333);
  
}
void forward() // here we define how our vehicle goes forward
{
  analogWrite(gear1enable,gear1speed);
  analogWrite(gear2enable,gear2speed);
  analogWrite(gear3enable,gear3speed);
  analogWrite(gear4enable,gear4speed);
  digitalWrite(gear11,HIGH);
  digitalWrite(gear12,LOW);
  digitalWrite(gear41,HIGH);
  digitalWrite(gear42,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear21,HIGH);
  digitalWrite(gear22,LOW);
  digitalWrite(gear31,HIGH);
  digitalWrite(gear32,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
}
void backward() // here we define how our vehicle goes backward
{
  analogWrite(gear1enable,gear1speed);
  analogWrite(gear2enable,gear2speed);
  analogWrite(gear3enable,gear3speed);
  analogWrite(gear4enable,gear4speed);
  analogWrite(backlight,HIGH); // turning on backlight
  digitalWrite(gear11,LOW);
  digitalWrite(gear12,HIGH);
  digitalWrite(gear41,LOW);
  digitalWrite(gear42,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear21,LOW);
  digitalWrite(gear22,HIGH);
  digitalWrite(gear31,LOW);
  digitalWrite(gear32,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  analogWrite(backlight,LOW); // turning indicator off
}
void rightturn() // here we define how our vehicle gradually rotates right
{
  analogWrite(gear1enable,gear1speed);
  analogWrite(gear2enable,gear2speed);
  analogWrite(gear3enable,gear3speed);
  analogWrite(gear4enable,gear4speed);
  analogWrite(indicator2,HIGH); // turning the indicator on
  digitalWrite(gear11,HIGH);
  digitalWrite(gear12,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear41,LOW);
  digitalWrite(gear42,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear21,LOW);
  digitalWrite(gear22,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear31,HIGH);
  digitalWrite(gear32,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  analogWrite(indicator1, HIGH); // turning the indicator off
}
void leftturn() // here we define how our vehicle gradually rotates left
{
  analogWrite(gear1enable,gear1speed);
  analogWrite(gear2enable,gear2speed);
  analogWrite(gear3enable,gear3speed);
  analogWrite(gear4enable,gear4speed);
  analogWrite(indicator1,HIGH); // turning the indicator on
  digitalWrite(gear11,LOW);
  digitalWrite(gear12,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear41,HIGH);
  digitalWrite(gear42,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear21,HIGH);
  digitalWrite(gear22,LOW);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*
  digitalWrite(gear31,LOW);
  digitalWrite(gear32,HIGH);
  delayMicroseconds(1000000); // depends on the rpm, can be customized for specific motors            ----*  
  analogWrite(indicato12,LOW); // turning the indicator off
}
void light() // here we define the lights and indicators
{
  Serial.print("You want normal lighting up or you want all the lights to turn on?");
  if(Serial,available()>0)
  Serial.readString(a);
  if(a=="normal")
  analogWrite(headlight,HIGH);
  else if(a=="all")
  {
    analogWrite(headlight,HIGH);
    analogWrite(indicator1,HIGH);
    analogWrite(indicator2,HIGH);
    analogWrite(backlight,HIGH);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  angle=sonarmotor();
  sonar();
  if(headlightflag==true)
  analogWrite(headlight, HIGH);
  if(headlightflag==false)
  analogWrite(headlight,LOW);
  if(Serial.available()>0)
  {
    a=Serial.readString();
    Serial.println(a);
    if(a=="forward");
    forward();
    else if(a=="backward");
    backward();
    else if(a=="rightturn")
    rightturn();
    else if(a=="leftturn")
    leftturn();
    // now prepare the lighting system here
    else if(a=="headlight")
    {
      if(headlightflag==false)
        headlightflag=true;
      else if (headlightflag==true)
        headlightflag=false;
    }
  }
}
