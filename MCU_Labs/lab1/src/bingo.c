/*
	Marco Vasquez Ovares
	B17032
*/

// encabezado pic12f683
#include <pic14/pic12f683.h>

typedef unsigned int word;

word __at 0x2007 __CONFIG = (_WDT_OFF & _MCLRE_OFF); // configuracion registro CONFIG

#define button GP3 
#define DELAY 1275

/* prototipo de funciones */

void bingo ();
int random ();
void delay (unsigned int time);

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
	//CMCON no se modifica ya que GP0, GP1 y GP2 son outputs
	ANSEL = 0x00;
	
	//unsigned int = ;
	
}

int random (){
	
	return 0; // check
}

void delay (unsigned int time){

	unsigned int i;
	unsigned int j;
	
	for(i=0; i<=time; i++)
		for(j=0; j<=DELAY; j++);
}

