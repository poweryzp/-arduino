const int buttonPin = 12;       //button pin number
const int ledPin =  13;         //LED pin number
int buttonState = 3;            //button state  1,2,3
unsigned long currentMillis;    //record the current time for blinking
long previousMillis = 0;        //store the last time LED was updated
long interval = 1000;           //interval at which to blink (milliseconds)
/////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);    
  digitalWrite(buttonPin, HIGH); //use internal pull up resistor
}////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
if (digitalRead(buttonPin) == LOW)   //Not pressed - HIGH; Pressed - LOW
   {  
    buttonState++;
}
    if (buttonState > 3) //button State from 1 to 3
    {
      buttonState = 1; 
    }  
    
    delay(450);             /////handle debouncing//////////////
   }// end if digitalRead(buttonPin)
///////////////////////////////////
if (buttonState==1)
  {
   digitalWrite(ledPin, HIGH); 
  }
if (buttonState==2)
  {
   currentMillis = millis();                          
   if (currentMillis - previousMillis > interval)    
     {
      previousMillis = currentMillis;   
      digitalWrite( ledPin, digitalRead( ledPin ) ^ 1 );   
     }
  }

if (buttonState==3)
  {
   digitalWrite(ledPin, LOW); 
  }
}
