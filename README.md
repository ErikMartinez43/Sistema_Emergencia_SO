 Sistema de Emergencias - Proyecto de Sistemas Operativos

Este proyecto simula un sistema de atención de emergencias inspirado en el comportamiento de un sistema operativo. Se modelan llamadas de emergencia, unidades de atención (policía, hospital, bomberos), asignación de recursos, y comunicación entre procesos concurrentes mediante memoria compartida y semáforos.

---

## 🧠 Objetivo
Modelar y simular un sistema distribuido y concurrente en C++ usando técnicas de sistemas operativos:
- Memoria compartida
- Semáforos
- Control de procesos
- Manejo de recursos y turnos
- Comunicación entre módulos

---

## 👥 Distribución del trabajo

### 👤 Persona 1 – Infraestructura y coordinación general
- `main.cpp`
- `Makefile`
- `infraestructura/memoria_compartida.cpp`
- `infraestructura/semaforos.cpp`
- `infraestructura/gestor_jornadas.cpp`
- `recursos/gestor_recursos.cpp`
- `include/memoria_compartida.h`, `semaforos.h`, `interfaces.h`

### 👤 Persona 2 – Generador de llamadas y módulo de aprendizaje
- `generador_llamadas/generador.cpp`
- `generador_llamadas/flujo_emergencias.cpp`
- `aprendizaje/modulo_aprendizaje.cpp`
- `include/estados.h`, `interfaces.h`

### 👤 Persona 3 – Módulos de unidades
- `unidades/comisaria.cpp`, `subestacion.cpp`, `patrulla.cpp`
- `unidades/hospital.cpp`, `ambulancia.cpp`
- `unidades/bomberos.cpp`, `vehiculos_bomberos.cpp`
- `ministerio_publico/ministerio.cpp`

---

## 📁 Estructura del proyecto

