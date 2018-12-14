// Read Out Arduino FW

/*
   FIXED OUTPUT LENGTH TO LET THE ARDUINO BE SYNCHRONIZED
   Baud rate 2Mbps
   1 byte arduino_ID
   2 byte evt counter
   24 bytes to send out data
   1 byte checksum
*/

const char* syncMessage = "Sync of all the Read-Out Arduinos"; // 33 characters => cannot be faked by the data stream, which is 28 bytes long

const byte arduino_identifier = 1; // assign a different ID to each of the arduino boards (from 1 to 8, even for wires+incl_strips and odd for strips)
volatile unsigned int evt_number = 0;
byte checksum = 0;

const byte header_len = 3;
const byte checksum_len = 1;

const byte n_of_boards = 6;
const byte n_of_SR = 4 * n_of_boards;
byte stored_data[n_of_SR];

unsigned char output[ header_len + n_of_SR + checksum_len ];

void setup()
{
  for (int i = 0; i < n_of_SR ; i++)
  {
    stored_data[i] = 0;
  }

  pinMode(2, INPUT); // TRIGGER <- FROM DIGIOR
  pinMode(3, INPUT); // SYNC <- FROM SYNC ARDUINO
  pinMode(4, OUTPUT); pinMode(5, OUTPUT); pinMode(6, OUTPUT); pinMode(7, OUTPUT); // CLOCK -> TO SRCLK
  pinMode(8, OUTPUT); pinMode(9, OUTPUT); pinMode(10, OUTPUT); pinMode(11, OUTPUT); pinMode(12, OUTPUT); // BUSY -> TO BUSY
  pinMode(13, OUTPUT); // BUILT-IN LED -> FLASHING WHEN TRIGGER IS RECEIVED
  pinMode(A0, INPUT); // INCOMING DATA <- FROM SROUT
  pinMode(A1, OUTPUT); // OUTGOING TEST DATA -> TO SRIN
  pinMode(A2, OUTPUT); // TEST EVEN -> TO TEST EVEN
  pinMode(A3, OUTPUT); // TEST ODD -> TO TEST ODD

  Serial.begin(2000000);

  attachInterrupt(digitalPinToInterrupt(3), sync_interrupt, RISING);
}

void  read_shift()
{
  byte stored = 0;
  for (int sr = n_of_SR - 1; sr >= 0 ; sr--)
  {
    for ( byte bn = 0 ; bn <= 7 ; bn ++)
    {
      stored = PINC & 0b00000001; // ok, because we the SROUT is on pin A0 (first bit in the byte)
      PORTD = PORTD | 0b11110000; // SRCLK HIGH
      stored_data[sr] = stored_data[sr] << 1 | stored; // ok, because we the SROUT is on pin A0 (first bit in the byte)
      PORTD = PORTD & 0b00001111; // SRCLK LOW
    }
  }
}

void sync_interrupt()
{
  evt_number = 0;
  Serial.println("");
  Serial.write(syncMessage);
  Serial.println("");
}

void loop()
{
  while ((PIND & 0b00000100) == 0b00000100) {} // DIGIOR is always HIGH. When a channel fires, it goes to LOW -> look for falling edge
  if ((PIND & 0b00001000) == 0b00001000)
  {
    PORTB = PORTB | 0b00011111; // BUSY HIGH
    delayMicroseconds(2); // 750ns
    PORTD = PORTD | 0b11110000; // SRCLK HIGH
    delayMicroseconds(2); // 750ns
    PORTD = PORTD & 0b00001111; // SRCLK LOW
    delayMicroseconds(2); // 750ns
    read_shift();
    PORTB = PORTB & 0b11100000; // BUSY LOW

    evt_number++;

    output[0] = (unsigned char) (arduino_identifier);
    output[1] = (unsigned char) (evt_number >> 8 & 0xff) ; // Most significant byte
    output[2] = (unsigned char) (evt_number & 0xff); // Less significant byte

    for (unsigned char i = 0; i < n_of_SR; i++)
    {
      output[header_len + i] = (unsigned char)(stored_data[i]);
    }

    checksum = 0;

    for (unsigned char i = 0; i < (header_len + n_of_SR); i++)
    {
      checksum ^= output[i];
    }
    output[header_len + n_of_SR + checksum_len - 1] = (unsigned char)(checksum);

    Serial.write(output, header_len + n_of_SR + checksum_len);
  }
}
