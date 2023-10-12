# PRÁCTICA 2 INTELIGENCIA ARTIFICIAL

## BÚSQUEDA A*. ENCUENTRA LA SALIDA DEL LABERINTO CON EL MENOR COSTE

### GABRIEL ÁNGEL CANALS SALLERAS

## COMPILACIÓN Y EJECUCIÓN

Para compilar el programa se debe ejecutar el siguiente comando en la terminal: 

`make -B`

Seguidamente debe ser ejecutado bajo el nombre "labyrinth" y adjuntando el archivo de entrada deseado con la extensión ".txt":

`./labyrinth <archivo_entrada>.txt`

Se desplegará en la consola un menú con las opciones disponibles para la ejecución del programa:

``` 
1. A* Search
2. Set Initial Node
3. Set Final Node
4. Print Labyrinth
5. Change Input File
6. Exit
```
## MENÚ DE OPCIONES

### 1. A* Search

Esta opción ejecuta el algoritmo de búsqueda A* sobre el laberinto de entrada. El algoritmo imprimirá en el fichero "busquedas.md" la instancia de esta búsqueda con los siguientes datos:

| Instancia | n | m | S | E | Camino | Coste | Nodos Generados | Nodos inspeccionados |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |

### 2. Set Initial Node

Esta opción solicita por consola el nodo inicial del laberinto. El nodo inicial debe ser un número entero entre 1 y n, donde n es el número de nodos del laberinto. El programa imprimirá la coordenada del nodo inicial seleccionado. En caso de que el nodo inicial no sea válido, el programa imprimirá un mensaje de error y se mantendrá el nodo inicial anterior.

Importante: El que fuera nodo inicial anterior no se elimina del laberinto, sino que se convierte en un muro.

### 3. Set Final Node

Esta opción solicita por consola el nodo final del laberinto. El nodo final debe ser un número entero entre 1 y n, donde n es el número de nodos del laberinto. El programa imprimirá la coordenada del nodo final seleccionado. En caso de que el nodo final no sea válido, el programa imprimirá un mensaje de error y se mantendrá el nodo final anterior.

Importante: El que fuera nodo final anterior no se elimina del laberinto, sino que se convierte en un muro.

### 4. Print Labyrinth

Esta opción imprime en consola el laberinto representando cada nodo mediante el carácter '■'. Cada nodo tendrá un color asociado dependiendo de su estado:

- Nodo inicial: Verde
- Nodo final: Amarillo
- Nodos cerrados: Azul
- Nodos abiertos: Magenta
- Muros: Negro
- Nodos libres: Blanco

En caso de utilizar el modo visual se utilizarán números para representar los nodos:
  
- 0 - Nodo libre.
- 1 - Muro.
- 3 - Nodo inicial.
- 4 - Nodo final.

### 5. Change Input File

Esta opción permite cambiar el fichero de entrada sobre el que se lee el laberinto. El fichero tendrá que ser en formato ".txt". En caso de que no sea un fichero válido, se seguirá ejecutando el programa sobre el fichero inicial.

### 6. Exit

Esta opción finaliza la ejecución del programa.

## CORRECTA VISUALIZACIÓN DE LOS RESULTADOS

Para la ejecución y correcta visualización de los resultados del programa es necesario utilizar un visualizador de Markdown como la página web [Markdown Live Preview](https://markdownlivepreview.com/) o alguna extensión de Markdown para Visual Studio Code como [Markdown Preview Enhanced](https://marketplace.visualstudio.com/items?itemName=shd101wyy.markdown-preview-enhanced).

En caso de no utilizar un visualizador de Markdown, los resultados se verán de la siguiente forma:

| Instancia \| n | m | S | E | Camino | Coste | Nodos Generados | Nodos inspeccionados |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| m1 | 11 | 10 | (5, 1) | (2, 3) | (5, 1)-(4, 2)-(3, 3)-(2, 3) | 19 | (5, 1)-(4, 2)-(3, 3)-(2, 3) | (5, 1)-(4, 2)-(5, 2)-(6, 2)-(3, 2)-(3, 3)-(4, 3)-(5, 3)-(2, 2)-(2, 3) | 

Para reinicializar el fichero de resultados, se debe ejecutar el siguiente comando en la terminal:

`make blank`

## MODOS DE EJECUCIÓN ALTERNATIVOS

### MODO DEBUG

Para ejecutar el programa en modo debug se debe ejecutar el siguiente comando en la terminal:

`./labyrinth <archivo_entrada>.txt -d`

En este modo, cuando se ejecuta el algoritmo de búsqueda A*, se imprime en consola el laberinto en cada iteración del algoritmo. No compatible con el modo visual.

### MODO VISUAL

Para ejecutar el programa en modo visual se debe ejecutar el siguiente comando en la terminal:

`./labyrinth <archivo_entrada>.txt -v`

En este modo, el laberinto se imprime en consola utilizando números para representar los nodos en lugar de cuadrados de colores. No compatible con el modo debug.