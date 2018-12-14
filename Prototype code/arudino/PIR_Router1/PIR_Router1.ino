//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 1000; 
 
boolean lockLow = true;
boolean takeLowTime; 
 
int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
bool flag = true;
 
/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("sensor active");
    delay(50);
  }
 
////////////////////////////
//LOOP
void loop(){
     
     if(Serial.available()>0)
     {
        byte receivedMessage = Serial.read();
        
        Serial.println(receivedMessage);
        if (receivedMessage == 0x52) // check for codeword "R"
        {
          flag = true;
          Serial.println(flag);
        }
     }
     
     if(digitalRead(pirPin) == HIGH && flag == true){
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       //if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         //lockLow = false;    
         delay(1500); // delay to let communication between router & cooordinator 
         Serial.println("M"); // send codeword to Coordinator to indicate motion is detected
         flag = false;     
         //Serial.println("---");
         //Serial.print("motion detected at ");
         //Serial.print(millis()/1000);
         //Serial.println(" sec");
         delay(50);
         //}        
         //takeLowTime = true;
       }
 
     if(digitalRead(pirPin) == LOW){      
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
 
 }
}
