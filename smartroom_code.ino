#include<LiquidCrystal.h>

#define RS 8
#define EN 9
#define D4 10
#define D5 11
#define D6 12
#define D7 13
#define R_led 4
#define W_led 5
#define out_ir 6
#define in_ir 7
#define buzzer 3
#define gas A0
#define temp A1
#define BUTTON A5

LiquidCrystal LCD(RS,EN,D4,D5,D6,D7);

void setup()
{
  pinMode(R_led,OUTPUT);
  pinMode(W_led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(in_ir,INPUT);
  pinMode(out_ir,INPUT);
  pinMode(temp,INPUT);
  pinMode(gas,INPUT);
  pinMode(BUTTON,INPUT);
  LCD.begin(16,2);
}

int people=0,open_led=0,cnt=0,temperature=0,read_gas=0,check=0,in=0,out=0;

void loop()
{  
  
    check_ir();
  
    check_Gas();

    check_Temperature(); 
  
    buttons();
  
}

void check_Gas()
{
  //take the read of the gas sensor to check if turn on the buzzer or not if it's read more than 250
  
  read_gas=analogRead(gas); 
  if(read_gas>=150)
  {
    digitalWrite(buzzer,HIGH);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }

  lcd_show();
}

void check_Temperature()
{
   //take the read of the temp sensor to check if turn on the red led or not if it's read more than 100
  
   int volt=map(analogRead(temp),0,1023,0,5000);
   temperature=volt/10;
   if(temperature>=100)
   {
    digitalWrite(R_led,HIGH);
   }
   else
   {
    digitalWrite(R_led,LOW);
   }

   lcd_show();
}

void check_ir()
{
 
  int read_out_ir=digitalRead(out_ir); //take the read of out ir
    
  if(read_out_ir==HIGH) //detect person
  {
    while(digitalRead(out_ir)==1){} //wait until person walks away from the sensor
      
    if(check==1&&in==1) //this means the person was inside the room exit
    {
       if(people>0)people--;

         if(!people)
         {
           digitalWrite(W_led,LOW);
         }
      
         check=0;
         in=0;
    }
    else //means the person is out of the room and will enter it
    {
      check=1;
      out=1;
    }
  }
  
   int read_in_ir=digitalRead(in_ir); //take read of in ir
  
    if(read_in_ir==HIGH) //detect person
    {
      while(digitalRead(in_ir)==1){} //wait until person walks away from the sensor
      if(check==1&&out==1) //this means the person enter the room
      {
         people++;
         digitalWrite(W_led,HIGH);
         out=0;
         check=0;       
      }
      else //means the person inside the room and will exit 
      {
        check=1;
        in=1;
      }
    }  
    
   lcd_show();          
}

void lcd_show()
{   
    if(cnt==0)
    {
       LCD.setCursor(0,0);
       LCD.print("Person in Room:");
       LCD.setCursor(0,1);
       LCD.print("    ");
       LCD.setCursor(0,1);
       LCD.print(people);      
    }
    else if(cnt==1) 
    {
      LCD.setCursor(0,0);
      LCD.print("Read of Gas:   ");
      LCD.setCursor(0,1);
      LCD.print("    ");
      LCD.setCursor(0,1);
      LCD.print(read_gas);           
    }
    else if(cnt==2)
    {
       LCD.setCursor(0,0);
       LCD.print("Read of Temp:");
       LCD.setCursor(0,1);
       LCD.print("    ");
       LCD.setCursor(0,1);
       LCD.print(temperature);
       LCD.print("c");       
    } 
}

void buttons()
{  
  //take the read of a button to determine what action should do
   int read_btn=analogRead(BUTTON);
   delay(10); //wait 10 milliseconds to avoid bouncing problem
   if(read_btn>=480&&read_btn<=487) //read of right button
   {
     cnt++;
     if(cnt>2)cnt=0;
     lcd_show();
   }
   else if(read_btn>=730&&read_btn<=738) //read of left button
   {
     int read_w=digitalRead(W_led);
     digitalWrite(W_led,!read_w);
   }  
}