//PIN
#include <stdio.h>
int main()
{
    int intentos = 3, pincorrecto, pines[] = {1234, 2345, 3456, 4567};
    printf("Bienvenido al cajero automático\n");
    do
    {
        printf("\nNúmero de intentos disponibles: %d", intentos);
        printf("\nInserte su PIN:\n\n");
        scanf("%d", &pincorrecto);
        if (pincorrecto == pines[0])
        {
            intentos = -1;
            break;
        }
        else if (pincorrecto == pines[1])
        {
            intentos = -1;
            break;
        }
        else if (pincorrecto == pines[2])
        {
            intentos = -1;
            break;
        }
        else if (pincorrecto == pines[3])
        {
            intentos = -1;
            break;
        }
        else
        {
            intentos-= 1;
            printf("Pin incorrecto.\n");
        }
        
    } while (intentos != 0);
    if (intentos == 0)
    {
        printf("Su usuario ha sido bloqueado");
        return 0;
    }
    printf("Acceso concedido");
    return 0;
}