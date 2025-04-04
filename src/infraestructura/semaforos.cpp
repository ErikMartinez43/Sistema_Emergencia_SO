#include "semaforos.h"

#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

struct sembuf operacion;


int crear_semaforos(key_t clave, int cantidad)
{
    int id = semget(clave, cantidad, IPC_CREAT | 0666);
    if(id == -1)
    {
        perror("Error al crear semaforo\n");
        exit(EXIT_FAILURE);
    }

    return id;
}

void inicializar_semaforo(int id, int num_semaforo, int valor)
{
    if(semctl(id, num_semaforo, SETVAL, valor) == -1)
    {
        perror("Error al inicializar semaforo\n");
    }
}

void tomar_semaforo(int id, int num_semaforo)
{
    operacion.sem_num = num_semaforo;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;

    if(semop(id, &operacion, 1) == -1)
    {
        perror("Error al tomar semaforo\n");
        exit(EXIT_FAILURE);
    }

}

void liberar_semaforo(int id, int num_semaforo)
{
    operacion.sem_num = num_semaforo;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    if(semop(id, &operacion, 1) == -1)
    {
        perror("Error al liberar semaforo\n");
        exit(EXIT_FAILURE);
    }
}

void eliminar_semaforo(int id)
{
    if(semctl(id, 0, IPC_RMID) == -1)
    {
        perror("Error a eliminar semaforo\n");
        exit(EXIT_FAILURE);
    }
}
