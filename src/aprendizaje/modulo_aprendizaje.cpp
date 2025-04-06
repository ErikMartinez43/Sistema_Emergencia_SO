#include "interfaces.h"
#include <stdio.h>


void aprendizaje_recomendar_respuesta(
    MemoriaCompartida* mem,
    int codigo_zona;
    int tipo_llamada;
    int* tipo_unidad;
    int* tipo_vehiculo;
 )
 {
    if( !mem || !tipo_unidad || !tipo_vehiculo) return;

    ZonaRiesgo* zona = obtener_codigo_zona(mem, codigo_zona);
    if(zona == NULL)
    {
        *tipo_unidad = UNIDAD_PATRULLA;
        *tipo_vehiculo = VEHICULO_PICKUP;
        return;
    }

    switch (tipo_llamada)
    {
    case LLAMADA_MEDICA:
        *tipo_unidad = UNIDAD_AMBULANCIA;
        break;
    case LLAMADA_POLICIAL:
        *tipo_unidad = UNIDAD_PATRULLA;
        break;
    case LLAMADA_INCENDIO:
        *tipo_unidad = UNIDAD_BOMBEROS;
        break;
    case LLAMADA_COMBINADA_MB:
        *tipo_unidad = UNIDAD_AMBULANCIA; //DEBERA REALIZAR SOLICITUD DE REFUERZOS
        break;
    case LLAMADA_COMBINADA_MP
        *tipo_unidad = UNIDAD_AMBULANCIA;//protocolo de refuerzos
        break;
    case LLAMADA_COMBINADA_Pb:
        *tipo_unidad = UNIDAD_PATRULLA; //SOLICITUD DE REFUERZOS
        break;
    case LLAMADA_TOTAL:
        *tipo_unidad = UNIDAD_PATRULLA; //respuesta incial mixta
        break;
    default:
        *tipo_unidad = UNIDAD_PATRULLA; //por defecto se enviara patrulla
        break;
    }

    //TIPO DE VEHICULO SEGUN TERRENO
    switch (zona->tipo_terreno)
    {
    case TERRENO_URBANO:
        *tipo_vehiculo = VEHICULO_SEDAN;
        break;
    case TERRENO_RURAL:
        *tipo_vehiculo = VEHICULO_PICKUP;
        break;
    case TERRENO_MONTANIOSO:
        *tipo_vehiculo = VEHICULO_TODO_TERRENO;
        break;
    case TERRENO_CONGESTIONADO:
        *tipo_vehiculo = VEHICULO_MOTO;
        break;
    default:
        *tipo_vehiculo = VEHICULO_SEDAN;
        break;
    }

    if(zona->nivel_riesgo == RIESGO_ALTO && tipo_vehiculo == VEHICULO_SEDAN)
    {
        *tipo_vehiculo = VEHICULO_PICKUP;
    }

 }