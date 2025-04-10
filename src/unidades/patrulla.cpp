#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
        fprintf(stderr, "[PATRULLA] Error conectando a memoria compartida.\n");
        return false;
    }

    semaforos = crear_conjunto_semaforos(clave, 8);
    if (semaforos.sem_id == -1)
    {
        fprintf(stderr, "[PATRULLA] Error conectando a semáforos.\n");
        return false;
    }

    return true;
}

void simular_atencion(int unidad_id, int llamada_id)
{
    MemoriaCompartida* mem = memoria.ptr_memoria;

    if (!tomar_semaforo(&semaforos, 2, 0)) return;

    printf("[PATRULLA] Unidad %d atendiendo llamada %d...\n", unidad_id, llamada_id);

    // Buscar la unidad y marcarla como ocupada
    for (int i = 0; i < mem->contador_unidades; ++i)
    {
        if (mem->unidades[i].id == unidad_id)
        {
            mem->unidades[i].estado = UNIDAD_OCUPADA;
            break;
        }
    }

    liberar_semaforo(&semaforos, 2);

    // Simular tiempo de intervención
    sleep(3); // tiempo de atención

    if (!tomar_semaforo(&semaforos, 2, 0)) return;

    // Marcar unidad como libre nuevamente
    for (int i = 0; i < mem->contador_unidades; ++i)
    {
        if (mem->unidades[i].id == unidad_id)
        {
            mem->unidades[i].estado = UNIDAD_DISPONIBLE;
            mem->unidades[i].timestamp = time(NULL);
            break;
        }
    }

    liberar_semaforo(&semaforos, 2);

    printf("[PATRULLA] Unidad %d finalizó intervención en llamada %d\n", unidad_id, llamada_id);
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "[USO] ./patrulla <unidad_id> <llamada_id>\n");
        return 1;
    }

    int unidad_id = atoi(argv[1]);
    int llamada_id = atoi(argv[2]);

    if (!inicializar_entorno()) return 1;

    simular_atencion(unidad_id, llamada_id);

    return 0;
}
