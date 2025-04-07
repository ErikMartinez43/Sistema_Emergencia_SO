#include "memoria_compartida.h"
#include "modulo_aprendizaje.h"
#include "interfaces.h"
#include <iostream>
#include <string.h>

using namespace std;

int main() {
    int shm_id = crear_clave_memoria(1234, sizeof(MemoriaCompartida));
    if (shm_id == -1) {
        perror("Error creando memoria");
        return 1;
    }

    MemoriaCompartida* mem = (MemoriaCompartida*) obtener_memoria(shm_id);
    if (mem == nullptr) {
        perror("Error obteniendo memoria");
        return 1;
    }

    // === Inicializar zonas ===
    ZonaRiesgo zona1 = {78, "Colonia El Pedregal", ZONA_SUR, ACTIVIDAD_CRIMEN_ORGANIZADO, RIESGO_ALTO, TERRENO_MONTANIOSO};
    ZonaRiesgo zona2 = {22, "Barrio El Centro", ZONA_CENTRO, ACTIVIDAD_NONE, RIESGO_BAJO, TERRENO_URBANO};

    mem->zonas[0] = zona1;
    mem->zonas[1] = zona2;

    // === Simular llamadas ===
    int tipo_unidad, tipo_vehiculo;

    cout << "\n===== LLAMADA MÉDICA desde zona 78 =====" << endl;
    aprendizaje_recomendar_respuesta(mem, 78, LLAMADA_MEDICA, &tipo_unidad, &tipo_vehiculo);
    cout << "Unidad: " << obtener_tipo_unidad(tipo_unidad) << endl;
    cout << "Vehículo: " << tipo_vehiculo << endl;

    cout << "\n===== LLAMADA POLICIAL desde zona 22 =====" << endl;
    aprendizaje_recomendar_respuesta(mem, 22, LLAMADA_POLICIAL, &tipo_unidad, &tipo_vehiculo);
    cout << "Unidad: " << obtener_tipo_unidad(tipo_unidad) << endl;
    cout << "Vehículo: " << tipo_vehiculo << endl;

    cout << "\n===== LLAMADA COMBINADA TOTAL desde zona 78 =====" << endl;
    aprendizaje_recomendar_respuesta(mem, 78, LLAMADA_TOTAL, &tipo_unidad, &tipo_vehiculo);
    cout << "Unidad: " << obtener_tipo_unidad(tipo_unidad) << endl;
    cout << "Vehículo: " << tipo_vehiculo << endl;

    eliminar_memoria(shm_id);
    return 0;
}
