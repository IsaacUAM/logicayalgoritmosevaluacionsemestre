/*
Nombre del proyecto:
Cajeros Automáticos Avanz
Nombre de los integrantes:
- Jorge Rafael Cubillo Navarro (Líder)
- Pablo José Alemán Solís
- Isaac Elías Aragón Alfaro
*/
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Transaccion
{
    string tipo;
    int monto;
    string cuentaDestino;
    time_t tiempo;
};

bool verificarPIN() // Función para verificar el PIN
{
    int intentos = 3, pincorrecto, pines[] = {1234, 2345, 3456, 4567}; // Declaramos las variables y el arreglo con los pines
    cout << "Bienvenido al cajero automático de Avanz" << endl;
    do // Bucle do while, comprueba hasta que los intentos son igual a 0
    {
        cout << "\nNúmero de intentos disponibles: " << intentos;
        cout << "\nInserte su PIN: "; // Pide al usuario el PIN, debe ser igual a uno de los que esté en el arreglo
        cin >> pincorrecto;
        if (pincorrecto == pines[0] || pincorrecto == pines[1] || pincorrecto == pines[2] || pincorrecto == pines[3])
        {
            return true; // Si el PIN es igual, entonces el bool es igual a true
        }
        else
        {
            intentos -= 1;
            cout << "Pin incorrecto.\n"; // Si el PIN no es igual, entonces resta un intento y vuelve a empezar el bucle
        }
    } while (intentos != 0);
    if (intentos == 0) // Si los intentos son igual a 0 entonces imprime que el usuario fue bloqueado y acaba el programa
    {
        cout << "Su usuario ha sido bloqueado." << endl;
    }
    return false;
}

// Función para imprimir recibo
void imprimirRecibo(int saldo, string tipo, int monto, string cuentaDestino = "")
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    cout << "\n\n============================" << endl;
    cout << "   RECIBO DE CAJERO AVANZ        " << endl;
    cout << "============================" << endl;
    cout << "Fecha y Hora: "
         << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-"
         << ltm->tm_mday << " "
         << 1 + ltm->tm_hour << ":"
         << 1 + ltm->tm_min << ":"
         << 1 + ltm->tm_sec << endl;
    if (tipo == "transferencia")
    {
        cout << "Transferencia de: $" << monto << endl;
        cout << "A la cuenta: " << cuentaDestino << endl;
    }
    cout << "Saldo restante: $" << saldo << endl;
    cout << "============================" << endl;
}

// Función para retirar dinero
void retirarDinero(int &saldo, vector<Transaccion> &transacciones)
{
    int montos[] = {100, 200, 400, 500};
    int opcion;
    cout << "\n\nSeleccione el monto a retirar:" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << i + 1 << ". $" << montos[i] << endl;
    }
    cout << "Ingrese su opción: ";
    cin >> opcion;

    if (opcion < 1 || opcion > 4)
    {
        cout << "\n\nOpción no válida. Por favor, seleccione una opción válida." << endl;
        return;
    }

    int monto = montos[opcion - 1];

    if (saldo < monto)
    {
        cout << "\n\nFondos insuficientes. No se puede retirar esa cantidad." << endl;
        return;
    }

    saldo -= monto;
    cout << "\n\nRetirando $" << monto << "..." << endl;
    // Simulación de retiro de dinero

    Transaccion transaccion = {"retiro", monto, "", time(0)};
    transacciones.push_back(transaccion);

    int postRetiroOpcion;
    do
    {
        cout << "\n\n==== Opciones Post Retiro ====" << endl;
        cout << "1. Imprimir recibo" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> postRetiroOpcion;

        switch (postRetiroOpcion)
        {
        case 1:
            imprimirRecibo(saldo, "retiro", monto);
            break;
        case 2:
            cout << "Gracias por utilizar el cajero automático Avanz. ¡Hasta luego!" << endl;
            exit(0); // Termina el programa
        default:
            cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        }
    } while (postRetiroOpcion != 2);
}

// Función para transferir dinero
void transferirDinero(int &saldo, unordered_map<string, int> &cuentas, vector<Transaccion> &transacciones)
{
    string cuentaDestino;
    int monto;

    cout << "\n\nIngrese el número de cuenta destino: ";
    cin >> cuentaDestino;

    if (cuentas.find(cuentaDestino) == cuentas.end())
    {
        cout << "Número de cuenta no válido. Por favor, intente nuevamente." << endl;
        return;
    }

    cout << "Ingrese el monto a transferir: ";
    cin >> monto;

    if (saldo < monto)
    {
        cout << "Fondos insuficientes. No se puede transferir esa cantidad." << endl;
        return;
    }

    saldo -= monto;
    cuentas[cuentaDestino] += monto;
    cout << "Transfiriendo $" << monto << " a la cuenta " << cuentaDestino << "..." << endl;

    Transaccion transaccion = {"transferencia", monto, cuentaDestino, time(0)};
    transacciones.push_back(transaccion);

    // Imprimir recibo de transferencia
    imprimirRecibo(saldo, "transferencia", monto, cuentaDestino);

    // Terminar el programa después de la transferencia
    cout << "Gracias por utilizar el cajero automático Avanz. ¡Hasta luego!" << endl;
    exit(0);
}

int main()
{
    if (!verificarPIN())
    {
        return 0;
    }

    int saldo = 1000;                   // Saldo disponible para fines de demostración
    unordered_map<string, int> cuentas; // Mapa de cuentas y saldos
    cuentas["12345678"] = 500;          // Cuenta de ejemplo
    cuentas["87654321"] = 700;          // Otra cuenta de ejemplo
    vector<Transaccion> transacciones;  // Lista de transacciones

    int opcion;
    bool continuar = true;
    do
    {
        cout << "\n\n==== MENÚ DEL CAJERO AVANZ ====" << endl;
        cout << "1. Retirar dinero" << endl;
        cout << "2. Consultar saldo" << endl;
        cout << "3. Transferir dinero" << endl;
        cout << "4. Imprimir recibo" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            retirarDinero(saldo, transacciones);
            break;
        case 2:
            cout << "Su saldo actual es: $" << saldo << endl;
            break;
        case 3:
            transferirDinero(saldo, cuentas, transacciones);
            break;
        case 4:
            imprimirRecibo(saldo, "consulta", 0);
            continuar = false;
            break;
        case 5:
            cout << "Gracias por utilizar el cajero automático Avanz. ¡Hasta luego!" << endl;
            continuar = false;
            break;
        default:
            cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
        }
    } while (continuar);

    return 0;
}