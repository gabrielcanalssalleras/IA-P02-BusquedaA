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
  Cell(int i_pos, int j_pos, int f_value, int g_value, int h_value, int kind);
  Cell();
  int GetIPos() const { return i_pos_; }
  int GetJPos() const { return j_pos_; }
  int GetKind() const { return kind_; }
  void SetKind(int kind) { kind_ = kind; }
  std::pair<int, int> GetPos() const { return std::make_pair(i_pos_, j_pos_); }
  std::string GetPosString() const;
  void SetFValue(int f_value) { f_value_ = f_value; }
  void SetGValue(int g_value) { g_value_ = g_value; }
  int GetFValue() const { return f_value_; }
  int GetGValue() const { return g_value_; }
  int GetHValue() const { return h_value_; }
  void CalculateHeuristic(Cell end_node, bool diagonal = 0);
  std::string PrintValues() const;
  bool operator==(const Cell& cell) const { return GetPos() == cell.GetPos(); }
  bool operator<(const Cell& cell) const { return GetFValue() < cell.GetFValue(); }
 private:
  int i_pos_, j_pos_, f_value_{0}, g_value_, h_value_;
  int kind_;
};

struct Instance {
  std::vector<Cell> path;
  std::vector<Cell> visited;
  std::vector<Cell> generated;
};

class Labyrinth : public Cell {
 public:
  Labyrinth(std::ifstream& input_file);
  void PrintLabyrinth();
  void PrintPath(std::vector<Cell> open_nodes, std::vector<Cell> closed_nodes, Cell current_node) const;
  void ChangeNode(bool final);
  Cell GetStartNode() const { return start_node_; }
  Cell GetEndNode() const { return end_node_; }
  Cell& Node(std::pair<int, int> pos) { return labyrinth_[pos.first][pos.second]; }
  int GetRows() const { return rows_; }
  int GetColumns() const { return columns_; }
  Instance AStarSearch() const;
  std::vector<std::vector<Cell>> GetLabyrinth() const { return labyrinth_; }
  std::vector<Cell> GetNeighbors(Cell node) const;
 private:
  std::vector<std::vector<Cell>> labyrinth_;
  int rows_;
  int columns_;
  Cell start_node_;
  Cell end_node_;
};