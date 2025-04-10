#include "memoria_compartida.h"
#include "semaforos.h"
#include "interfaces.h"
#include "tipos.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

GestionMemoria memoria;
GestionSemaforos semaforos;

bool inicializar_entorno()
{
    key_t clave = 0x1234;
    //conectar memoria compartida
    memoria = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));
    if(memoria.ptr_memoria == NULL)
    {
        fprintf(stderr, "[ERROR] No se pudo conectar a la memoria compartida\n");
        return false;
    }
    //conectar semaforos (usar la misma clave y cantidad que en otros procesos)
    semaforos = crear_conjunto_semaforos(clave, 8);
    if(semaforos.sem_id == -1)
    {
        fprintf(stderr, "[ERROR] No se pudo conectar al conjunto de semaforos\n");
        return false;
    }
    return true;
}

Llamada generar_llamada(int id)
{
    Llamada nueva;
    nueva.id = id;

    //seleccionar tipo de llamada aleatoriamente
    nueva.tipo = static_cast<TipoLlamada>(rand()%7);

    //Terreno aleatorio
    nueva.tipo_terreno = static_cast<TipoTerreno>(rand()%4);
    
    //simular zona geografica aleatoria (codigos del 100 al 199)
    nueva.zona.codigo = 100 + rand()%100;

    //estado inicial
    nueva.estado = LLAMADA_PENDIENTE;

    //tiempos
    nueva.tiempos.creacion = time(NULL);
    nueva.tiempos.asignacion = 0;
    nueva.tiempos.resolucion = 0;

    //Asignar el PID del proceso (si aplica)
    nueva.operador = getpid();

    return nueva;
}

bool registrar_llamada(Llamada nueva)
{
    //bloquear acceso a llamadas
    if(!tomar_semaforo(&semaforos, 0, 0)) //semaforo 0 --> llamadas
    {
        return false;
    }

    MemoriaCompartida* mem = memoria.ptr_memoria;

    if(mem->contador_llamadas >= MAX_LLAMADAS)
    {
        fprintf(stderr, "[ERROR] No se pudo registrar mas llamadas. limite alcanzado.\n");
        liberar_semaforo(&semaforos, 0);
        return false;
    }

    //Insertar la llamada en la siguiente posicion libre
    mem->llamadas[mem->contador_llamadas] = nueva; //inserta la llamada en el arreglo llamdas
    mem->contador_llamadas++;//aumenta el contrador global de llamadas

    //liberar semaforo cuando termina
    liberar_semaforo(&semaforos, 0);

    return true;
}

int main()
{
    if(!inicializar_entorno()) return 1;

    srand(time(NULL));

    for(int i = 0; i < 10; ++i)
    {
        Llamada llamada = generar_llamada(i + 1);
        if(registrar_llamada(llamada))
        {
            printf("[v] Llamada %d registrada en zona %d, tipo %s\n",
                    llamada.id,
                    llamada.zona.codigo,
                    obtener_tipo_llamada(llamada.tipo));
        }
        else
        {
            printf("[✕] Fallo al registrar la llamada %d\n", llamada.id);
        }

        sleep(1); //espera 1 segundo entre llamadas
    }
    return 0;
}