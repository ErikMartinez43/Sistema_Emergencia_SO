#ifndef APRENDIZAJE_H
#define APRENDIZAJE_H

#include "tipos.h"

void aprendizaje_recomendar_respuesta(
    MemoriaCompartida* mem,
    int codigo_zona,
    int tipo_llamada,
    int* tipo_unidad,
    int* tipo_vehiculo
 );

#endif //fin de APRENDIZAJE_H