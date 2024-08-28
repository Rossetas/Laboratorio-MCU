/*
	Marco Vasquez Ovares
	B17032
*/

// encabezado pic12f683
#include <pic14/pic12f683.h>

typedef unsigned int word;

word __at 0x2007 __CONFIG = (_WDT_OFF & _MCLRE_OFF); // configuracion registro CONFIG

#define button GP3
#define EN_display GP5
#define DELAY 1275

/* prototipo de funciones */

void bingo ();
int random_displayA (unsigned int);
int random_displayB (unsigned int);
void delay (unsigned int);
void display_value (unsigned int, unsigned int);

/*****************************/
/*****************************/
void main ( void ) {

	bingo();
	
}
/*****************************/
/*****************************/

void bingo(){

	/* registers */
	TRISIO = 0x08;		// pin3 as input
	GPIO = 0x00;		// pines en bajo
	//GPIO = 0x06;		// pines en bajo, P5 = alto, P5 = EN
	//CMCON no se modifica ya que GP0, GP1 y GP2 son outputs
	ANSEL = 0x00;
	
	/* variables */
	unsigned int tiempo = 0;
	unsigned int random_x = 2; //  
	unsigned int random_y = 8; //   
	unsigned int display_A = 0x; // value display A
	unsigned int display_B = 0x; // value display B
	unsigned int times = 0; // contador del numero de veces que sale un numero (bola)
	unsigned int blink = 0; // contador interno para llevar los blinks
	
	
		while (1){
			
			if (button == 0){ // boton en estado estacionario
				
				}
				
			else if (button == 1){ // boton activado
				
				}
				
			else if (times == 11){ // condicion de reset in game
				
				times = 0; // reset times
				
				}
		
		}
	
}

/* generacion de numeros aleatorios */
int random_displayA (unsigned int random_x){
	
	return 0; // check
}

int random_displayB (unsigned int random_y){
	
	return 0; // check
}
/* ********************************* */

void delay (unsigned int tiempo){

	unsigned int i;
	unsigned int j;
	
	for(i=0; i<=tiempo; i++)
		for(j=0; j<=DELAY; j++);
}

void display_value (unsigned int value, unsigned int display){
	
	EN_display = display;
	
	if (value == 0){
		
		GP0 = 0;
		GP1 = 0;
		GP2 = 0;
		GP4 = 0;
		
		}
		
	else if (value == 1){
		
		GP0 = 1;
		GP1 = 0;
		GP2 = 0;
		GP4 = 0;
		
		}

	else if (value == 2){
		
		GP0 = 0;
		GP1 = 1;
		GP2 = 0;
		GP4 = 0;
		
		}
		
	else if (value == 3){
		
		GP0 = 1;
		GP1 = 1;
		GP2 = 0;
		GP4 = 0;
		
		}
		
	else if (value == 4){
		
		GP0 = 0;
		GP1 = 0;
		GP2 = 1;
		GP4 = 0;
		
		}
		
	else if (value == 5){
		
		GP0 = 1;
		GP1 = 0;
		GP2 = 1;
		GP4 = 0;
		
		}
		
	else if (value == 6){
		
		GP0 = 0;
		GP1 = 1;
		GP2 = 1;
		GP4 = 0;
		
		}
		
	else if (value == 7){
		
		GP0 = 1;
		GP1 = 1;
		GP2 = 1;
		GP4 = 0;
		
		}
		
	else if (value == 8){
		
		GP0 = 0;
		GP1 = 0;
		GP2 = 0;
		GP4 = 1;
		
		}
		
	else if (value == 9){
		
		GP0 = 1;
		GP1 = 0;
		GP2 = 0;
		GP4 = 1;
		
		}
	
	// adicionales
	
	// case default
	else if (value == 10){
		
		GP0 = 0;
		GP1 = 1;
		GP2 = 0;
		GP4 = 1;
		
		}
	
	// case display off (NAND + inv)	
	else if (value == 15){
		
		GP0 = 1;
		GP1 = 1;
		GP2 = 1;
		GP4 = 1;
		
		}
	
	}

