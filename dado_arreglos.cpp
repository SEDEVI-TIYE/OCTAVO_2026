#include <iostream>
#include <iomanip>
#include <array>
#include <random>
#include <ctime>
using namespace std;

int main()
{
// usa el motor predeterminado de generación de números aleatorios para
// producir valores int seudoaleatorios distribuidos de manera uniforme de 1 a 6
default_random_engine motor( static_cast< unsigned int >( time(0) ) );
uniform_int_distribution< unsigned int > intAleatorio( 1, 6 );

const size_t tamanioArreglo = 7; // ignora el elemento cero
array< unsigned int, tamanioArreglo > frecuencia = {}; // inicializa con ceros

// tira el dado 6 000 000 de veces; usa el valor del dado como índice de frecuencia
for ( unsigned int tiro = 1; tiro <= 6000000; ++tiro )
++frecuencia[ intAleatorio( motor ) ];

cout << "Cara" << setw( 13 ) << "Frecuencia" << endl;

// imprime el valor de cada elemento del arreglo
for ( size_t cara = 1; cara < frecuencia.size(); ++cara )
cout << setw( 4 ) << cara << setw( 13 ) << frecuencia[ cara ]<< endl;
} 