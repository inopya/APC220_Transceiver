
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
  digitalWrite(SET, LOW);         // poner en modo configuracion
  delay(50);
  APCport.print("WR 415372 3 9 3 0");  //consultar el datasheet para detalle de los parametros
  APCport.write(0x0D); 
  APCport.write(0x0A);
  delay(100);
  digitalWrite(SET, HIGH);        // volver al modo normal
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
  APCport.write(0x0D);
  APCport.write(0x0A);
  delay(100);                     // pausa para estabilizar
  
  while (APCport.available()) {
    Serial.write(APCport.read()); 
  }
  digitalWrite(SET, HIGH);        // volver al modo normal
}


//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************
