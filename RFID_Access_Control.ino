#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(9,10);
int read_count=0;
int j=0,k=0; // Variables to iterate in for loops
char data_temp, RFID_data[12];
char Saved_Tags[5][12]={
  {'5','6','0','0','4','8','8','E','1','B','8','B'},
  {'0','0','0','1','3','E','5','C','5','0','3','3'},
  {'5','6','0','0','1','0','9','3','5','7','8','2'},
  {'5','6','0','0','1','0','E','3','C','A','6','F'},
  {'5','6','0','0','4','8','8','E','1','A','8','A'}};
boolean tag_check,tag_status,entry_control;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
  RecieveData();
  CheckData();
  AccessCheck();
}

void RecieveData()
{
  lcd.setCursor(0,0);
  lcd.print("Swipe Your Card");
  if(mySerial.available())
  {
    read_count=0;
    while(mySerial.available() && read_count<13)
    {
      data_temp=mySerial.read();
      RFID_data[read_count]=data_temp;
      read_count++;
      delay(5);
    }
    Serial.println(RFID_data);
  }
}
void CheckData()
{
  if(read_count==12)
  {
    entry_control=true;
    for(k=0;k<5;k++)
    {
      for(j=0;j<12;j++)
      {
        if(Saved_Tags[k][j]==RFID_data[j])
        {
          tag_check=true;
         }
         else
         {
           tag_check=false;
           break;
         }
        }
         if(tag_check==true)
         {
          tag_status=true;
         }
    }
         read_count=0;
  }}

void AccessCheck()
{
  if(entry_control==true)
  {
    if(tag_status==true)
    {
      lcd.clear();
      delay(50);
      lcd.setCursor(0,1);
      lcd.print("Access Granted");
      Serial.println("Access Granted");
     }
     else
     {
      lcd.clear();
      delay(50);
      lcd.setCursor(0,1);
      lcd.print("Access Denied");
      Serial.println("Access Denied");
     }
     entry_control=false;
     tag_status=false;
  }
}
