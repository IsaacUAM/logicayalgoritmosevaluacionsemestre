/*Automatización de servicios bancarios mediante un cajero automático*/
#include <stdio.h>
int main()
{
    int pins[] = {1234, 4321, 1111, 9999};
    int input_pin;
    int valid_pins = 4;
    int i;
    printf("Ingrese su PIN");
    scanf("%d",&input_pin);

    for(i = 0; i < valid_pins; i++)
    {
        pins[i];
    }
    if (pins[0,1,2,3])
    {
        printf("\nBienvenido");
    }
    else
    {
        printf ("\nIncorrecto. Intente nuevamente");
    }
}