# Envio de señales infrarojas (STM32 Blue Pill)

En el proyecto se utiliza Arduino para poder codificar un transmisor y receptor a través de la comunicación infrarroja para controlar de forma remota la intensidad del LED.

Primero lee la entrada analógica de dos botones y un potenciómetro. Cuando presionamos el botón 1 en el transmisor entonces se envía el modo por infrarrojo al receptor. Al presionar el botón 2 el LED del receptor debe conmutar tres estados: apagado, prendido, control de la intensidad analógica, que son los modos con los que cuenta el transmisor. 

En la pantalla OLED del receptor se muestra el voltaje recibido por el transmisor. Este voltaje debe estar entre 0 y 3.3 V.

## Componentes

- Placa STM32 Blue Pill: Se utiliza la placa STM32 Blue Pill como microcontrolador principal.
- Pantalla OLED(SSD1306): Se emplea una pantalla OLED de 128x64 píxeles para mostrar información como el voltaje y el porcentaje de potencia.
- Emisor Infrarrojo: Se utiliza un emisor infrarrojo para enviar comandos a otro dispositivo.
- Potenciómetro: Se utiliza un potenciómetro para controlar la potencia del dispositivo.
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
   - Lectura del potenciómetro: Se lee el valor del potenciómetro analógico y se convierte a voltaje y porcentaje de potencia.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687414766/ui5uetjzstrbnyzc1zzn.png)
   
   - Actualización de la pantalla: Se muestra el voltaje y porcentaje de potencia en la pantalla OLED, así como el modo de funcionamiento actual.
   
   ![Image text](https://res.cloudinary.com/dmyp0t903/image/upload/v1687414852/yepduh5aspz9phnnoabs.png)
   
   - Lectura de los botones: Se lee el estado de los botones para detectar cambios.
   - Acciones de los botones:
     - Botón 1: Al presionar este botón, se envía el valor actual de la potencia por infrarrojo.
     - Botón 2: Al presionar este botón, se cambia el modo de funcionamiento (apagado, encendido o controlado).
   - Modo de funcionamiento: Según el modo actual, se ajusta la potencia del dispositivo controlado.
4. Funciones auxiliares:
   - `mandarValor()`: Esta función se ejecuta al presionar el botón 1 y envía el valor actual de la potencia por infrarrojo.
   - `conmutar()`: Esta función se ejecuta al presionar el botón 2 y cambia el modo de funcionamiento.
   - `sending()`: Esta función devuelve el valor a enviar por infrarrojo según el modo de funcionamiento actual.

## Uso

1. Conexiones: Asegúrese de conectar correctamente la pantalla OLED, el emisor infrarrojo y el potenciómetro a los pines correspondientes de la placa STM32 Blue Pill.
2. Carga del código: Cargue el código en su placa STM32 utilizando el entorno de desarrollo STM32CubeIDE o el entorno de desarrollo compatible de su elección.
3. Funcionamiento: Al encender la placa STM32 Blue Pill, la pantalla OLED mostrará el voltaje y porcentaje de potencia actuales. Utilice el potenciómetro para ajustar la potencia. Puede enviar el valor actual por infrarrojo presionando el botón 1 y cambiar el modo de funcionamiento presionando el