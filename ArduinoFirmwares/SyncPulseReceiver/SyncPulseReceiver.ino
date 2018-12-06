// Receive a sync pulse

void setup()
{
  pinMode(3, INPUT); // SYNC <- FROM SYNC ARDUINO

  Serial.begin(230400);
  
  attachInterrupt( digitalPinToInterrupt(3), sync_interrupt, RISING );
  
  Serial.print("SYNC receiver ON");
}

void sync_interrupt()
{
  Serial.write("Sync received\n");
}

void loop()
{  
    
}
