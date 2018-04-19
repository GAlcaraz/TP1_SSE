/*
 * tp1.c
 *
 *  Created on: Apr 19, 2018
 *      Author: galca
 */


#include "sapi.h"
#include "tp1.h"

#ifdef TP1_1

int main(void){
   boardConfig();
   while(1) {
      gpioWrite( LEDB, ON );
      delay(50);
      gpioWrite( LEDB, OFF );
      delay(50);
   }
   return 0 ;
}
#endif

#ifdef TP1_2

int main(void){
   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   bool_t valor;
   while(1) {

      valor = !gpioRead( TEC1 );
      gpioWrite( LEDB, valor );

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

      valor = !gpioRead( GPIO0 );
      gpioWrite( GPIO1, valor );
   }
	return 0 ;
}

#endif
