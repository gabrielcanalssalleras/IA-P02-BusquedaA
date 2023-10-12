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

/** Turns a vector of integers into a string.
 *  @param[in] vector: Vector to turn into string 
 *  @return String containing the vector
*/
std::string VectorToString(std::vector<Cell> vector) {
  std::string result;
  if (vector.size() == 0) return "No path";
  for (int i = 0; i < vector.size(); i++) {
    result += "(" + std::to_string(vector[i].GetPos().first + 1) + "," + 
              std::to_string(vector[i].GetPos().second + 1) + ")";
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
  output_file << "| " << id << " | " << std::to_string(labyrinth.GetRows()) 
              << " | " << std::to_string(labyrinth.GetColumns()) << " | "
              << labyrinth.GetStartNode().GetPosString() << " | "
              << labyrinth.GetEndNode().GetPosString() << " | " 
              << path << " | " << "s"/* graph.CalculateCost(table.path) */ << " | " 
              << generated << " | " << visited << " | \n";
  return output_file;
}

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

bool IsNodeValid(int row, int col, Labyrinth& labyrinth) {
  if (row < 0 || col < 0) return false;
  if (row >= labyrinth.GetRows() || col >= labyrinth.GetColumns()) return false;
  if (labyrinth.Node(std::make_pair(row, col)).GetKind() == 1) return false;
  return true;
}

/** Gives a random number between two numbers.
 *  @param[in] min: Minimum number
 *  @param[in] max: Maximum number
 *  @return Random number between min and max
*/
int GetRandomNumber(int min, int max) {
  return rand() % (max - min + 1) + min;
}