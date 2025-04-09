#ifndef MEMORIA_COMPARTIDA_H
#define MEMORIA_COMPARTIDA_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "tipos.h"

#define CLAVE_BASE 0x1234 //Clave base para memoria compartida
#define PERMISOS 0666 // Permisos 
/**
 * @brief Crea y gestiona segmentos de memoria compartida
 * 
 * Esta clase encapsula el manejo de memoria compartida para el sistema de emergencias
 * proporcionando un interfaz segura para acceso concurrente
 */
typedef struct
{
    int shm_id;                     //ID del segmento de memoria compartida
    MemoriaCompartida* ptr_memoria; //Puntero a la memoria compartida
    bool creado;                    //bandera para verificar si se creo el segmento
}GestionMemoria;

/**
 * @brief Crea o adjunta a un segmento de memoria compartida
 * @param clave Clave unica para el segmento
 * @param tamanio Tamaño del segmento a crear
 * @return Objeto GestionMemoria inicializado
 */
GestionMemoria crear_memoria_compartida(key_t clave, size_t tamanio);

/**
 * @brief Destruye un segmento de memoria compartida
 * @param gm Objeto GestionMemoria a destruir
 */
void destruir_memoria_compartida(GestionMemoria* gm);

/**
 * @brief Obtiene puntero a la memoria compartida
 * @param gm Obejto GestionMemoria
 * @return puntero a la memoria compartida o NULL en error
 */
MemoriaCompartida* obtener_memoria(GestionMemoria* gm);

/**
 * @brief Genera una clave unica para memoria compartida
 * @param ruta Ruta base para generacion de clave
 * @param id Identificador unico
 * @return Clave generada o -1 en erro
 */
static key_t generar_clave(const char* ruta, int id);

//funciones avanzadas para manejo seguro
int bloquear_memoria(GestionMemoria* gm);
int liberar_memoria(GestionMemoria* gm);


#endif
/**
 * @author erik
 */