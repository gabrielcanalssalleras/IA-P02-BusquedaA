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
 * Archivo cell.h: declaración de la clase Cell y su hija Labyrinth.
 * Contiene la declaración de los métodos de la clase Cell y Labyrinth,
 * así como el struct de la solución a la búsqueda.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#pragma once

#include "aux_functions.h"

// Clase Cell
class Cell {
 public:
  // Constructores
  Cell(int i_pos, int j_pos, int kind);
  Cell() = default; // Constructor por defecto
  
  // Getters
  int GetIPos() const { return i_pos_; }
  int GetJPos() const { return j_pos_; }
  int GetKind() const { return kind_; }
  std::pair<int, int> GetPos() const { return std::make_pair(i_pos_, j_pos_); }
  std::string GetPosString() const;
  int GetFValue() const { return f_value_; }
  int GetGValue() const { return g_value_; }
  int GetHValue() const { return h_value_; }
  
  // Imprime los valores de la celda
  std::string PrintValues() const;

  // Setters
  void SetKind(int kind) { kind_ = kind; }
  void SetGValue(int g_value) { g_value_ = g_value; }
  void SetFValue(int f_value) { f_value_ = f_value; }
  
  // Calcula la heurística de la celda durante la búsqueda
  void CalculateHeuristic(Cell end_node, bool diagonal = 0);

  // Comprueba si la celda es diagonal a otra
  bool IsDiagonal(Cell node, std::vector<std::vector<Cell>> labyrinth) const;
  
  // Sobrecarga de operadores
  bool operator==(const Cell& cell) const { return GetPos() == cell.GetPos(); }
  bool operator<(const Cell& cell) const { return GetFValue() < cell.GetFValue(); }
 
 private:
  // Atributos
  int i_pos_{0}, j_pos_{0}, kind_{0};
  // Coste acumulado g(n), heurística h(n) y total f(n)
  int f_value_{0}, g_value_{0}, h_value_{0}; 

  Cell* parent_;
};

// Define un vector de Cells como CellVector
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
  std::vector<CellVector> GetLabyrinth() const { return labyrinth_; } // Devuelve el laberinto
  
  // Obtiene los vecinos de un nodo
  CellVector GetNeighbors(Cell node) const;

  // Calcula los valores de un nodo
  void CalculateValues(Cell& node, Cell& current_node) const;

  // Accede a un nodo del laberinto por su posición
  Cell& Node(std::pair<int, int> pos) { return labyrinth_[pos.first][pos.second]; }

  // Búsqueda A*
  Instance AStarSearch() const;
 
 private:
  // Atributos
  std::vector<CellVector> labyrinth_;
  int rows_, columns_;
  Cell start_node_, end_node_;
};

// Funciones auxiliares que comprueban si un nodo está en un vector

// Comprueba si un nodo está en el vector de nodos abiertos
inline bool IsOpenNode(Cell node, CellVector open) {
  return std::find(open.begin(), open.end(), node) != open.end();
}

// Comprueba si un nodo está en el vector de nodos cerrados
inline bool IsClosedNode(Cell node, CellVector closed) {
  return std::find(closed.begin(), closed.end(), node) != closed.end();
}

// Comprueba si un nodo está en el vector del camino final
inline bool IsInPath(Cell node, CellVector path) {
  return std::find(path.begin(), path.end(), node) != path.end();
}