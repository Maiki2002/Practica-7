# Envio de señales infrarojas (STM32 Blue Pill)

En el proyecto se utiliza Arduino para poder codificar un transmisor y receptor a través de la comunicación infrarroja para controlar de forma remota la intensidad del LED.

Primero lee la entrada analógica de dos botones y un potenciómetro. Cuando presionamos el botón 1 en el transmisor entonces se envía el modo por infrarrojo al receptor. Al presionar el botón 2 el LED del receptor debe conmutar tres estados: apagado, prendido, control de la intensidad analógica, que son los modos con los que cuenta el transmisor. 

En la pantalla OLED del receptor se muestra el voltaje recibido por el transmisor. Este voltaje debe estar entre 0 y 3.3 V.

## Componentes

- Placa STM32 Blue Pill: Se utiliza la placa STM32 Blue Pill como microcontrolador principal.
- Pantalla OLED(SSD1306): Se emplea una pantalla OLED de 128x64 píxeles para mostrar información como el voltaje y el porcentaje de potencia.
- Emisor Infrarrojo: Se utiliza un emisor infrarrojo para enviar comandos a otro dispositivo.
- Potenciómetro: Se utiliza un potenciómetro para controlar la potencia del led.
- Botones.
- Led.
- Resistencias.

## Funcionamiento (Transmisor)

1. Importacion de librerias, redefinición de macros y declaracion de funciones auxiliares: Se definen las configuraciones necesarias, como las dimensiones de la pantalla OLED, el protocolo infrarrojo utilizado, los pines de entrada/salida, las variables globales. A su vez, se declaran las funciones que nos ayudaran para el envio y el cambio de modo.

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687411819/onbwi3vxpw7dgu2bljtf.png)

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687412036/s579fqkkk0ypsfmxkkgz.png)

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687412471/aj5gx7i4ehbykupcinoj.png)

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687412907/jzjvoyn1ha8mgub3viv5.png)

2. Inicialización (setup): Se inicializan las librerías y se configuran los pines necesarios, incluyendo los pines de los botones, el LED y la comunicación con la pantalla OLED.

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687413188/udpukrhpn4zxjeezky3x.png)


3. Bucle principal(loop):
   - Lectura del potenciómetro: Se lee el valor del potenciómetro analógico y se convierte a voltaje y porcentaje de potencia. A su vez, si el modo es variable, el valor registrado por el potenciometro se mostrara mediante el led.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687414766/ui5uetjzstrbnyzc1zzn.png)
   
   - Actualización de la pantalla: Se muestra el voltaje y porcentaje de potencia en la pantalla OLED, así como el modo de funcionamiento actual.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687414852/yepduh5aspz9phnnoabs.png)
   
   - Lectura de los botones: Se lee el estado de los botones para detectar cambios.
   - Acciones de los botones:
     - Botón 1: Al presionar este botón, se envía el valor actual de la potencia por infrarrojo.
     - Botón 2: Al presionar este botón, se cambia el modo de funcionamiento (apagado, encendido o controlado).
   - Modo de funcionamiento: Según el modo actual, se ajusta la potencia del dispositivo controlado.
   
   ![Image text]( https://res.cloudinary.com/dmyp0t903/image/upload/v1687445663/t3onimg3gc6iaejjkmop.png)
   
   
4. Funciones auxiliares:
   - `mandarValor()`: Esta función se ejecuta al presionar el botón 1 y envía el modo actual del transmisor por infrarrojo. 
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687446246/r1a6dq04einccixuckpm.png)
   
   - `conmutar()`: Esta función se ejecuta al presionar el botón 2 y cambia el modo de funcionamiento del transmisor, simplemente incrementando el modo.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687446421/ycyfoopbc2n5o28ml2oe.png)
   
   
   - `sending()`: Esta función devuelve el valor a enviar por infrarrojo según el modo de funcionamiento actual.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687446500/bilxnscwncsscvuovcyn.png)

## Esquema electrico (Transmisor)


## Compilacion

Se recomienda trabajar con la extension de visual studio code platformio. Tambien es necesario tener las librerias necesarias para compilar un proyecto de ARM y para reconocer el STM32.

Solo basta con dar click para compilar el proyecto, en la palomita.
Para grabar el proyecto en el microcontrolador, basta con darle click en la flecha. Si todo esta bien, mandara un mensaje de "success" en la terminal.

![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687447280/ya6dchxmhrnejgfg87ql.png)

