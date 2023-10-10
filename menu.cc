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

#include "graph.h"

int Menu(Graph& graph) {
  std::cout << "Choose an option:\n";
  std::cout << "1. Breadth First Search\n";
  std::cout << "2. Depth First Search\n";
  std::cout << "3. Change Input File\n";
  std::cout << "4. Print Graph Edges\n";
  std::cout << "5. Exit\n";
  char option;
  std::cin >> option;
  switch (option) {
    case '1':
      std::cout << "Breadth First Search\n";
      BreadthFirstSearchMenu(graph);
      return 0;
    case '2':
      std::cout << "Depth First Search\n";
      DepthFirstSearchMenu(graph);
      return 0;
    case '3':
      std::cout << "Change input file\n";
      return 3;
    case '4':
      std::cout << "Print Graph Edges\n";
      graph.PrintGraph();
      return 2;
    case '5':
      std::cout << "Exit\n";
      return 1;
    default:
      std::cout << "Invalid option\n";
      return 0;
  }
}

inline bool ExistentNode(Graph& graph, int node) {
  if (!graph.NodeExists(node)) {
    std::cout << "The node does not exist\n";
    return false;
  }
  return true;
}

void BreadthFirstSearchMenu(Graph& graph) {
  std::cout << "Choose a node to start the search: ";
  int start_node;
  std::cin >> start_node;
  if (!ExistentNode(graph, start_node)) return;
  std::cout << "Choose a node to end the search: ";
  int end_node;
  std::cin >> end_node;
  if (!ExistentNode(graph, end_node)) return;
  StoreSearch(graph, start_node, end_node, false);
}

void DepthFirstSearchMenu(Graph& graph) {
  std::cout << "Choose a node to start the search: ";
  int start_node;
  std::cin >> start_node;
  if (!ExistentNode(graph, start_node)) return;
  std::cout << "Choose a node to end the search: ";
  int end_node;
  std::cin >> end_node;
  if (!ExistentNode(graph, end_node)) return;
  StoreSearch(graph, start_node, end_node, true);
}