#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial SIM900A(10,11); //TX|RX
int hour=12,minute=0,second=0;
int check=0,recall=0;
const float OffSet=0.483;
float V,P;
void setup() {
  lcd.begin();
  Serial.begin(9600);
  SIM900A.begin(9600);
  lcd.backlight();
  Serial.println("SIM900A Ready");
}//Just a setting
void loop() {
  V=analogRead(0)*5.00/1024;//Receive values ​​from pressure sensors
  P=(V-OffSet)*400;//Convert to kilopascal
  second++;
  if (second>59){//Just a timer
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
  lcd.clear();//Display to LCD screen
  lcd.print("TIME: ");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  lcd.print(":");
  lcd.print(second);
  lcd.setCursor(1,1);
  lcd.print("WHITEWHALEWATCH");
  Serial.print(P,1);
  Serial.println(" KPa");
  delay(990);
  if (P>20.0){//Sends a message when the P over 20 kilopascal
    SendMessage();
    second++;
    check=1;
  }
  while (check!=0){//Check if the child is still drowned
    recall++;
    second++;
    Serial.println(recall);
    delay(990);
    if (recall==10){
      check=0;
      recall=0;
    }
  }
}

void SendMessage(){
  //Fuction used to send messages
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
