#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial SIM900A(10,11); //TX|RX
int hour=12,minute=0,second=0;
void setup() 
{
  lcd.begin();
  Serial.begin(9600);
  SIM900A.begin(9600);
  lcd.backlight();
  Serial.println("SIM900A Ready");
}
void loop() {
  second++;
  if (second>59){
    minute++;
    second=0;
  }
  if (minute>59){
    hour++;
    minute=0;
  }
  if (hour>23){
    hour=0;
  }
  lcd.clear();
  lcd.print("TIME: ");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  lcd.setCursor(1,1);
  lcd.print("WHITEWHALEWATCH");
  delay(990);
  if (Serial.read()=='s'){
    SendMessage();
    second++;
  }
}

void SendMessage() {
  Serial.println("Sending Message");
  SIM900A.println("AT+CMGF=1");
  delay(200);
  Serial.println("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+660917499494\"\r");
  delay(200);
  Serial.println("Set SMS Content");
  SIM900A.println("WHITEWHALEWATCH");
  delay(200);
  Serial.println("Finish");
  SIM900A.println((char)26);//ASCII code of CTRL+Z
  delay(400);
  Serial.println("Message has been sent");
}
