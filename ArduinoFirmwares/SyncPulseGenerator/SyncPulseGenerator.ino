// Send a sync pulse to the other 8 Arduino boards when S is sent via serial from the PC
// The PC will send S after having turned on all the other ROA

char incomingByte = 0;

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  Serial.begin(230400);
}

void loop()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read(); // reading the character sent via serial
    if (incomingByte == 'S') // if the character is S, the sync is sent
    {
      PORTC = PORTC | 0b00001111; // clock pin HIGH
      delayMicroseconds(4);
      PORTC = PORTC & 0b11110000; // clock pin LOW
      Serial.print("SyncSent\n");
      digitalWrite(LED_BUILTIN, HIGH);   // builtin LED on
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);    // builtin LED off
    }
  }
}
