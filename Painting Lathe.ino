#include <LiquidCrystal.h>
//#include "stepper.h"

#define rs 12
#define rw 11
#define en 10
#define d4 9
#define d5 8
#define d6 7
#define d7 6
#define contrast 50

#define left 13
#define right 4
#define pot A0



LiquidCrystal lcd(rs,rw, en, d4, d5, d6, d7);


void display_speed(char line[], int data)
{
      lcd.setCursor(0, 0);
      lcd.print(line);   
      lcd.setCursor(0, 1);
      lcd.print(data);
}

int average_analog(int analog_value)
{
  const int array_size = 5;
  static int average_array[array_size];
  static int counter = 0;
  int average_total = 0;

  average_array[counter] = analog_value;
  
  counter++;
  if (counter > array_size-1) counter = 0;  
  
  for(int i = 0; i < array_size; i++)
  {
    average_total += average_array[i];  
  }

  return average_total/array_size;
}

void setup() {
  
  analogWrite(5,contrast);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  //pinMode(5, OUTPUT);
  //digitalWrite(5, LOW);
  
}

void loop()
{
  int state = 99;
  int pot_value = 0;
  int last_update = millis();
  

  //lcd.print("hello");

  while(true)
  {
    //delay(250);
    

    if(!digitalRead(left) && digitalRead(right)) state = 1;
    else if(!digitalRead(right) && digitalRead(left)) state = 0;
    else if(!digitalRead(right) && !digitalRead(left)) state = 2;
    else state = 99;

    pot_value = average_analog(analogRead(pot));

    if(millis() >= (last_update + 250))
    {
      lcd.clear();
      last_update = millis();

      switch(state)
      {
        case 0:
        display_speed("Turning left", pot_value);


        //todo set stepper direction left
        //todo set speed           
        break;

        case 1:
        display_speed("Turning right", pot_value);

        //todo set stepper direction right
        //todo set speed                
        break;

        case 2:
        display_speed("Following mode", pot_value);

        //todo set stepper direction right
        //todo follow pot//program a move_to()
        break;
    
        case 98:
        //sleep modeeee

        case 99:
        lcd.setCursor(0, 0);
        lcd.print("Idle");
        break;

        default:
        lcd.setCursor(0, 0);
        lcd.print("error 0");
        break;
      }  

    }
    
  }
}

