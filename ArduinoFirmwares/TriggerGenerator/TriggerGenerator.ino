// Send a sync pulse to the other 8 Arduino boards every 1 min

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  Serial.begin(230400);
  Serial.print("SYNC pulser ON");
}

void loop()
{
    PORTC = PORTC & 0b11110000; // clock pin HIGH
    Serial.write("Trig sent\n");
    delayMicroseconds(4);
    PORTC = PORTC | 0b00001111; // clock pin LOW
    delay(1000); // ms
}
