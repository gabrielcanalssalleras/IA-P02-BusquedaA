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
 * Archivo aux_functions.cc: implementación.
 * Contiene implementación de las funciones auxiliares para el programa principal.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#include "aux_functions.h"
#include "cell.h"
#include "labyrinth.h"

// Variables globales para el modo debug y visual
bool debug;
bool visual;

/** Imprime el mensaje de ayuda para el usuario.
 *  En caso de uso incorrecto, imprime el mensaje y el programa finaliza.
 *  Este programa requiere un fichero de extensión txt para ejecutarse correctamente.
 *
 *  @param[in] argc: Número de parámetros en la linea de comandos
 *  @param[in] argv: Vector de parámetros en la linea de comandos
 */
void Usage(int argc, char *argv[]) {
  if (argc > 1) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {  // Texto de ayuda
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    }
    if (argc > 2) parameter = argv[2];
    if (parameter == "-d" || parameter == "--debug") { // Modo debug
      std::cout << "Debug mode activated\n";
      debug = true;
    }
    if (parameter == "-v" || parameter == "--visual") {  // Modo visual
      std::cout << "Visual mode activated\n";
      visual = true;
    }
  }
  if (argc < 2 || argc > 3) {  // Uso incorrecto
    std::cout << argv[0] << "-- Search algorithm. A* Search." << std::endl;
    std::cout << "Usage: input_file.txt\n";
    std::cout << "Try " << argv[0] << " --help for more information\n";
    exit(EXIT_SUCCESS);
  }
}

/** Convierte un vector de celdas en un string.
 *  @param[in] vector: Vector de celdas
 *  @return String conteniendo las celas del vector
*/
std::string VectorToString(CellVector vector) {
  std::string result;
  if (vector.size() == 0) return "No path";  // Si no hay camino
  for (int i = 0; i < vector.size(); i++) {
    result += vector[i].GetPosString();  // Añade la posición del nodo de la forma (x,y)
    if (i != vector.size() - 1) result += "-"; // Añade un guión entre nodos
  }
  return result;
}

/** Produce los resultados de la búsqueda y los almacena en un fichero en formato Markdown.
 *  @param[in] labyrinth: Laberinto sobre el que se realiza la búsqueda
 *  @param[in] instance_name: Nombre de la instancia
 *  @return Output file stream conteniendo los resultados de la búsqueda
*/
std::ofstream StoreSearch(Labyrinth& labyrinth, std::string& instance_name) {
  std::ofstream output_file;
  output_file.open("busquedas.md", std::ios_base::app);               // Abre el fichero en modo append
  if (output_file.tellp() == 0) {                                     // Si el fichero está vacío, añade la cabecera en Markdown
    output_file << "| Instancia | n | m | S | E |  Camino | ";
    output_file << "Coste | Nodos Generados | Nodos inspeccionados |\n"; 
    output_file << "| --- | --- | --- | --- | --- | --- | --- | --- | --- |\n";
  }
  std::string id = instance_name.substr(0, instance_name.size() - 4); // Elimina la extensión
  Instance table = labyrinth.AStarSearch();                           // Realiza la búsqueda
  std::string path = VectorToString(table.path);                      // Convierte el camino a string
  std::string generated = VectorToString(table.generated);            // Convierte los nodos generados a string
  std::string visited = VectorToString(table.visited);                // Convierte los nodos visitados a string
  std::string start = std::to_string(labyrinth.GetStartNode().GetKind());
  int cost = 0;
  if (path != "No path") cost = table.path.back().GetGValue();        // Si hay camino, obtiene el coste 
  output_file << "| " << id << " | " << std::to_string(labyrinth.GetRows()) 
              << " | " << std::to_string(labyrinth.GetColumns()) << " | "
              << labyrinth.GetStartNode().GetPosString() << " | "
              << labyrinth.GetEndNode().GetPosString() << " | " 
              << path << " | " << cost << " | " 
              << generated << " | " << visited << " | \n";
  return output_file;
}

/**
 * @brief Comprueba si un nodo es válido para transitar.
 * 
 * @param[in] row: Filas del nodo
 * @param[in] col: Columna del nodo
 * @param[in] labyrinth: Laberinto en el que se encuentra el nodo
 * @return true si el nodo es válido, false en caso contrario
 */
bool IsNodeValid(int row, int col, Labyrinth& labyrinth) {
  if (row < 0 || col < 0) return false; // Si el nodo está fuera del laberinto
  if (row >= labyrinth.GetRows() || col >= labyrinth.GetColumns()) return false; 
  if (labyrinth.Node(std::make_pair(row, col)).GetKind() == 1) return false; // Si el nodo es un muro
  return true;
}

/**
 * @brief Construye el camino de la solución a partir de los padres.
 * 
 * @param[in] current_node: Último nodo comprobado
 * @param[in] parents: Vector de pares de nodos (hijo, padre)
 * @param[in] start_node: Nodo inicial del laberinto
 * @return CellVector que representa el camino de la solución
 */
CellVector ConstructPath(Cell current_node, Cell start_node,
                         std::vector<std::pair<Cell,Cell>> parents) {
  CellVector path;
  while (current_node.GetKind() != 3) {         // Mientras no se llegue al nodo inicial
    path.push_back(current_node); 
    for (int i = 0; i < parents.size(); i++) {
      if (parents[i].first == current_node) {
        current_node = parents[i].second;      // Se añade el padre del nodo actual al camino
        break;
      }
    }
  }
  path.push_back(start_node);
  std::reverse(path.begin(), path.end());      // Se invierte el camino para mostrarlo de la forma correcta
  return path;
}

/**
 * @brief Comprueba si un nodo abierto tiene un padre mejor que el actual.
 * 
 * @param node: Nodo abierto que se quiere comprobar
 * @param current_node: Nodo actual de la búsqueda. Posible padre de node
 * @param labyrinth: Laberinto en el que se encuentra el nodo
 * @param parents: Vector de pares de nodos (hijo, padre)
 */
void UpdateIfBetter(Cell& node, Cell& current_node, 
                          std::vector<CellVector> labyrinth,
                          std::vector<std::pair<Cell,Cell>>& parents) {
  int g_value = current_node.GetGValue();
  if (current_node.IsDiagonal(node, labyrinth)) g_value += 7; // Si el nodo es diagonal el coste es 7
  else g_value += 5;                                          // Si el nodo es adyacente el coste es 5
  for (int i = 0; i < parents.size(); i++) {  
    if (parents[i].first == node) {
      if (g_value < parents[i].first.GetGValue()) {                       // Si el padre actual es mejor que el anterior
        parents[i].first.SetGValue(g_value);                              // Se actualiza el coste
        parents[i].first.SetFValue(g_value + parents[i].first.GetHValue());   // Se actualiza el valor total
        // el nodo
        parents[i].second = current_node;                       // Se actualiza el padre

      }
      break;
    }
  }
}

/**
 * @brief Comprueba si un nodo vecino es inválido para transitar.
 * 
 * @param neighbor: Nodo vecino
 * @param current_node: Nodo actual de la búsqueda
 * @param closed_nodes: Vector de nodos cerrados
 * @return true si el nodo es inválido, false en caso contrario
 */
bool InvalidNeighbor(Cell& neighbor, Cell& current_node, 
                     CellVector& closed_nodes) {
  return neighbor.GetPos() == std::make_pair(-1, -1) ||  // Si el nodo no existe en el laberinto
  IsClosedNode(neighbor, closed_nodes);                  // Si el nodo ya está cerrado
}