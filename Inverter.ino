#define clk PD2
#define dt PD4

uint16_t period = 30000;
bool state = 0;

void setup() {
  DDRD &= ~_BV(clk);
  PORTD |= _BV(clk);
  
  DDRD &= ~_BV(dt);
  PORTD |= _BV(dt);
  
  DDRD |= _BV(PB1);

  TCCR1A &= ~_BV(WGM10);
  TCCR1A &= ~_BV(WGM11);
  TCCR1A |= _BV(COM1A0);
  TCCR1A &= ~_BV(COM1A1);

  TCCR1B |= _BV(WGM12);
  TCCR1B &= ~_BV(WGM13);

  OCR1A = period;

  EICRA |= _BV(ISC01);
  EICRA &= ~_BV(ISC00);

  EIMSK |= _BV(INT0);

  sei();
}

void loop() {
}

ISR(INT0_vect){
  state = ((PIND & (1 << dt)) >> dt);
  if(state){
    period = period + 40;
    if(period > 65535){
      period = 65535;
    }
  }
  else{
    period = period - 40;
    if(period < 4){
      period = 4;
    }
  }
  OCR1A = period;
}
