/*EJEMPLOS DE USO DE FLUJOS DE ARCHIVOS:*/

//////////////PRIMER ARCHIVO:SALUDO CON OFSTREAM//////////////////////
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream archivo("mensaje.txt");

    archivo << "Hola, este es mi primer archivo.";

    archivo.close();

    cout << "Archivo guardado.";

    return 0;
}

///////////GUARDAR VARIABLES Y VARIOS VALORES//////////////////////////
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string nombre = "Laura";
    int edad = 16;
    double nota = 4.7;

    ofstream archivo("estudiante.txt");

    archivo << "Nombre: " << nombre << endl;
    archivo << "Edad: " << edad << endl;
    archivo << "Nota: " << nota << endl;

    archivo.close();

    cout << "Datos guardados correctamente.";

    return 0;
}


//////////////////////////////////AGREGAR INFORMACIÓN SIN DAÑAR LA ANTERIOR//////////////////////////////////////////////7
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string nombre;
    double nota;

    cout << "Nombre del estudiante: ";
    getline(cin, nombre);

    cout << "Nota: ";
    cin >> nota;

    ofstream archivo("estudiantes.txt", ios::app);

    archivo << nombre << " - " << nota << endl;

    archivo.close();

    cout << "Registro agregado.";

    return 0;
}

///////////////////////////LEER ARCHIVOS///////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream archivo("mensaje.txt");

    string linea;

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();

    return 0;
}
