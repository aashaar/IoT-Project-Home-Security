char dataString[50] = {0};
int a = 0;

void setup() {
  Serial.begin(9600);              //Starting serial communication
}

void loop() {
  if (a <= 10) {
    sprintf(dataString, "%02X", a);// convert a value to hexa
    Serial.println(dataString);// send the data
    manva();
    delay(1000);// give the loop some break
  }
  else {
    sprintf(dataString, "%02X", a);// convert a value to hexa
    Serial.println(dataString);// send the data
    aashaar();
    delay(1000);
  }
  a++;// a value increase every loop
}

void manva() {
  Serial.print("Manva");
}

void aashaar() {
  Serial.print("Aashaar");
}
