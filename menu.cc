/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 3º
 * Práctica 1: Algoritmos de búsqueda. Búsquedas no informadas.
 * Autor: Gabriel Ángel Canals Salleras
 * Correo: alu0101460468@ull.edu.es
 * Fecha: 26/09/2023
 *
 * Archivo p06_automata_simulator.cc: implementación.
 * Contiene implementación de los métodos de las clases language, string, alphabet, symbol
 * para conseguir la obtención de la concatenación, unión, intersección, diferencia,
 * inversa y potencia de cada lenguaje dado, así como su alfabeto en caso de necesitarlo.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 * Historial de revisiones
 * 26/09/2023 - Creación (primera versión) del código
 */

#include "aux_functions.h"

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
    case '1':
      std::cout << "\nA* Search\n\n";
      StoreSearch(labyrinth, filename);
      return 0;
    case '2':
      std::cout << "\nSet Initial Node\n\n";
      labyrinth.ChangeNode(0);
      return 0;
    case '3':
      std::cout << "\nSet Final Node\n\n";
      labyrinth.ChangeNode(1);
      return 0;
    case '4':
      std::cout << "\nPrint Labyrinth\n\n";
      labyrinth.PrintLabyrinth();
      return 2;
    case '5':
      std::cout << "\nChange Input File\n\n";
      return 3;
    case '6':
      std::cout << "\nExit\n\n";
      return 1;
    default:
      std::cout << "\nInvalid option\n\n";
      return 0;
  }
}