#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
int POTValue1 = 0;
int POTValue2 = 0;
int pressure = 0;
int mappedValue = 0;
const int minValue = 9;             
const int maxValue = 1010;         
const int minValueMapped = 0;       
const int maxValueMapped = 20;  
const int buttonPin = 6;  
int buttonstate = 0;   
int i = 10;
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
  char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {10, 9, 8}; //connect to the column pinouts of the keypad

  //initialize an instance of class NewKeypad
  Keypad CustomKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void setup()

{
	
	lcd.begin();
  pinMode(A0, INPUT);
	lcd.backlight();
  pinMode(7, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop()
{ 
  lcd.setCursor(0, 0);
  lcd.print("Equipment ready for");
  lcd.setCursor(0, 1);
  lcd.print("Ammonia");
  delay(2000);
  lcd.clear();


  
  lcd.setCursor(0, 0);
  lcd.print("Compressor stage");
  // set the place to display the value on LCD to column 0, line 1:
  lcd.setCursor(0, 1);
  lcd.print("Learning: pot");
  // print out the value on LCD:
  delay(1000);

  while(mappedValue != 11){

      digitalWrite(7, LOW);
      //int mappedValue = map(POTValue1, minValue, maxValue, minValueMapped, maxValueMapped);
      POTValue1 = analogRead(A0);
      POTValue2 = analogRead(A1);
      lcd.clear();  
      lcd.setCursor(0, 0);
      lcd.print("Set pressure in chamber");
      lcd.setCursor(0, 1);
      lcd.print(mappedValue);
      delay(100);
      mappedValue = map(POTValue1, minValue, maxValue, minValueMapped, maxValueMapped);
      continue;
    }

  while(mappedValue == 11){

        int buttonstate = digitalRead(6);
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print("lock this");
        lcd.setCursor(0, 1);
        lcd.print("pressure reading?");
        delay(500);
        digitalWrite(7,HIGH);
        delay(100);

        if(buttonstate == 1){

          digitalWrite(7,LOW);
          char cus1;
          cus1 = CustomKeypad.getKey();
          if (cus1 == "1"){
            digitalWrite(7, HIGH);
            lcd.clear();  
            lcd.setCursor(0, 0);
            lcd.print("Process 1 finished successfully");
            lcd.clear();  
            lcd.setCursor(0, 1);
            lcd.print("Press any key to proceed to step 2");
            if (cus1){
            Serial.println(cus1);
            break;
            }

          }
        }
      }
  
  while(i>0){
    lcd.clear();  
    lcd.setCursor(0, 0);
    lcd.print("Process 2 begining");
    delay(100);
  }

}


