#include <LiquidCrystal.h> 
#include <Wire.h>
#include <LSM303.h>
#include <RedBot.h>
RedBotEncoder encoder = RedBotEncoder(A0, 3); 
int lCount;
int rCount;
LSM303 compass;
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); 
 
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
char report[16];
int dLay = 2000;
float Pi = 3.14159; 
void setup() {

  
lcd.begin(16,2); 

pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
 Wire.begin();
  compass.init();
  compass.enableDefault(); 
  compass.m_min = (LSM303::vector<int16_t>){-2000, -1300, -2000};
  compass.m_max = (LSM303::vector<int16_t>){+1000, +1900, +2400};
 
}
 
void loop() {


digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;

lcd.setCursor(0,0); 
lcd.print("Mesafe: "); 
lcd.print(distanceCm); 
lcd.print(" cm");
delay(20);

//int yon = (int)heading;
lcd.setCursor(0, 1);
int x = pusula();
 lcd.print("N: ");
 lcd.print(x);
 int y = WEncodersag();
 int z = WEncodersol();
 lcd.print(" R:");
 lcd.print(y);
 lcd.print(" L:");
 lcd.print(z);
//compass.read();  
 //float heading = compass.heading();  


}
int pusula(){
  compass.read();
  float heading = compass.heading();
  snprintf(report, sizeof(report), "Heading:%+5d",(int)heading );
  return (int)heading;
}
int WEncodersag(){

rCount = encoder.getTicks(RIGHT);


int rightCount =2*rCount;
int mesafe1=((int)2*PI*rightCount)/100;

return mesafe1;
} 
int WEncodersol(){
 lCount = encoder.getTicks(LEFT);
int leftCount =2*lCount;
int mesafe=((int)2*PI*leftCount)/100;
return mesafe;
}
