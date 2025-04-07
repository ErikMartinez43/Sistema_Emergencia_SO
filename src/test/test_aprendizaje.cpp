#include "memoria_compartida.h"
#include "modulo_aprendizaje.h"
#include "interfaces.h"
#include <iostream>
#include <string.h>

using namespace std;

int main() {
    // Crear memoria compartida
    int shm_id = crear_clave_memoria(1234, sizeof(MemoriaCompartida));
    if (shm_id == -1) {
        perror("Error creando memoria");
        return 1;
    }

    // Obtener puntero a memoria
    MemoriaCompartida* mem = (MemoriaCompartida*) obtener_memoria(shm_id);
    if (mem == nullptr) {
        perror("Error obteniendo memoria");
        return 1;
    }

    // Simular una zona de riesgo
    ZonaRiesgo zona;
    zona.codigo_zona = 78;
    strcpy(zona.nombre, "Colonia El Pedregal");
    zona.zona_general = ZONA_SUR;
    zona.nivel_riesgo = RIESGO_ALTO;
    zona.actividad_criminal = ACTIVIDAD_CRIMEN_ORGANIZADO;
    zona.tipo_terreno = TERRENO_MONTANIOSO;

    // Insertarla en la memoria compartida
    mem->zonas[0] = zona;

    // Ejecutar el módulo de aprendizaje
    int tipo_unidad = -1;
    int tipo_vehiculo = -1;
    aprendizaje_recomendar_respuesta(mem, 78, LLAMADA_COMBINADA_MB, &tipo_unidad, &tipo_vehiculo);

    // Mostrar resultado
    cout << "Zona: " << zona.nombre << endl;
    cout << "Unidad sugerida: " << obtener_tipo_unidad(tipo_unidad) << endl;
    cout << "Vehículo sugerido: " << tipo_vehiculo << endl;

    // Limpiar memoria
    eliminar_memoria(shm_id);
    return 0;
}
