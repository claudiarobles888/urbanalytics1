#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"
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
    printf("----Generacion de datos historicos----\n");
    FILE *file = fopen("datos_historicos.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo de datos históricos.\n");
        return;
    }

    srand(time(NULL));

    for (int dia = 1; dia <= 30; dia++) {
        fprintf(file, "Dia %d:\n", dia);
        for (int i = 0; i < num_zonasUrbanas; i++) {
            zona[i].CO = 4 + rand() % 200;
            zona[i].SO2 = 40 + rand() % 40;
            zona[i].NO2 = 25 + rand() % 30;
            zona[i].PM25 = 15 + rand() % 50;
            zona[i].temperatura = 10 + rand() % 30;
            zona[i].viento = 0 + rand() % 20;
            zona[i].humedad = 30 + rand() % 70;

            fprintf(file, "  Zona %d (%s):\n", zona[i].id, zona[i].nombre);
            fprintf(file, "    CO: %.2f, SO2: %.2f, NO2: %.2f, PM2.5: %.2f\n", zona[i].CO, zona[i].SO2, zona[i].NO2, zona[i].PM25);
            fprintf(file, "    Temperatura: %.2f°C, Viento: %.2f m/s, Humedad: %.1f%%\n",
                    zona[i].temperatura, zona[i].viento, zona[i].humedad);
        }
    }

    fclose(file);
    printf("Datos historicos generados y guardados en datoshistoricos.txt\n");
}

