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

    if (startDelimiter == 0x7E) //check for start delimiter of the API packet.
    {
      
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
         Serial.println("start of msg");
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
            activateCamera(); // function call to send API packet to camera's xbee
            Serial.println("Activation message sent to Camera");
         }
       } 
    }
  }
}


void activateCamera()
{
  Serial.write(0x7E); // start byte
  Serial.write((byte)0x00); //high part of length
  Serial.write(0x0F); //low part of length, the number of bytes that follow this line excluding Checksum
  Serial.write(0x10); // API frame type: Transmit Request
  Serial.write((byte)0x0); //frame id set to zero for no reply
  // Following 8 bytes are destination address - MAC address of Camera's receiver zigbee - 0013A200415B8CBA
  Serial.write(0x00);
  Serial.write(0x13);
  Serial.write(0xA2);
  Serial.write(0x00);
  Serial.write(0x41);
  Serial.write(0x5B);
  Serial.write(0x8C);
  Serial.write(0xBA);
  // destination address ends

  // Following 2 bytes are Network address - set to default values - 0xFF 0xFE
  Serial.write(0xFF); 
  Serial.write(0xFE);
  // network address ends

  Serial.write(0x00); //set broadcast radius to default 0
  Serial.write(0x00); // set options to default 0

  Serial.write(0x41); // Payload = "A" -> A denotes 'Activate camera'

  //checksum
  long checksum = 0x10 + 0x13 + 0xA2 + 0x41 + 0x5B + 0x8C + 0xBA + 0xFF + 0xFE + 0x41;
  checksum = 0xFF - (checksum & 0xFF);
  Serial.write(checksum); //write checksum to Serial  
}
