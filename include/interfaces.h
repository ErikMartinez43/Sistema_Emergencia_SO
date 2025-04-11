#ifndef INTERFACES_H
#define INTERFACES_H

#include "tipos.h"
#include "estados.h"
/**
 * INTERFACES GENERALES ENTRE MODULOS DEL SISTEMA
 */

//FUNCIONES SOBRE LLAMADAS
/*
    *Busca una llamada en estado pendiente dentro de la memoria
    * param mem Puntero a la memoria compartida
    * returna Puntero a la llamada disponible, o NULL, si no hay.
*/
Llamada* obtener_llamada_disponible(MemoriaCompartida* mem);

/*
    *marca una llamada como finalizada
    *parametro llamada puntero a la llamada
*/
void finalizar_llamada(Llamada* llamada);

/*
//FUNCIONES SOBRE UNIDADES
*/
/**
 * busca una unidad disponible del tipo especificado
 * parametro mem puntero a la memoria compartida
 * parametro tipo, tipo de unidad(PATRULLA, AMBULANCIA, BOMBEROS)
 * retorna un puntero a la unidad libre o null si no la hay
 */
Unidad* buscar_unidad_disponible(MemoriaCompartida* mem, TipoUnidad tipo);
/**
 * Asigna una unidad a una llamada especifica
 * parametro unidad, puntero a la unidad
 * parametro llamada_id, ID de la llamada que atendera
 */
void asignar_unidad(Unidad* unidad, int llamada_id);

//FUNCIONES SOBRE ZONAS DE RIESGO
/**
 * Determina si una zona tiene alto riesgo
 * parametro mem, puntero a la memoria copartida
 * parametro codigo_zona, codigo de la zona a evaluar
 * retorna 1 si es de riesto alto, 0 si no lo es
 */
int zona_riesgosa(MemoriaCompartida* mem, int codigo_zona);

/**
 * devuelve un puntero a la zona de riesgo por codigo
 * parametro mem puntero a la memoria compartida
 * parametro codigo_zona codigo a buscar
 * retorna puntero a la estructura ZonaRiesgo, o NULL su no existe
 */

ZonaRiesgo* obtener_codigo_zona(MemoriaCompartida* mem, int codigo_zona);

//FUNCIONES AUXILIARES DE DESCRIPCION

/**
 * retorna una cadena string con la descripcion del nivel de riesgo
 */

const char* obtener_nombre_riesgo(NivelRiesgo nivel);
/**
 * retorna una cadena que describe el tipo de llamada
 */
const char* obtener_tipo_llamada(TipoLlamada tipo);
/**
 * retorna un string que describe actividad criminal
 */
const char* obtener_actividad_criminal(ActividadCriminal actividad);
/**
 * devuelve un string que describe el tipo de unidad
 */
const char* obtener_tipo_unidad(TipoUnidad tipo_unidad);
/**
 * devuelve descripcion de gravedad del paciente
 */
const char* obtener_gravedad(GravedadPaciente gravedad);

void eliminar_llamada_finalizada(MemoriaCompartida* mem, int id_llamada);

void limpiar_llamadas_finalizadas(MemoriaCompartida* mem);

#endif //INTERFACES_H