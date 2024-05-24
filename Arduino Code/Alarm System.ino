#include <Keypad.h>

#define buzzer 8
#define trigPin 9
#define echoPin 10

long duration;
int distance, initialDistance, currentDistance, i;
int screenOffMsg =0;
String password="1234";
String tempPassword;
boolean activated = false; 
boolean isActivated;
boolean activateAlarm = false;
boolean alarmActivated = false;
boolean enteredPassword; 
boolean passChangeMode = false;
boolean passChanged = false;

const byte ROWS = 4; 
const byte COLS = 4; 
char keypressed;

char keyMap[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {14, 15, 16, 17}; 
byte colPins[COLS] = {18, 19, 20, 21}; 
Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS); 


void setup() { 
  pinMode(buzzer, OUTPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop() {
  if (activateAlarm) {
    
   
    int countdown = 9; 
    while (countdown != 0) {
      
      countdown--;
      tone(buzzer, 700, 100);
      delay(1000);
    }
    
    initialDistance = getDistance();
    activateAlarm = false;
    alarmActivated = true;
  }

  if (alarmActivated == true){
      currentDistance = getDistance() + 10;
      if ( currentDistance < initialDistance) {
        tone(buzzer, 2000); 
        
        enterPassword();
      }
    }

  if (!alarmActivated) {
    if (screenOffMsg == 0 ){
      
      screenOffMsg = 1;
    }
    keypressed = myKeypad.getKey();
     if (keypressed =='A'){        
      tone(buzzer, 1000, 200);
      activateAlarm = true;            
    }
    else if (keypressed =='B') {
      
      int i=1;
      tone(buzzer, 2000, 100);
      tempPassword = "";
      
      passChangeMode = true;
      passChanged = true;   
      while(passChanged) {      
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
         tempPassword += keypressed;
         
         i++;
         tone(buzzer, 2000, 100);
        }
      }
      if (i > 5 || keypressed == '#') {
        tempPassword = "";
        i=1;
       
      }
      if ( keypressed == '*') {
        i=1;
        tone(buzzer, 2000, 100);
        if (password == tempPassword) {
          tempPassword="";
          
          while(passChangeMode) {
            keypressed = myKeypad.getKey();
            if (keypressed != NO_KEY){
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9' ) {
                tempPassword += keypressed;
                
                i++;
                tone(buzzer, 2000, 100);
              }
            }
            if (i > 5 || keypressed == '#') {
              tempPassword = "";
              i=1;
              tone(buzzer, 2000, 100);
              
            }
            if ( keypressed == '*') {
              i=1;
              tone(buzzer, 2000, 100);
              password = tempPassword;
              passChangeMode = false;
              passChanged = false;
              screenOffMsg = 0;
            }            
          }
        }
      }
    }
   }
 }
}

void enterPassword() {
  int k=5;
  tempPassword = "";
  activated = true;
  
      while(activated) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;
         
          k++;
        }
      }
      if (k > 9 || keypressed == '#') {
        tempPassword = "";
        k=5;
       
      }
      if ( keypressed == '*') {
        if ( tempPassword == password ) {
          activated = false;
          alarmActivated = false;
          noTone(buzzer);
          screenOffMsg = 0; 
        }
        else if (tempPassword != password) {
         
          delay(2000);
          
        }
      }    
    }
}

long getDistance(){
  //int i=10;
  
  //while( i<=10 ) {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);


  distance = duration*0.034/2;
 
  return distance;

}
