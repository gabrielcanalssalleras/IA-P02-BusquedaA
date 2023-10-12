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
 * Archivo p06_automata_simulator.cc: implementación.
 * Contiene implementación de los métodos de la clase Graph.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 */

#include "cell.h"

Cell::Cell(int i_pos, int j_pos, int kind) 
  : i_pos_(i_pos), j_pos_(j_pos), kind_(kind) {}

std::string Cell::GetPosString() const {
  return "(" + std::to_string(i_pos_ + 1) +
         ", " + std::to_string(j_pos_ + 1) + ")";
}

void Cell::CalculateHeuristic(Cell end_node, bool diagonal) {
  h_value_ = (std::abs(i_pos_ - end_node.GetIPos()) + 
             std::abs(j_pos_ - end_node.GetJPos())) * 3;
  f_value_ = g_value_ + h_value_;
}

std::string Cell::PrintValues() const {
  return "f: " + std::to_string(f_value_) + ", g: " + std::to_string(g_value_)
          + ", h: " + std::to_string(h_value_);
}