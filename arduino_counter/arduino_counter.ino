#include <dht.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 6);
#define DHT11PIN 4
dht DHT;

int timer1;
int timer2;
int person=0;
int day=0;
int flag1=0;
int flag2=0;
int ir1=2; 
int ir2=7; 
int relay=8; 
String value="0";
String change="d";
void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("J Project.");
}


void loop() {
int chk = DHT.read(DHT11PIN);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("H:T=");
lcd.print((float)DHT.humidity, 2);
lcd.print(":");
lcd.print((float)DHT.temperature, 2);
lcd.setCursor(0, 1);
lcd.print("V=");
lcd.print(value);

delay(100);
if(digitalRead(ir1)==LOW && digitalRead(ir2)==LOW){
  day=1;
  person=0;
}
if(digitalRead(ir1)==HIGH && digitalRead(ir2) == HIGH){
  day=0;
}
if(digitalRead (ir1) == LOW && flag1==0){
  timer1 = millis(); 
  flag1=1;
  }
if(digitalRead (ir2) == LOW && flag2==0){
    timer2 = millis(); 
    flag2=1;
    }
if (flag1==1 && flag2==1)
{ 
    if((timer1-timer2)<0){
        person=person+1;
      }
    else if((timer1-timer2)>0)
    {
        person=person-1;
        if(person==-1){
          person=0;
        }
  }
  if (day==1)
  { 
    value="d";
    digitalWrite(relay, LOW); 
    delay(500);
  }
  if (person>0 && day==0){
    value=String(person);
    digitalWrite(relay, HIGH); 
    delay(500);

  }
  if (person==0 && day==0){
    value=String(person);
    digitalWrite(relay, LOW); 
    delay(500);
  }
  flag1=0;
  flag2=0;
  }
  if(change!=value)
  {
    change=value;
    Serial.print(value);
  }
}
