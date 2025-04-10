#include "modulo_aprendizaje.h"

RegistroAprendizaje* buscar_historial(MemoriaCompartida* mem, int zona, TipoIncidente tipo)
{
    for (int i = 0; i < mem->contador_historial; ++i)
    {
        if (mem->historial[i].zona.codigo == zona &&
            mem->historial[i].tipo_incidente == tipo)
        {
            return &mem->historial[i];
        }
    }
    return NULL;
}

void registrar_incidente(MemoriaCompartida* mem, int zona, TipoIncidente tipo, TipoTerreno terreno)
{
    RegistroAprendizaje* registro = buscar_historial(mem, zona, tipo);

    if (registro)
    {
        registro->conteo++;
        registro->ultimo_registro = time(NULL);
    }
    else if (mem->contador_historial < MAX_HISTORIAL)
    {
        int i = mem->contador_historial++;
        mem->historial[i].zona.codigo = zona;
        mem->historial[i].tipo_incidente = tipo;
        mem->historial[i].tipo_terreno = terreno;
        mem->historial[i].conteo = 1;
        mem->historial[i].ultimo_registro = time(NULL);
        mem->historial[i].timestamp = time(NULL);
    }
}

NivelRiesgo calcular_peligrosidad(MemoriaCompartida* mem, int zona)
{
    int total = 0;

    for (int i = 0; i < mem->contador_historial; ++i)
    {
        if (mem->historial[i].zona.codigo == zona)
        {
            total += mem->historial[i].conteo;
        }
    }

    if (total > 20) return RIESGO_CRITICO;
    if (total > 10) return RIESGO_ALTO;
    if (total > 5) return RIESGO_MEDIO;
    return RIESGO_BAJO;
}

int evaluar_falsa_alarma(MemoriaCompartida* mem, int zona, TipoIncidente tipo)
{
    RegistroAprendizaje* registro = buscar_historial(mem, zona, tipo);

    if (!registro)
        return 1; // no hay historial, sospechosa

    time_t ahora = time(NULL);
    double segundos = difftime(ahora, registro->ultimo_registro);

    // Si ha pasado mucho tiempo desde el último incidente y solo hubo uno, puede ser falsa
    if (registro->conteo == 1 && segundos > 3600 * 24 * 30) // más de 30 días
        return 1;

    return 0;
}
