/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Inteligencia Artificial
 * Curso: 3º
 * Práctica 1: Algoritmos de búsqueda. Búsquedas no informadas.
 * Autor: Gabriel Ángel Canals Salleras
 * Correo: alu0101460468@ull.edu.es
 * Fecha: 26/09/2023
 *
 * Archivo graph.h: Fichero de cabecera principal.
 * Contiene las llamadas a las distintas librerías del lenguaje C++ y 
 * la declaración de la clase Graph. También contiene las declaraciones 
 * de algunas funciones auxiliares.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 * Historial de revisiones
 * 26/09/2023 - Creación (primera versión) del código
 */

#pragma once

#include "aux_functions.h"

class Cell {
 public:

  Cell(int i_pos, int j_pos, int kind);
  Cell() = default;

  int GetIPos() const { return i_pos_; }
  int GetJPos() const { return j_pos_; }
  int GetKind() const { return kind_; }
  std::pair<int, int> GetPos() const { return std::make_pair(i_pos_, j_pos_); }
  std::string GetPosString() const;
  int GetFValue() const { return f_value_; }
  int GetGValue() const { return g_value_; }
  int GetHValue() const { return h_value_; }
  
  std::string PrintValues() const;

  void SetKind(int kind) { kind_ = kind; }
  void SetGValue(int g_value) { g_value_ = g_value; }
  void SetFValue(int f_value) { f_value_ = f_value; }
  
  void CalculateHeuristic(Cell end_node, bool diagonal = 0);

  bool IsDiagonal(Cell node, std::vector<std::vector<Cell>> labyrinth) const;
  
  bool operator==(const Cell& cell) const { return GetPos() == cell.GetPos(); }
  bool operator<(const Cell& cell) const { return GetFValue() < cell.GetFValue(); }
 
 private:
 
  int i_pos_{0}, j_pos_{0}, kind_{0};
  int f_value_{0}, g_value_{0}, h_value_{0};
};

typedef std::vector<Cell> CellVector;

struct Instance {
  CellVector path;
  CellVector visited;
  CellVector generated;
};

class Labyrinth : public Cell {
 public:

  Labyrinth(std::ifstream& input_file);
 
  void PrintLabyrinth(CellVector open_nodes = {}, CellVector closed_nodes = {}, 
                      Cell current_node = Cell(), CellVector path = {}) const;
 
  void ChangeNode(bool final);
 
  Cell GetStartNode() const { return start_node_; }
  Cell GetEndNode() const { return end_node_; }
  Cell& Node(std::pair<int, int> pos) { return labyrinth_[pos.first][pos.second]; }
  int GetRows() const { return rows_; }
  int GetColumns() const { return columns_; }
  std::vector<CellVector> GetLabyrinth() const { return labyrinth_; }
  CellVector GetNeighbors(Cell node) const;

  Instance AStarSearch() const;
 
 private:
 
  std::vector<CellVector> labyrinth_;
  int rows_, columns_;
  Cell start_node_, end_node_;
};

inline bool IsOpenNode(Cell node, CellVector open) {
  return std::find(open.begin(), open.end(), node) != open.end();
}

inline bool IsClosedNode(Cell node, CellVector closed) {
  return std::find(closed.begin(), closed.end(), node) != closed.end();
}

inline bool IsInPath(Cell node, CellVector path) {
  return std::find(path.begin(), path.end(), node) != path.end();
}