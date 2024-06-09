#include <iostream>

using namespace std;

// Función para retirar dinero
void retirarDinero(int &saldo) {
    int montos[] = {100, 200, 400, 500};
    int opcion;
    cout << "Seleccione el monto a retirar:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". $" << montos[i] << endl;
    }
    cout << "Ingrese su opción: ";
    cin >> opcion;
    
    if (opcion < 1 || opcion > 4) {
        cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        return;
    }
    
    int monto = montos[opcion - 1];
    
    if (saldo < monto) {
        cout << "Fondos insuficientes. No se puede retirar esa cantidad." << endl;
        return;
    }

    saldo -= monto;
    cout << "Retirando $" << monto << "..." << endl;
    // Simulación de retiro de dinero
}

int main() {
    int saldo = 1000; // Saldo disponible para fines de demostración

    int opcion;
    do {
        cout << "==== Menú del Cajero Automático ====" << endl;
        cout << "1. Retirar dinero" << endl;
        cout << "2. Consultar saldo" << endl;
        cout << "3. Transferencia" << endl;
        cout << "4. Depósito" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                retirarDinero(saldo);
                break;
            case 2:
                cout << "Su saldo actual es: $" << saldo << endl;
                break;
            case 3:
                // Lógica para transferencia
                cout << "Función de transferencia aún no implementada." << endl;
                break;
            case 4:
                // Lógica para depósito
                cout << "Función de depósito aún no implementada." << endl;
                break;
            case 5:
                cout << "Gracias por utilizar el cajero automático. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        }
    } while (opcion != 5);

    return 0;
}
