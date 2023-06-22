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


3. Bucle principal:
   - Lectura del potenciómetro: Se lee el valor del potenciómetro analógico y se convierte a voltaje y porcentaje de potencia.
   
   
   
   - Actualización de la pantalla: Se muestra el voltaje y porcentaje de potencia en la pantalla OLED, así como el modo de funcionamiento actual.
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



## Funcionamiento (Receptor) 
   1. Se define la configuracion de la pantalla Oled y de los pines.

<img width="491" alt="image" src="https://github.com/Maiki2002/Practica-7/assets/105370860/b83eb2dd-ac01-40bc-8aae-867fcda00cc8">

   2. Se incluyen todas las bibliotecas necesarias y se definen las variables globales.

<img width="680" alt="image" src="https://github.com/Maiki2002/Practica-7/assets/105370860/160a75ca-2497-44b3-8ca4-f01997c07e8d">

   3. `Void setup()`: Se hace la configuración para mostrar en la pantalla oled, asi como la configuración de entrada para el receptor y la inicialización de esta.

<img width="728" alt="image" src="https://github.com/Maiki2002/Practica-7/assets/105370860/c18000de-3a32-4998-a110-63d5422b2186">

   4. `Void loop()`: mediante la funcion `irmp_get_data` podemos saber si el receptor está recibiendo una señal infraroja, en caso de que cumpla la función, mostrará lo que está registrando. En caso contrario mostrará en el Oled que aún no está recibiendo la información. Cuando se esté recibiendo la señal infraroja se evaluará que stá recibiendo y dependiendo el valor hará una tarea específica de impresion en la oled.
En el segundo if dependiendo su valor, realizará una escritura para el led conectado a la Blue Pill, si es 0 se apagará el led, si es uno enciende un 100% y si es algun otro valor, encenderá según lo recibido por el emisor.

<img width="782" alt="image" src="https://github.com/Maiki2002/Practica-7/assets/105370860/abe0143f-d050-4e0d-89a1-0b64093a17b9">
<img width="770" alt="image" src="https://github.com/Maiki2002/Practica-7/assets/105370860/23457227-a90e-45f5-ac5a-5ad1f86321a5">

## Uso 
La placa Blue Pill tiene que estar ejecutando el programa, se debe verificar que el receptor infrarojo esté conectado y funcionando al recibir alguna señal asi como la pantalla Oled.

## Conexión
   - El led debe estar conectado a la bluepill en el pin PA1.
   - Los pines PA7 y PA6 debestar conectados en SDA(PA7) y SCL(PA6).
   - El emisor infrarojo debe star conectado en el pin PA6.

![P7_bb](https://github.com/Maiki2002/Practica-7/assets/105370860/db43c400-4668-4c2c-9411-9c363dc312a1)
