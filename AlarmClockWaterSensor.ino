//Download Libraries and setup before using program
//Wire.h is included in Arduino
//LiquidCrystal_I2C link: https://drive.google.com/file/d/1Oc56q2GPs5SOA-PdbVHHSxKCnI9KY5xd/view
//Keypad link: https://drive.google.com/file/d/1weX2h1kf_NG5WA_a8FldEMcP84hp16RO/view
//VirtualbotixRTC link: https://drive.google.com/file/d/1weX2h1kf_NG5WA_a8FldEMcP84hp16RO/view


#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Keypad.h>
#include <Wire.h>

#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define sensorPin A0

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

virtuabotixRTC myRTC(2, 3, 4);

const byte numRows= 4;
const byte numCols= 4;

char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows] = {12,11,10,9};
byte colPins[numCols]= {8,7,6,5};
int i1,i2,i3,i4;
char c1,c2,c3,c4;
char keybuttonpressed,keybuttonpressedx;
int A_hour=NULL;
int A_minute=NULL;
int AlarmIsActive=NULL;
int buzzer = 13;
int sensorValue = 0;
int percentlevel = 0;
int sensorValueMain = 0;
int percentlevelMain = 0;

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


void setup() {
  Serial.begin(9600);
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
                                       
}

void loop() {
   
  while(keybuttonpressed == NO_KEY){
  keybuttonpressed = myKeypad.getKey();
  lcd.clear();
  myRTC.updateTime();
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  percentlevel = map(sensorValue, 0, 600, 0, 100);
  

  //alarm if time reached, sensor value < 450 (not near max capacity)
  if(myRTC.hours==A_hour && myRTC.minutes==A_minute && AlarmIsActive==1 && myRTC.seconds >= 0 && myRTC.seconds <= 2 && sensorValue < 450){
    AlarmIsActive = 0; //turns off alarm
    while(keybuttonpressedx == NO_KEY){
      //Serial.println("Alarm mode low water"); //test code
    tone(buzzer, 1000);
    delay(100);
    tone(buzzer, 2000);
    delay(100);
    lcd.clear();
    lcd.print("Water Level LOW"); //Message to show when the alarm is ringing
    lcd.setCursor(0,1);
    lcd.print("Press Key");
    keybuttonpressedx = myKeypad.getKey();
    }
  }

  //alarm if time reached, sensor is >= 450 (near max capacity)
  if(myRTC.minutes!=A_minute && AlarmIsActive==1 && sensorValue >= 450){
    AlarmIsActive = 0; //turns off alarm
    //Serial.println("Alarm is off"); //test code
    //Serial.println(AlarmIsActive); //test code
    while(keybuttonpressedx == NO_KEY){
      //Serial.println("Alarm mode buzzer"); //test code
    tone(buzzer, 1000);
    delay(200);
    tone(buzzer, 2000);
    delay(200);
    lcd.clear();
    lcd.print("Water Level FULL"); //Message to show when the alarm is ringing
    lcd.setCursor(0,1);
    lcd.print("Press Key");
    keybuttonpressedx = myKeypad.getKey();
    }
  }


  //keyboard code DO NOT TOUCH
  keybuttonpressedx = NO_KEY;
  noTone(buzzer);
  lcd.setCursor(0,0);
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.setCursor(0,1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  delay(100);
  }
 

         if (keybuttonpressed == '*')
             {
              lcd.clear();
              lcd.print("     Setup");
             delay(1000);
              lcd.clear();
              lcd.print("Setup year");

             char keybuttonpressed2 = myKeypad.waitForKey();  
                    if (keybuttonpressed2 != NO_KEY && keybuttonpressed2 !='*' && keybuttonpressed2 !='#' && keybuttonpressed2 !='A' && keybuttonpressed2 !='B' && keybuttonpressed2 !='C' && keybuttonpressed2 !='D' )
                      {
                       c1 = keybuttonpressed2;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                 char      keybuttonpressed3 = myKeypad.waitForKey();
                    if (keybuttonpressed3 != NO_KEY && keybuttonpressed3 !='*' && keybuttonpressed3 !='#' && keybuttonpressed3 !='A' && keybuttonpressed3 !='B' && keybuttonpressed3 !='C' && keybuttonpressed3 !='D' )
                      {
                       c2 = keybuttonpressed3;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
                   char  keybuttonpressed4 = myKeypad.waitForKey();
                   if (keybuttonpressed4 != NO_KEY && keybuttonpressed4 !='*' && keybuttonpressed4 !='#' && keybuttonpressed4 !='A' && keybuttonpressed4 !='B' && keybuttonpressed4 !='C' && keybuttonpressed4 !='D' )
                      {
                       c3 = keybuttonpressed4;
                       lcd.setCursor(2, 1);
                       lcd.print(c3);
                       }
                   char   keybuttonpressed5 = myKeypad.waitForKey();
                   if (keybuttonpressed5 != NO_KEY && keybuttonpressed5 !='*' && keybuttonpressed5 !='#' && keybuttonpressed5 !='A' && keybuttonpressed5 !='B' && keybuttonpressed5 !='C' && keybuttonpressed5 !='D' )
                      {
                       c4 = keybuttonpressed5;
                       lcd.setCursor(3, 1);
                       lcd.print(c4);
                       }

                     i1=(c1-48)*1000;
                     i2=(c2-48)*100;
                     i3=(c3-48)*10;
                     i4=c4-48;
                     int N_year=i1+i2+i3+i4;
                   delay(500);
                     lcd.clear();
                     lcd.print("Setup month");

                     char keybuttonpressed6 = myKeypad.waitForKey();  
                    if (keybuttonpressed6 != NO_KEY && keybuttonpressed6 !='*' && keybuttonpressed6 !='#' && keybuttonpressed6 !='A' && keybuttonpressed6 !='B' && keybuttonpressed6 !='C' && keybuttonpressed6 !='D' )
                      {
                       c1 = keybuttonpressed6;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keybuttonpressed7 = myKeypad.waitForKey();
                    if (keybuttonpressed7 != NO_KEY && keybuttonpressed7 !='*' && keybuttonpressed7 !='#' && keybuttonpressed7 !='A' && keybuttonpressed7 !='B' && keybuttonpressed7 !='C' && keybuttonpressed7 !='D' )
                      {
                       c2 = keybuttonpressed7;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_month=i1+i2;
                     delay(500);

                     lcd.clear();
                     lcd.print("Setup Day");
                     
                 
                      char keybuttonpressed8 = myKeypad.waitForKey();
                    if (keybuttonpressed8 != NO_KEY && keybuttonpressed8 !='*' && keybuttonpressed8 !='#' && keybuttonpressed8 !='A' && keybuttonpressed8 !='B' && keybuttonpressed8 !='C' && keybuttonpressed8 !='D' )
                      {
                        c1 = keybuttonpressed8;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                      char keybuttonpressed9 = myKeypad.waitForKey();
                    if (keybuttonpressed9 != NO_KEY && keybuttonpressed9 !='*' && keybuttonpressed9 !='#' && keybuttonpressed9 !='A' && keybuttonpressed9 !='B' && keybuttonpressed9 !='C' && keybuttonpressed9 !='D' )
                      {
                        c2 = keybuttonpressed9;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_day=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Setup hour");
         
                     char keybuttonpressed10 = myKeypad.waitForKey();  
                    if (keybuttonpressed10 != NO_KEY && keybuttonpressed10 !='*' && keybuttonpressed10 !='#' && keybuttonpressed10 !='A' && keybuttonpressed10 !='B' && keybuttonpressed10 !='C' && keybuttonpressed10 !='D' )
                      {
                       c1 = keybuttonpressed10;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keybuttonpressed11 = myKeypad.waitForKey();
                    if (keybuttonpressed11 != NO_KEY && keybuttonpressed11 !='*' && keybuttonpressed11 !='#' && keybuttonpressed11 !='A' && keybuttonpressed11 !='B' && keybuttonpressed11 !='C' && keybuttonpressed11 !='D' )
                      {
                        c2 = keybuttonpressed11;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Setup minutes");

                    char keybuttonpressed12 = myKeypad.waitForKey();
                    if (keybuttonpressed12 != NO_KEY && keybuttonpressed12 !='*' && keybuttonpressed12 !='#' && keybuttonpressed12 !='A' && keybuttonpressed12 !='B' && keybuttonpressed12 !='C' && keybuttonpressed12 !='D' )
                      {
                        c1 = keybuttonpressed12;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                   char    keybuttonpressed13 = myKeypad.waitForKey();
                    if (keybuttonpressed13 != NO_KEY && keybuttonpressed13 !='*' && keybuttonpressed13 !='#' && keybuttonpressed13 !='A' && keybuttonpressed13 !='B' && keybuttonpressed13 !='C' && keybuttonpressed13 !='D' )
                      {
                        c2 = keybuttonpressed13;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_minutes=i1+i2;
                    delay(500);
                     lcd.clear();

                    myRTC.setDS1302Time(22, N_minutes, N_hour, 1, N_day, N_month, N_year);

                    keybuttonpressed=NO_KEY; 
              }

              
             if (keybuttonpressed == 'A'){
              lcd.clear();
              lcd.print("  Alarm setup  ");
              delay(1000);
              lcd.clear();
              lcd.print("Set alarm hour");
               
               char keybuttonpressed14 = myKeypad.waitForKey();
                    if (keybuttonpressed14 != NO_KEY && keybuttonpressed14 !='*' && keybuttonpressed14 !='#' && keybuttonpressed14 !='A' && keybuttonpressed14 !='B' && keybuttonpressed14 !='C' && keybuttonpressed14 !='D' )
                      {
                       c1 = keybuttonpressed14;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keybuttonpressed15 = myKeypad.waitForKey();
                    if (keybuttonpressed15 != NO_KEY && keybuttonpressed15 !='*' && keybuttonpressed15 !='#' && keybuttonpressed15 !='A' && keybuttonpressed15 !='B' && keybuttonpressed15 !='C' && keybuttonpressed15 !='D' )
                      {
                        c2 = keybuttonpressed15;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Set alarm minutes");
                      char keybuttonpressed16 = myKeypad.waitForKey();
                    if (keybuttonpressed16 != NO_KEY && keybuttonpressed16 !='*' && keybuttonpressed16 !='#' && keybuttonpressed16 !='A' && keybuttonpressed16 !='B' && keybuttonpressed16 !='C' && keybuttonpressed16 !='D' )
                      {
                       c1 = keybuttonpressed16;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keybuttonpressed17 = myKeypad.waitForKey();
                    if (keybuttonpressed17 != NO_KEY && keybuttonpressed17 !='*' && keybuttonpressed17 !='#' && keybuttonpressed17 !='A' && keybuttonpressed17 !='B' && keybuttonpressed17 !='C' && keybuttonpressed17 !='D' )
                      {
                        c2 = keybuttonpressed17;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }


                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_minute=i1+i2;
                    delay(500);
                     lcd.clear();
                      AlarmIsActive=1;
                      keybuttonpressed=NO_KEY;
             }
             if (keybuttonpressed == 'B')
             {
              if(AlarmIsActive==0){
                lcd.clear();
                lcd.print(" NO ALARM");
                lcd.setCursor(0, 1);
                lcd.print(" SET");
                keybuttonpressed=NO_KEY;
                delay(1000);
              }
              
              if(AlarmIsActive==1){
                lcd.clear();
                lcd.print(" ALARM");
                lcd.setCursor(0, 1);
                lcd.print(" DEACTIVATED");
                AlarmIsActive=0;
                keybuttonpressed=NO_KEY;
                delay(1000);
              }
             }
             if (keybuttonpressed == 'C')
             {
              if(AlarmIsActive==0){
                keybuttonpressed=NO_KEY;
                while(keybuttonpressed == NO_KEY){
                  sensorValueMain = analogRead(sensorPin);
                  //Serial.println(sensorValue);
                  percentlevelMain = map(sensorValueMain, 0, 630, 0, 100);
                  delay(300);
                  lcd.clear();
                  lcd.print("SENSOR: ");
                  lcd.print(sensorValueMain);
                  lcd.setCursor(0, 1);
                  lcd.print("Value: ");
                  lcd.print(percentlevelMain);
                  keybuttonpressed = myKeypad.getKey();
                }
                keybuttonpressed=NO_KEY;
                delay(100);
              }
              
              if(AlarmIsActive==1){
                lcd.clear();
                lcd.print(" ALARM IS SET");
                lcd.setCursor(0,1);
                lcd.print(" RETURNING");
                keybuttonpressed=NO_KEY;
                delay(2000);
              }
             }
             if (keybuttonpressed == 'D')
             {
              if(AlarmIsActive==0){
                lcd.clear();
                lcd.print(" NO ALARM SET");
                lcd.setCursor(0, 1);
                lcd.print(" RETURNING");
                keybuttonpressed=NO_KEY;
                delay(1000);
              }
              
              if(AlarmIsActive==1){
                lcd.clear();
                lcd.print(" ALARM TIME:");
                lcd.setCursor(0,1);
                lcd.print(A_hour);
                lcd.print(":");
                lcd.print(A_minute);
                keybuttonpressed=NO_KEY;
                delay(2000);
              }
             }
             else {
              myRTC.updateTime();
              keybuttonpressed=NO_KEY;
             }
             

}
