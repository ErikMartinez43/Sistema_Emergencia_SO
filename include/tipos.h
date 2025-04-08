
#ifndef TIPOS_H
#define TIPOS_H

#include "estados.h"

#include <sys/types.h>
#include <time.h>


#define MAX_LLAMADAS 50
#define MAX_UNIDADES 30
#define MAX_INCIDENTES 100
#define MAX_HISTORIAL 100
#define MAX_TURNOS 50
#define MAX_DETENIDOS 20
#define MAX_PACIENTES 50
#define MAX_ZONAS 100


//ESTRUCTURA LLAMADAS ACTIVAS
typedef struct
{
    int id; //identificador de llamdas
    TipoLLamada tipo;
    TipoTerreno tipo_terreno;
    EstadoLlamada estado;
    pid_t operador;//PID del proceso que maneja la llamada
    Ubicacion zona; //zona geografica
    struct 
    {
        time_t creacion;
        time_t asignacion;
        time_t resolucion;
    }tiempos;

}Llamada;

//ESTRUCTURA: UNIDADES DISPONIBLE
typedef struct
{
    int id;
    TipoUnidad tipo; //0:patrulla, 1:Ambulancia, 2:bomberos
    TipoTerreno tipo_terreno;
    EstadoUnidad estado; //1:libre, 0:ocupada
    Ubicacion zona; //ubicacion geografica
    NivelRiesgo prioridad; //nivel de riesgo
}Unidad;

typedef struct
{
    int codigo_zona; //codigo unico de la colonia o sector
    char nombre[50]; //nombre colonia, barrio o sector
    Ubicacion zona_general;
    ActividadCriminal actividad;
    NivelRiesgo nivel_riesgo;
    TipoTerreno tipo_terreno; //URBARNO, RURAL, MONTANIOS, CONGESTIONADO
}ZonaRiesgo;


//ESTRUCTURA ASIGNACION DE INDENTES
typedef struct
{
    int unidad_id;
    int llamada_id;
    EstadoIncidente estado; //0:en camino, 1: en el lugar, 2: traslado, 3:finalizado
}IncidenteAsignado;

//ESTRUCTURA: HISTORIAL/APRENDIZAJE
typedef struct
{
 Ubicacion zona;
 TipoDelito tipo_incidente; //0:robo, 1:herida, etc..
 TipoTerreno tipo_terreno;
 int conteo;
 time_t ultimo_registro;
}RegistroAprendizaje;

//ESTRUCTURA: TURNOS Y JORNADAS
typedef struct 
{
    int id_personal;
    TipoUnidad tipo_unidad; //0:comisaria, 1:hospital, 2:ambulancia
    time_t inicio_turno;
    time_t fin_turno;
    EstadoTurno estado; //0:activo, 1:descanso, 2:fuers de servicio
}Turno;

//ESTRUCTURA LISTA DE DETENIDOS
typedef struct
{
    int id_detenido;
    char nombre[50];
    TipoDelito delito; //codigo de delitos
    time_t fecha_ingreso;
    EstadoDetenido estado; //0:en custodia, 1:trasladado, 2:liberado
}Detenido;

//ESTRUCTURA: PACIENTES/URGENCIAS
typedef struct 
{
    int id_paciente;
    char nombre[50];
    GravedadPacientegravedad; // 0:leve, 1:moderado, 2:grave
    EstadoPaciente estado; //0:esperando, 1:en ambulancia, 2: en hospital
    time_t hora_ingreso;
}Paciente;

typedef enum
{
    LLAMADA_MEDICA = 0,
    LLAMADA_POLICIAL = 1,
    LLAMADA_INCENDIO = 2,
    LLAMADA_COMBINADA_MP = 3, //medica + policial 
    LLAMADA_COMBINADA_MB = 4, //medica + bomberos
    LLAMADA_COMBINADA_Pb = 5, //policial + bomberos
    LLAMADA_TOTAL = 6 //medica + policial +bomberos
}TipoLLamada;

//TIPO DE UNIDAD
typedef enum 
{
    UNIDAD_PATRULLA = 0,
    UNIDAD_AMBULANCIA = 1,
    UNIDAD_BOMBEROS = 2,
    UNIDAD_COMBINADA = 3
}TipoUnidad;

//TIPO DE TERRENO
typedef enum
{
    TERRENO_URBANO = 0,
    TERRENO_RURAL = 1,
    TERRENO_MONTANIOSO = 2,
    TERRENO_CONGESTIONADO = 3
}TipoTerreno;

//NIVELES DE RIESGO
typedef enum
{
    RIESGO_BAJO = 0,
    RIESGO_MEDIO = 1,
    RIESGO_ALTO = 3
}NivelRiesgo;

typedef enum
{
    DELITO_HURTO = 0,
    DELITO_ASALTO = 1,
    DELITO_HOMICIDIO = 2,
    DELITO_VIOLECIA_DOMESTICA = 3,
    DELITO_DISTURBIOS = 4,
    DELITO_ESCANDALO_PUBLICO = 5
}TipoDelito;

//TIPOS DE VEHICULO
typedef enum
{
    VEHICULO_SEDAN = 0,
    VEHICULO_PICKUP = 1,
    VEHICULO_MOTO = 2,
    VEHICULO_TODO_TERRENO = 3
}TiposVehiculo;

//ACTIVIDAD CRIMINAL (PARA ZONAS DE RIESGO)
typedef enum
{
    ACTIVIDAD_NONE = 0, //sin actividad relevante
    ACTIVIDAD_CRIMEN_ORGANIZADO = 1,
    ACTIVIDAD_TRAFICO_PERSONAS = 2,
    ACTIVIDAD_VENTA_DROGA = 3,
    ACTIVIDAD_SICARIATO = 4,
    ACTIVIDAD_EXTORSION = 5,
    ACTIVIDA_PANDILLAS = 6
}ActividadCriminal;

//UBICACION ZONAS GEOGRAFICAS
typedef enum 
{
    ZONA_CENTRO = 0,
    ZONA_NORTE = 1, 
    ZONA_SUR = 2,
    ZONA_OESTE = 3,
    ZONA_ESTE =4
}Ubicacion;


//ESTRUCTURA GLOBAL
typedef struct
{
    Llamada llamadas[MAX_LLAMADAS];
    int contador_llamadas;
    sem_t sem_llamadas;

    Unidad unidades [MAX_UNIDADES];
    int contador_unidades;
    sem_t sem_unidades;

    IncidenteAsignado incidentes[MAX_INCIDENTES];
    int contador_incidentes;
    sem_t sem_incidente;

    RegistroAprendizaje historial[MAX_HISTORIAL];
    int contador_historial:
    sem_t sem_historial;

    Turno turnos[MAX_TURNOS];
    int contador_turnos;
    sem_t sem_turnos;

    Detenido detenidos[MAX_DETENIDOS];
    int contador_detenidos:
    sem_t sem_detenidos;

    Paciente pacientes[MAX_PACIENTES];
    int contador_pacientes;
    sem_t sem_pacientes;

    ZonaRiesgo zonas[MAX_ZONAS];
    int contador_zonas;
    sem_t sem_zonas;

}MemoriaCompartida;




#endif
