#include "memoria_compartida.h"
#include "semaforos.h"
#include "modulo_aprendizaje.h"
#include "interfaces.h"
#include <stdio.h>
#include <string.h>

void verificar_estado_sistema(MemoriaCompartida* mem, GestionSemaforos* gs);

// Entrada principal para pruebas de integración del sistema
int main()
{
    key_t clave = 0x1234;
    GestionMemoria gm = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    GestionSemaforos gs = crear_conjunto_semaforos(clave, 8);

    if (gs.creado)
    {
        for (int i = 0; i < gs.num_semaforos; ++i)
        {
            inicializar_semaforo(&gs, i, 1);
        }
    }

    // Simulación de una llamada pendiente
    /*int i = gm.ptr_memoria->contador_llamadas++;
    gm.ptr_memoria->llamadas[i].id = 1;
    gm.ptr_memoria->llamadas[i].tipo = LLAMADA_POLICIAL;
    gm.ptr_memoria->llamadas[i].tipo_terreno = TERRENO_URBANO;
    gm.ptr_memoria->llamadas[i].estado = LLAMADA_PENDIENTE;
    gm.ptr_memoria->llamadas[i].zona.codigo = 101;
    gm.ptr_memoria->llamadas[i].tiempos.creacion = time(NULL);*/
    printf("[INFO] Solo se registrara unidad, no se generara llamada aqui.\n");

    // Simulación de una unidad disponible
    int u = gm.ptr_memoria->contador_unidades++;
    gm.ptr_memoria->unidades[u].id = 10;
    gm.ptr_memoria->unidades[u].tipo = UNIDAD_PATRULLA;
    gm.ptr_memoria->unidades[u].estado = UNIDAD_DISPONIBLE;
    gm.ptr_memoria->unidades[u].zona.codigo = 101;
    gm.ptr_memoria->unidades[u].tipo_terreno = TERRENO_URBANO;

    // Búsqueda de llamada y unidad disponibles
    Llamada* llamada = obtener_llamada_disponible(gm.ptr_memoria);
    Unidad* unidad = buscar_unidad_disponible(gm.ptr_memoria, UNIDAD_PATRULLA);

    if (llamada && unidad)
    {
        asignar_unidad(unidad, llamada->id);
        llamada->estado = LLAMADA_EN_ATENCION;
    }

    // Visualización del estado actual del sistema
    verificar_estado_sistema(gm.ptr_memoria, &gs);

    destruir_memoria_compartida(&gm);
    eliminar_conjunto_semaforos(&gs);

    return 0;
}

// Visualiza el estado de los contadores de memoria compartida y los semáforos
void verificar_estado_sistema(MemoriaCompartida* mem, GestionSemaforos* gs)
{
    if (!mem)
    {
        fprintf(stderr, "[ERROR] Memoria no inicializada.\n");
        return;
    }

    printf("\n=== ESTADO DEL SISTEMA ===\n");
    printf("Llamadas activas: %d\n", mem->contador_llamadas);
    printf("Unidades registradas: %d\n", mem->contador_unidades);
    printf("Incidentes activos: %d\n", mem->contador_incidentes);
    printf("Zonas de riesgo definidas: %d\n", mem->contador_zonas);

    if (!gs || gs->sem_id == -1)
    {
        fprintf(stderr, "[ADVERTENCIA] Semáforos no disponibles.\n");
        return;
    }

    printf("\n=== ESTADO DE LOS SEMÁFOROS ===\n");
    for (int i = 0; i < gs->num_semaforos; ++i)
    {
        int val = obtener_valor_semaforo(gs, i);
        if (val != -1)
        {
            printf("Semáforo [%d] → %d\n", i, val);
        }
    }
    printf("===========================\n\n");
}
