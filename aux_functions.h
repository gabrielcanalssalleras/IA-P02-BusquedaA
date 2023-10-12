/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Práctica 2: Búsqueda A*. Encuentra la salida del laberinto con el menor coste
 * Autor: Gabriel Ángel Canals Salleras
 * Correo: alu0101460468@ull.edu.es
 * Fecha: 12/10/2023
 *
 * Archivo aux_functions.h: declaración.
 * Contiene la declaración de las funciones auxiliares para el programa principal 
 * y de distintas constantes que se utilizarán a lo largo del programa.
 * Además, incluye las librerías necesarias para su correcto funcionamiento.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class Cell;
class Labyrinth;

#include "cell.h"

// Define un vector de celdas como CellVector
typedef std::vector<Cell> CellVector;

// Variable global para el modo debug
extern bool debug;
extern bool visual;

// Constantes para la impresión del laberinto
const std::string kBlueSquare = "\033[1;34m■\033[0m ";    // Closed node
const std::string kGreenSquare = "\033[1;32m■\033[0m ";   // Start node & path
const std::string kYellowSquare = "\033[1;33m■\033[0m ";  // Final node
const std::string kWhiteSquare = "\033[1;37m■\033[0m ";   // Free node
const std::string kBlackSquare = "\033[1;30m■\033[0m ";   // Wall
const std::string kMagentaSquare = "\033[1;35m■\033[0m "; // Open node

// Texto de ayuda
const std::string kHelpText = "./graph -- Search algorithms. A* Search. \n\
Usage: ./graph filein.txt \n\
\n\
filein.txt: File to read. \n\
\n\
This program reads a file, takes the representation of a labyrinth \n\
and performs a search on it from start to end (A* algorithm)\n";

// Declaración de la función de modo de uso
void Usage(int argc, char *argv[]);

// Menú de opciones
int Menu(Labyrinth& labyrinth, std::string& filename);

// Convierte un vector de celdas a un string
std::string VectorToString(CellVector vector);

// Comprueba si un nodo está disponible para transitar
bool IsNodeValid(int row, int col, Labyrinth& labyrinth);

// Realiza el flujo de salida que contiene la solución de la búsqueda
std::ofstream StoreSearch(Labyrinth& labyrinth, std::string& instance_name);

// Obtiene un número aleatorio entre un rango
int GetRandomNumber(int min, int max);

// Construye el camino de la solución a partir de los padres
CellVector ConstructPath(Cell current_node, Cell start_node,
                         std::vector<std::pair<Cell,Cell>> parents);