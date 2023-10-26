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
 * Archivo labyrinth.h: declaración de la clase Labyrinth.
 * Contiene la declaración de los métodos de la Labyrinth,
 * así como el struct de la solución a la búsqueda.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#pragma once

#include "cell.h"

// Define un vector de celdas como CellVector
typedef std::vector<Cell> CellVector;

// Representa una solución de la búsqueda
struct Instance {
  CellVector path;      // Camino de la solución
  CellVector generated; // Nodos generados durante la búsqueda
  CellVector visited;   // Nodos visitados durante la búsqueda
};

// Clase Labyrinth (hereda de Cell)
class Labyrinth {
 public:
  // Constructores
  Labyrinth(std::ifstream& input_file);
  
  // Imprime el laberinto
  void PrintLabyrinth(CellVector open_nodes = {}, CellVector closed_nodes = {}, 
                      Cell current_node = Cell(), CellVector path = {}) const;

  // Cambia el nodo inicial o final para poder modificarlo manualmente
  void ChangeNode(bool final);
 
  // Getters
  Cell GetStartNode() const { return start_node_; }
  Cell GetEndNode() const { return end_node_; }
  int GetRows() const { return rows_; }
  int GetColumns() const { return columns_; }
  int GetChosenHeuristic() const { return chosen_heuristic_; }
  std::vector<CellVector> GetLabyrinth() const { return labyrinth_; } // Devuelve el laberinto
  
  // Obtiene los vecinos de un nodo
  CellVector GetNeighbors(Cell node) const;

  // Calcula los valores de un nodo
  void CalculateValues(Cell& node, Cell& current_node) const;

  // Accede a un nodo del laberinto por su posición
  Cell& Node(std::pair<int, int> pos) { return labyrinth_[pos.first][pos.second]; }

  // Allows to change the heuristic
  void ChangeHeuristic();

  // Búsqueda A*
  Instance AStarSearch() const;
 
  std::ofstream LabyrinthToFile (CellVector open_nodes, CellVector closed_nodes,
                               Cell current_node, CellVector path) const;

 private:
  // Atributos
  std::vector<CellVector> labyrinth_;
  int rows_, columns_;
  Cell start_node_, end_node_;
  int chosen_heuristic_{1};
};
