#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

GestionMemoria memoria;
GestionSemaforos semaforos;

// --------------------------------------
// Inicialización del entorno
// --------------------------------------
bool inicializar_entorno()
{
    key_t clave = 0x1234;
    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    semaforos = crear_conjunto_semaforos(clave, 8);
    if (!memoria.ptr_memoria || semaforos.sem_id == -1) return false;

    for (int i = 0; i < semaforos.num_semaforos; ++i)
        inicializar_semaforo(&semaforos, i, 1);

    return true;
}

// --------------------------------------
// Inicializar unidades disponibles
// --------------------------------------
void inicializar_unidades()
{
    if (tomar_semaforo(&semaforos, 1, 0)) {
        MemoriaCompartida* mem = memoria.ptr_memoria;
        //INICIALIZAR PATRULLAS
        for (int i = 0; i < 5; ++i) {
            Unidad u;
            u.id = 100 + i;
            u.tipo = UNIDAD_PATRULLA;
            u.estado = UNIDAD_DISPONIBLE;
            u.tipo_terreno = static_cast<TipoTerreno>(rand() % 4);
            u.zona.codigo = 100 + rand() % 100;
            u.zona.nombre[0] = '\0';
            u.zona.latitud = 0;
            u.zona.longitud = 0;
            u.zona.descripcion[0] = '\0';
            u.prioridad = RIESGO_BAJO;
            u.timestamp = time(NULL);
            mem->unidades[mem->contador_unidades++] = u;
        }
        //INICIALIZAR BOMBEROS
        for (int i = 0; i < 5; ++i) {
            Unidad u;
            u.id = 100 + i;
            u.tipo = UNIDAD_BOMBEROS;
            u.estado = UNIDAD_DISPONIBLE;
            u.tipo_terreno = static_cast<TipoTerreno>(rand() % 4);
            u.zona.codigo = 100 + rand() % 100;
            u.zona.nombre[0] = '\0';
            u.zona.latitud = 0;
            u.zona.longitud = 0;
            u.zona.descripcion[0] = '\0';
            u.prioridad = RIESGO_BAJO;
            u.timestamp = time(NULL);
            mem->unidades[mem->contador_unidades++] = u;
        }
        //INICIALIZAR AMBULANCIAS
        for (int i = 0; i < 5; ++i) {
            Unidad u;
            u.id = 100 + i;
            u.tipo = UNIDAD_AMBULANCIA;
            u.estado = UNIDAD_DISPONIBLE;
            u.tipo_terreno = static_cast<TipoTerreno>(rand() % 4);
            u.zona.codigo = 100 + rand() % 100;
            u.zona.nombre[0] = '\0';
            u.zona.latitud = 0;
            u.zona.longitud = 0;
            u.zona.descripcion[0] = '\0';
            u.prioridad = RIESGO_BAJO;
            u.timestamp = time(NULL);
            mem->unidades[mem->contador_unidades++] = u;
        }

        liberar_semaforo(&semaforos, 1);
        printf("[MAIN] Unidades inicializadas correctamente.\n");
    }
}

// --------------------------------------
// Lanzar procesos secundarios
// --------------------------------------
void lanzar_proceso(const char* ruta, const char* nombre)
{
    pid_t pid = fork();
    if (pid == 0) {
        execl(ruta, nombre, NULL);
        perror("[MAIN] Error al lanzar proceso");
        exit(1);
    }
    else if (pid > 0) {
        printf("[MAIN] Proceso %s lanzado con PID: %d\n", nombre, pid);
    }
    else {
        perror("[MAIN] Error en fork()");
    }
}

// --------------------------------------
// Entrada principal
// --------------------------------------
int main()
{
    srand(time(NULL));

    if (!inicializar_entorno()) {
        fprintf(stderr, "[MAIN] Error en la inicialización.\n");
        return 1;
    }

    inicializar_unidades();

    // Lanzar todos los procesos
    lanzar_proceso("./bin/hospital", "hospital");
    lanzar_proceso("./bin/comisaria", "comisaria");
    lanzar_proceso("./bin/bomberos", "bomberos");
    lanzar_proceso("./bin/generador", "generador");

    printf("[MAIN] Todos los procesos fueron lanzados.\n");

    // Mantener el proceso main activo para monitoreo (opcional)
    while (1) {
        pause();  // Espera indefinida a señales (podés reemplazar por sleep)
    }

    return 0;
}
