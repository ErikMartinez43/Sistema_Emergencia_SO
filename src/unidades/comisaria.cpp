#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "tipos.h"
#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"

GestionMemoria memoria;
GestionSemaforos semaforos;

bool inicializar_entorno()
{
    key_t clave = 0x1234;

    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if (!memoria.ptr_memoria)
    {
        fprintf(stderr, "[ERROR] No se pudo conectar a la memoria compartida.\n");
        return false;
    }

    semaforos = crear_conjunto_semaforos(clave, 8);
    if (semaforos.sem_id == -1)
    {
        fprintf(stderr, "[ERROR] No se pudo conectar al conjunto de semáforos.\n");
        return false;
    }

    return true;
}

// Procesa una llamada policial y deriva a subestación
void atender_llamadas_policiales()
{
    while (1)
    {
        if (!tomar_semaforo(&semaforos, 0, 0)) continue;

        MemoriaCompartida* mem = memoria.ptr_memoria;

        for (int i = 0; i < mem->contador_llamadas; ++i)
        {
            Llamada* l = &mem->llamadas[i];

            if (l->estado == LLAMADA_PENDIENTE &&
                (l->tipo == LLAMADA_POLICIAL || 
                 l->tipo == LLAMADA_COMBINADA_MP ||
                 l->tipo == LLAMADA_COMBINADA_PB ||
                 l->tipo == LLAMADA_TOTAL))
            {
                printf("[COMISARÍA] Atendiendo llamada %d en zona %d\n", l->id, l->zona.codigo);

                // Marcar como en atención
                l->estado = LLAMADA_EN_ATENCION;
                l->tiempos.asignacion = time(NULL);

                // Derivar a subestación (simulado por ahora)
                // → Aquí se podría usar fork para crear un proceso hijo

                break; // solo procesamos una a la vez
            }
        }

        liberar_semaforo(&semaforos, 0);

        sleep(1); // Espera antes de volver a buscar
    }
}

int main()
{
    if (!inicializar_entorno()) return 1;

    printf("[COMISARÍA] Proceso iniciado. PID: %d\n", getpid());

    atender_llamadas_policiales();

    return 0;
}
