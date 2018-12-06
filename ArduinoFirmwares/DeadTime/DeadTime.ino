
volatile unsigned long trigger_time = 0;
volatile unsigned long trigger_time2 = 0;

void setup()
{
  Serial.begin(2000000);
}


void loop()
{
  trigger_time = micros(); // takes 4µs
  Serial.write((byte*)(trigger_time),4);
  trigger_time2 = micros(); // takes 4µs
  Serial.print("\n");
  Serial.print(trigger_time2-trigger_time);
  Serial.print("\n");
}
