#ifndef MODULO_APRENDIZAJE_H
#define MODULO_APRENDIZAJE_H

#include "tipos.h"
#include <time.h>

/**
 * Busca un registro de historial en base a la zona y tipo de incidente.
 * @param mem Memoria compartida
 * @param zona Código de zona
 * @param tipo Tipo de incidente (médico, policial, incendio, etc.)
 * @return Puntero al registro si existe, NULL si no se encontró
 */
RegistroAprendizaje* buscar_historial(MemoriaCompartida* mem, int zona, TipoIncidente tipo);

/**
 * Registra un nuevo incidente o actualiza uno existente.
 * @param mem Memoria compartida
 * @param zona Código de zona
 * @param tipo Tipo de incidente
 * @param terreno Tipo de terreno
 */
void registrar_incidente(MemoriaCompartida* mem, int zona, TipoIncidente tipo, TipoTerreno terreno);

/**
 * Estima el nivel de peligrosidad de una zona según el historial.
 * @param mem Memoria compartida
 * @param zona Código de zona
 * @return NivelRiesgo estimado
 */
NivelRiesgo calcular_peligrosidad(MemoriaCompartida* mem, int zona);

/**
 * Evalúa si una llamada es posiblemente falsa por comparación histórica.
 * @param mem Memoria compartida
 * @param zona Código de zona
 * @param tipo Tipo de incidente
 * @return 1 si es posiblemente falsa, 0 si no lo es
 */
int evaluar_falsa_alarma(MemoriaCompartida* mem, int zona, TipoIncidente tipo);

#endif // MODULO_APRENDIZAJE_H
