byte RFin_bytes[19];
#define MAX_MILLIS_TO_WAIT 10000  //or whatever
  byte startDelimiter = 126; //0x7E;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) 
  {   
    byte iByte = Serial.read();

    if (iByte == 0x7E)
    {
      Serial.println("start of msg");
      while ( (Serial.available()<18))
      {      
         // hang in this loop until we either get 18 bytes of data or 1 second
         // has gone by
      }
      if(Serial.available() < 18)
      {
                 // the data didn't come in - handle that problem here
           Serial.println("ERROR - Didn't get 18 bytes of data!");
      }
      else
      {
           RFin_bytes[0] = 0x7E;
           for(int n=1; n<19; n++)
              RFin_bytes[n] = Serial.read(); // Then: Get them.
    
           for(int n=0; n<19; n++)
           {
              Serial.print(n);
              Serial.print(" - ");
              Serial.println(RFin_bytes[n]);
           }
    
        Serial.println("===============");
      } 
    }
  }

  
  
  
}
