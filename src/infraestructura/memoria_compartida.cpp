#include "memoria_compartida.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int crear_clave_memoria(key_t clave, size_t tamaño)
{
    int id = shmget(clave, tamaño, IPC_CREAT | 0666);
    if (id == -1)
    {
        perror("Error al crear memoria compartida");
        exit(EXIT_FAILURE);
    }

    return id;
}

void* obtener_memoria(int id)
{
    void* ptr = shmat(id, NULL, 0);
    if (ptr == (void*)-1)
    {
        perror("Error al obtener puntero a memoria");
        exit(EXIT_FAILURE);
    }
    
    return ptr;
}


void liberar_memoria(void* ptr)
{
    if(shmdt(ptr) == -1)
    {
        perror("Error al liberar memoria");
        exit(EXIT_FAILURE);
    }
}

void eliminar_memoria(int id)
{
    if(shmctl(id, IPC_RMID, NULL) == -1)
    {
        perror("Error al eliminar memoria");
        exit(EXIT_FAILURE);
    }
}