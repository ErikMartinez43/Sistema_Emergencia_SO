#include "semaforos.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#if defined (__linux__)
typedef union {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}semun;
#endif

//Operacion semop con timeout
static int semop_timeout(int semid, struct sembuf *sops, size_t nsops, int timeout_ms)
{
    if(timeout_ms <= 0)
    {
        return semop(semid, sops, nsops);
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout_ms / 1000;
    ts.tv_nsec += (timeout_ms % 1000) * 1000000;

    return semtimedop(semid, sops, nsops, &ts);
}

GestionSemaforos crear_conjunto_semaforos(key_t clave, int num_semaforos)
{
    GestionSemaforos gs = {.sem_id = -1, .num_semaforos = num_semaforos, .creado = false};
    
    if(num_semaforos <= 0 || num_semaforos > MAX_SEMAFOROS)
    {
        fprintf(stderr, "Numero de semaforos invalido: %d\n", num_semaforos);
        return gs;
    }

    //intentar crear un nuevo conjunto
    gs.sem_id = semget(clave, num_semaforos, IPC_CREAT | IPC_EXCL | PERMISOS_SEM);
    if(gs.sem_id != -1)
    {
        gs.creado = true;
        return gs;
    }

    //si ya existe, unirse al conjunto existente
    if(errno == EEXIST)
    {
        gs.sem_id = semget(clave, num_semaforos, PERMISOS_SEM);
        if(gs.sem_id != -1)
        {
            return gs;
        }
    }

    perror("Error al crear/obtener conjunto de semaforos");
    gs.sem_id = -1;
    return gs;
}

bool inicializar_semaforo(GestionSemaforos *gs, int num_semaforo, int valor)
{
    if(!gs || gs->sem_id == -1 || num_semaforo < 0 || num_semaforo >= gs->num_semaforos)
    {
        fprintf(stderr, "parametros invalidos para incializacion\n");
        return false;
    }

    semun arg;
    arg.val = valor;
    if (semctl(gs->sem_id, num_semaforo, SETVAL, arg) == -1)
    {
        perror("Error al inicializar semaforo\n");
        return false;
    }
    return true;
}

bool tomar_semaforo(GestionSemaforos *gs, int num_semaforo, int timeout_ms)
{
    if(!gs || gs->sem_id == -1 ||  num_semaforo < 0 || num_semaforo >= gs->num_semaforos )
    {
        fprintf(stderr, "Parametros invalidos para tomar semafor\n");
        return false;
    }

    struct sembuf op = {
        .sem_num = (unsigned short)num_semaforo,
        .sem_op = -1, //decrementa el semaforo (operacion wait)
        .sem_flg = 0
    };

    if(semop_timeout(gs->sem_id, &op, 1, timeout_ms) == -1)
    {
        if(errno == EAGAIN)
        {
            fprintf(stderr, "Timeout al tomar semaforo %d\n", num_semaforo);
        }else
        {
            perror("Error al tomar semaforo\n");
        }
        return false;
    }

    return true;
}

bool liberar_semaforo(GestionSemaforos *gs, int num_semaforo)
{
    if(!gs || gs->sem_id == -1 || num_semaforo < 0 || num_semaforo >= gs->num_semaforos)
    {
        fprintf(stderr, "Parametros invalidos para liberar semaforo\n");
        return false;
    }

    struct sembuf op = {
        .sem_num = (unsigned short)num_semaforo,
        .sem_op = 1, //incrementa el semaforo (operacion signal)
        .sem_flg = 0
    };
    
    if (semop(gs->sem_id, &op, 1)== -1)
    {
        perror("Error al liberar semaforo\n");
        return false;
    }
    return true;   
}


void eliminar_conjunto_semaforos(GestionSemaforos *gs)
{
    if(!gs || gs->sem_id == -1)
    {
        return;
    }

    //solo eliminar si fuimos los creadores
    if(gs->creado)
    {
        if(semctl(gs->sem_id, 0, IPC_RMID) == -1)
        {
            perror("Advertencia: Error al eliminar conjunto de semaforos");
        }
    }
    gs->sem_id = -1;
    gs->creado = false;
}

int obtener_valor_semaforo(GestionSemaforos *gs, int num_semaforo)
{
    if (!gs || gs->sem_id == -1 || num_semaforo < 0 || num_semaforo >= gs->num_semaforos)
    {
        fprintf(stderr, "Parámetros inválidos para obtener valor de semáforo\n");
        return -1;
    }

    int val = semctl(gs->sem_id, num_semaforo, GETVAL);
    if (val == -1)
    {
        perror("Error al obtener valor del semáforo");
    }
    return val;
}
