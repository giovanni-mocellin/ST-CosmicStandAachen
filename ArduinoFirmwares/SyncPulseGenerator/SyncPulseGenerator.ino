// Send a sync pulse to the other 8 Arduino boards every 10 sec

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  Serial.begin(2000000);
  Serial.print("SYNC pulser ON\n");
}

void loop()
{
    PORTC = PORTC | 0b00001111; // clock pin HIGH
    Serial.write("Sync sent\n");
    delayMicroseconds(4);
    PORTC = PORTC & 0b11110000; // clock pin LOW
    delay(10000); // ms
}
