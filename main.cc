/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 3º
 * Práctica 1: Algoritmos de búsqueda. Búsquedas no informadas.
 * Autor: Gabriel Ángel Canals Salleras
 * Correo: alu0101460468@ull.edu.es
 * Fecha: 26/09/2023
 *
 * Archivo main.cc: programa cliente.
 * Contiene la función main del proyecto que recibe los parámetros del cliente
 * para luego llamar a las funciones que imprimirán el resultado de la operación
 * solicitada en el fichero de salida de nombre fileout.txt.
 *
 * Referencias:
 * https://drive.google.com/file/d/15HKX9AdAv0_3KYwmYDA2VWz-riiimztK/view
 * Historial de revisiones
 * 26/09/2023 - Creación (primera versión) del código
 */

#include "aux_functions.h"

/** Main function
 *  @param[in] argc Number of command line parameters
 *  @param[in] argv Vector containing (char*) the parameters
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::ifstream input_file;
  std::string file_name{argv[1]};
  input_file.open(file_name);
  if (input_file.fail()) {
    std::cerr << "The file failed to open, use --help for further information\n";
    return 1;
  }
  Labyrinth labyrinth(input_file);
  labyrinth.PrintLabyrinth();
  int signal = 0;
  while (signal != 1)
  {
    signal = Menu(labyrinth, file_name);
    if (signal == 3) {
      std::cout << "Enter the new file name: ";
      std::cin >> file_name;
      input_file.close();
      input_file.open(file_name);
      if (input_file.fail()) {
        std::cerr << "The file failed to open. Using " << argv[1] << " instead\n\n";
        input_file.open(argv[1]);
      }
      labyrinth = Labyrinth(input_file);
    }
  }
  return 0;
}