void monitoreoContaminacionActual(struct zonaUrbana *zona)
{
    const float limiteCO = 4.0;    // En gm/m³
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
    const float limiteCO = 4.0;    // En gm/m³
    const float limiteSO2 = 40.0;  // En µg/m³
    const float limiteNO2 = 25.0;  // En µg/m³
    const float limitePM25 = 15.0; // En µg/m³

    printf("---- Prediccion de niveles futuros ----\n");

    FILE *file = fopen("datos_historicos.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de datos históricos.\n");
        return;
    }

    float sum_CO[num_zonasUrbanas] = {0};
    float sum_SO2[num_zonasUrbanas] = {0};
    float sum_NO2[num_zonasUrbanas] = {0};
    float sum_PM25[num_zonasUrbanas] = {0};
    float sum_temperatura[num_zonasUrbanas] = {0};
    float sum_viento[num_zonasUrbanas] = {0};
    float sum_humedad[num_zonasUrbanas] = {0};

    char line[256];
    int dia = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Dia", 3) == 0) {
            dia++;
            continue;
        }

        int zona_id;
        char nombre[50];
        float CO, SO2, NO2, PM25, temperatura, viento, humedad;

        sscanf(line, " Zona %d (%[^)]):", &zona_id, nombre);
        fgets(line, sizeof(line), file);
        sscanf(line, " CO: %f, SO2: %f, NO2: %f, PM2.5: %f", &CO, &SO2, &NO2, &PM25);
        fgets(line, sizeof(line), file);
        sscanf(line, " Temperatura: %f°C, Viento: %f m/s, Humedad: %f%%", &temperatura, &viento, &humedad);

        sum_CO[zona_id] += CO;
        sum_SO2[zona_id] += SO2;
        sum_NO2[zona_id] += NO2;
        sum_PM25[zona_id] += PM25;
        sum_temperatura[zona_id] += temperatura;
        sum_viento[zona_id] += viento;
        sum_humedad[zona_id] += humedad;
    }

    fclose(file);

    FILE *pred_file = fopen("predicciones.txt", "w");
    if (pred_file == NULL) {
        printf("Error al abrir el archivo de predicciones.\n");
        return;
    }

    for (int i = 0; i < num_zonasUrbanas; i++) {
        float promedio_CO = sum_CO[i] / dia;
        float promedio_SO2 = sum_SO2[i] / dia;
        float promedio_NO2 = sum_NO2[i] / dia;
        float promedio_PM25 = sum_PM25[i] / dia;
        float promedio_temperatura = sum_temperatura[i] / dia;
        float promedio_viento = sum_viento[i] / dia;
        float promedio_humedad = sum_humedad[i] / dia;

        float prediccion_CO = (promedio_CO + zona[i].CO) / 2;
        float prediccion_SO2 = (promedio_SO2 + zona[i].SO2) / 2;
        float prediccion_NO2 = (promedio_NO2 + zona[i].NO2) / 2;
        float prediccion_PM25 = (promedio_PM25 + zona[i].PM25) / 2;

        fprintf(pred_file, "Prediccion para (%s):\n", zona[i].nombre);
        fprintf(pred_file, "  CO: %.2f %s\n", prediccion_CO, (prediccion_CO > limiteCO) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(pred_file, "  SO2: %.2f %s\n", prediccion_SO2, (prediccion_SO2 > limiteSO2) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(pred_file, "  NO2: %.2f %s\n", prediccion_NO2, (prediccion_NO2 > limiteNO2) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(pred_file, "  PM2.5: %.2f %s\n", prediccion_PM25, (prediccion_PM25 > limitePM25) ? "(Excede el limite)" : "(Dentro del limite)");

        if (prediccion_CO > limiteCO || prediccion_SO2 > limiteSO2 || prediccion_NO2 > limiteNO2 || prediccion_PM25 > limitePM25) {
            fprintf(pred_file, "  Alerta: Se recomienda tomar medidas preventivas.\n");
        }

        printf("Prediccion para (%s):\n", zona[i].nombre);
        printf("  CO: %.2f %s\n", prediccion_CO, (prediccion_CO > limiteCO) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  SO2: %.2f %s\n", prediccion_SO2, (prediccion_SO2 > limiteSO2) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  NO2: %.2f %s\n", prediccion_NO2, (prediccion_NO2 > limiteNO2) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  PM2.5: %.2f %s\n", prediccion_PM25, (prediccion_PM25 > limitePM25) ? "(Excede el limite)" : "(Dentro del limite)");

        if (prediccion_CO > limiteCO || prediccion_SO2 > limiteSO2 || prediccion_NO2 > limiteNO2 || prediccion_PM25 > limitePM25) {
            printf("  Alerta: Se recomienda tomar medidas preventivas.\n");
        }
    }

    fclose(pred_file);
    printf("Predicciones calculadas y guardadas en predicciones.txt\n");
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
    printf("----Calculo de promedios historicos----\n");

    FILE *file = fopen("datos_historicos.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de datos históricos.\n");
        return;
    }

    float sum_CO[num_zonasUrbanas] = {0};
    float sum_SO2[num_zonasUrbanas] = {0};
    float sum_NO2[num_zonasUrbanas] = {0};
    float sum_PM25[num_zonasUrbanas] = {0};
    float sum_temperatura[num_zonasUrbanas] = {0};
    float sum_viento[num_zonasUrbanas] = {0};
    float sum_humedad[num_zonasUrbanas] = {0};

    char line[256];
    int dia = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Dia", 3) == 0) {
            dia++;
            continue;
        }

        int zona_id;
        char nombre[50];
        float CO, SO2, NO2, PM25, temperatura, viento, humedad;

        sscanf(line, " Zona %d (%[^)]):", &zona_id, nombre);
        fgets(line, sizeof(line), file);
        sscanf(line, " CO: %f, SO2: %f, NO2: %f, PM2.5: %f", &CO, &SO2, &NO2, &PM25);
        fgets(line, sizeof(line), file);
        sscanf(line, " Temperatura: %f°C, Viento: %f m/s, Humedad: %f%%", &temperatura, &viento, &humedad);

        sum_CO[zona_id] += CO;
        sum_SO2[zona_id] += SO2;
        sum_NO2[zona_id] += NO2;
        sum_PM25[zona_id] += PM25;
        sum_temperatura[zona_id] += temperatura;
        sum_viento[zona_id] += viento;
        sum_humedad[zona_id] += humedad;
    }

    fclose(file);

    FILE *prom_file = fopen("promedios_historicos.txt", "w");
    if (prom_file == NULL) {
        printf("Error al abrir el archivo de promedios históricos.\n");
        return;
    }

    for (int i = 0; i < num_zonasUrbanas; i++) {
        float promedio_CO = sum_CO[i] / dia;
        float promedio_SO2 = sum_SO2[i] / dia;
        float promedio_NO2 = sum_NO2[i] / dia;
        float promedio_PM25 = sum_PM25[i] / dia;
        float promedio_temperatura = sum_temperatura[i] / dia;
        float promedio_viento = sum_viento[i] / dia;
        float promedio_humedad = sum_humedad[i] / dia;

        fprintf(prom_file, "Promedios historicos para (%s):\n", zona[i].nombre);
        fprintf(prom_file, "  CO: %.2f %s\n", promedio_CO, (promedio_CO > 4.0) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(prom_file, "  SO2: %.2f %s\n", promedio_SO2, (promedio_SO2 > 40.0) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(prom_file, "  NO2: %.2f %s\n", promedio_NO2, (promedio_NO2 > 25.0) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(prom_file, "  PM2.5: %.2f %s\n", promedio_PM25, (promedio_PM25 > 15.0) ? "(Excede el limite)" : "(Dentro del limite)");
        fprintf(prom_file, "  Temperatura: %.2f°C\n", promedio_temperatura);
        fprintf(prom_file, "  Viento: %.2f m/s\n", promedio_viento);
        fprintf(prom_file, "  Humedad: %.1f%%\n", promedio_humedad);
        
        printf("Promedios historicos para (%s):\n", zona[i].nombre);
        printf("  CO: %.2f %s\n", promedio_CO, (promedio_CO > 4.0) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  SO2: %.2f %s\n", promedio_SO2, (promedio_SO2 > 40.0) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  NO2: %.2f %s\n", promedio_NO2, (promedio_NO2 > 25.0) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  PM2.5: %.2f %s\n", promedio_PM25, (promedio_PM25 > 15.0) ? "(Excede el limite)" : "(Dentro del limite)");
        printf("  Temperatura: %.2f°C\n", promedio_temperatura);
        printf("  Viento: %.2f m/s\n", promedio_viento);
        printf("  Humedad: %.1f%%\n", promedio_humedad);
    }

    fclose(prom_file);
    printf("Promedios historicos calculados y guardados en promedios_historicos.txt\n");
}