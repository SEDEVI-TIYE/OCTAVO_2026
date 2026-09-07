#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main()
{
const size_t tamanioArreglo = 11;
 array< unsigned int, tamanioArreglo > n =
 { 0, 0, 0, 0, 0, 8, 1, 2, 4, 2, 1 };

 cout << "Distribucion de calificaciones:" << endl;

// para cada elemento del arreglo n, imprime una barra del gráfico
for ( size_t i = 0; i < n.size(); ++i )
{
// imprime etiquetas de las barras ("0-9:", ..., "90-99:", "100:" )
if ( 0 == i )
cout << " 0-9: ";
else if ( 10 == i )
cout << " 100: ";
else
cout << i * 10 << "-" << ( i * 10 ) + 9 << ": ";

// imprime barra de asteriscos
for ( unsigned int estrellas = 0; estrellas < n[ i ]; ++estrellas )
cout << '*';

cout << endl; // inicia una nueva línea de salida
} // fin de for externo
}