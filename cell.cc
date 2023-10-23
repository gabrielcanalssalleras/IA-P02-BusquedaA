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
 * Archivo cell.cc: implementación de la clase Cell.
 * Contiene la implementación de los métodos de la clase Cell.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#include "cell.h"

/**
 * @brief Construye un nuevo objeto Cell:: Cell
 * 
 * @param i_pos: posición i de la celda
 * @param j_pos: posición j de la celda
 * @param kind: tipo de celda (1 muro, 0 nodo libre, 3 nodo inicial o 4 nodo final)
 */
Cell::Cell(int i_pos, int j_pos, int kind) 
  : i_pos_(i_pos), j_pos_(j_pos), kind_(kind) {}

/**
 * @brief Devuelve la posición de la celda en forma de string
 * 
 * @return std::string con la posición de la celda
 */
std::string Cell::GetPosString() const {
  return "(" + std::to_string(i_pos_ + 1) +         // +1 para que empiece en 1
         ", " + std::to_string(j_pos_ + 1) + ")";   
}

/**
 * @brief Calcula la distancia euclídea entre dos celdas
 * 
 * @param x1: posición i de la primera celda
 * @param y1: posición j de la primera celda
 * @param x2: posición i de la segunda celda
 * @param y2: posición j de la segunda celda
 * @return int con la distancia euclídea entre las celdas
 */
int euclideanDistance(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

/**
 * @brief Calcula la distancia diagonal entre dos celdas
 * 
 * @param x1: posición i de la primera celda
 * @param y1: posición j de la primera celda
 * @param x2: posición i de la segunda celda
 * @param y2: posición j de la segunda celda
 * @return int con la distancia diagonal entre las celdas
 */
int diagonalDistance(int x1, int y1, int x2, int y2) {
int dx = std::abs(x2 - x1);
int dy = std::abs(y2 - y1);
int d_min = std::min(dx, dy);
return 10 * d_min + 5 * (dx + dy - 2 * d_min);
}

/**
 * @brief Calcula la heurística de la celda durante la búsqueda
 * 
 * @param end_node: último nodo del laberinto
 * @param diagonal: booleano que indica si se trata de un movimiento diagonal
 */
void Cell::CalculateHeuristic(Cell end_node, int chosen_heuristic) {
  switch (chosen_heuristic) {
  default: // Por defecto, se utiliza la distancia Manhattan
  case 1:  // Distancia Manhattan
    h_value_ = (std::abs(i_pos_ - end_node.GetIPos()) +  
               std::abs(j_pos_ - end_node.GetJPos())) * 3;
    break;
  case 2: // Distancia euclídea
    h_value_ = euclideanDistance(i_pos_, j_pos_, 
        end_node.GetIPos(), end_node.GetJPos());
    break;
  case 3: // Distancia Diagonal
    h_value_ = diagonalDistance(i_pos_, j_pos_, 
        end_node.GetIPos(), end_node.GetJPos());
    break;
  }
}


/**
 * @brief Impresión de los valores de la celda
 * 
 * @return std::string conteniendo los valores de la celda
 */
std::string Cell::PrintValues() const {
  return "f: " + std::to_string(f_value_) + ", g: " + std::to_string(g_value_)
          + ", h: " + std::to_string(h_value_);
}

/**
 * @brief Comprueba si los nodos están en diagonal
 * 
 * @param node: nodo con el que se compara
 * @param labyrinth: laberinto sobre el que se opera
 * @return true si los nodos están en diagonal, false en caso contrario
 */
bool Cell::IsDiagonal(Cell node, std::vector<std::vector<Cell>> labyrinth) const {
  std::pair<int, int> a_pos = GetPos();
  std::pair<int, int> b_pos = node.GetPos();
  int dx = std::abs(a_pos.first - b_pos.first);
  int dy = std::abs(a_pos.second - b_pos.second);
  return dx == 1 && dy == 1; // Si dx y dy son 1, los nodos están en diagonal
}