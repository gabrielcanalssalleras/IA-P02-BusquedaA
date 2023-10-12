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
 * Archivo menu.cc: implementación del menú del programa.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#include "aux_functions.h"

/**
 * @brief Imprime el menú y opera en torna a la opción escogida
 * 
 * @param labyrinth: laberinto sobre el que se opera
 * @param filename: nombre del fichero de entrada
 * @return int: 0 si se ha escogido una opción, 1 si se ha escogido salir
 */
int Menu(Labyrinth& labyrinth, std::string& filename) {
  std::cout << "Choose an option:\n";
  std::cout << "1. A* Search\n";
  std::cout << "2. Set Initial Node\n";
  std::cout << "3. Set Final Node\n";
  std::cout << "4. Print Labyrinth\n";
  std::cout << "5. Change Input File\n";
  std::cout << "6. Exit\n";
  char option;
  std::cin >> option;
  switch (option) {
    case '1': // Realizar búsqueda A*
      std::cout << "\nA* Search\n\n";
      StoreSearch(labyrinth, filename);
      return 0;
    case '2': // Cambiar nodo inicial
      std::cout << "\nSet Initial Node\n\n";
      labyrinth.ChangeNode(0);
      return 0;
    case '3': // Cambiar nodo final
      std::cout << "\nSet Final Node\n\n";
      labyrinth.ChangeNode(1);
      return 0;
    case '4': // Imprimir laberinto
      std::cout << "\nPrint Labyrinth\n\n";
      labyrinth.PrintLabyrinth();
      return 0;
    case '5': // Cambiar fichero de entrada
      std::cout << "\nChange Input File\n\n";
      return 3;
    case '6': // Salir
      std::cout << "\nExit\n\n";
      return 1;
    default: // Opción inválida
      std::cout << "\nInvalid option\n\n";
      return 0;
  }
}