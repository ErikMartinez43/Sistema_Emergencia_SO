#ifndef MEMORIA_COMPARTIDA_H
#define MEMORIA_COMPARTIDA_H

#include <sys/types.h>

int crear_clave_memoria(key_t clave, size_t tamaño);

void* obtener_memoria(int id);

void liberar_memoria(void* ptr);

void eliminar_memoria(int id);

#endif