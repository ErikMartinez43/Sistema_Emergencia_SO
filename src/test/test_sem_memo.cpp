#include "memoria_compartida.h"
#include "semaforos.h"
#include <stdio.h>

/**
 * @brief Verifica el estado actual del sistema de emergencias
 * 
 * Imprime los contadores de memoria compartida y el valor de los semáforos
 */
void verificar_estado_sistema(GestionMemoria *gm, GestionSemaforos *gs)
{
    if (!gm || !gm->ptr_memoria)
    {
        fprintf(stderr, "[Error] Memoria compartida no inicializada.\n");
        return;
    }

    printf("\n==== ESTADO DE LA MEMORIA COMPARTIDA ====\n");
    printf("Llamadas activas: %d\n", gm->ptr_memoria->contador_llamadas);
    printf("Unidades registradas: %d\n", gm->ptr_memoria->contador_unidades);
    printf("Incidentes activos: %d\n", gm->ptr_memoria->contador_incidentes);
    printf("Historial de aprendizaje: %d\n", gm->ptr_memoria->contador_historial);
    printf("Turnos asignados: %d\n", gm->ptr_memoria->contador_turnos);
    printf("Detenidos registrados: %d\n", gm->ptr_memoria->contador_detenidos);
    printf("Pacientes registrados: %d\n", gm->ptr_memoria->contador_pacientes);
    printf("Zonas de riesgo definidas: %d\n", gm->ptr_memoria->contador_zonas);

    if (!gs || gs->sem_id == -1)
    {
        fprintf(stderr, "[Advertencia] Conjunto de semáforos no disponible.\n");
        return;
    }

    printf("\n==== ESTADO DE LOS SEMÁFOROS ====\n");
    for (int i = 0; i < gs->num_semaforos; ++i)
    {
        int val = obtener_valor_semaforo(gs, i);
        if (val != -1)
        {
            printf("Semáforo [%d] → Valor actual: %d\n", i, val);
        }
    }

    printf("=====================================\n\n");
}

int main()
{
    key_t clave = 0x1234;
    GestionMemoria gm = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    GestionSemaforos gs = crear_conjunto_semaforos(clave, 8); // por ejemplo

    // Inicializa los semáforos 
    if (gs.creado)
    {
        for (int i = 0; i < gs.num_semaforos; i++)
        {
            inicializar_semaforo(&gs, i, 1);
        }
    }

    // Llamás a tu verificación
    verificar_estado_sistema(&gm, &gs);

    // limpiar
    destruir_memoria_compartida(&gm);
    eliminar_conjunto_semaforos(&gs);

    return 0;
}

