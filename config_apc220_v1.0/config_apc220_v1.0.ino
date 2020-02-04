
/*
  #       _\|/_   A ver..., ¿que tenemos por aqui?
  #       (O-O)        
  # ---oOO-(_)-OOo---------------------------------
   
   
  ##########################################################
  # ****************************************************** #
  # *            DOMOTICA PARA AFICIONADOS               * #
  # *     Configuracion del modulo RF433  APC220         * #
  # *          Autor:  Eulogio López Cayuela             * #
  # *                                                    * #
  # *       Versión v1.0      Fecha: 03/02/2020          * #
  # ****************************************************** #
  ##########################################################
*/

#define __VERSION__ "\Configuracion del modulo RF433  APC220 v1.0\n"

/*
  
 ===== NOTAS DE LA VERSION =====
 
 >> Cuando se lee la configuracion del modulo se obtiene un linea similar a esta (PARAM 415370 2 9 3 0 )

"PARAM AAAAAA B C D E"

	AAAAAA, es la frecuencia de trabajo del modulo expresada en KHz 
	Puede oscilar entre 418MHz y 455MHz
	- en el ejemplo 415.370 MHz 

	B, es la velocidad de transmision de radio frecuencia puede tomar los siguientes valores
	1 (2400bps), 2 (4800bps), 3 (9600bps), 4 (19200bps)
	- en el ejemplo 4800bps
	
	C, es la potencia de emision, puede tomar valores entre 0 y 9, siendo 9 la mayor potencia
	- en el ejemplo 9
	
	D, velodidad de transferencia entre el modulo y arduino o PC 	, toma valores entre 0 y 6
	0 (1200bps), 1 (2400bps), 2 (4800bps),3 (9600bps), 4 (19200bps), 5 (38400bps), 6 (57600bps)
	- en el ejemplo 9600bps
	
	E, es el control de paridad de la informacion emitida por RF
	0 (sin control de paridad), 1 (paridad par), 2 (paridad impar)
  - sin control de paridad

>> Para grabar informacion se ha de enviar una linea similar...
   WR 434000 3 9 3 0

  Esta configuracion seria: Frecuencia de emision 434MHz, velocidad RF 9600, 
  maxima potencia, Puerto serie 9600 y sin control de paridad
 
*/


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        IMPORTACION DE LIBRERIAS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#include <SoftwareSerial.h>



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DECLARACION DE CONSTANTES  Y  VARIABLES GLOBALES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

//------------------------------------------------------
//Definiciones para pines y variables
//------------------------------------------------------
#define SET      8
#define AUX      9
#define TXD     11
#define RXD     10
#define EN      12 
#define VCC     13
#define GND    GND

SoftwareSerial APCport(RXD, TXD);  //definimos el puerto serie Software para comunicar con el modulo RF



//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 
//***************************************************************************************************
//         FUNCION DE CONFIGURACION
//***************************************************************************************************
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 

void setup() 
{
  Serial.begin(9600);
  Serial.println(F(__VERSION__));
  
  APCport.begin(9600);  //iniciar el puerto serie software para comunicar con el APC220
  
  pinMode(SET,OUTPUT);
  pinMode(AUX,INPUT);
  pinMode(EN,OUTPUT);
  pinMode(VCC,OUTPUT);

  digitalWrite(SET,HIGH);
  digitalWrite(VCC,HIGH);
  digitalWrite(EN,HIGH);
  
  delay(1000);

  write_config();
  delay(1000);
  
  read_config();
  delay(5000);
}

  

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 
//***************************************************************************************************
//  BUCLE PRINCIPAL DEL PROGRAMA   (SISTEMA VEGETATIVO)
//***************************************************************************************************
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm 

void loop() 
{
  //no hacemos nada en esta seccion
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ###################################################################################################### 
        BLOQUE DE FUNCIONES: LECTURAS DE SENSORES, COMUNICACION SERIE, CONTROL LCD...
   ###################################################################################################### 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  ESCRIBIR CONFIGURACION
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void write_config()
{
  Serial.println(F("ESTABLECIENDO NUEVA CONFIGURACION...\n"));
  digitalWrite(SET, LOW);               // poner en modo configuracion
  delay(50);
  APCport.print("WR 415372 3 9 3 0");   // consultar el datasheet para detalle de los parametros
  APCport.write(0x0D);                  // fin de linea
  APCport.write(0x0A);                  // y retorno de carro. Similar a hacer un 'println', pero con println no funciona :(
  delay(100);
  digitalWrite(SET, HIGH);              // volver al modo normal
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  LEER CONFIGURACION
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void read_config() 
{
  Serial.println(F("CONFIGURACION ACTUAL:\n"));
  digitalWrite(SET, LOW);         // poner en modo configuracion
  delay(50);                      // pausa para estabilizar
  APCport.print("RD");            // peticion de datos
  APCport.write(0x0D);            // fin de linea
  APCport.write(0x0A);            // y retorno de carro. Similar a hacer un 'println', pero con println no funciona :(
  delay(100);                     // pausa para estabilizar
  
  while (APCport.available()) {
    Serial.write(APCport.read()); 
  }
  digitalWrite(SET, HIGH);        // volver al modo normal
}


//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************
