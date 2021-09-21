//This code is about collecting fare from passenger
//I've replaced rfid to keypad.
//The route involves only from Tagbilaran-Loay

#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

char Y;
char N;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {7,6,5,4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3,2,1,0}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

class BusFareCollection{
  	
  	public:
  
void discountedFare(){
  customKey = customKeypad.getKey();
  switch(customKey){
  
  case '*':
    if(customKey == '*'){
    	Y = '*';  
    }
    
  case '#':
    if(customKey == '#'){
    	'#';  
    }
    
  }
  
}
  
  
void triggerKeypad() {
  customKey = customKeypad.getKey();
  switch(customKey) 
  {   
  case '1': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Baclayon");
    lcd.setCursor(0,1);
    lcd.print("Discounted? Y/N")
    delay(4000);
    lcd.print("Fare: 15php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '2': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Albur");
    lcd.setCursor(0,1);
    lcd.print("Fare: 25php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '3': 
    lcd.setCursor(0,0);
	lcd.print("Origin: Albur");
    break;  
    
  case 'A': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '4': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '5': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;  
    
  case '6': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case 'B': 
    lcd.setCursor(0,1);
	lcd.print("Dest: Albur");
    break;  
  
  case '7': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;  
    
  case '8': 
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '9':  
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
   
  case 'C':  
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loboc");
    lcd.setCursor(0,1);
    lcd.print("Fare: 50php");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You've paid the");
    lcd.setCursor(0,1);
    lcd.print("fare. Thanks!");
    delay(4000);
    lcd.clear();
    break;
    
  case '*':  
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  case '0':  
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  }
}
};


void setup()
{
lcd.begin(16, 2);               // start lcd
for(int i=0;i<=3;i++);
lcd.setCursor(0,0);
  lcd.print("Fare Collection");
  lcd.setCursor(0,1);
  lcd.print("by Group 4");
delay(4000);
lcd.clear();
}

void loop() {
  BusFareCollection q;
	q.triggerKeypad();
} 