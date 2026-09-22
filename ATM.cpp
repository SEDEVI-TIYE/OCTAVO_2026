#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string ARCHIVO_CUENTAS = "cuentas.txt";

/////////ESTRUCTURAS EN C++(STRUCT)/////////////////
////////CLASE 1/////////
// Estructura que representa una cuenta bancaria
struct Cuenta {
    string titular;
    string numeroCuenta;
    int pin;
    float saldo;
    vector<string> movimientos; // historial simple
};
 

// Función para mostrar el menú principal
void mostrarMenu() {
    cout << "\n========== CAJERO AUTOMÁTICO ==========\n";
    cout << "1. Consultar saldo\n";
    cout << "2. Retirar dinero\n";
    cout << "3. Depositar dinero\n";
    cout << "4. Cambiar PIN\n";
    cout << "5. Ver movimientos\n";
    cout << "0. Salir\n";
    cout << "=======================================\n";
    cout << "Elige una opción: ";
}

// Menú inicial: iniciar sesión o crear usuario
void mostrarMenuInicial() {
    cout << "\n========== BIENVENIDO AL BANCO ==========\n";
    cout << "1. Iniciar sesión\n";
    cout << "2. Crear usuario\n";
    cout << "0. Salir\n";
    cout << "===========================================\n";
    cout << "Elige una opción: ";
}



//////CLASE 2//////////////////////
///////////////////FLUJO DE ARCHIVOS////////////////////////
// Guarda todas las cuentas en un archivo de texto (cuentas.txt)
// Formato por línea: titular;numeroCuenta;pin;saldo;mov1~mov2~mov3
void guardarCuentas(const vector<Cuenta>& cuentas) {
    ofstream archivo(ARCHIVO_CUENTAS);

    if (!archivo.is_open()) {
        cout << "\n[Aviso] No se pudo guardar la información en el archivo.\n";
        return;
    }

    for (const Cuenta& c : cuentas) {
        archivo << c.titular << ";" << c.numeroCuenta << ";" << c.pin << ";" << c.saldo << ";";

        for (int i = 0; i < (int)c.movimientos.size(); i++) {
            archivo << c.movimientos[i];
            if (i != (int)c.movimientos.size() - 1) {
                archivo << "~"; // separador entre movimientos
            }
        }
        archivo << "\n";
    }

    archivo.close();
}

// Carga las cuentas desde el archivo de texto (si existe) al iniciar el programa
void cargarCuentas(vector<Cuenta>& cuentas) {
    ifstream archivo(ARCHIVO_CUENTAS);

    if (!archivo.is_open()) {
        // Aún no existe el archivo (primera vez que se usa el programa)
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campo;
        Cuenta c;

        getline(ss, c.titular, ';');
        getline(ss, c.numeroCuenta, ';');

        getline(ss, campo, ';');
        c.pin = stoi(campo);

        getline(ss, campo, ';');
        c.saldo = stof(campo);

        // Lo que queda de la línea son los movimientos, separados por '~'
        getline(ss, campo);
        if (!campo.empty()) {
            stringstream movStream(campo);
            string mov;
            while (getline(movStream, mov, '~')) {
                c.movimientos.push_back(mov);
            }
        }

        cuentas.push_back(c);
    }

    archivo.close();
}


// Función para validar el PIN
bool validarPIN(Cuenta& cuenta) {
    int intentos = 3;
    int pinIngresado;
 
    while (intentos > 0) {
        cout << "Ingresa tu PIN (quedan " << intentos << " intentos): ";
        cin >> pinIngresado;
 
        if (pinIngresado == cuenta.pin) {
            cout << "\n¡Bienvenido/a, " << cuenta.titular << "!\n";
            return true;
        } else {
            intentos--;
            cout << "PIN incorrecto.\n";
        }
    }
 
    cout << "Has superado el número de intentos. Tarjeta bloqueada.\n";
    return false;
}

