#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,1);
#include <avr/io.h>
#include <avr/interrupt.h>;
#define PWM 0
#define BUTTON A3
#define PWM_BRIGHTNESS 255
int buttonState = LOW;
int ledState = HIGH;
unsigned long prevDBT = 0;
unsigned long DBdelay = 50;
int counter = 0;
unsigned long currmil = millis();
unsigned long prevmil = 0;
const long rate = 500;

void setup()
{
  mySerial.begin(9600);
  cli();
  pinMode(PWM, OUTPUT);
  pinMode(BUTTON, INPUT);
  // digitalWrite(PWM, LOW)
  // attachInterrupt(digitalPinToInterrupt(BUTTON), loop, RISING);
 // attachInterrupt(BUTTON, loop, RISING);
  // GIMSK = 0b00100000;    // turns on pin change interrupts
  // PCMSK = 0b00010011;    // turn on interrupts on pins PB0, PB1, &amp;amp; PB4
  
  PCMSK |= (1 << PWM); //sbi(PCMSK,INTERRUPTPIN) also works but I think this is more clear // tell pin change mask to listen to pin2 /pb3 //SBI
//GIMSK |= (1 << PCIE);   // enable PCINT interrupt in the general interrupt mask //SBI
//
sei();
}

void loop()
{
  buttonState = digitalRead(BUTTON);
  if ( (millis() - prevDBT) > DBdelay) {
    if (buttonState == HIGH) {
      counter ++;
      switch(counter) {
        case 1:
        analogWrite(PWM, PWM_BRIGHTNESS);
        break;
      case 2:
        analogWrite(PWM, PWM_BRIGHTNESS/2);
         break;
      case 3:
        analogWrite(PWM, PWM_BRIGHTNESS/4);
       break;
      case 4:
        Blink();
        break;
      case 5:
        analogWrite(PWM, 0);
        counter = 0;
        break;
      }
    }
  }
}

void Blink(){
  if (currmil - prevmil >= rate) {
    prevmil = currmil;
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(PWM, ledState);
  }
}
