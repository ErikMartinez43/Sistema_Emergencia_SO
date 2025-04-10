#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "tipos.h"
#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"

GestionMemoria memoria;
GestionSemaforos semaforos;

bool inicializar_entorno()
{
    key_t clave = 0x1234;

    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if (!memoria.ptr_memoria)
    {
        fprintf(stderr, "[SUBESTACIÓN] Error conectando a la memoria.\n");
        return false;
    }

    semaforos = crear_conjunto_semaforos(clave, 8);
    if (semaforos.sem_id == -1)
    {
        fprintf(stderr, "[SUBESTACIÓN] Error conectando a semáforos.\n");
        return false;
    }

    return true;
}

void gestionar_intervenciones()
{
    while (1)
    {
        if (!tomar_semaforo(&semaforos, 0, 0)) continue;

        MemoriaCompartida* mem = memoria.ptr_memoria;

        for (int i = 0; i < mem->contador_llamadas; ++i)
        {
            Llamada* l = &mem->llamadas[i];

            if (l->estado == LLAMADA_EN_ATENCION &&
                (l->tipo == LLAMADA_POLICIAL || l->tipo == LLAMADA_COMBINADA_MP ||
                 l->tipo == LLAMADA_COMBINADA_PB || l->tipo == LLAMADA_TOTAL))
            {
                printf("[SUBESTACIÓN] Recibiendo llamada %d en zona %d. Buscando patrulla...\n",
                       l->id, l->zona.codigo);

                Unidad* patrulla = buscar_unidad_disponible(mem, UNIDAD_PATRULLA);

                if (patrulla)
                {
                    printf("[SUBESTACIÓN] Patrulla %d asignada a llamada %d\n", patrulla->id, l->id);
                    asignar_unidad(patrulla, l->id);

                    pid_t pid = fork();//Crea un nuevo proceso duplicando el actual, devuelve PID del hijo
                    if(pid == 0)
                    {
                        //Proceso hijo ejecuta binario de patrulla
                        char id_unidad[10], id_llamada[10];// crea buffers para guardar los IDs convertidos a texto
                        sprintf(id_unidad, "%d", patrulla->id); //convierte los id de enteros a cadenas
                        sprintf(id_llamada, "%d", l->id);
                        // execl() reemplaza el proceso hijo por el ejecutable "patrulla"
                        execl("./bin/patrulla", "patrulla", id_unidad, id_llamada, NULL);//si execl() funciona nada despues de aqui se ejecuta en el hijo
                        perror("[SUBESTACION] Error al lanzar patrulla");    //si execl() falla, imprime mensaje con su causa          
                        exit(1);//el hijo termina si falla
                    }
                    else if (pid > 0)//aqui se ejecuta el proceso padre (subestacion)
                    {
                        printf("[SUBESTACION] Proceso patrulla lanzado con PID %d\n", pid);//informa que se derivo correctamente a patrulla
                    }
                    else //fallo de fork()
                    {
                        perror("[SUBESTACION] Error en fork()");//perror usa mensaje del sistema
                    }
                    

                    // Simular que enviamos la llamada a patrulla (aquí iría fork a patrulla.cpp)
                    l->estado = LLAMADA_FINALIZADA;
                    l->tiempos.resolucion = time(NULL);
                }
                else
                {
                    printf("[SUBESTACIÓN] No hay patrullas disponibles para llamada %d\n", l->id);
                }

                break;
            }
        }

        liberar_semaforo(&semaforos, 0);
        sleep(1);
    }
}

int main()
{
    if (!inicializar_entorno()) return 1;

    printf("[SUBESTACIÓN] Proceso iniciado. PID: %d\n", getpid());

    gestionar_intervenciones();

    return 0;
}
