/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Date: 2016-04-26
 */

/*==================[inclusions]=============================================*/

#include "sapi.h"     // <= sAPI header
#include <stdlib.h>
#include <string.h>

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukas Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET.
int main(void){

	// ------------- INICIALIZACIONES -------------

	// Inicializar la placa
	boardConfig();

	// Inicializar UART_USB a 115200 baudios
	uartConfig( UART_USB, 115200 );

	uint8_t dato  = 0;
	uint8_t dato1 = 1;
	uint8_t dato2 = 78;
	int32_t dato3 = 1234;

	/* Buffer */
	static char uartBuff[10];

//	uartWriteByte( UART_USB, 'h' - 32 );   // Envia 'H'
//	uartWriteByte( UART_USB, 'A' + 32 );   // Envia 'a'
//
//	/* Enviar un Enter */
//	uartWriteByte( UART_USB, '\r' ); // Envia '\r', retorno de carro
//	uartWriteByte( UART_USB, '\n' ); // Envia '\n', nueva linea
//
//	uartWriteByte( UART_USB, dato1 + 48 ); // Envia '1'
//	uartWriteByte( UART_USB, ' ' );        // Envia ' '
//	uartWriteByte( UART_USB, '1' );        // Envia '1'
//	uartWriteByte( UART_USB, 32 );         // Envia ' '
//
//	// Convertir un numero entero de 2 di�gitos ASCII y enviar
//	uartWriteByte( UART_USB, (dato2/10) + 48 ); // Envia '7'
//	uartWriteByte( UART_USB, (dato2%10) + 48 ); // Envia '8'
//
//	uartWriteString( UART_USB, "\r\n" ); // Enviar un Enter
//
//	uartWriteByte( UART_USB, 'H' );  // Envia 'H'
//	uartWriteByte( UART_USB, 'o' );  // Envia 'o'
//	uartWriteByte( UART_USB, 'l' );  // Envia 'l'
//	uartWriteByte( UART_USB, 'a' );  // Envia 'a'
//	uartWriteByte( UART_USB, '\r' ); // Envia '\r', retorno de carro
//	uartWriteByte( UART_USB, '\n' ); // Envia '\n', nueva linea
//
//	uartWriteString( UART_USB, "Chau\r\n" ); // Envi�a "Chau\r\n"
//
//	char miTexto[] = "Hola de nuevo\r\n";
//
//	uartWriteString( UART_USB, miTexto ); // Envi�a "Hola de nuevo\r\n"
//
//	miTexto[0] = 'h';
//	uartWriteString( UART_USB, miTexto ); // Envia "hola de nuevo\r\n"
//
//	// Conversion de muestra entera a ascii con base decimal usando itoa()
//	itoa( dato3, uartBuff, 10 ); // base 10 significa decimal
//	uartWriteString( UART_USB, uartBuff );
//	uartWriteString( UART_USB, "\r\n" ); // Enviar un Enter
//	uartWriteString( UART_USB, "A ver que tiene un string sin inicializar\r\n" ); // Enviar un Enter

	uint8_t receiveByte= '*';  //Inicializo sin dato *
	float a, c;
	float b = 0.5;
	static char numero[5]="0.5";
	static char miBuffer[20];
   // ------------- REPETIR POR SIEMPRE -------------
	while(1) {
//

	static char uartBuffer[20];
	char * ptr;
	ptr = uartBuffer;
	while (receiveByte != 'g' ){//Verficar si el protocolo que tiene mi DeltaOhm termina con /n
		if (uartReadByte(UART_USB, &receiveByte) != 0){//Si hay datos sin leer en la FIFO, los leo
			//uartWriteByte( UART_USB, receiveByte);
			*ptr = receiveByte;
			ptr++;
			gpioWrite( LEDR,ON );
			//delay(1000);
		}
		//receiveByte = 'g';
		gpioWrite( LEDR,OFF );
	}
	gpioWrite( LEDG ,ON );
	//uartWriteString( UART_USB, uartBuffer );
	//uartWriteString( UART_USB, "string Ingresado\r\n" ); // Enviar un Enter
	//delay(1000);
//	//Este puntero a bytes  debe contener solo en numero por ejemplo 0.55, osea que si forma parte de una cadena hay
//	// que primero parcearlo en un string auxialiar los numero y el punto
	//a = atof( uartBuffer); //Convierto un string a float
	//c = a+b;
	//floatToString(c,miBuffer,4);
//	//floatToString(muestra,uartBuff,3);
//
//	/* Enviar muestra y Enter */
//	uartWriteString( UART_USB, miBuffer );
//	uartWriteString( UART_USB, "numero Sumado\r\n" );
	char 	delimitador = ' ';
	char *ptrDelimitador = &delimitador;
	char* token= "q";
	char* rest = uartBuffer;
	while ((token = strtok_r(rest, ptrDelimitador, &rest)) != 0){

	    	uartWriteString( UART_USB, token );
	    	uartWriteString( UART_USB, "\r\n" );

	}
	delay(1000);
	}
//	// Si recibe un byte de la UART_USB lo guardarlo en la variable dato.
//		if(  uartReadByte( UART_USB, &dato ) ){
//
//		//    		  *ptr =  dato;
//		//    		  ptr++;
//			  uartWriteByte( UART_USB, dato);
//	//
//	//	 // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
//	//
//	//
//		}

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
