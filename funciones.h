#define num_zonasUrbanas 5
#define prom_historico 30

struct zonaUrbana{
    int id;
    char nombre[50];
    float CO, SO2, NO2, PM25;
    float temperatura, viento, humedad;
};

void captureDatosActuales(struct zonaUrbana *zona);
void calcularPromediosHistoricos(struct zonaUrbana *zona, int num_datos);
void predictNivelesFuturos(struct zonaUrbana *zona);
void monitoreoContaminacionActual(struct zonaUrbana *zona);
void generateDatosHistoricos(struct zonaUrbana *zona);
void guardarDatosActuales(struct zonaUrbana *zona);
void mostrarDatosHistoricos();