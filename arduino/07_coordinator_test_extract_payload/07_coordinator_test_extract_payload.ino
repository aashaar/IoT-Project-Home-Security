byte RFin_bytes[19];
#define MAX_MILLIS_TO_WAIT 15000  //timeout
unsigned long starttime;
#define motion 0x4D 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  starttime = millis();
  while (Serial.available()) 
  {   
    byte startDelimiter = Serial.read();

    if (startDelimiter == 0x7E)
    {
      Serial.println("start of msg");
      while ( (Serial.available()<18)) // total message size is 19 byte. Since 1 byte is already read, we wait for rest 18 bytes
      {      
         // hang in this loop until we either get 18 bytes of data or 15 seconds(timeout)
      }
      if(Serial.available() < 18) 
      {
                 // if the data didn't come in - handle that problem here
           Serial.println("ERROR - Didn't get 18 bytes of data!");
      }
      else
      {
           RFin_bytes[0] = 0x7E;   // put first byte StartDelimiter already read
           for(int n=1; n<19; n++)
              RFin_bytes[n] = Serial.read(); // Then: Get them.
           
           // print entire payload
           /*  
           for(int n=0; n<19; n++)
           {
              Serial.print(n);
              Serial.print(" - ");
              Serial.println(RFin_bytes[n]);
           }
           Serial.println("===============");
           */

           if (RFin_bytes[15] == motion)
           {
              Serial.println("Motion detected");
           }
      } 
    }
  }
}
