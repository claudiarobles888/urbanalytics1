#include <stdio.h>
#include "funciones.h"
#include <time.h>
#include <string.h>

void captureDatosActuales(struct zonaUrbana *zona)
{
    printf("----Captura de datos actuales----\n");
    getchar();

    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        printf("Ingrese el nombre de la zona urbana: ");
        fgets(zona[i].nombre, sizeof(zona[i].nombre), stdin);
        zona[i].nombre[strcspn(zona[i].nombre, "\n")] = '\0';

        printf("Ingrese el CO2: ");
        scanf("%f", &zona[i].CO);
        printf("Ingrese el SO2: ");
        scanf("%f", &zona[i].SO2);
        printf("Ingrese el NO2: ");
        scanf("%f", &zona[i].NO2);
        printf("Ingrese el PM25: ");
        scanf("%f", &zona[i].PM25);
        printf("Ingrese la temperatura: ");
        scanf("%f", &zona[i].temperatura);
        printf("Ingrese la velocidad del viento: ");
        scanf("%f", &zona[i].viento);
        printf("Ingrese la humedad: ");
        scanf("%f", &zona[i].humedad);
        getchar();
    }
}

void generateDatosHistoricos(struct zonaUrbana *zona)
{
    printf("-----Generacion de datos historicos-----\n");
    FILE *file = fopen("datos_historicos.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de datos históricos.\n");
        return;
    }
    
    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        zona[i].CO = 4 + rand() % 200;
        zona[i].SO2 = 40 + rand() % 40;
        zona[i].NO2 = 25 + rand() % 30;
        zona[i].PM25 = 15 + rand() % 50;
        zona[i].temperatura = 10 + rand() % 30;
        zona[i].viento = 0 + rand() % 20;
        zona[i].humedad = 30 + rand() % 70;
        printf("%s:\n", zona[i].nombre);
        printf("  CO: %.2f, SO2: %.2f, NO2: %.2f, PM2.5: %.2f\n", zona[i].CO, zona[i].SO2, zona[i].NO2, zona[i].PM25);
        printf("  Temperatura: %.2f°C, Viento: %.2f m/s, Humedad: %.1f%%\n",
               zona[i].temperatura, zona[i].viento, zona[i].humedad);
        fprintf(file, "%s:\n", zona[i].nombre);

        fprintf(file, "  CO: %.2f, SO2: %.2f, NO2: %.2f, PM2.5: %.2f\n", zona[i].CO, zona[i].SO2, zona[i].NO2, zona[i].PM25);
        fprintf(file, "  Temperatura: %.2f°C, Viento: %.2f m/s, Humedad: %.1f%%\n",
                zona[i].temperatura, zona[i].viento, zona[i].humedad);
    }
    fclose(file);
}

