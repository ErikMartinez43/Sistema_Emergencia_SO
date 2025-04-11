#include "interfaces.h"
#include <string.h>
#include <cstdio>

//====== FUNCIONES SOBRE LLAMADAS =======

Llamada *obtener_llamada_disponible(MemoriaCompartida *mem)
{
    for(int i = 0; i < mem->contador_llamadas; ++i)
    {
        if(mem->llamadas[i].estado == LLAMADA_PENDIENTE)
        {
            return &mem->llamadas[i];
        }
    }
    return NULL;
}

void finalizar_llamada(Llamada *llamada)
{
    if(llamada)
    {
        llamada->estado = LLAMADA_FINALIZADA;
        llamada->tiempos.resolucion = time(NULL);
    }
}

//========= FUNCIONES SOBRE UNIDADES ==================
Unidad *buscar_unidad_disponible(MemoriaCompartida *mem, TipoUnidad tipo)
{
    for(int i = 0; i < mem->contador_unidades; ++i)
    {
        if(mem->unidades[i].estado == UNIDAD_DISPONIBLE && mem->unidades[i].tipo == tipo)
        {
            return &mem->unidades[i];
        }
    }
    return NULL;
}

void asignar_unidad(Unidad *unidad, int llamada_id)
{
    (void)llamada_id;
    if(unidad)
    {
        unidad->estado = UNIDAD_OCUPADA;
        unidad->prioridad = RIESGO_MEDIO;
    }
}

//======= FUNCIONES SOBRE UBICACION
int zona_riesgosa(MemoriaCompartida *mem, int codigo_zona)
{
    for(int i = 0; i < mem->contador_zonas; ++i)
    {
        if(mem->zonas[i].codigo_zona == codigo_zona)
        {
            return mem->zonas[i].nivel_riesgo >= RIESGO_ALTO;
        }
    }
    return 0;
}

ZonaRiesgo *obtener_codigo_zona(MemoriaCompartida *mem, int codigo_zona)
{
    for(int i = 0; i < mem->contador_zonas; ++i)
    {
        if(mem->zonas[i].codigo_zona == codigo_zona)
        {
            return &mem->zonas[i];
        }
    }
    return NULL;
}

//=========FUNCIONES AUXILIARES=============================
const char *obtener_nombre_riesgo(NivelRiesgo nivel)
{
    switch (nivel)
    {
    case RIESGO_BAJO: return "Bajo";
    case RIESGO_MEDIO: return "Medio";
    case RIESGO_ALTO: return "Alto";
    case RIESGO_CRITICO: return "Critico";
    default: return "Desconocido";
    }
}

const char *obtener_tipo_llamada(TipoLlamada tipo)
{
    switch (tipo)
    {
    case LLAMADA_MEDICA: return "Medica";
    case LLAMADA_POLICIAL: return "Policial";
    case LLAMADA_INCENDIO: return "Incendio";
    case LLAMADA_COMBINADA_MP: return "Médica + Policial";
    case LLAMADA_COMBINADA_MB: return "Médica + Bomberos";
    case LLAMADA_COMBINADA_PB: return "Policial + Bomberos";
    case LLAMADA_TOTAL: return "Total (Médica + Policial + Bomberos)";
    default: return "Desconocida";
    }
}

const char *obtener_actividad_criminal(ActividadCriminal actividad)
{
    switch (actividad)
    {
        case ACTIVIDAD_NONE: return "Sin actividad";
        case ACTIVIDAD_CRIMEN_ORGANIZADO: return "Crimen organizado";
        case ACTIVIDAD_TRAFICO_PERSONAS: return "Tráfico de personas";
        case ACTIVIDAD_VENTA_DROGA: return "Venta de droga";
        case ACTIVIDAD_SICARIATO: return "Sicariato";
        case ACTIVIDAD_EXTORSION: return "Extorsión";
        case ACTIVIDAD_PANDILLAS: return "Pandillas";
        default: return "Desconocida";
    }
}

const char *obtener_tipo_unidad(TipoUnidad tipo_unidad)
{
    switch (tipo_unidad)
    {
        case UNIDAD_PATRULLA: return "Patrulla";
        case UNIDAD_AMBULANCIA: return "Ambulancia";
        case UNIDAD_BOMBEROS: return "Bomberos";
        case UNIDAD_COMBINADA: return "Combinada";
        default: return "Desconocida";
    }   
}

const char *obtener_gravedad(GravedadPaciente gravedad)
{
    switch (gravedad)
    {
        case GRAVEDAD_LEVE: return "Leve";
        case GRAVEDAD_MODERADA: return "Moderada";
        case GRAVEDAD_GRAVE: return "Grave";
        default: return "Desconocida";
    } 
}

void eliminar_llamada_finalizada(MemoriaCompartida* mem, int id_llamada)
{
    bool encontrada = false;

    for (int i = 0; i < mem->contador_llamadas; ++i)
    {
        if (mem->llamadas[i].id == id_llamada && mem->llamadas[i].estado == LLAMADA_FINALIZADA)
        {
            encontrada = true;
            // Mover las demás llamadas para ocupar el espacio vacío
            for (int j = i; j < mem->contador_llamadas - 1; ++j)
            {
                mem->llamadas[j] = mem->llamadas[j + 1];
            }
            mem->contador_llamadas--;  // Reducir el contador de llamadas activas
            printf("[INFO] Llamada %d eliminada correctamente de la memoria.\n", id_llamada);
            break;
        }
    }

    if (!encontrada)
    {
         fprintf(stderr, "[ADVERTENCIA] No se encontró llamada %d para eliminar.\n", id_llamada);
    }
}

void limpiar_llamadas_finalizadas(MemoriaCompartida *mem)
{
    if(!mem) return;

    int nueva_pos = 0;
    for(int i =0; i < mem->contador_llamadas; ++i)
    {
        //copiar a nueva posicion si no esta finalizada
        if(mem->llamadas[i].estado != LLAMADA_FINALIZADA)
        {
            //copiar a nueva posicion si no esta finalizada
            if(i != nueva_pos)
            {
                mem->llamadas[nueva_pos] = mem->llamadas[i];
            }
            nueva_pos++;
        }
    }

    mem->contador_llamadas = nueva_pos;
}
