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

bool inicializar_entorno() {
    key_t clave = 0x1234;
    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if (!memoria.ptr_memoria) {
        fprintf(stderr, "[HOSPITAL] Error conectando a memoria.\n");
        return false;
    }

    semaforos = crear_conjunto_semaforos(clave, 8);
    if (semaforos.sem_id == -1) {
        fprintf(stderr, "[HOSPITAL] Error conectando a semaforos.\n");
        return false;
    }
    return true;
}

void gestionar_llamadas_medicas() {
    while (1) {
        if (!tomar_semaforo(&semaforos, 0, 0)) continue;

        MemoriaCompartida* mem = memoria.ptr_memoria;

        for (int i = 0; i < mem->contador_llamadas; ++i) {
            Llamada* l = &mem->llamadas[i];

            if (l->estado == LLAMADA_PENDIENTE &&
                (l->tipo == LLAMADA_MEDICA || 
                 l->tipo == LLAMADA_COMBINADA_MB ||
                 l->tipo == LLAMADA_COMBINADA_MP ||
                 l->tipo == LLAMADA_TOTAL))
            {
                printf("[HOSPITAL] Atendiendo llamada %d en zona %d\n", l->id, l->zona.codigo);
                l->estado = LLAMADA_EN_ATENCION;
                l->tiempos.asignacion = time(NULL);

                Unidad* ambulancia = buscar_unidad_disponible(mem, UNIDAD_AMBULANCIA);

                if (ambulancia) {
                    printf("[HOSPITAL] Ambulancia %d asignada a llamada %d\n", ambulancia->id, l->id);
                    asignar_unidad(ambulancia, l->id);

                    pid_t pid = fork();
                    if (pid == 0) {
                        char id_unidad[10], id_llamada[10];
                        sprintf(id_unidad, "%d", ambulancia->id);
                        sprintf(id_llamada, "%d", l->id);
                        execl("./bin/ambulancia", "ambulancia", id_unidad, id_llamada, NULL);
                        perror("[HOSPITAL] Error al lanzar ambulancia");
                        exit(1);
                    } else if (pid > 0) {
                        printf("[HOSPITAL] Ambulancia lanzada con PID %d\n", pid);
                    } else {
                        perror("[HOSPITAL] Error en fork()");
                    }
                } else {
                    printf("[HOSPITAL] No hay ambulancias disponibles para llamada %d\n", l->id);
                }
                break;  // procesar solo una llamada a la vez
            }
        }

        liberar_semaforo(&semaforos, 0);
        sleep(1);  // espera breve antes de volver a revisar
    }
}

int main() {
    if (!inicializar_entorno()) return 1;

    printf("[HOSPITAL] Proceso hospital listo. PID: %d\n", getpid());

    gestionar_llamadas_medicas();

    return 0;
}