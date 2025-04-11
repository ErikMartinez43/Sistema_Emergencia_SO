#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "tipos.h"
#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"

GestionMemoria memoria;
GestionSemaforos semaforos;

// Elimina una llamada de memoria compartida una vez finalizada
/*void eliminar_llamada_finalizada(MemoriaCompartida* mem, int id_llamada)
{
    bool encontrada = false;

    for (int i = 0; i < mem->contador_llamadas; ++i)
    {
        if (mem->llamadas[i].id == id_llamada && mem->llamadas[i].estado == LLAMADA_FINALIZADA)
        {
            encontrada = true;
            // Mover las demás llamadas para ocupar el espacio vacío
            for (int j = i; j < mem->contador_llamadas - 1; ++j)
            {
                mem->llamadas[j] = mem->llamadas[j + 1];
            }
            mem->contador_llamadas--;  // Reducir el contador de llamadas activas
            printf("[INFO] Llamada %d eliminada correctamente de la memoria.\n", id_llamada);
            break;
        }
    }

    if (!encontrada)
        fprintf(stderr, "[ADVERTENCIA] No se encontró llamada %d para eliminar.\n", id_llamada);
}*/

bool inicializar_entorno()
{
    key_t clave = 0x1234;
    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if (!memoria.ptr_memoria)
    {
        fprintf(stderr, "[PATRULLA] Error conectando a memoria.\n");
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

void atender_llamada(int id_unidad, int id_llamada)
{
    tomar_semaforo(&semaforos, 0, 0);
    MemoriaCompartida* mem = memoria.ptr_memoria;

    // Patrulla ocupada
    for (int i = 0; i < mem->contador_unidades; ++i)
        if (mem->unidades[i].id == id_unidad)
            mem->unidades[i].estado = UNIDAD_OCUPADA;

    printf("[PATRULLA] Unidad %d atendiendo llamada policial %d\n", id_unidad, id_llamada);

    sleep(3); // simulación tiempo atención

    // Finalizar llamada
    for (int i = 0; i < mem->contador_llamadas; ++i) {
        if (mem->llamadas[i].id == id_llamada) {
            mem->llamadas[i].estado = LLAMADA_FINALIZADA;
            mem->llamadas[i].tiempos.resolucion = time(NULL);
            printf("[PATRULLA] Llamada policial %d finalizada.\n", id_llamada);
            break;
        }
    }

    eliminar_llamada_finalizada(mem, id_llamada);

    // Patrulla disponible nuevamente
    for (int i = 0; i < mem->contador_unidades; ++i)
        if (mem->unidades[i].id == id_unidad)
            mem->unidades[i].estado = UNIDAD_DISPONIBLE;

    liberar_semaforo(&semaforos, 0);
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        fprintf(stderr, "[PATRULLA] Uso: %s <id_unidad> <id_llamada>\n", argv[0]);
        return 1;
    }
    if (!inicializar_entorno()) return 1;
    atender_llamada(atoi(argv[1]), atoi(argv[2]));
    return 0;
}