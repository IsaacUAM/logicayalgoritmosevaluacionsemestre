#include <iostream>
#include <ctime>
#include <unordered_map>

using namespace std;

// Función para verificar PIN
bool verificarPIN() {
    int intentos = 3, pincorrecto, pines[] = {1234, 2345, 3456, 4567};
    cout << "Bienvenido al cajero automático de Avanz" << endl;
    do {
        cout << "\nNúmero de intentos disponibles: " << intentos;
        cout << "\nInserte su PIN:\n\n";
        cin >> pincorrecto;
        if (pincorrecto == pines[0] || pincorrecto == pines[1] || pincorrecto == pines[2] || pincorrecto == pines[3]) {
            return true;
        } else {
            intentos -= 1;
            cout << "Pin incorrecto.\n";
        }
    } while (intentos != 0);
    if (intentos == 0) {
        cout << "Su usuario ha sido bloqueado." << endl;
    }
    return false;
}

// Función para imprimir recibo
void imprimirRecibo(int saldo, string tipo, int monto, string cuentaDestino = "") {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    cout << "============================" << endl;
    cout << "        RECIBO DE CAJERO        " << endl;
    cout << "============================" << endl;
    cout << "Fecha y Hora: " 
         << 1900 + ltm->tm_year << "-" 
         << 1 + ltm->tm_mon << "-" 
         << ltm->tm_mday << " " 
         << 1 + ltm->tm_hour << ":" 
         << 1 + ltm->tm_min << ":" 
         << 1 + ltm->tm_sec << endl;
    if (tipo == "transferencia") {
        cout << "Transferencia de: $" << monto << endl;
        cout << "A la cuenta: " << cuentaDestino << endl;
    }
    cout << "Saldo restante: $" << saldo << endl;
    cout << "============================" << endl;
}

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

    int postRetiroOpcion;
    do {
        cout << "==== Opciones Post Retiro ====" << endl;
        cout << "1. Imprimir recibo" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> postRetiroOpcion;

        switch (postRetiroOpcion) {
            case 1:
                imprimirRecibo(saldo, "retiro", monto);
                break;
            case 2:
                cout << "Gracias por utilizar el cajero automático. ¡Hasta luego!" << endl;
                return;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        }
    } while (postRetiroOpcion != 2);
}

// Función para transferir dinero
void transferirDinero(int &saldo, unordered_map<string, int> &cuentas) {
    string cuentaDestino;
    int monto;
    
    cout << "Ingrese el número de cuenta destino: ";
    cin >> cuentaDestino;

    if (cuentas.find(cuentaDestino) == cuentas.end()) {
        cout << "Número de cuenta no válido. Por favor, intente nuevamente." << endl;
        return;
    }

    cout << "Ingrese el monto a transferir: ";
    cin >> monto;
    
    if (saldo < monto) {
        cout << "Fondos insuficientes. No se puede transferir esa cantidad." << endl;
        return;
    }

    saldo -= monto;
    cuentas[cuentaDestino] += monto;
    cout << "Transfiriendo $" << monto << " a la cuenta " << cuentaDestino << "..." << endl;
    
    // Imprimir recibo de transferencia
    imprimirRecibo(saldo, "transferencia", monto, cuentaDestino);

    // Terminar el programa después de la transferencia
    cout << "Gracias por utilizar el cajero automático. ¡Hasta luego!" << endl;
    exit(0);
}

int main() {
    if (!verificarPIN()) {
        return 0;
    }

    int saldo = 1000; // Saldo disponible para fines de demostración
    unordered_map<string, int> cuentas; // Mapa de cuentas y saldos
    cuentas["12345678"] = 500; // Cuenta de ejemplo
    cuentas["87654321"] = 700; // Otra cuenta de ejemplo

    int opcion;
    do {
        cout << "==== Menú del Cajero Automático ====" << endl;
        cout << "1. Retirar dinero" << endl;
        cout << "2. Consultar saldo" << endl;
        cout << "3. Transferir dinero" << endl;
        cout << "4. Imprimir recibo" << endl;
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
                transferirDinero(saldo, cuentas);
                break;
            case 4:
                imprimirRecibo(saldo, "consulta", 0);
                break;
            case 5:
                cout << "Gracias por utilizar el cajero automático. ¡Hasta luego!" << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        }
    } while (opcion != 5);

    return 0;
}