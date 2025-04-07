
#ifndef TIPOS_H
#define TIPOS_H

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
    int tipo;
    int tipo_terreno;
    int estado;
    int zona; //codigo de zona geografica
    int unidad_asignada; //id de unidad asignada
    pid_t operador; //PID del proceso que maneja la llamada
}Llamada;

//ESTRUCTURA: UNIDADES DISPONIBLE
typedef struct
{
    int id;
    int tipo; //0:patrulla, 1:Ambulancia, 2:bomberos
    int tipo_terreno;
    int disponible; //1:libre, 0:ocupada
    int zona; //ubicacion geografica
    int prioridad; //nivel de riesgo
}Unidad;

typedef struct
{
    int codigo_zona; //codigo unico de la colonia o sector
    char nombre[50]; //nombre colonia, barrio o sector
    int zona_general;
    int actividad_criminal;
    int nivel_riesgo;
    int tipo_terreno; //URBARNO, RURAL, MONTANIOS, CONGESTIONADO
}ZonaRiesgo;


//ESTRUCTURA ASIGNACION DE INDENTES
typedef struct
{
    int unidad_id;
    int llamada_id;
    int estado; //0:en camino, 1: en el lugar, 2: traslado, 3:finalizado

}IncidenteAsignado;

//ESTRUCTURA: HISTORIAL/APRENDIZAJE
typedef struct
{
 int zona;
 int tipo_incidente; //0:robo, 1:herida, etc..
 int tipo_terreno;
 int conteo;
 time_t ultimo_registro;
}RegistroAprendizaje;

//ESTRUCTURA: TURNOS Y JORNADAS
typedef struct 
{
    int id_personal;
    int tipo_unidad; //0:comisaria, 1:hospital, 2:ambulancia
    time_t inicio_turno;
    time_t fin_turno;
    int estado; //0:activo, 1:descanso, 2:fuers de servicio
}Turno;

//ESTRUCTURA LISTA DE DETENIDOS

typedef struct
{
    int id_detenido;
    char nombre[50];
    int delito; //codigo de delitos
    time_t fecha_ingreso;
    int estado; //0:en custodia, 1:trasladado, 2:liberado
}Detenido;

//ESTRUCTURA: PACIENTES/URGENCIAS
typedef struct 
{
    int id_paciente;
    char nombre[50];
    int gravedad; // 0:leve, 1:moderado, 2:grave
    int estado; //0:esperando, 1:en ambulancia, 2: en hospital
    time_t hora_ingreso;
}Paciente;




//ESTRUCTURA GLOBAL
typedef struct
{
    Llamada llamadas[MAX_LLAMADAS];
    Unidad unidades [MAX_UNIDADES];
    IncidenteAsignado incidentes[MAX_INCIDENTES];
    RegistroAprendizaje historial[MAX_HISTORIAL];
    Turno turnos[MAX_TURNOS];
    Detenido detenidos[MAX_DETENIDOS];
    Paciente pacientes[MAX_PACIENTES];
    ZonaRiesgo zonas[MAX_ZONAS];

}MemoriaCompartida;


#endif
