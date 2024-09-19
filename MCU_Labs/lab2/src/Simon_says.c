/*
	Marco Vasquez Ovares
	B17032
*/


// librerias
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Estados de la FSM

#define IDLE	0
#define	START	1
#define INITIAL	2
#define PLAY	3
#define CHECK	4
#define RESET	5

#define LVL		31 // restringido, por ejemplo 255 no funciona

/* prototipo de funciones */

void simon ();
void FSM ();
void delay (int);
void initalize_array ();

/*** global variables ***/

int inputs	[LVL];
int stage	[LVL];
int state;
int next_state = 0;
int button = 0;
int turn = 4;
int EN = 1;
int FLAG = 1;
int timer = 0;
int cooldown = 0;
int reuse = 0x400;
int null = 0;

/*****************************/
/*****************************/
int main(void)
{
	simon();
}
/*****************************/
/*****************************/

void simon(){
	
	/*** configuration registers ***/
	DDRB = 0x0F; // configuracion del puerto B, 0 es input / 1 es output
	
	/*** configuration interrupt ****/
	GIMSK = 0xF8; // habilitar interrupciones INT1, INT0, PCIE0, PCIE2, PCIE1
	//PCMSK0 = 0x80; // pin PCINT7 (PB7) -> habilitar irq PCIE0
	//PCMSK1 = 0x4; // pin PCINT10 (PA2) -> habilitar irq PCIE1
	//PCMSK2 = 0x01; // pin PCINT11 (PD0) -> habilitar irq PCIE2
	PCMSK = 0x80; // pin PCINT7 (PB7) -> habilitar irq PCIE0
	PCMSK1 = 0x4; // pin PCINT10 (PA2) -> habilitar irq PCIE1
	MCUCR = 0x0A; // sin restricciones de clock
	
	/*** configuration Timers ***/
	TCCR0A = 0x00; // modo normal
	TCCR0B = 0x03; // prescala con 64
	TCNT0  = 0x00; // Timer en 0	
	
	srand(null);
	initalize_array();
	
	sei(); // habilitar la interrupcion global
	
	state = IDLE;
	
	while(1){
		
		FSM ();
		
		}
	}
	
void FSM (){
	
	switch(state){
		
		case IDLE:	// estado de prueba
					PORTB = 0x01;		// red
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x02;		// blue
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x04;		// green
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x08;		// yellow
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x0F;		// all
					_delay_ms(50000); 
					PORTB = 0x00;
					_delay_ms(10000);
					
					state = START;
	  
		break;
		
		case START:
					if ( button != 0 ){
					state = INITIAL;
					button = 0;
					}
						
		break;  
		
		case INITIAL:
		
					PORTB = 0x0F;
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x0F;
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					state = PLAY;
					
		break;
		
		case PLAY:
					next_state =1, timer =0, FLAG =1;
					
					for (int i=0; i < turn; i++){
							
						switch(stage[i]){
							
							case 1:
									PORTB = 0x01;		// red
									delay(reuse);
									PORTB = 0x00;
									_delay_ms(2000);
							break;
							
							case 2:
									PORTB = 0x02;		// blue
									delay(reuse);
									PORTB = 0x00;
									_delay_ms(2000);;
							break;
							
							case 3:
									PORTB = 0x04;		// green
									delay(reuse);
									PORTB = 0x00;
									_delay_ms(2000);;
							break;
							
							case 4:
									PORTB = 0x08;		// yellow
									delay(reuse);
									PORTB = 0x00;
									_delay_ms(2000);;
							break;
							
							default:
									state = RESET;
							break;
							
							}
						}
						reuse -= 0x64;
					
					state = CHECK;
		break;
		
		case CHECK:
					if (timer == turn){
						for (int i=0; i < turn; i++){
							if (stage[i] != inputs[i]){
								next_state = 0;
								break;
									}
								}
								
								if (next_state == 0){
									state = RESET;
								}
								
								else{
									state = PLAY;
									timer = 0;
									turn++;
									}	
						}
					else {
							state = CHECK;
							null++;
						}
		break;
		
		case RESET:
					PORTB = 0x0F;
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x0F;
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					PORTB = 0x0F;
					_delay_ms(10000);
					PORTB = 0x00;
					_delay_ms(10000);
					
					button =0, timer =0, turn =4, FLAG =1, reuse =0x400;
					state = START;
					initalize_array();
					srand(null);
		break;
		
		default:
				state = IDLE;
		break;

		}
	}
	
void delay ( int overflows ){
	
	//int aux=0;
	EN = 0;
	cooldown = 0;
	TIMSK = 0x2;
	TCNT0 = 0x00;
	
	while (cooldown < overflows){
			PORTB &= 0xFF;
			//aux++;
		}
		
		EN = 1;
		TIMSK = 0x0;
	}
	
void initalize_array(){
	
	const int MIN_VAL = 1;
	const int MAX_VAL = 4;
	int prev = 0;
	
	//menset(inputs, 0, sizeof(inputs)); // no funciona
	
	for (int i=0; i < LVL; i++){
		inputs[i] = 0;
		int rng = prev;
		
		while (rng == prev){
			rng = (rand() % (MAX_VAL - MIN_VAL + 1)) + MIN_VAL;
		}
		
		stage[i] = rng;
		prev = rng;
		}
	}
	
/*** Interruptions ***/

ISR ( INT0_vect ) // pin PD2
{
	button = 0x1; // boton rojo
	
	if (next_state){
		inputs[timer] = button;
		timer++;
		}
}

ISR ( INT1_vect ) // pin PD3
{
	button = 0x2; // boton azul
	
	if (next_state){
		inputs[timer] = button;
		timer++;
		}
}

ISR ( PCINT_B_vect ) // pin PB7
{
	button = 0x3; // boton verde
	FLAG = ~FLAG;
	
	if (next_state == 1 && FLAG == 1){
		inputs[timer] = button;
		timer++;
		}
}

ISR ( PCINT_A_vect ) // pin PA2
{
	button = 0x4; // boton amarillo
	FLAG = ~FLAG; 
	
	if (next_state == 1 && FLAG == 1){
		inputs[timer] = button;
		timer++;
		}
}

ISR ( TIMER0_OVF_vect )
{
	if (~EN) {
		cooldown++;
		}
}


/*
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB = 0x08; //Configuracion del puerto

  //Parpadear
  while (1) {
    PORTB = 0x00; //PORTB &= ~(1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(500); 
    PORTB = 0x08; //PORTB |=  (1 << PB3); //Esto se puede hacer tambien asi
    _delay_ms(500); 
  }
}
*/
