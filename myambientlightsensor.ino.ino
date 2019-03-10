#include <LiquidCrystal.h>

char array1[]=" REG:51;54;35;57";  

char array2[]="  *DATA: 0000*   ";  

int tim = 50;                       


LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
int photoresistorPin =A0;      
int backlight=3;
int LDR_out;
int pwm_backlight;     

void setup()
{
  lcd.clear(); 
  delay(200); 
  Serial.begin(9600);
  lcd.begin(16, 2);    
  lcd.clear();  
  lcd.setCursor(0,0);  
  pinMode(photoresistorPin,INPUT);
  pinMode(backlight,OUTPUT);
       
 
}

void loop() 
{
 
  
  LDR_out=analogRead(photoresistorPin);
  
  if((LDR_out/8)>75)
  {
 
   pwm_backlight=(LDR_out/8);
  analogWrite(backlight,pwm_backlight-75);
  }
  else if(((LDR_out/8)<=75) && ((LDR_out/8)>20))
  {
    analogWrite(backlight,8);
  }
   else if((LDR_out/8)<=20)
   {
    analogWrite(backlight,4);
   }
   
  else 
  {
    analogWrite(backlight,400);
  }
    
  //0x30 is equivalent to decimal 48 and ascii 00
  
  array2[9]=analogRead(photoresistorPin)/1000+0x30;   //Take one thousand
  array2[10]=analogRead(photoresistorPin)/100%10+0x30;//Take one hundred 
  array2[11]=analogRead(photoresistorPin)/10%10+0x30; //Take ten
  array2[12]=analogRead(photoresistorPin)%10+0x30;    //Take ones
  
  for (int c = 0; c < 16; c++)
  {
      lcd.print(array1[c]);  
      delay(tim);     
  } 
  lcd.setCursor(0,1);                                 
  for (int a = 0; a < 16; a++)
  {
    lcd.print(array2[a]);   
        delay(tim);         
                                      
  }
  
}
