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
#include "labyrinth.h"

/**
 * @brief Construye un nuevo objeto Labyrinth:: Labyrinth
 * 
 * @param input_file: fichero de entrada
 */
Labyrinth::Labyrinth(std::ifstream& input_file) {
  std::string line;
  std::getline(input_file, line);                      // La primera línea contiene el número de filas
  rows_ = std::stoi(line);
  std::getline(input_file, line);                      // La segunda línea contiene el número de columnas
  columns_ = std::stoi(line);
  for (int i = 0; i < rows_; i++) {   
    CellVector row;
    std::getline(input_file, line);
    for (int j = 0, k = 0; j < columns_; j++, k++) {   // Se lee el laberinto
      if (line[k] == '3') {start_node_ = Cell(i, j, 3);} // El nodo inicial se representa con un 3
      if (line[k] == '4') end_node_ = Cell(i, j, 4);   // El nodo final se representa con un 4
      row.push_back(Cell(i, j, line[k++] - '0'));      // El resto de nodos se representan con un 0 o un 1
    }
    labyrinth_.push_back(row);                         // Se añade la fila al laberinto
  }
}

std::ofstream Labyrinth::LabyrinthToFile (CellVector open_nodes, CellVector closed_nodes,
                               Cell current_node, CellVector path) const {
  std::ofstream output_file;
  output_file.open("laberintos_solucionados.txt", std::ios_base::app);
  for (std::vector<Cell> row : labyrinth_) {
    for (Cell cell : row) {
        // si está en el path imprimir un 2
        if (std::find(path.begin(), path.end(), cell) == path.end())
        output_file << cell.GetKind() << " ";
        else output_file << "2 ";
    }
    output_file << "\n";
  }
  output_file << "\n\n";

  return output_file;
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
      if (visual) {
        // si está en el path imprimir un 2
        if (std::find(path.begin(), path.end(), cell) == path.end())
        std::cout << cell.GetKind() << " ";
        else std::cout << "2 ";

      }         // En el modo visual el laberinto se representa con números
      else {
        if (cell.GetKind() == 1) std::cout << kBlackSquare;   // Muro = Cuadrado negro
        if (cell.GetKind() == 3) std::cout << kGreenSquare;   // Nodo inicial = Cuadrado verde
        if (cell.GetKind() == 4) std::cout << kYellowSquare;  // Nodo final = Cuadrado amarillo
        if (cell.GetKind() == 0) { 
          if (IsClosedNode(cell, closed_nodes))
            if (cell == current_node || IsInPath(cell, path)) 
              std::cout << kGreenSquare;                      // Nodo parte del camino final = Cuadrado verde
            else std::cout << kBlueSquare;                    // Nodo cerrado = Cuadrado azul
          else if (!open_nodes.empty() && IsOpenNode(cell, open_nodes)) 
            std::cout << kMagentaSquare;                      // Nodo abierto = Cuadrado magenta
          else std::cout << kWhiteSquare;                     // Nodo no generado = Cuadrado blanco
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
  // Se comprueba que el nodo esté dentro del laberinto
  if (i_pos < 0 || i_pos > rows_ - 1 || j_pos < 0 || j_pos > columns_ - 1) {  
    std::cerr << "The node is out of bounds. No changes applied.\n";
    return;
  }
  if (final) {
    std::pair<int, int> end_pos = end_node_.GetPos();   // El nodo final se convierte en un muro
    Node(end_pos).SetKind(1);
    labyrinth_[i_pos][j_pos] = Cell(i_pos, j_pos, 4);
    end_node_ = Cell(i_pos, j_pos, 4);          // Se actualiza el nodo final
  } else {
    std::pair<int, int> start_pos = start_node_.GetPos();
    Node(start_pos).SetKind(1);                         // El nodo inicial se convierte en un muro
    labyrinth_[i_pos][j_pos] = Cell(i_pos, j_pos, 3);
    start_node_ = Cell(i_pos, j_pos, 3);        // Se actualiza el nodo inicial
  }
  std::cout << "The " << (final ? "final" : "initial") << " node has been set to"
            << " (" << i_pos << ", " << j_pos << ")\n"; // Se imprime el nodo modificado
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
  for (int di = -1; di <= 1; di++) {                // Se comprueban los 8 vecinos del nodo
    for (int dj = -1; dj <= 1; dj++) {
      if (di == 0 && dj == 0) continue;
      if (IsNodeValid(i + di, j + dj, labyrinth)) { // Si el nodo es válido, se añade al vector de vecinos
        neighbors.push_back(labyrinth_[i + di][j + dj]);
      } else {
        neighbors.push_back(Cell(-1, -1, 1));       // Si el nodo no es válido, se añade un nodo inválido (-1, -1)
      }
    }
  }
  return neighbors;
}

/**
 * @brief Allows to change the heuristic used in the search
 * 
 */
void Labyrinth::ChangeHeuristic() {
  std::cout << "Choose a heuristic:\n";
  std::cout << "1. Manhattan Distance\n";
  std::cout << "2. Diagonal Distance\n";
  std::cout << "3. Euclidian Distance\n";
  char option;
  std::cin >> option;
  switch (option) {
    case '1': // Distancia Manhattan
      chosen_heuristic_ = 1;
      break;
    case '2': // Distancia Diagonal
      chosen_heuristic_ = 2;
      break;
    case '3': // Distancia Euclidiana
      chosen_heuristic_ = 3;
      break;
    default: // Opción inválida
      std::cout << "\nInvalid option\n\n";
      break;
  }
}

/**
 * @brief Calcula los valores g, h y f de un nodo
 * 
 * @param node: nodo del que se quieren calcular los valores
 * @param current_node: nodo actual de la búsqueda
 */
void Labyrinth::CalculateValues(Cell& node, Cell& current_node) const {
  if (current_node.IsDiagonal(node, labyrinth_))        // Actualiza el valor g(n) del nodo:
    node.SetGValue(current_node.GetGValue() + 7);        // Si el nodo es diagonal, el coste es 7
  else node.SetGValue(current_node.GetGValue() + 5);      // Si el nodo es adyacente, el coste es 5
  node.CalculateHeuristic(GetEndNode(), GetChosenHeuristic());                // Se calcula la heurística del nodo h(n) y su f(n)
  node.SetFValue(node.GetGValue() + node.GetHValue());
}

// SortByFValue
/**
 * @brief Ordena un vector de nodos según su valor f(n)
 * 
 * @param nodes: vector de nodos a ordenar
 * @return CellVector con los nodos ordenados
 */
CellVector SortByFValue(CellVector nodes) {
  // sort by f(n) and if f(n) is equal, sort by the closest to the end node
  std::sort(nodes.begin(), nodes.end(), [](Cell a, Cell b) {
    return a.GetFValue() < b.GetFValue();
  });
  return nodes;
}


/** Obtiene un número aleatorio entre un rango.
 *  @param[in] min: Número mínimo
 *  @param[in] max: Número máximo
 *  @return Número aleatorio entre min y max
*/
int GetRandomNumber(CellVector nodes) {
  if (nodes.size() == 1) return 0;
  if (nodes.size() == 2) return rand() % 2;
  return rand() % 3;
}

/**
 * @brief Realiza una búsqueda A* sobre el laberinto
 * 
 * @return Instancia con la solución del laberinto
 */
Instance Labyrinth::AStarSearch() const {
  CellVector open_nodes{GetStartNode()}, closed_nodes, generated{GetStartNode()};
  Cell current_node = GetStartNode();
  std::vector<std::pair<Cell,Cell>> parents;                        // Vector de pares de nodos (hijo, padre)
  current_node.CalculateHeuristic(GetEndNode(), GetChosenHeuristic());  // Se calcula la heurística del nodo inicial y su f(n)
  current_node.SetFValue(current_node.GetGValue() + current_node.GetHValue());
  bool path_found = false, first = true;
  while (true) {                                                    // Mientras haya nodos abiertos y no se haya encontrado el camino
    if (open_nodes.empty()) return Instance{{}, generated, closed_nodes}; // Si no hay camino se devuelve una instancia vacía
    int random = GetRandomNumber(open_nodes);
    if (first) first = false;
    else {
      //std::cout << "random: " << random << "\n";
      current_node = open_nodes[random]; 
    }
    closed_nodes.push_back(current_node);                           // Se añade el nodo a los nodos cerrados
    // erase the current node from the open nodes
    open_nodes.erase(open_nodes.begin() + random);                           // Se elimina el nodo de los nodos abiertos
    if (current_node.GetKind() == 4) break;                         // Si el nodo es el nodo final, se ha encontrado el camino
    for (Cell neighbor : GetNeighbors(current_node)) {              // Por cada vecino del nodo
      if (InvalidNeighbor(neighbor, current_node, closed_nodes)) continue;
      if (!IsOpenNode(neighbor, open_nodes)) {                      // Si el nodo no está en los nodos abiertos
        CalculateValues(neighbor, current_node);                      // Se calculan los valores g, h y f del nodo
        //if (neighbor.GetGValue() > neighbor.GetHValue()) continue;
        open_nodes.push_back(neighbor);                               // Se añade el nodo a los nodos abiertos y a los nodos generados
        generated.push_back(neighbor);     
        parents.push_back(std::make_pair(neighbor, current_node));  // Se añade el par (hijo, padre) al vector de padres
      } else 
        UpdateIfBetter(neighbor, current_node, GetLabyrinth(), 
                                          parents, open_nodes); // Si el nodo está abierto, se actualiza en caso de ser mejor
    }
    if (!open_nodes.empty()) open_nodes = SortByFValue(open_nodes); // Reordena según f(n)
    if (debug) {                                                    // Si se está en modo debug
      PrintLabyrinth(open_nodes, closed_nodes, current_node);         // Se imprime el laberinto en cada iteración
      while (std::cin.get() != '\n');                                 // Se espera a que se pulse enter para continuar
    }
  }
  CellVector path = ConstructPath(current_node, GetStartNode(), parents);   // Se construye el camino
  PrintLabyrinth(open_nodes, closed_nodes, Cell(-1, -1, -1), path);         // Se imprime el laberinto final
  LabyrinthToFile(open_nodes, closed_nodes, Cell(-1, -1, -1), path);
  return Instance{path, generated, closed_nodes};                           // Se devuelve la instancia con la solución
}