# PRÁCTICA 1 INTELIGENCIA ARTIFICIAL

## BÚSQUEDAS NO INFORMADAS

### GABRIEL ÁNGEL CANALS SALLERAS

## COMPILACIÓN Y EJECUCIÓN

Para compilar el programa se debe ejecutar el siguiente comando en la terminal: 

`make -B`

Seguidamente debe ser ejecutado bajo el nombre "graph" y adjuntando el archivo de entrada deseado con la extensión ".txt":

`./graph <archivo_entrada>.txt`

Se desplegará en la consola un menú con las opciones disponibles para la ejecución del programa:

``` 
1. Breadth First Search
2. Depth First Search
3. Change Input File
4. Print Graph Edges
5. Exit 
```
## MENÚ DE OPCIONES

### 1. Breadth First Search

Esta opción ejecuta el algoritmo de búsqueda en anchura (BFS) sobre el grafo de entrada. El algoritmo solicita por consola como parámetros el nodo de origen y el nodo de destino, e imprimirá en el fichero "busquedas_amplitud" la instancia de esta búsqueda con los siguientes datos:

| Instancia | n | m | Vo | Vd | Camino | Distancia | Nodos Generados | Nodos inspeccionados |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |

### 2. Depth First Search

Esta opción ejecuta el algoritmo de búsqueda en profundidad (DFS) sobre el grafo de entrada. El algoritmo solicita por consola como parámetros el nodo de origen y el nodo de destino, e imprimirá en el fichero "busquedas_profundidad" la instancia de esta búsqueda con los siguientes datos:

| Instancia | n | m | Vo | Vd | Camino | Distancia | Nodos Generados | Nodos inspeccionados |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |

### 3. Change Input File

Esta opción permite cambiar el archivo de entrada por uno nuevo. El programa solicitará por consola el nombre del nuevo archivo de entrada y lo cargará en memoria.

### 4. Print Graph Edges

Esta opción imprime en consola los nodos y aristas del grafo de entrada de la siguiente forma:

`i: 1 j: 2 content: X` 

Donde "i" y "j" son los nodos y "content" es el contenido referente al coste de su arista. Content será -1 si no existe arista entre los nodos o 0 si i = j.

### 5. Exit

Esta opción finaliza la ejecución del programa.

## CORRECTA VISUALIZACIÓN DE LOS RESULTADOS

Para la ejecución y correcta visualización de los resultados del programa es necesario utilizar un visualizador de Markdown como la página web [Markdown Live Preview](https://markdownlivepreview.com/) o alguna extensión de Markdown para Visual Studio Code como [Markdown Preview Enhanced](https://marketplace.visualstudio.com/items?itemName=shd101wyy.markdown-preview-enhanced).

En caso de no utilizar un visualizador de Markdown, los resultados se verán de la siguiente forma:

| Instancia \| n | m | Vo | Vd | Camino | Distancia | Nodos Generados | Nodos inspeccionados |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| ID-10 | 5 | 3 | 1 | 5 | 1-2-5 | 3 | 1-2-5 | 1-2-5 |

Para reinicializar el fichero de resultados, se debe ejecutar el siguiente comando en la terminal:

`make blank`