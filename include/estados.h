#ifndef ESTADOS_H
#define ESTADOS_H

//TIPOS DE LLAMADAS
#define LLAMADA_MEDICA 0
#define LLAMADA_POLICIAL 1
#define LLAMADA_INCENDIO 2
#define LLAMADA_COMBINADA_MP 3 //medica + policial 
#define LLAMADA_COMBINADA_MB 4 //medica + bomberos
#define LLAMADA_COMBINADA_Pb 5 //policial + bomberos
#define LLAMADA_TOTAL 6 //medica + policial +bomberos

//ZONAS GEOGRAFICAS
#define ZONA_CENTRO 0
#define ZONA_NORTE 1
#define ZONA_SUR 2
#define ZONA_OESTE 3
#define ZONA_ESTE 4

//TIPO DE TERRENO
#define TERRENO_URBANO 0
#define TERRENO_RURAL 1
#define TERRENO_MONTANIOSO 2
#define TERRENO_CONGESTIONADO 3

//NIVELES DE RIESGO
#define RIESGO_BAJO 0
#define RIESGO_MEDIO 1
#define RIESGO_ALTO 2


//TIPO DE UNIDAD
#define UNIDAD_PATRULLA 0
#define UNIDAD_AMBULANCIA 1
#define UNIDAD_BOMBEROS 2

//TIPO DE VEHICULO
#define VEHICULO_SEDAN 0
#define VEHICULO_PICKUP 1
#define VEHICULO_MOTO 2
#define VEHICULO_TODO_TERRENO 3

//CODIGO DE DELITO
#define DELITO_HURTO 0
#define DELITO_ASALTO 1
#define DELITO_HOMICIDIO 2
#define DELITO_VIOLECIA_DOMESTICA 3
#define DELITO_DISTURBIOS 4
#define DELITO_ESCANDALO_PUBLICO 5

//GRAVEDAD DEL PACIENTE
#define GRAVEDA_LEVE 0
#define GRAVEDAD_MODERADA 1
#define GRAVEDAD_GRAVE 2

//ESTADOS DE LA LLAMADA
#define LLAMADA_PENDIENTE 0
#define LLAMADA_EN_ATENCION 1
#define LLAMADA_FINALIZADA 2

//ESTADO DE INCIDENTE
#define INCIDENTE_EN_CAMINO 0
#define INCIDENTE_EN_LUGAR 1
#define INCIDENTE_TRASLADADO 2
#define INCIDENTE_CERRADO 3

//ESTADOS DEL TURNO
#define TURNO_ACTIVO 0
#define TURNO_DESCANSO 1
#define TURNO_FUERA_SERVICIO 2

//ESTADOS DEL DETENIDO
#define DETENIDO_EN_CUSTODIA 0
#define DETENIDO_TRASLADADO 1
#define DETENIDO_LIBERADO 2

//ESTADO DEL PACIENTE
#define PACIENTE_ESPERANDO 0
#define PACIENTE_EN_RUTA 1
#define PACIENTE_HOSPITAL 2

//ACTIVIDAD CRIMINAL (PARA ZONAS DE RIESGO)
#define ACTIVIDA_NONE 0 //sin actividad relevante
#define ACTIVIDAD_CRIMEN_ORGANIZADO 1
#define ACTIVIDAD_TRAFICO_PERSONAS 2
#define ACTIVIDAD_VENTA_DROGA 3
#define ACTIVIDAD_SICARIATO 4
#define ACTIVIDAD_EXTORSION 5
#define ACTIVIDA_PANDILLAS

#endif