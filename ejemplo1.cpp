/*
Autores:
CIF:
Versión:



*/
#include <stdio.h>
#include <stdbool.h>

// Definir pins válidos
const int valid_pins[] = {4567, 8910, 1112, 1314, 1516};
const int num_valid_pins = sizeof(valid_pins) / sizeof(valid_pins[0]);

// Función para ver si un pin es válido
bool is_valid_pin(int pin) {
    for (int i = 0; i < num_valid_pins; ++i) {
        if (pin == valid_pins[i]) {
            return true;
        }
    }
    return false;
}

// Función para retirar dinero
void withdraw_money(double *balance, int option) {
    double amount = 0;
    switch (option) {
        case 1: amount = 100; break;
        case 2: amount = 200; break;
        case 3: amount = 300; break;
        case 4: amount = 500; break;
        default: printf("Opción inválida.\n"); return;
    }

    if (*balance >= amount) {
        *balance -= amount;
        printf("Retiró C$%.2f. Saldo restante: C$%.2f.\n", amount, *balance);
    } else {
        printf("Fondos insuficientes para retiro.\n");
    }
}

// Función para imprimir recibo
void print_receipt(double balance) {
    printf("Recibo:\n");
    printf("Saldo actual: C$%.2f\n", balance);
    printf("Gracias por usar nuestro cajero.\n");
}

// Main
int main() {
    double account_balance = 1000.0; // Valor inicial
    int entered_pin;
    int attempts = 3;

    printf("Bienvenido al cajero Avanz\n");

    while (attempts > 0) {
        printf("Ingrese su PIN: ");
        scanf("%d", &entered_pin);

        if (is_valid_pin(entered_pin)) {
            printf("PIN correcto. Acceso concedido.\n");

            // Menú
            int choice;
            do {
                printf("\nMenú de retiro:\n");
                printf("1. Retirar C$100\n");
                printf("2. Retirar C$200\n");
                printf("3. Retirar C$300\n");
                printf("4. Retirar C$500\n");
                printf("5. Imprimir recibo\n");
                printf("6. Realizar otra transacción\n");
                printf("7. Salir\n");
                printf("Seleccione una opción: ");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= 4) {
                    withdraw_money(&account_balance, choice);
                } else if (choice == 5) {
                    print_receipt(account_balance);
                } else if (choice == 6) {
                    printf("Vuelva a ingresar el número de cuenta.\n");
                } else if (choice == 7) {
                    printf("Gracias por usar nuestro cajero. ¡Hasta luego!\n");
                    break;
                } else {
                    printf("Opción inválida. Intente nuevamente.\n");
                }
            } while (choice != 7);

            break;
        } else {
            attempts--;
            printf("PIN incorrecto. Le quedan %d intentos.\n", attempts);
        }
    }

    if (attempts == 0) {
        printf("Agotó los intentos. Su tarjeta ha sido bloqueada.\n");
    }

    return 0;
}