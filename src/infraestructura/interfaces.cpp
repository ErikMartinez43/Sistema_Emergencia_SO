#include "interfaces.h"
#include <string.h>
#include <stdio.h>

//LLAMADAS

Llamada* obtener_llamada_disponible(MemoriaCompartida *mem)
{
    for(int i = 0; i < MAX_LLAMADAS; ++i)//recorre el arreglo de llamadas en memoria compartida
    {
        if(mem->llamadas[i].estado == LLAMADA_PENDIENTE) //Busca la primera llamada en el arreglo en el arreglo de llamadas
        {
            return &mem->llamadas[i];//retorna un puntero a la primera llamada encontrada
        }
    }
    return NULL;//devuelve null si no hay llamadas pendientes
}

//CAMBIA EL ESTADO DE UNA LLAMADA A FINALIZADA
void finalizar_llamada(Llamada* llamada)
{
    if(llamada != NULL)//verifica que el puntero no sea nulo antes de modificar
    {
        llamada->estado = LLAMADA_FINALIZADA;
    }
}

//UNIDADES

Unidad* buscar_unidad_disponible(MemoriaCompartida* mem, int tipo)
{
    for(int i = 0; i < MAX_UNIDADES; ++i)
    {
        if(mem->unidades[i].tipo == tipo && mem->unidades[i].disponible == 1)//verifica el tipo de unidad (patrulla, ambulancia, etc.) y el estado de la misma(libre, ocupada)
        {
            return &mem->unidades[i];//devuelve un puntero a la primera que cumpla esas dos condiciones
        }
    }
    return NULL;
}

void asignar_unidad(Unidad* unidad, int llamada_id)
{
    if(unidad != NULL)
    {
        unidad->disponible = 0; //marca la unidad como ocupada
        printf("Unidad %d asignada a llamadas %d\n", unidad->id, llamada_id); //imprime mensaje de unidad asignada al id de llamada
    }
}

//ZONAS DE RIESGO
int zona_riesgosa(MemoriaCompartida* mem, int codigo_zona)
{
    for(int i = 0; i < 100; ++i)//recorre el arreglo zonas en memoria
    {
        if(mem->zonas[i].codigo_zona == codigo_zona)//compara codigo por zona
        {
            return mem->zonas[i].nivel_riesgo == RIESGO_ALTO; //retorna 1 si el nivel de riesgo es alto o si no encuentra la zona
        }
    }
    return 0;
}

ZonaRiesgo* obtener_codigo_zona(MemoriaCompartida* mem, int codigo_zona)
{
    for(int i = 0; i < 100; ++i)
    {
        if(mem->zonas[i].codigo_zona == codigo_zona)
        {
            return &mem->zonas[i]; //retorna un puntero a la estrcutura zona de riesgo
                                    //que tenga este codigo
        }
    }
    return NULL;//devuelve null si no la encuentra
}

//FUNCIONES AUXILIARES DE DESCRIPCION
const char* obtener_nombre_riesgo(int nivel)
{
    switch (nivel)
    {
    case RIESGO_BAJO: return "Bajo";
    case RIESGO_MEDIO: return "Medio";
    case RIESGO_ALTO: return "Alto";
    default: return "desconocido";
    }
}

const char* obtener_tipo_llamada(int tipo)
{
    switch (tipo)
    {
    case LLAMADA_MEDICA: return "medica";
    case LLAMADA_POLICIAL: return "policial";
    case LLAMADA_INCENDIO: return "incendio";
    case LLAMADA_COMBINADA_MP: return "medica + policial";
    case LLAMADA_COMBINADA_MB: return "medica + bomberos";
    case LLAMADA_COMBINADA_Pb: return "Policial + bomberos";
    case LLAMADA_TOTAL: return "Todas las unidades";
    default: return "Desconocido";
    };
}

const char* obtener_actividad_criminal(int actividad)
{
    switch (actividad)
    {
        case ACTIVIDAD_CRIMEN_ORGANIZADO: return "Crimen organizado";
        case ACTIVIDAD_TRAFICO_PERSONAS: return "Trafico de persona";
        case ACTIVIDAD_VENTA_DROGA: return "Venta de droga";
        case ACTIVIDAD_SICARIATO: return "Sicariato";
        case ACTIVIDAD_EXTORSION: return "Extorsion";
        default: return "Ninguna";
   
    }
}

const char* obtener_tipo_unidad(int tipo_unidad)
{
    switch (tipo_unidad)
    {
    case UNIDAD_PATRULLA: return "Patrulla";
    case UNIDAD_AMBULANCIA: return "Ambulancia";
    case UNIDAD_BOMBEROS: return "Bomberos";
    default: return "desconocido";
    }
}

const char *obtener_gravedad(int gravedad)
{
    switch (gravedad)
    {
    case GRAVEDA_LEVE: return "Leve";
    case GRAVEDAD_MODERADA: return "Moderada";
    case GRAVEDAD_GRAVE: return "Grave";
    default: return "Desconocida";
    }
}
