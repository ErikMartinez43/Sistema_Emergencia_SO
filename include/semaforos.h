#ifndef SEMAFOROS_H
#define SEMAFOROS_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdbool.h>

#define MAX_SEMAFOROS 20    //maximo numero de semaforos por conjunto
#define PERMISOS_SEM 0644 // Escritura y lectura solo para el usuario

//union necesaria para operaciones semctl,
#ifndef _SEMUN_DEFINED
#define _SEMUN_DEFINED
union
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}semun;
#endif

//estructura para manejo seguro de semaforos
typedef struct
{
    int sem_id;           //ID del conjunto de semaforos
    int num_semaforos;   //numero de semaforos en el conjunto
    bool creado;        // indica si este proceso creo los semaforos
}GestionSemaforos;

/**
 * @brief Crea o se une a un conjunto de semaforos
 * @param clave Clave IPC para el conjunto
 * @param num_semaforos Numero de semaforos en el conjunto
 * @return Estructura GestionSemaforos inicializada
 */
GestionSemaforos crear_conjunto_semaforos(key_t clave, int num_semaforos);

/**
 * @brief Inicializa un semaforo con un valor especifico
 * @param gs Estructura de gestiom de semaforos
 * @param num_semaforo Indice del semaforo en el conjunto
 * @param valor Valor inicial del semaforo
 * @return true si tuvo exito, false en caso de error
 */
bool inicializar_semaforo(GestionSemaforos *gs, int num_semaforo, int valor);

/**
 * @brief opera sobre un semaforo (wait/take)
 * @param gs Estructura de gestion de semaforo
 * @param num_semaforo Indice del semaforo en el conjunto
 * @param timeout_ms Tiempo maximo de espera en milisegundos (0 para infinito)
 * @return true si tuvo exito, false en caso de error o timeout
 */
bool tomar_semaforo(GestionSemaforos *gs, int num_semaforo, int timeout_ms);

/**
 * @brief Libera un semaforo (signal/release)
 * @param gs Estructura de gestion de semaforos
 * @param num_semaforo Indice del semaforo en el conjunto
 * @return true si tuvo exito, false en caso de error
 */
bool liberar_semaforo(GestionSemaforos *gs, int num_semaforo);

/**
 * @brief Elimina un conjunto de semaforos
 * @param gs EStructura de gestion de semaforos
 * @note solo tiene efecto sie le proceso fue el creador
 */
 void eliminar_conjunto_semaforos(GestionSemaforos *gs);

 /**
 * @brief Obtiene el valor actual de un semáforo
 * @param gs Estructura de gestión de semáforos
 * @param num_semaforo Índice del semáforo
 * @return valor actual, o -1 en caso de error
 */
int obtener_valor_semaforo(GestionSemaforos *gs, int num_semaforo);

#endif