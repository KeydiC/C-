#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

const int FILAS = 6;
const int COLUMNAS = 5;

void mostrarAsientos(const char asientos[FILAS][COLUMNAS], float ocupacion) {
    system("clear");

    cout << "         1         2         3         4         5" << endl;
    cout << ":::::::::::::::::::::::::   PANTALLA   ::::::::::::::::::::::::::" << endl;
    char fila = 'A';
    for (int i = 0; i < FILAS; i++) {
        cout << fila << "        ";
        for (int j = 0; j < COLUMNAS; j++) {
            if (asientos[i][j] == '*') {
                cout << fila << j + 1 << "         ";
            } else {
                cout << "  " << asientos[i][j] << "       ";
            }
        }
        cout << endl;
        fila++;
    }

    cout << endl;
    cout << "Ocupación de la sala: " << ocupacion * 100 << "%" << endl;
}

bool validarAsiento(char fila, int columna) {
    fila = toupper(fila);
    return (fila >= 'A' && fila <= 'F') && (columna >= 1 && columna <= 5);
}

bool verificarDisponibilidad(const char asientos[FILAS][COLUMNAS], char fila, int columna) {
    int filaN = toupper(fila) - 'A'; // Convierte la fila a mayúscula
    int columnaIndex = columna - 1;
    return asientos[filaN][columnaIndex] == '*';
}

bool realizarCompra(char asientos[FILAS][COLUMNAS], int cantidad, float costo, int& asientosDisponibles) {
    int contador = 0;
    if (cantidad > asientosDisponibles) {
        cout << "No hay suficientes asientos disponibles para la cantidad de boletos solicitados." << endl;
        return false;
    }

    if (cantidad == FILAS * COLUMNAS) {
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                asientos[i][j] = 'X';
            }
        }
        asientosDisponibles -= cantidad;
        return true;
    }

    char asientosTemp[FILAS][COLUMNAS];
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            asientosTemp[i][j] = asientos[i][j];
        }
    }

    while (contador < cantidad) {
        mostrarAsientos(asientosTemp, 1 - (asientosDisponibles / static_cast<float>(FILAS * COLUMNAS)));
        cout << "Elija el asiento " << contador + 1 << ": ";
        char fila;
        int columna;
        cin >> fila >> columna;

        if (!validarAsiento(fila, columna)) {
            cout << "El asiento especificado no existe. Intente nuevamente." << endl;
            continue;
        }

        int filaN = toupper(fila) - 'A'; // Convierte la fila a mayúscula
        int columnaIndex = columna - 1;

        if (!verificarDisponibilidad(asientosTemp, fila, columna)) {
            cout << "El asiento especificado no está disponible. Intente nuevamente." << endl;
            continue;
        }

        asientosTemp[filaN][columnaIndex] = 'X';
        contador++;
    }

    mostrarAsientos(asientosTemp, 1 - (asientosDisponibles / static_cast<float>(FILAS * COLUMNAS)));

    char confirmacion;
    cout << "¿Está seguro de la compra? (S/N): ";
    cin >> confirmacion;

    if (confirmacion == 'S' || confirmacion == 's') {
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (asientosTemp[i][j] == 'X') {
                    asientos[i][j] = 'X';
                }
            }
        }
        asientosDisponibles -= cantidad;
        return true;
    } else {
        return false;
    }
}

void realizarCorteCaja(const char asientos[FILAS][COLUMNAS], float costo) {
    int boletosVendidos = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (asientos[i][j] == 'X') {
                boletosVendidos++;
            }
        }
    }

    float ocupacion = boletosVendidos / static_cast<float>(FILAS * COLUMNAS);
    float ventaTotal = boletosVendidos * costo;

    cout << "-------------------CORTE DE CAJA-------------------" << endl;
    cout << "Total de boletos vendidos: " << boletosVendidos << endl;
    cout << "Porcentaje de ocupación: " << ocupacion * 100 << "%" << endl;
    cout << "Venta total: $" << ventaTotal << endl;
}

int main() {
    float costoBoleto;
    cout << "Ingrese el costo del boleto: $";
    cin >> costoBoleto;

    char asientos[FILAS][COLUMNAS];
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            asientos[i][j] = '*';
        }
    }

    int asientosDisponibles = FILAS * COLUMNAS;

    int opcion;
    do {
        cout << "******" << endl;
        cout << "*             MENU             *" << endl;
        cout << "******" << endl;
        cout << "1.- Comprar boletos" << endl;
        cout << "2.- Hacer corte de caja" << endl;
        cout << "3.- Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "-------------------COMPRA DE BOLETOS-------------------" << endl;
                int cantidad;
                cout << "Boletos a comprar (0 = salir): ";
                cin >> cantidad;

                if (cantidad == 0) {
                    break;
                }

                if (cantidad > asientosDisponibles) {
                    cout << "La cantidad de boletos solicitados supera la capacidad del cine." << endl;
                    break;
                }

                if (realizarCompra(asientos, cantidad, costoBoleto, asientosDisponibles)) {
                    mostrarAsientos(asientos, 1 - (asientosDisponibles / static_cast<float>(FILAS * COLUMNAS)));
                } else {
                    cout << "La compra ha sido cancelada." << endl;
                }

                break;
            }
            case 2: {
                realizarCorteCaja(asientos, costoBoleto);
                break;
            }
            case 3: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
            }
        }
    } while (opcion != 3);

    return 0;
}

