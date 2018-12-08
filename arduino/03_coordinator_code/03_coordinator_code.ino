 int ledPin = 13;
//String msg ="";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(ledPin, OUTPUT);
  if(Serial.available() > 0)
  {
    Serial.write(Serial.read());

//////
    //byte str = Serial.read();
    //Serial.write(str);
    //String myString = String(str);
    //Serial.println(str);
    //msg = msg + myString;
    //Serial.println(msg);

    
    /*int i = 0;
    for(i;i<str.length();i++)
    {
      Serial.println(i);
      Serial.print("\t");
      Serial.write(str.charAt(i),DEC);
    }
    Serial.println("============");
    */
    /*if(str.endsWith("hello world!"))
    {
      Serial.println("True");
      delay(50);
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
    }*/
//////
  }
}
