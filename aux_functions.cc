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
    if (parameter == "--help") {
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    }
    if (argc > 2) parameter = argv[2];
    if (parameter == "-d" || parameter == "--debug") {
      std::cout << "Debug mode activated\n";
      debug = true;
      visual = true;
    }
    if (parameter == "-v" || parameter == "--visual") {
      std::cout << "Visual mode activated\n";
      visual = true;
    }
  }
  if (argc < 2 || argc > 3) {
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
  if (vector.size() == 0) return "No path";
  for (int i = 0; i < vector.size(); i++) {
    result += vector[i].GetPosString();
    if (i != vector.size() - 1) result += "-";
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
  output_file.open("busquedas.md", std::ios_base::app);
  if (output_file.tellp() == 0) { 
    output_file << "| Instancia | n | m | S | E |  Camino | ";
    output_file << "Coste | Nodos Generados | Nodos inspeccionados |\n";
    output_file << "| --- | --- | --- | --- | --- | --- | --- | --- | --- |\n";
  }
  std::string id = instance_name.substr(0, instance_name.size() - 4);
  Instance table = labyrinth.AStarSearch();
  std::string path = VectorToString(table.path);
  std::string generated = VectorToString(table.generated);
  std::string visited = VectorToString(table.visited);
  std::string start = std::to_string(labyrinth.GetStartNode().GetKind());
  int cost = 0;
  if (path != "No path") cost = table.path.back().GetGValue();
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
  if (row < 0 || col < 0) return false;
  if (row >= labyrinth.GetRows() || col >= labyrinth.GetColumns()) return false;
  if (labyrinth.Node(std::make_pair(row, col)).GetKind() == 1) return false;
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
  while (current_node.GetKind() != 3) {
    path.push_back(current_node);
    for (int i = 0; i < parents.size(); i++) {
      if (parents[i].first == current_node) {
        current_node = parents[i].second;
        break;
      }
    }
  }
  path.push_back(start_node);
  std::reverse(path.begin(), path.end());
  return path;
}

/** Obtiene un número aleatorio entre un rango.
 *  @param[in] min: Número mínimo
 *  @param[in] max: Número máximo
 *  @return Número aleatorio entre min y max
*/
int GetRandomNumber(int min, int max) {
  return rand() % (max - min + 1) + min;
}