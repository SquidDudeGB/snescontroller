// Global Pin Variables

// Digital Pin Numbers
#define DATA1_DPIN 2
#define CLOCK_DPIN 3
#define LATCH_DPIN 4

// Port Pin Numbers
#define DATA1_PIN 1
#define CLOCK_PIN 0
#define LATCH_PIN 4

#define WAIT_FALLING_EDGE(pin) while(!bitRead(PIND, pin) && true); while(bitRead(PIND, pin) && true);
#define WAIT_RISING_EDGE(pin) while(bitRead(PIND, pin) && true); while(!bitRead(PIND, pin) && true);

const word controlData = 0b1110010100100000; // L + Down-Right + Select + Y + B
                         //bysSUDLRaxlr0000

void setup() {
pinMode(DATA1_DPIN, OUTPUT);
pinMode(CLOCK_DPIN, INPUT);
pinMode(LATCH_DPIN, INPUT_PULLUP);
}

void loop() {
  noInterrupts();
  
  WAIT_FALLING_EDGE(LATCH_PIN);
  
  bool pressed = false;

  for(int8_t clocks = 0; clocks < 16; clocks++){
    int8_t btn = 0xF - clocks;

    
    pressed = controlData & (1 << btn);

    bitWrite(PORTD, DATA1_PIN, !(pressed && true));
    

    /* wait for console poll next button */
    WAIT_RISING_EDGE(CLOCK_PIN);
  }
  
  interrupts();
}
