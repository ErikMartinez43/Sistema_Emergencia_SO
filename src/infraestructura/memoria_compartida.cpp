#include "memoria_compartida.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

//Constantes de configuracion
#define MAX_INTENTOS 3
#define TIEMPO_ESPERA 1     //segundos entre reintentos
//#define PERMISOS 0644       //Permisos: usuario lectura/escritura, grupo lectura y otros lectura

GestionMemoria crear_memoria_compartida(key_t clave, size_t tamanio)
{
    GestionMemoria gm = {.shm_id = -1, .ptr_memoria = NULL, .creado = false};
    if(tamanio == 0)
    {
        fprintf(stderr, "Error: Tamaño no puede ser cero\n");
        return gm;
    }

    for (int intento = 0; intento < MAX_INTENTOS; ++intento)
    {
        gm.shm_id = shmget(clave, tamanio, IPC_CREAT | IPC_EXCL | PERMISOS);
        if(gm.shm_id != -1)
        {
            gm.creado = true;
            break;
        }

        //si ya existe, intentamos adjuntarnos
        if(errno == EEXIST)
        {
            gm.shm_id = shmget(clave, tamanio, PERMISOS);
            if(gm.shm_id != -1)
            {
                break;
            }
        }

        if(intento == MAX_INTENTOS -1)
        {
            fprintf(stderr, "Error: no se puedo crear/adjuntar memoria despues de %d intentos\n");
            return gm;
        }
        sleep(TIEMPO_ESPERA);
    }
    //adjuntar la memoria
    gm.ptr_memoria = (MemoriaCompartida*)shmat(gm.shm_id, NULL, 0);
    if(gm.ptr_memoria == (void*)-1)
    {
        perror("Error en shmat\n");
        gm.shm_id = -1;
        return gm;
    }
    //Inicializar si somos los creadores
    if(gm.creado)
    {
        memset(gm.ptr_memoria, 0, tamanio );
    }

    return gm;
}

void destruir_memoria_compartida(GestionMemoria *gm)
{
    if (!gm || gm->shm_id == -1)
    {
        return;
    }

    //desvincular memoria
    if(shmdt(gm->ptr_memoria) == -1)
    {
        perror("Advertencia: Error al desvincular memoria \n");
    }
    //solo la eliminamos si fuimos los creadores
    if(gm->creado)
    {
        if(shmctl(gm->shm_id, IPC_RMID, NULL) == -1)
        {
            perror("Advertencia: Error al eliminar segmento");
        }
    }

    gm->shm_id -1;
    gm->ptr_memoria;
    gm->creado = false;
}

MemoriaCompartida *obtener_memoria(GestionMemoria *gm)
{
    if(!gm || gm->shm_id == -1)
    {
        fprintf(stderr, "Error: memoria no inicializada \n");
        return NULL;
    }
    return gm->ptr_memoria;
}

static key_t generar_clave(const char *ruta, int id)
{
    if (!ruta)
    {
        fprintf(stderr, "Error: Ruta no puede ser NULL\n");
        return -1;
    }

    key_t clave = ftok(ruta, id);
    if(clave == -1)
    {
        perror("Error en ftok\n");
    }
    return clave;
}

int bloquear_memoria(GestionMemoria *gm)
{
    if(!gm || !gm->ptr_memoria)
    {
        fprintf(stderr, "Error: memoria no valida para bloqueo\n");
        return -1;
    }

    //implementacion basica
    //mas adelante usar semaforos
    printf("memoria bloqueada para acceso exclusivo\n");
    return 0;
}

int liberar_memoria(GestionMemoria *gm)
{
    if(!gm || gm->ptr_memoria)
    {
        fprintf(stderr, "Error: Memoria no valida para liberacion\n");
        return -1;
    }
    //implementacion basica, usar semaforos mas adelante
    printf("Memoria liberada para acceso\n");
    return 0;
}
/**
 * @author erik
 */