void mostrarDatosHistoricos()
{
    printf("---- Mostrar datos historicos ----\n");
    FILE *file = fopen("datos_historicos.txt", "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de datos históricos.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);
}

void monitoreoContaminacionActual(struct zonaUrbana *zona)
{
    const float limiteCO = 4.0;    // En ppm
    const float limiteSO2 = 40.0;  // En µg/m³
    const float limiteNO2 = 25.0;  // En µg/m³
    const float limitePM25 = 15.0; // En µg/m³

    printf("---- Monitoreo de contaminacion actual ----\n");
    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        printf("%s:\n", zona[i].nombre);

        printf("  CO: %.2f gm/m³ ", zona[i].CO);
        if (zona[i].CO > limiteCO)
        {
            printf("(Excede el limite de %.2f gm/m³)\n", limiteCO);
            printf("  Alerta: Reduzca el trafico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("  SO2: %.2f µg/m³ ", zona[i].SO2);
        if (zona[i].SO2 > limiteSO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteSO2);
            printf("  Alerta: Reduzca el trafico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("  NO2: %.2f µg/m³ ", zona[i].NO2);
        if (zona[i].NO2 > limiteNO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteNO2);
            printf("  Alerta: Reduzca el trafico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("  PM2.5: %.1f µg/m³ ", zona[i].PM25);
        if (zona[i].PM25 > limitePM25)
        {
            printf("(Excede el limite de %.1f µg/m³)\n", limitePM25);
            printf("  Alerta: Suspenda actividades al aire libre.\n");
        }
        else
        {
            printf("(Dentro del límite)\n");
        }
    }
}

void predictNivelesFuturos(struct zonaUrbana *zona)
{
    const float limiteCO = 4.0;    // En mg/m³
    const float limiteSO2 = 40.0;  // En µg/m³
    const float limiteNO2 = 25.0;  // En µg/m³
    const float limitePM25 = 15.0; // En µg/m³

    printf("---- Prediccion de niveles futuros ----\n");
    FILE *file = fopen("reporte_predicciones.txt", "w");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de reporte.\n");
        return;
    }

    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        float factorTemperatura = zona[i].temperatura / 30.0;
        float factorViento = zona[i].viento / 10.0;
        float factorHumedad = zona[i].humedad / 50.0;

        if (factorTemperatura < 0)
            factorTemperatura = 0;
        if (factorViento < 0)
            factorViento = 0;
        if (factorHumedad < 0)
            factorHumedad = 0;

        float predCO = zona[i].CO * (1.0 + factorTemperatura + factorHumedad) / (1.0 + factorViento);
        float predSO2 = zona[i].SO2 * (1.0 + factorTemperatura + factorHumedad) / (1.0 + factorViento);
        float predNO2 = zona[i].NO2 * (1.0 + factorTemperatura + factorHumedad) / (1.0 + factorViento);
        float predPM25 = zona[i].PM25 * (1.0 + factorTemperatura + factorHumedad) / (1.0 + factorViento);

        printf("%s:\n", zona[i].nombre);
        printf("  Predicción para mañana:\n");
        printf("    CO: %.2f gm/m³ ", predCO);
        if (predCO > limiteCO)
        {
            printf("(Excede el limite de %.2f gm/m³)\n", limiteCO);
            printf("    Alerta: Reduzca el tráfico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("    SO2: %.2f µg/m³ ", predSO2);
        if (predSO2 > limiteSO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteSO2);
            printf("    Alerta: Reduzca el tráfico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("    NO2: %.2f µg/m³ ", predNO2);
        if (predNO2 > limiteNO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteNO2);
            printf("    Alerta: Reduzca el tráfico vehicular y cierre temporalmente las industrias.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("    PM2.5: %.2f µg/m³ ", predPM25);
        if (predPM25 > limitePM25)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limitePM25);
            printf("    Alerta: Suspenda actividades al aire libre.\n");
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        fprintf(file, "%s:\n", zona[i].nombre);
        fprintf(file, "  Prediccion para maniana:\n");
        fprintf(file, "    CO: %.2f gm/m³\n", predCO);
        fprintf(file, "    SO2: %.2f µg/m³\n", predSO2);
        fprintf(file, "    NO2: %.2f µg/m³\n", predNO2);
        fprintf(file, "    PM2.5: %.2f µg/m³\n", predPM25);
    }

    fclose(file);
}

void guardarDatosActuales(struct zonaUrbana *zona)
{
    FILE *file = fopen("reporte_datos_actuales.txt", "w");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de reporte.\n");
        return;
    }

    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        fprintf(file, "%s:\n", zona[i].nombre);
        fprintf(file, "  CO: %.2f mg/m³\n", zona[i].CO);
        fprintf(file, "  SO2: %.2f µg/m³\n", zona[i].SO2);
        fprintf(file, "  NO2: %.2f µg/m³\n", zona[i].NO2);
        fprintf(file, "  PM2.5: %.2f µg/m³\n", zona[i].PM25);
        fprintf(file, "  Temperatura: %.2f°C\n", zona[i].temperatura);
        fprintf(file, "  Viento: %.2f m/s\n", zona[i].viento);
        fprintf(file, "  Humedad: %.2f\n", zona[i].humedad);
    }

    fclose(file);
}

void calcularPromediosHistoricos(struct zonaUrbana *zona, int num_datos)
{
    printf("---- Calculo de promedios historicos ----\n");
    const float limiteCO = 4.0;    // En mg/m³
    const float limiteSO2 = 40.0;  // En µg/m³
    const float limiteNO2 = 25.0;  // En µg/m³
    const float limitePM25 = 15.0; // En µg/m³

    printf("Promedios Historicos para los ultimos 30 dias ");
    for (int i = 0; i < num_zonasUrbanas; i++)
    {
        float sumaCO = 0.0;
        float sumaSO2 = 0.0;
        float sumaNO2 = 0.0;
        float sumaPM25 = 0.0;
        float sumaTemperatura = 0.0;
        float sumaViento = 0.0;
        float sumaHumedad = 0.0;

        for (int j = 0; j < num_datos; j++)
        {
            sumaCO += zona[i].CO;
            sumaSO2 += zona[i].SO2;
            sumaNO2 += zona[i].NO2;
            sumaPM25 += zona[i].PM25;
            sumaTemperatura += zona[i].temperatura;
            sumaViento += zona[i].viento;
            sumaHumedad += zona[i].humedad;
        }

        float promCO = sumaCO / num_datos;
        float promSO2 = sumaSO2 / num_datos;
        float promNO2 = sumaNO2 / num_datos;
        float promPM25 = sumaPM25 / num_datos;
        float promTemperatura = sumaTemperatura / num_datos;
        float promViento = sumaViento / num_datos;
        float promHumedad = sumaHumedad / num_datos;

        printf("%s:\n", zona[i].nombre);
        printf("  Promedio CO: %.2f mg/m³ ", promCO);
        if (promCO > limiteCO)
        {
            printf("(Excede el limite de %.2f mg/m³)\n", limiteCO);
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("  Promedio SO2: %.2f µg/m³ ", promSO2);
        if (promSO2 > limiteSO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteSO2);
        }
        else
        {
            printf("(Dentro del limite)\n");
        }

        printf("  Promedio NO2: %.2f µg/m³ ", promNO2);
        if (promNO2 > limiteNO2)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limiteNO2);
        }
        else
        {
            printf("(Dentro del límite)\n");
        }

        printf("  Promedio PM2.5: %.2f µg/m³ ", promPM25);
        if (promPM25 > limitePM25)
        {
            printf("(Excede el limite de %.2f µg/m³)\n", limitePM25);
        }
        else
        {
            printf("(Dentro del límite)\n");
        }

        printf("  Promedio Temperatura: %.2f°C\n", promTemperatura);
        printf("  Promedio Viento: %.2f m/s\n", promViento);
        printf("  Promedio Humedad: %.2f\n", promHumedad);
    }
}