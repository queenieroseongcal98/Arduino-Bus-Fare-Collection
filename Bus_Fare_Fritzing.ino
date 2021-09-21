#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <Ethernet.h>


#define RST_PIN         42          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
#define No_Of_Card       5

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4;
const byte COLS = 4;

char keymap[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

char customKey;

Keypad customKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, ROWS, COLS);


int aBAL = 200;
//int bBAL = 2000;
//int cBAL = 2000;
//int dBAL = 2000;
//int eBAL = 2000;

byte id[No_Of_Card][4]={
  {255, 96, 217, 63},             //RFID NO-1
  {158, 80, 217, 63},             //RFID NO-2
  {206, 62, 217, 63},             //RFID NO-3
  {217, 198, 07, 229},            //RFID NO-4
  {199, 106, 251, 160}            //RFID NO-5
};

byte id_temp[5][5];              //sudlanan sa card
byte i;
int j=0;
int s=0;
int Loc,Orig,Des,Payment;
boolean result = false;

//String uid1 = "FF 60 D9 3F";
//String uid2 = "9E 50 D9 3F";
//String uid3 = "CE 3E D9 3F";
//String uid4 = "D9 C6 07 E5";
//String uid5 = "C7 6A FB A0";

void setup() {
  // put your setsup code here, to run once:
  lcd.init();                      
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //
  for(byte i=0;i<6;i++)
  {
    key.keyByte[i]=0xFF;        
  }
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Implementing Bus");
  lcd.setCursor(0,1);
  lcd.print("Fare Collection");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Using Arduino &");
  lcd.setCursor(0,1);
  lcd.print("RFID by Group 4");
  delay(2000);
  lcd.clear();
}

void loop() {
  // your main code
  //triggerKeypad();
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Your Card...");
  rfidDetect();
  delay(1000);
  lcd.clear();
  customKey = customKeypad.getKey();
  if(customKey != NO_KEY)
  {
    triggerKeypad();
  }

}

void rfidDetect()
{
  //lcd.setCursor(0,0);
  //lcd.print("Scan Your Card...");
  int m=0;
  if(!mfrc522.PICC_IsNewCardPresent())
  return;
  if(!mfrc522.PICC_ReadCardSerial())
  return;
  for(i=0;i<4;i++)
  {
   id_temp[0][i]=mfrc522.uid.uidByte[i]; 
             delay(50);
  }
  
   for(i=0;i<No_Of_Card;i++)
  {
          if(id[i][0]==id_temp[0][0])
          {
            if(id[i][1]==id_temp[0][1])
            {
              if(id[i][2]==id_temp[0][2])
              {
                if(id[i][3]==id_temp[0][3])
                {
                  Serial.println("Card detected:");
                  for(s=0;s<4;s++)
                  {
                    Serial.print(mfrc522.uid.uidByte[s]);
                  }
                   Serial.print(" ");
                   Sending_To_db();
                   j=0;
                            
                            mfrc522.PICC_HaltA(); 
                            mfrc522.PCD_StopCrypto1();   
                            return; 
                }
              }
            }
          }
   else
   {j++;
    if(j==No_Of_Card)
    {
      Serial.println("Card detected:");
      for(s=0;s<4;s++)
        {
          Serial.print(mfrc522.uid.uidByte[s]);
        }
      Serial.print(" ");
      Sending_To_db();
      j=0;
    }
   }
  }
  
     // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}

void Sending_To_db()  
 {
    if(j!=No_Of_Card)
    {
      Serial.print('1');
      Serial.print(" ");
      Serial.println();
      Serial.print("Valid Card");
      Serial.println();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Authenticating..");
      lcd.setCursor(0,1);
      lcd.print("Valid Card");
      delay(1000);
      lcd.clear();
    }
    else
    {
      Serial.print('0');
      Serial.print(" ");
      Serial.println();
      Serial.print("Unknown/Invalid card");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Unknown card..");
      lcd.setCursor(0,1);
      lcd.print("Invalid Card");
      delay(3000);
      lcd.clear();
    }
 }

void triggerKeypad()
{
  //customKey = customKeypad.getKey();
  switch(customKey) 
  {   
  case '1': 
    Serial.print("Tabgi-Baclayon");
    Serial.println();
   // Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Baclayon");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(2000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '2': 
    Serial.print("Tagbi-Albur");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Albur");
    Serial.print("Fare: 25php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 25php");
    delay(2000);
    lcd.clear();
    Payment = aBAL - 25;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '3': 
    Serial.print("Tagbi-Loay");
    Serial.println();
   // Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Tagbi-Loay");
    Serial.print("Fare: 37php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 37php");
    delay(2000);
    lcd.clear();
    Payment = aBAL - 37;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case 'A': 
    Serial.print("Baclayon-Tagbi");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Baclayon-Tagbi");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(2000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '4': 
    Serial.print("Baclayon-Albur");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Baclayon-Albur");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '5': 
    Serial.print("Baclayon-Loay");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Baclayon-Loay");
    Serial.print("Fare: 25php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 25php");
    delay(4000);;
    lcd.clear();
    Payment = aBAL - 25;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break; 
    
  case '6': 
    Serial.print("Albur-Tagbi");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Albur-Tagbi");
    Serial.print("Fare: 25php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 25php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 25;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case 'B': 
    Serial.print("Albur-Baclayon");
    Serial.println();
   // Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Albur-Baclayon");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;   
  
  case '7': 
    Serial.print("Albur-Loay");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Albur-Loay");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break; 
    
  case '8': 
    Serial.print("Loay-Albur");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Loay-Albur");
    Serial.print("Fare: 15php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 15php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 15;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '9':  
    Serial.print("Loay-Baclayon");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Loay-Baclayon");
    Serial.print("Fare: 25php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 25php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 25;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
   
  case 'C':  
    Serial.print("Loay-Tagbilaran");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Loay-Tagbilaran");
    Serial.print("Fare: 37php");
    Serial.println();
    //Serial.print(" ");
    lcd.setCursor(0,1);
    lcd.print("Fare: 37php");
    delay(4000);
    lcd.clear();
    Payment = aBAL - 37;
    Serial.print("Balance is: ");
    Serial.print(Payment);
    Serial.println();
    Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Balance is: ");
    lcd.setCursor(0,1);
    lcd.print(Payment);
    Serial.print("Thanks!");
    //Serial.print(" ");
    lcd.setCursor(0,2);
    lcd.print("Thanks!");
    aBAL=Payment;
    delay(4000);
    lcd.clear();
    break;
    
  case '*':  
    Serial.print("Invalid");
    Serial.print("Set Route Again!");
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  case '0':  
    Serial.print("Invalid");
    Serial.print("Set Route Again!");
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  case '#':  
    Serial.print("Invalid");
    Serial.print("Set Route Again!");
    //Serial.print(" ");
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  case 'D': 
    Serial.print("Invalid");
    Serial.print("Set Route Again!");
    //Serial.print(" "); 
    lcd.setCursor(0,0);
    lcd.print("Invalid");
    lcd.setCursor(0,1);
    lcd.print("Set route again!");
    delay(4000);
    lcd.clear();
    break;
    
  }
}