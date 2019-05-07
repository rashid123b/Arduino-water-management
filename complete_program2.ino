
//library code for LCD:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
const int rs = 5, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*
The lcd circuit:
 * LCD RS pin to digital pin 5
 * LCD Enable pin to digital pin 4
 * LCD D4 pin to digital pin 3
 * LCD D5 pin to digital pin 2
 * LCD D6 pin to digital pin 1
 * LCD D7 pin to digital pin 0
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// The ultrasonic sensor on reserve tank is connected to pins 6 & 7 
#define echoOnReserve 6
#define triggerOnReserve 7

// The ultrasonic sensor on tank is connected to pins 8 & 9
#define echoOnTank 8
#define triggerOnTank 9

//initiating time and distance for ultra-Sonic Sensor 
float time=0;
float distanceOnReserve = 0;
float distanceOnTank = 0;   

 
//initiating motor in the reserve tank to pin 10 & 11
const int MotorToReserve = 10;
const int MotorToTank = 11;

//LED Pin
int Led_RedT = A1; // Red LED for motor state in a supply Tank
int Led_RedR = A0; //Red LED for motor state in reserve Tank
int Led_GreenT = A2; //Green LED for motor state in a supply Tank
int Led_GreenR = A3; //Green LED for motor state in reserve Tank


void setup()
{
 
// initialize digital pin for LED as an output.
pinMode(Led_RedT, OUTPUT);
pinMode(Led_RedR, OUTPUT);
pinMode(Led_GreenT, OUTPUT);
pinMode(Led_GreenR, OUTPUT);

// initialize digital pin for Ulra-Sonic sensor in reserve tank.
 pinMode(triggerOnReserve,OUTPUT); // set the trigger pin as an output
 pinMode(echoOnReserve,INPUT); // set the echo pin as an input
 pinMode(MotorToReserve, OUTPUT);// set the motor pin as an output

Serial.begin(9600); // Starting Serial Communication

 // initialize digital pin for Ulra-Sonic sensor in Supply tank.
 pinMode(triggerOnTank,OUTPUT); // set the trigger pin as an output
 pinMode(echoOnTank,INPUT); // set the echo pin as an input
 pinMode(MotorToTank, OUTPUT);// set the motor pin as an output

 // set up the LCD's number of columns and rows(16x2):
 lcd.begin(16, 2);
 lcd.setCursor(3,0); // set up LCD cursor
 lcd.print(" WATER ");
 lcd.setCursor(1,1);
 lcd.print(" MANAGEMENT STM ");
 delay(1000);
}

//Void loops for reserve tank and supply tank that shall run simultaneously 
void loop() {
  reserveSensor();
  tankSensor();
  }


//program loop for Reserve Tank
void reserveSensor(){
  
  lcd.clear();
 digitalWrite(triggerOnReserve,LOW);
 delayMicroseconds(2);
 digitalWrite(triggerOnReserve,HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerOnReserve,LOW);
 delayMicroseconds(2);
 time=pulseIn(echoOnReserve,HIGH); // stores the time span between the transmitted and reflected waves
 distanceOnReserve=time*0.034/2; //formula to calculate the distance in cm
 lcd.setCursor(0,0);
 lcd.print("LEVELR:");
 lcd.setCursor(0,1);
 lcd.print("Distance:");
 delay(50);



 if (distanceOnReserve >=50){//set empty distance 
  digitalWrite(MotorToReserve, HIGH);
digitalWrite(Led_RedR, LOW);
digitalWrite(Led_GreenR, HIGH);
  lcd.setCursor(7,0);
 lcd.print("empty");
 lcd.setCursor(9,1);
 lcd.print(distanceOnReserve);//print Reserve tank water level 
  delay(500);
  }

else if(distanceOnReserve >= 25 && distanceOnReserve < 50)//set above average distance
 { 
digitalWrite(MotorToReserve, HIGH);
digitalWrite(Led_RedR, LOW);
digitalWrite(Led_GreenR, HIGH);
 lcd.setCursor(7,0);
 lcd.print("Bellow AVG");
 lcd.setCursor(9,1);
 lcd.print(distanceOnReserve);
 delay(500);
 }


else if(distanceOnReserve < 25 && distanceOnReserve > 10)// set below average level
 {
digitalWrite(MotorToReserve, HIGH);
digitalWrite(Led_RedR, LOW);
digitalWrite(Led_GreenR, HIGH);
 lcd.setCursor(7,0);
 lcd.print("Above AVG");
 lcd.setCursor(9,1);
 lcd.print(distanceOnReserve);
 delay(500);
 }


  else if (distanceOnReserve <= 10 ){ // set empty level
 digitalWrite(MotorToReserve, LOW);
digitalWrite(Led_GreenR, LOW);
digitalWrite(Led_RedR, HIGH);
 lcd.setCursor(7,0);
 lcd.print("FULL TANK");
 lcd.setCursor(9,1);
 lcd.print(distanceOnReserve);
 delay(500);

    } 
}


// program loop for supply Tank
void tankSensor(){
  
  lcd.clear();
 digitalWrite(triggerOnTank,LOW);
 delayMicroseconds(2);
 digitalWrite(triggerOnTank,HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerOnTank,LOW);
 delayMicroseconds(2);
 time=pulseIn(echoOnTank,HIGH); // stores the time span between the transmitted and reflected waves
 distanceOnTank=time*0.034/2; //formula to calculate the distance in cm
 lcd.setCursor(0,0);
 lcd.print("LEVELT:");
 lcd.setCursor(0,1);
 lcd.print("Distance:");
 //digitalWrite(MotorToTank, LOW);
 delay(10);
 
if (distanceOnTank >=50){
  digitalWrite(MotorToTank, HIGH);
  digitalWrite(Led_GreenT, HIGH);
  digitalWrite(Led_RedT, LOW);
  
 lcd.setCursor(7,0);
 lcd.print("empty");
 lcd.setCursor(9,1);
 lcd.print(distanceOnTank);
  delay(500);
  }

else if(distanceOnTank >= 25 && distanceOnTank < 50)
 {
digitalWrite(MotorToTank, HIGH);
digitalWrite(Led_RedT, LOW);
digitalWrite(Led_GreenT, HIGH);
 
 lcd.setCursor(7,0);
 lcd.print("Bellow AVG");
 lcd.setCursor(9,1);
 lcd.print(distanceOnTank);
 delay(500);
 }


else if(distanceOnTank < 25 && distanceOnTank > 10)
 {
digitalWrite(MotorToTank, HIGH);
digitalWrite(Led_RedT, LOW);
digitalWrite(Led_GreenT, HIGH);
 
 lcd.setCursor(7,0);
 lcd.print("Above AVG");
 lcd.setCursor(9,1);
 lcd.print(distanceOnTank);
 delay(500);
 }


 else if (distanceOnTank <= 10 ){
digitalWrite(MotorToTank, LOW);
digitalWrite(Led_RedT, HIGH);
digitalWrite(Led_GreenT, LOW); 
 lcd.setCursor(7,0);
 lcd.print("FULL TANK");
 lcd.setCursor(9,1);
 lcd.print(distanceOnTank);
 delay(500);

    } 

}
