byte RFin_bytes[19];
#define MAX_MILLIS_TO_WAIT 15000  //timeout
unsigned long starttime;
#define motion 0x4D
#define positiveAck 0x44 
#define negativeAck 0x46 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  starttime = millis();
  delay(1000);
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
         Serial.println("error - Didn't get 18 bytes of data!");
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
            Serial.println("motion detected");
            activateLight(); // function call to send API packet to Light's xbee
            activateCamera(); // function call to send API packet to camera's xbee
            Serial.println("activation message sent to Camera");
         }
         else if (RFin_bytes[15] == positiveAck)
         {
            Serial.println("positive acknowledgement received from camera");
            deactivateLight(); // function call to turn off the light
            resumeSensing(); // function call to send packet to resume sensing
            Serial.println("resume sensing msg sent");
         }
         else if (RFin_bytes[15] == negativeAck)
         {
            Serial.println("********** error encountered in capturing image at camera. please check the camera. ************");
            deactivateLight(); // function call to turn off the light
            resumeSensing(); // function call to send packet to resume sensing
            Serial.println("resume sensing msg sent");
         }
       } 
    }
    /*
    else
      Serial.print("****************");
      Serial.println(startDelimiter);
      */
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

  //checksum - sum of everything that is non-zero after 'low part of length'
  long checksum = 0x10 + 0x13 + 0xA2 + 0x41 + 0x5B + 0x8C + 0xBA + 0xFF + 0xFE + 0x41;
  checksum = 0xFF - (checksum & 0xFF);
  Serial.write(checksum); //write checksum to Serial  
}

void resumeSensing()
{
  Serial.write(0x7E); // start byte
  Serial.write((byte)0x00); //high part of length
  Serial.write(0x0F); //low part of length, the number of bytes that follow this line excluding Checksum
  Serial.write(0x10); // API frame type: Transmit Request
  Serial.write((byte)0x0); //frame id set to zero for no reply
  // Following 8 bytes are destination address - MAC address of PIR Sensor's receiver zigbee - 0013A200410809D7
  Serial.write(0x00);
  Serial.write(0x13);
  Serial.write(0xA2);
  Serial.write(0x00);
  Serial.write(0x41);
  Serial.write(0x08);
  Serial.write(0x09);
  Serial.write(0xD7);
  // destination address ends

  // Following 2 bytes are Network address - set to default values - 0xFF 0xFE
  Serial.write(0xFF); 
  Serial.write(0xFE);
  // network address ends

  Serial.write(0x00); //set broadcast radius to default 0
  Serial.write(0x00); // set options to default 0

  Serial.write(0x52); // Payload = "R" -> A denotes 'Resume Sensing'

  //checksum - sum of everything that is non-zero after 'low part of length'
  long checksum = 0x10 + 0x13 + 0xA2 + 0x41 + 0x08 + 0x09 + 0xD7 + 0xFF + 0xFE + 0x52;
  checksum = 0xFF - (checksum & 0xFF);
  Serial.write(checksum); //write checksum to Serial
}

void activateLight()
{
  Serial.write(0x7E); // start byte
  Serial.write((byte)0x00); //high part of length
  Serial.write(0x10); //low part of length, the number of bytes that follow this line excluding Checksum
  Serial.write(0x17); // API frame type: Transmit Request
  Serial.write((byte)0x0); //frame id set to zero for no reply
  // Following 8 bytes are destination address - MAC address of PIR Sensor's receiver zigbee - 0013A200410809D7
  Serial.write(0x00);
  Serial.write(0x13);
  Serial.write(0xA2);
  Serial.write(0x00);
  Serial.write(0x41);
  Serial.write(0x08);
  Serial.write(0x09);
  Serial.write(0xDD);
  // destination address ends

  // Following 2 bytes are Network address - set to default values - 0xFF 0xFE
  Serial.write(0xFF); 
  Serial.write(0xFE);
  // network address ends

  Serial.write(0x02); //set remote command options to 02
  
  Serial.write(0xD3); // AT command - Pin D3

  Serial.write(0x5); // Parameter Value. (HIGH)
  
  //checksum - sum of everything that is non-zero after 'low part of length'
  long checksum = 0x17 + 0x13 + 0xA2 + 0x41 + 0x08 + 0x09 + 0xDD + 0xFF + 0xFE + 0x02 +0xD3 +0x5;
  checksum = 0xFF - (checksum & 0xFF);
  Serial.write(checksum); //write checksum to Serial
}


void deactivateLight()
{
  Serial.write(0x7E); // start byte
  Serial.write((byte)0x00); //high part of length
  Serial.write(0x10); //low part of length, the number of bytes that follow this line excluding Checksum
  Serial.write(0x17); // API frame type: Transmit Request
  Serial.write((byte)0x0); //frame id set to zero for no reply
  // Following 8 bytes are destination address - MAC address of PIR Sensor's receiver zigbee - 0013A200410809D7
  Serial.write(0x00);
  Serial.write(0x13);
  Serial.write(0xA2);
  Serial.write(0x00);
  Serial.write(0x41);
  Serial.write(0x08);
  Serial.write(0x09);
  Serial.write(0xDD);
  // destination address ends

  // Following 2 bytes are Network address - set to default values - 0xFF 0xFE
  Serial.write(0xFF); 
  Serial.write(0xFE);
  // network address ends

  Serial.write(0x02); //set remote command options to 02
  
  Serial.write(0xD3); // AT command - Pin D3

  Serial.write(0x4); // Parameter Value. (LOW)
  
  //checksum - sum of everything that is non-zero after 'low part of length'
  long checksum = 0x17 + 0x13 + 0xA2 + 0x41 + 0x08 + 0x09 + 0xDD + 0xFF + 0xFE + 0x02 +0xD3 +0x4;
  checksum = 0xFF - (checksum & 0xFF);
  Serial.write(checksum); //write checksum to Serial
}
