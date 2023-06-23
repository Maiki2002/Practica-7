#Práctica
# Envio de señales infrarojas (STM32 Blue Pill) 

En el proyecto se utiliza Arduino para poder codificar un transmisor y receptor a través de la comunicación infrarroja para controlar de forma remota la intensidad del LED.

Primero lee la entrada analógica de dos botones y un potenciómetro. Cuando presionamos el botón 1 en el transmisor entonces se envía el modo por infrarrojo al receptor. Al presionar el botón 2 el LED del receptor debe conmutar tres estados: apagado, prendido, control de la intensidad analógica, que son los modos con los que cuenta el transmisor. 

En la pantalla OLED del receptor se muestra el voltaje recibido por el transmisor. Este voltaje debe estar entre 0 y 3.3 V.

## Dentro de este repositorio se encuentran las ramas Emisor, Receptor y complement, con los cuales fueron áreas de trabajo.
