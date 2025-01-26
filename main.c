#include <stdio.h>
#include "funciones.h"
#include <time.h>
#include <string.h>

int main()
{
    struct zonaUrbana zona[num_zonasUrbanas];
    int opc;
    do
    {
        printf("-----Bienvenido a Urbanalytics-----\n");
        printf("Seleccione una opcion:\n");
        printf("1. Ingreso de datos actuales\n2. Monitoreo de contaminacion actual\n3. Predecir niveles futuros\n4. Calculo de promedios historicos\n5. Salir\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            captureDatosActuales(zona);
            guardarDatosActuales(zona);
            generateDatosHistoricos(zona);
            break;

        case 2:
            monitoreoContaminacionActual(zona);
            break;

        case 3:
            predictNivelesFuturos(zona);
            break;

        case 4:
            calcularPromediosHistoricos(zona, prom_historico);
            break;

        case 5:
            printf("Saliendo del sistema\n");
            break;

        default:
        printf("Opcion no valida\n");
            break;
        }
    } while (opc != 5);

    return 0;
}