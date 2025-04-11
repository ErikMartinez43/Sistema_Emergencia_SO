#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>

#include "tipos.h"
#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"

GestionMemoria memoria;
GestionSemaforos semaforos;

// Inicializa memoria compartida y semáforos
bool inicializar_entorno()
{
    key_t clave = 0x1234;

    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if (!memoria.ptr_memoria)
    {
        fprintf(stderr, "[BOMBEROS] Error conectando a memoria.\n");
        return false;
    }

    semaforos = crear_conjunto_semaforos(clave, 8);
    if (semaforos.sem_id == -1)
    {
        fprintf(stderr, "[BOMBEROS] Error conectando a semáforos.\n");
        return false;
    }

    return true;
}

// Gestiona llamadas de tipo incendio o combinadas
void gestionar_incendios()
{
    while (1)
    {
        if (!tomar_semaforo(&semaforos, 0, 0)) continue;

        MemoriaCompartida* mem = memoria.ptr_memoria;

        for (int i = 0; i < mem->contador_llamadas; ++i)
        {
            Llamada* l = &mem->llamadas[i];

            if (l->estado == LLAMADA_PENDIENTE &&
                (l->tipo == LLAMADA_INCENDIO || 
                 l->tipo == LLAMADA_COMBINADA_MB || 
                 l->tipo == LLAMADA_COMBINADA_PB ||
                 l->tipo == LLAMADA_TOTAL))
            {
                printf("[BOMBEROS] Atendiendo llamada %d en zona %d\n", l->id, l->zona.codigo);
                l->estado = LLAMADA_EN_ATENCION;
                l->tiempos.asignacion = time(NULL);

                // Buscar unidad de bomberos disponible
                Unidad* unidad = buscar_unidad_disponible(mem, UNIDAD_BOMBEROS);

                if (unidad)
                {
                    printf("[BOMBEROS] Unidad %d asignada a llamada %d\n", unidad->id, l->id);
                    asignar_unidad(unidad, l->id);

                    // Lanzar proceso hijo: ./bin/vehiculos_bomberos
                    pid_t pid = fork();
                    if (pid == 0)
                    {
                        // Proceso hijo prepara argumentos
                        char id_unidad[10], id_llamada[10];
                        sprintf(id_unidad, "%d", unidad->id);
                        sprintf(id_llamada, "%d", l->id);

                        // Ejecutar binario
                        execl("./bin/vehiculos_bomberos", "vehiculos_bomberos", id_unidad, id_llamada, NULL);
                        perror("[BOMBEROS] Error al lanzar unidad de bomberos");
                        exit(1);
                    }
                    else if (pid > 0)
                    {
                        printf("[BOMBEROS] Proceso unidad bomberos lanzado con PID %d\n", pid);
                    }
                    else
                    {
                        perror("[BOMBEROS] Error en fork()");
                    }
                }
                else
                {
                    printf("[BOMBEROS] No hay unidades disponibles para llamada %d\n", l->id);
                }

                break; // Procesa una sola llamada por ciclo
            }
        }

        liberar_semaforo(&semaforos, 0);
        sleep(1); // Breve espera para no saturar CPU
    }
}

int main()
{
    if (!inicializar_entorno()) return 1;

    printf("[BOMBEROS] Proceso iniciado. PID: %d\n", getpid());

    gestionar_incendios();

    return 0;
}
