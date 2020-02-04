# APC220_Transceiver
***Utilidad para configurar el APC220 desde Arduino / linux***

Recordad que hasta una proxima version en al que trataré de hacer 
que la grabacion y lectura de configuracion en el modulo sea 
algo mas interactiva, por ahora debemos modificar el programa 
de arduino para despues conectar el modulo y que se cargen los valores

Consejos, que no obligaciones.
1. Grabar el programa en arduino sin tener el modulo conectado.
2. Desconectar Arduino del USB de programacion y/o de cualquier otra fuente de alimentacion
3. Conectar el modulo como se indica en la fotografia (es la manera mas comoda)
   o bien mediante cables dupont.
4. Volver a conectar Arduino al ordenador apra que se produzca la grabacion de la configuracion o para leer la que contiene   
   
#### Guia de conexion del APC220 directamente sobre Arduino
![](./imagenes/pics/conexionApc220.jpg)

en la fotografia y marcados en rojo esta la distribucion fisica de pines del APC220
Haremos coincidir el pin GND del modulo con el propio de la tarjeta Arduino UNO
y el resto coindiriran con pines digitales tal como se indica.

		####ARDUINO     APC220
		GND         GND
		13	--->	VCC
		12	--->	EN
		11	--->	RXD
		10	--->	TXD
		 9	--->	AUX
		 8	--->	SET

Notad que al definir las funciones de los pines en el esketch de arduino al pin 11 ---> se le asigna la funcion TXD
y al pin 10 ---> la funcion RXD, dado que dichos pines han de estar intercambiados entre el puerto serie de Arduino y el del módulo

Segun el datasheet del fabricante el modulo consume como maximo unos 35mA (y eso seria emitiendo)
Puesto que vamos a trabajar con el sin emitir nada, solo configurandolo, 
podemos asumir sin temor a equivocarnos que un pin de arduino que puede entregar hasta 40mA
será suficiente para limentarlo.
Aprovechamos esto para poder conectar el modulo directamente en los pines de arduino sin necesidad
de cableado y programar un pin digital (en nuestro caso D13) como salida Activa que hara las veces de Vcc para el modulo