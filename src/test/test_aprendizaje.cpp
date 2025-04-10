#include "memoria_compartida.h"
#include "modulo_aprendizaje.h"
#include "interfaces.h"
#include <stdio.h>

int main()
{
    key_t clave = 0x5678;
    GestionMemoria gm = crear_memoria_compartida(clave, sizeof(MemoriaCompartida));

    int codigo_zona = 101;
    TipoIncidente tipo = INCIDENTE_POLICIAL;

    printf("Registrando 7 incidentes en zona %d...\n", codigo_zona);
    for (int i = 0; i < 7; ++i)
    {
        registrar_incidente(gm.ptr_memoria, codigo_zona, tipo, TERRENO_URBANO);
    }

    NivelRiesgo riesgo = calcular_peligrosidad(gm.ptr_memoria, codigo_zona);
    printf("Nivel de riesgo estimado: %s\n", obtener_nombre_riesgo(riesgo));

    int falsa = evaluar_falsa_alarma(gm.ptr_memoria, codigo_zona, tipo);
    printf("¿Posible falsa alarma?: %s\n", falsa ? "Sí" : "No");

    destruir_memoria_compartida(&gm);
    return 0;
}

