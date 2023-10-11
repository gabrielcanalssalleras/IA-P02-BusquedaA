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

Cell::Cell(int i_pos, int j_pos, int f_value, int g_value, int h_value, int kind)
  : i_pos_(i_pos), j_pos_(j_pos), f_value_(f_value), 
  g_value_(g_value), h_value_(h_value), kind_(kind) {}

Cell::Cell() { 
  i_pos_ = 0;
  j_pos_ = 0;
  f_value_ = 0;
  g_value_ = 0;
  h_value_ = 0;
  kind_ = 0;
}

