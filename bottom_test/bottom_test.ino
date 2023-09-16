void setup()
{
  pinMode(6, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int val = digitalRead(6);
  Serial.println(val);
  if (val == HIGH){
    digitalWrite(11,HIGH);
  }else{
    digitalWrite(11,LOW);
  }
}
