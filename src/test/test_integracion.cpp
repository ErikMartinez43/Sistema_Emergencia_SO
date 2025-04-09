#include "semaforos.h"

int main(){
    //Crear conjunto de semaforos
    key_t clave = ftok("/tmp", 'S');
    GestionSemaforos gs = crear_conjunto_semaforos(clave, 3);
    
    if(gs.sem_id == -1)
    {
        return 1;
    }

    //incializar semaforo
    if(gs.creado)
    {
        inicializar_semaforo(&gs, 0, 1); //semaforo binario
        inicializar_semaforo(&gs, 1, 5); //semaforo contador
    }

    //uso tipico
    if(tomar_semaforo(&gs, 0, 1000)) //timeout de 1 s
    {   //seccion critica
        liberar_semaforo(&gs, 0);
    }

    //limpieza
    eliminar_conjunto_semaforos(&gs);
    return 0;
}
