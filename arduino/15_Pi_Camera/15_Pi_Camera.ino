char result[10] ={0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    byte receivedMessage = Serial.read();
    
    if (receivedMessage == 0x41) // check for codeword "A"
    {
      Serial.println("A");
      delay(30000);
      Serial.println("D"); // codeword for Done (positive ack) to be sent to the coordinator.
    }
    
    /*else
    {
      Serial.write(receivedMessage);
      Serial.println("Some other message.");
    }
    */
    
  }

}
