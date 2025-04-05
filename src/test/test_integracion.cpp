#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/wait.h>

#include "include/memoria_compartida.h"
#include "include/semaforos.h"

#define CLAVE_MEMORIA 1234
#define CLAVE_SEMAFORO 5678

using namespace std;

int main()
{
    int shm_id = crear_clave_memoria(CLAVE_MEMORIA, sizeof(int));
    int* contador = (int*) get_memoria(shm_id);
    *contador = 0;

    int sem_id = crear_semaforos(CLAVE_SEMAFORO, 1);
    inicializar_semaforo(sem_id, 0, 1);

    pid_t pid = fork();

    if(pid_t == -1)
    {
        perror("Error al hacer fork\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++)
    {
        tomar_semaforo(sem_id, 0);
        int copia = *contador;
        usleep(100000);
        copia++;
        *contador = copia;

        cout <<"Proceso" <<getpid() <<"Incremento contador a "<< *contador << endl;
        
        liberar_semaforo(sem_id, 0);
        sleep(1);
    }

    if(pid > 0)
    {
        wait(NULL);

        liberar_memoria(contador);
        eliminar_memoria(shm_id);
        eliminar_semaforo(sem_id);

        cout << "Recursos limpiados por el proceso padre.\n"
    }


    return 0;
}