// Consultar saldo
void consultarSaldo(const Cuenta& cuenta) {
    cout << "\n--- CONSULTA DE SALDO ---\n";
    cout << "Titular: " << cuenta.titular << endl;
    cout << "Cuenta:  " << cuenta.numeroCuenta << endl;
    cout << "Saldo:   $" << cuenta.saldo << endl;
}
 
// Retirar dinero
void retirar(Cuenta& cuenta) {
    float monto;
    cout << "\n--- RETIRO ---\n";
    cout << "Saldo disponible: $" << cuenta.saldo << endl;
    cout << "¿Cuánto deseas retirar? $";
    cin >> monto;
 
    if (monto <= 0) {
        cout << "Monto inválido.\n";
    } else if (monto > cuenta.saldo) {
        cout << "Fondos insuficientes.\n";
    } else {
        cuenta.saldo -= monto;
        cuenta.movimientos.push_back("Retiro: -$" + to_string(monto));
        cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.saldo << endl;
    }
}
 
// Depositar dinero
void depositar(Cuenta& cuenta) {
    float monto;
    cout << "\n--- DEPÓSITO ---\n";
    cout << "¿Cuánto deseas depositar? $";
    cin >> monto;
 
    if (monto <= 0) {
        cout << "Monto inválido.\n";
    } else {
        cuenta.saldo += monto;
        cuenta.movimientos.push_back("Depósito: +$" + to_string(monto));
        cout << "Depósito exitoso. Nuevo saldo: $" << cuenta.saldo << endl;
    }
}
 
// Cambiar PIN
void cambiarPIN(Cuenta& cuenta) {
    int pinActual, nuevoPIN, confirmacion;
 
    cout << "\n--- CAMBIAR PIN ---\n";
    cout << "Ingresa tu PIN actual: ";
    cin >> pinActual;
 
    if (pinActual != cuenta.pin) {
        cout << "PIN incorrecto. No se puede cambiar.\n";
        return;
    }
 
    cout << "Ingresa el nuevo PIN: ";
    cin >> nuevoPIN;
    cout << "Confirma el nuevo PIN: ";
    cin >> confirmacion;
 
    if (nuevoPIN == confirmacion) {
        cuenta.pin = nuevoPIN;
        cuenta.movimientos.push_back("Cambio de PIN realizado");
        cout << "PIN actualizado correctamente.\n";
    } else {
        cout << "Los PIN no coinciden. Intenta de nuevo.\n";
    }
}
 
// Ver movimientos
void verMovimientos(const Cuenta& cuenta) {
    cout << "\n--- ÚLTIMOS MOVIMIENTOS ---\n";
 
    if (cuenta.movimientos.empty()) {
        cout << "No hay movimientos registrados.\n";
        return;
    }
 
    for (int i = 0; i < cuenta.movimientos.size(); i++) {
        cout << i + 1 << ". " << cuenta.movimientos[i] << endl;
    }
}

// Busca una cuenta por número de cuenta. Devuelve puntero a la cuenta o nullptr si no existe.
Cuenta* buscarCuenta(vector<Cuenta>& cuentas, const string& numeroCuenta) {
    for (int i = 0; i < (int)cuentas.size(); i++) {
        if (cuentas[i].numeroCuenta == numeroCuenta) {
            return &cuentas[i];
        }
    }
    return nullptr;
}

