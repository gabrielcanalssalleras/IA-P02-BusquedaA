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
 * Archivo aux_functions.cc: implementación.
 * Contiene implementación de las funciones auxiliares para el programa principal.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 */

#include "aux_functions.h"

/** Prints how to use correctly the program.
 *  In case of incorrect usage, prints the message and the program finishes.
 *  This program requires a natural number to execute properly.
 *
 *  @param[in] argc: Number of command line parameters
 *  @param[in] argv: Vector containing (char*) the parameters
 */
void Usage(int argc, char *argv[]) {
  if (argc > 1) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
  if (argc != 2) {
    std::cout << argv[0] << "-- Search algorithms. Uninformed Search." << std::endl;
    std::cout << "Usage: input_file.txt\n";
    std::cout << "Try " << argv[0] << " --help for more information\n";
    exit(EXIT_SUCCESS);
  }
}

/** Gets the name of the instance based on the number of lines of the file.
 *  @param[in] filename: Name of the file to read
 *  @return Name of the instance
 */
std::string GetID(std::string filename) {
  int number_of_lines = 1;
  std::string line;
  std::ifstream file(filename);
  std::getline(file, line);
  std::getline(file, line);
  while (std::getline(file, line)) ++number_of_lines;
  if (number_of_lines == 1) return "ID-1";
  line = "ID-" + std::to_string(number_of_lines);
  return line;
}

/** Turns a vector of integers into a string.
 *  @param[in] vector: Vector to turn into string 
 *  @return String containing the vector
*/
std::string VectorToString(std::vector<int> vector) {
  std::string result;
  if (vector.size() == 0) return "No path";
  for (int i = 0; i < vector.size(); i++) {
    result += std::to_string(vector[i]);
    if (i != vector.size() - 1) result += "-";
  }
  return result;
}

/** Stores the results of the search in a file in Markdown format.
 *  @param[in] graph: Graph to search
 *  @param[in] start_node: Starting node
 *  @param[in] end_node: Ending node
 *  @param[in] depth_first: True if depth first search, false if breadth first search
 *  @return Output file stream
*/
/* std::ofstream StoreSearch(Graph& graph, int start_node, int end_node, bool depth_first) {
  std::string filename = depth_first ? "busquedas_profundidad.md" : "busquedas_amplitud.md";
  std::ofstream output_file;
  output_file.open(filename, std::ios_base::app);
  if (output_file.tellp() == 0) { 
    output_file << "| Instancia | n | m | Vo |";
    output_file << " Vd | Camino | Distancia | Nodos Generados | Nodos inspeccionados |\n";
    output_file << "| --- | --- | --- | --- | --- | --- | --- | --- | --- |\n";
  }
  std::string id = GetID(filename);
  Instance table = depth_first ? graph.DepthFirstSearch(start_node, end_node) 
                              : graph.BreadthFirstSearch(start_node, end_node);
  std::string path = VectorToString(table.path);
  std::string generated = VectorToString(table.generated);
  std::string visited = VectorToString(table.visited);
  output_file << "| " << id << " | " << graph.Size() << " | " << graph.EdgeCount() << " | " 
              << start_node << " | " << end_node << " | " << path << " | " << graph.CalculateCost(table.path)
              << " | " << generated << " | " << visited << " | \n";
  return output_file;
} */

/** Checks if a node is in a branch.
 *  @param[in] node: Node to check
 *  @param[in] branch: Branch to check
 *  @return True if the node is in the branch, false otherwise
*/
bool FoundInBranch(int node, std::vector<int> branch) {
  for (int i = 0; i < branch.size(); i++) {
    if (branch[i] == node) return true;
  }
  return false;
}

/** Gives a random number between two numbers.
 *  @param[in] min: Minimum number
 *  @param[in] max: Maximum number
 *  @return Random number between min and max
*/
int GetRandomNumber(int min, int max) {
  return rand() % (max - min + 1) + min;
}