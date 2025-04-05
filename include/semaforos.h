#ifndef SEMAFOROS_H
#define SEMAFORS_H

#include <sys/types.h>

int crear_semaforos(key_t clave, int cantidad);

void inicializar_semaforo(int id, int num_semaforo, int valor);

void tomar_semaforo(int id, int num_semaforo);

void liberar_semaforo(int id, int num_semaforo);

void eliminar_semaforo(int id);

#endif