// Crear un nuevo usuario / cuenta
void crearUsuario(vector<Cuenta>& cuentas) {
    Cuenta nueva;

    cout << "\n--- CREAR USUARIO ---\n";
    cout << "Nombre del titular: ";
    cin.ignore();
    getline(cin, nueva.titular);

    cout << "Número de cuenta (ej. 1234567891): ";
    cin >> nueva.numeroCuenta;

    // Verificamos que el número de cuenta no esté ya registrado
    if (buscarCuenta(cuentas, nueva.numeroCuenta) != nullptr) {
        cout << "Ya existe una cuenta con ese número. Usuario no creado.\n";
        return;
    }

    int pin, confirmacion;
    cout << "Crea un PIN (4 dígitos): ";
    cin >> pin;
    cout << "Confirma el PIN: ";
    cin >> confirmacion;

    if (pin != confirmacion) {
        cout << "Los PIN no coinciden. Usuario no creado.\n";
        return;
    }

    nueva.pin = pin;

    float depositoInicial;
    cout << "Depósito inicial: $";
    cin >> depositoInicial;
    nueva.saldo = (depositoInicial > 0) ? depositoInicial : 0.0f;

    if (nueva.saldo > 0) {
        nueva.movimientos.push_back("Depósito inicial: +$" + to_string(nueva.saldo));
    }

    cuentas.push_back(nueva);
    guardarCuentas(cuentas); // persistimos el nuevo usuario en el archivo

    cout << "\n¡Usuario creado con éxito y guardado en " << ARCHIVO_CUENTAS << "! Ya puedes iniciar sesión con tu número de cuenta y PIN.\n";
}
 
int main() {
    // Lista de cuentas registradas en el sistema
    vector<Cuenta> cuentas;

    // Intentamos cargar las cuentas guardadas previamente en el archivo de texto
    cargarCuentas(cuentas);

    // Si el archivo no existía (primera ejecución), creamos una cuenta de prueba y la guardamos
    if (cuentas.empty()) {
        Cuenta cuentaPrueba;
        cuentaPrueba.titular = "Juan Pérez";
        cuentaPrueba.numeroCuenta = "1234567890";
        cuentaPrueba.pin = 1234;
        cuentaPrueba.saldo = 2500.00f;
        cuentas.push_back(cuentaPrueba);
        guardarCuentas(cuentas);
    }

    cout << "========== BIENVENIDO AL CAJERO ==========\n";
    cout << "Se cargaron " << cuentas.size() << " cuenta(s) desde " << ARCHIVO_CUENTAS << "\n";

    int opcionInicial;
    do {
        mostrarMenuInicial();
        cin >> opcionInicial;

        if (opcionInicial == 1) {
            // Iniciar sesión
            string numeroCuenta;
            cout << "\nIngresa tu número de cuenta: ";
            cin >> numeroCuenta;

            Cuenta* cuenta = buscarCuenta(cuentas, numeroCuenta);

            if (cuenta == nullptr) {
                cout << "No existe una cuenta con ese número.\n";
                continue;
            }

            if (!validarPIN(*cuenta)) {
                continue; // Vuelve al menú inicial si falla el PIN
            }

            // Menú de operaciones de la cuenta
            int opcion;
            do {
                mostrarMenu();
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        consultarSaldo(*cuenta);
                        break;
                    case 2:
                        retirar(*cuenta);
                        guardarCuentas(cuentas); // actualizamos el archivo tras el cambio
                        break;
                    case 3:
                        depositar(*cuenta);
                        guardarCuentas(cuentas);
                        break;
                    case 4:
                        cambiarPIN(*cuenta);
                        guardarCuentas(cuentas);
                        break;
                    case 5:
                        verMovimientos(*cuenta);
                        break;
                    case 0:
                        cout << "\nSesión cerrada. Hasta pronto, " << cuenta->titular << ".\n";
                        break;
                    default:
                        cout << "\nOpción no válida. Intenta de nuevo.\n";
                }

            } while (opcion != 0);

        } else if (opcionInicial == 2) {
            crearUsuario(cuentas);

        } else if (opcionInicial == 0) {
            guardarCuentas(cuentas); // guardado final por seguridad
            cout << "\n¡Gracias por usar el cajero! Hasta pronto.\n";

        } else {
            cout << "\nOpción no válida. Intenta de nuevo.\n";
        }

    } while (opcionInicial != 0);

    return 0;
}