#include "fifo.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>


DEFINE_STATIC_FIFO(rx_fifo,256);

ISR(USART_RX_vect)
{
	uint8_t c;
	c = UDR0;
	fifo_put(&rx_fifo,c);
	if (fifo_check(&rx_fifo) > 25)
		PORTC&=~(1<<5);
}

int main(void) {

	PORTD=0x21;
	DDRD=0xe0;
	PORTC=0x21;
	DDRC=0x20;
	PORTB=0x00;
	DDRB=0x3f;

	UCSR0A =0;
	UCSR0B = (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
#define BAUD 50000
#include <util/setbaud.h>

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif

	sei();

	//esp throws random data on start
	_delay_ms(2000);
	fifo_clear(&rx_fifo);

	while(1)
	{
		intptr_t inbuff;
	    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			inbuff = fifo_check(&rx_fifo);
		}
		if (inbuff < 20)
		{
			PORTC|=(1<<5);
		}
		if (inbuff && (PINC & 0x01))
		{
			uint16_t REG;
			uint8_t ch;
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				fifo_get(&rx_fifo,&ch);
			}
			REG = (uint16_t)ch << 6;
			REG|= 1<<5;
			PORTB = REG >>8;
			PORTD = REG & 0xff;
			_delay_us(1);
			PORTD&=~(1<<5);
			_delay_us(1);
			PORTD|=(1<<5);
		}
	}
	return 0;
}
