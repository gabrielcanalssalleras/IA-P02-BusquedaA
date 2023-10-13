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
 * Archivo main.cc: programa cliente.
 * Contiene la función main del proyecto que recibe los parámetros del cliente
 * para luego llamar a las funciones que imprimirán el resultado de la operación
 * solicitada en el fichero de salida de nombre fileout.txt.
 *
 * Referencias:
 * https://drive.google.com/file/d/1ZSin5hXGXC3EMwkbmoFqA_ZgnnQxcq7F/view
 */

#include "aux_functions.h"

/** Función principal del programa.
 *  @param[in] argc Número de parámetros en la linea de comandos
 *  @param[in] argv Vector de parámetros en la linea de comandos
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv);              // Comprueba el modo de uso
  std::ifstream input_file;
  std::string file_name{argv[1]}; // Nombre del fichero de entrada
  input_file.open(file_name);     // Se abre el fichero de entrada
  if (input_file.fail()) {
    std::cerr << "The file failed to open, use --help for further information\n";
    return 1;                     // Error al abrir el fichero
  }
  Labyrinth labyrinth(input_file);
  labyrinth.PrintLabyrinth();     // Se imprime el laberinto
  int signal = 0;
  while (signal != 1)             // Se repite hasta que se de la señal de salida
  {
    signal = Menu(labyrinth, file_name); // Se muestra el menú y se recibe la señal
    if (signal == 3) {                   // Cambiar fichero de entrada
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
  return 0;                       // Fin del programa con éxito
}