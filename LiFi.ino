#define SAMPLE 90

bool newBit = 1;
bool oldBit = 1;

bool readBit();

void setup() {
  Serial.begin(2000000);
}

void loop() {
  newBit = readBit();

  if (!newBit && oldBit){
    int N = 0;
    delay(SAMPLE*1.5);
    
    for (int i =0; i<4; i++){
      //Serial.print(readBit());
      N |= readBit() << i;
      delay(SAMPLE);
    }

    if (N == 14) Serial.println("00");
    else if (N == 13) Serial.println("01");
    else if (N == 11) Serial.println("10");
    else if (N == 7) Serial.println("11");
    else Serial.println("??");
    
  }
  
  oldBit = newBit;
   
}

bool readBit(){

  // Set ADC A0
  __asm__ (
    "LDS  r24,    0x007A\n\t"
    "ORI  r24,    0xC7\n\t"
    "STS  0x007A, r24\n\t"
    "LDS  r24,    0x007C\n\t"
    "ANDI r24,    0xF0\n\t"
    "ORI  r24,    0x40\n\t"
    "STS  0x007C, r24");

  // Read ADC
  while( !(ADCSRA & (1<<ADIF)) );
  bool val = ADC > 900 ? true : false;

  // Clear ADC & return
  ADCSRA |= (1<<ADIF);
  return val;
}
