#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
// define los tamaños de los arreglos
const size_t tamanioRespuesta = 20; // tamaño del arreglo respuestas
const size_t tamanioFrecuencia = 6; // tamaño del arreglo frecuencia
// coloca las respuestas de la encuesta en el arreglo respuestas
const array< unsigned int, tamanioRespuesta > respuestas = { 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 4, 3, 3, 3, 2, 3, 3, 2, 2, 5 };

// inicializa los contadores de frecuencia con 0
array< unsigned int, tamanioFrecuencia > frecuencia = {};
// para cada respuesta, selecciona el elemento de respuestas y usa ese valor
// acomo subíndice de frecuencia para determinar el elemento a incrementar
for ( size_t respuesta = 0; respuesta < respuestas.size(); ++respuesta ){
     ++frecuencia[ respuestas[ respuesta ] ];
}
     cout << "Calificacion" << setw( 17 ) << "Frecuencia" << endl;

// imprime el valor de cada elemento del arreglo
for ( size_t calificacion = 1; calificacion < frecuencia.size(); ++calificacion ){
cout << setw( 6 ) << calificacion << setw( 17 ) << frecuencia[ calificacion ]<< endl;
}


}