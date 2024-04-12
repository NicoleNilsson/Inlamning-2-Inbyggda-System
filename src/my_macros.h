#ifndef __MY_MACROS_H
#define __MY_MACROS_H


#define BIT_SET(byte, nbit) ((byte) |= (1 << (nbit))) //set bit on byte as 1
#define BIT_CLEAR(byte ,nbit) ((byte) &= ~(1 << (nbit))) //set bit on byte as 0
#define BIT_CHECK(byte, nbit) ((byte) & (1 << (nbit))) //check if bit on byte is 1 
#define BIT_FLIP(byte, nbit) ((byte) ^= (1 << (nbit))) //flip all bits (so all 1 set as 0, all 0 set as 1)

//led macros
#define configOutput(byte, nbit) BIT_SET(byte, nbit)
#define LEDOn() BIT_SET(PORTx, nbit)
#define LEDOff() BIT_CLEAR(PORTx, nbit)

//timer macros
#define initiateTimer1() (TCCR1A = 0, TCCR1B = 0)
#define PRESCALE_TIMER1_256 BIT_SET(TCCR1B, CS12)

//timer interrupt macros
#define disableCompBInterrupt() BIT_CLEAR(TIMSK1, OCIE1B)
#define enableCompBInterrupt() BIT_SET(TIMSK1, OCIE1B)
#define COMPB_ENABLED BIT_CHECK(TIMSK1, OCIE1B)

#define enableCompAInterrupt() BIT_SET(TIMSK1, OCIE1A)

//ADC macros
#define startADCConversion() BIT_SET(ADCSRA, ADSC)
#define ADC_CONVERSION_IN_PROGRESS BIT_CHECK(ADCSRA, ADSC)

//uart macros
#define HAS_RECIEVED_CHAR (UCSR0A & (1 << RXC0))
#define REGISTER_EMPTY (UCSR0A & (1 << UDRE0))
#define SERIAL_8N1 0x06

#endif //__MY_MACROS_H