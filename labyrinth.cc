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
 * Archivo labyrinth.cc: implementación de la clase Labyrinth.
 * Contiene la implementación de los métodos de la clase Labyrinth.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */
#include "cell.h"

/**
 * @brief Construye un nuevo objeto Labyrinth:: Labyrinth
 * 
 * @param input_file: fichero de entrada
 */
Labyrinth::Labyrinth(std::ifstream& input_file) {
  std::string line;
  std::getline(input_file, line);
  rows_ = std::stoi(line);
  std::getline(input_file, line);
  columns_ = std::stoi(line);
  for (int i = 0; i < rows_; i++) {
    CellVector row;
    std::getline(input_file, line);
    for (int j = 0, k = 0; j < columns_; j++, k++) {
      if (line[k] == '3') start_node_ = Cell(i, j, 3);
      if (line[k] == '4') end_node_ = Cell(i, j, 4);
      row.push_back(Cell(i, j, line[k++] - '0'));
    }
    labyrinth_.push_back(row);
  }
}

/**
 * @brief Imprime el laberinto. Los muros se imprimirán en negro,
 *        los nodos libres en blanco, el nodo inicial en verde y
 *        el nodo final en amarillo. Los nodos se representan mediante
 *        el carácter '■'.
 * 
 * @param open_nodes: nodos abiertos. Se imprimirán en magenta
 * @param closed_nodes: nodos cerrados. Se imprimirán en azul
 * @param current_node: nodo actual. Se imprimirá en verde
 * @param path: camino encontrado. Se imprimirá en verde
 */
void Labyrinth::PrintLabyrinth(CellVector open_nodes, CellVector closed_nodes,
                               Cell current_node, CellVector path) const {
  for (std::vector<Cell> row : labyrinth_) {
    for (Cell cell : row) {
      if (visual) std::cout << cell.GetKind() << " ";
      else {
        if (cell.GetKind() == 1) std::cout << kBlackSquare;
        if (cell.GetKind() == 3) std::cout << kGreenSquare;
        if (cell.GetKind() == 4) std::cout << kYellowSquare;
        if (cell.GetKind() == 0) {
          if (IsClosedNode(cell, closed_nodes))
            if (cell == current_node || IsInPath(cell, path)) 
              std::cout << kGreenSquare;
            else std::cout << kBlueSquare;
          else if (!open_nodes.empty() && IsOpenNode(cell, open_nodes)) 
            std::cout << kMagentaSquare;
          else std::cout << kWhiteSquare;
        }
      }
    }
    std::cout << "\n";
  }
}

/**
 * @brief Cambia el nodo inicial o final para poder modificarlo manualmente
 * 
 * @param final: booleano que indica si se quiere cambiar el nodo final
 */
void Labyrinth::ChangeNode(bool final) {
  int i_pos, j_pos;
  std::cout << "Enter the row of the node: ";
  std::cin >> i_pos;
  std::cout << "Enter the column of the node: ";
  std::cin >> j_pos;
  if (i_pos < 1 || i_pos > rows_ || j_pos < 1 || j_pos > columns_) {
    std::cerr << "The node is out of bounds. No changes applied.\n";
    return;
  }
  if (final) {
    std::pair<int, int> end_pos = end_node_.GetPos();
    Node(end_pos).SetKind(1);
    labyrinth_[i_pos - 1][j_pos - 1] = Cell(i_pos - 1, j_pos - 1, 4);
    end_node_ = Cell(i_pos - 1, j_pos - 1, 4);
  } else {
    std::pair<int, int> start_pos = start_node_.GetPos();
    Node(start_pos).SetKind(1);
    labyrinth_[i_pos - 1][j_pos - 1] = Cell(i_pos - 1, j_pos - 1, 3);
    start_node_ = Cell(i_pos - 1, j_pos - 1, 3);
  }
  std::cout << "The " << (final ? "final" : "initial") << " node has been set to"
            << " (" << i_pos << ", " << j_pos << ")\n";
}

/**
 * @brief Obtiene los vecinos de un nodo
 * 
 * @param node: nodo del que se quieren obtener los vecinos
 * @return CellVector con los vecinos del nodo
 */
CellVector Labyrinth::GetNeighbors(Cell node) const {
  CellVector neighbors;
  std::pair<int, int> pos = node.GetPos();
  Labyrinth labyrinth = *this;
  int i = pos.first, j = pos.second;
  for (int di = -1; di <= 1; di++) {
    for (int dj = -1; dj <= 1; dj++) {
      if (di == 0 && dj == 0) continue;
      if (IsNodeValid(i + di, j + dj, labyrinth)) {
        neighbors.push_back(labyrinth_[i + di][j + dj]);
      } else {
        neighbors.push_back(Cell(-1, -1, 1));
      }
    }
  }
  return neighbors;
}

/**
 * @brief Realiza una búsqueda A* sobre el laberinto
 * 
 * @return Instancia con la solución del laberinto
 */
Instance Labyrinth::AStarSearch() const {
  CellVector open_nodes{GetStartNode()}, closed_nodes, generated{GetStartNode()};
  Cell current_node;
  std::vector<std::pair<Cell,Cell>> parents;
  current_node.CalculateHeuristic(GetEndNode());
  bool path_found = false;
  while (!open_nodes.empty() && !path_found) {
    current_node = open_nodes[0];
    closed_nodes.push_back(current_node);
    open_nodes.erase(open_nodes.begin());
    if (current_node.GetKind() == 4) path_found = true;
    CellVector neighbors = GetNeighbors(current_node);
    for (int i = 0; i < neighbors.size(); i++) {
      if (neighbors[i].GetPos() == std::make_pair(-1, -1)) continue;
      if (IsClosedNode(neighbors[i], closed_nodes)) continue;
      if (!IsOpenNode(neighbors[i], open_nodes)) {
        neighbors[i].CalculateHeuristic(GetEndNode());
        if (current_node.IsDiagonal(neighbors[i], labyrinth_)) 
          neighbors[i].SetGValue(current_node.GetGValue() + 7);
        else neighbors[i].SetGValue(current_node.GetGValue() + 5);
        open_nodes.push_back(neighbors[i]);
        generated.push_back(neighbors[i]);
        parents.push_back(std::make_pair(neighbors[i], current_node));
      }
    }
    if (!open_nodes.empty()) std::sort(open_nodes.begin(), open_nodes.end());
    if (debug) {
      PrintLabyrinth(open_nodes, closed_nodes, current_node);
      while (std::cin.get() != '\n');
    }
  }
  if (open_nodes.empty() && !path_found) return Instance{{}, generated, closed_nodes};
  CellVector path = ConstructPath(current_node, GetStartNode(), parents);
  PrintLabyrinth(open_nodes, closed_nodes, Cell(-1, -1, -1), path);
  return Instance{path, generated, closed_nodes};
}