# Sistema de Emergencias - Proyecto de Sistemas Operativos

Este proyecto simula un sistema de atención de emergencias. Se modelan llamadas de emergencia, unidades de atención (policía, hospital, bomberos), asignación de recursos y comunicación entre procesos mediante memoria compartida y semáforos.

---

## Objetivo

Modelar y simular un sistema distribuido en C++:
- Memoria compartida
- Semáforos
- Control de procesos
- Manejo de recursos y turnos
- Comunicación entre módulos
---

## Distribución del trabajo

### Erik – Infraestructura y coordinación general
- `main.cpp`
- `Makefile`
- `infraestructura/memoria_compartida.cpp`
- `infraestructura/semaforos.cpp`
- `infraestructura/gestor_jornadas.cpp`
- `recursos/gestor_recursos.cpp`
- `include/memoria_compartida.h`, `semaforos.h`, `interfaces.h`

### Ezequiel – Generador de llamadas y módulo de aprendizaje
- `generador_llamadas/generador.cpp`
- `generador_llamadas/flujo_emergencias.cpp`
- `aprendizaje/modulo_aprendizaje.cpp`
- `include/estados.h`, `interfaces.h`

### Carlos – Módulos de unidades
- `unidades/comisaria.cpp`, `subestacion.cpp`, `patrulla.cpp`
- `unidades/hospital.cpp`, `ambulancia.cpp`
- `unidades/bomberos.cpp`, `vehiculos_bomberos.cpp`
- `ministerio_publico/ministerio.cpp`

---

## Estructura del proyecto

