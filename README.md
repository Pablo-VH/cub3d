# cub3D 🇪🇸

cub3D es un proyecto de la escuela 42 que implementa un motor gráfico en 3D utilizando la técnica de **raycasting**, similar al utilizado en juegos clásicos como *Wolfenstein 3D*. Está escrito en C y permite al jugador explorar un mapa en primera persona.


## 🧠 Descripción

El objetivo de este proyecto es crear un juego en 3D simple que renderice entornos a partir de un mapa 2D, utilizando cálculos matemáticos para simular perspectiva. El proyecto ofrece una base para entender cómo funcionan los motores gráficos a bajo nivel, incluyendo movimiento, rotación y detección de colisiones.


## ✨ Características principales

- Motor de renderizado en 3D basado en **raycasting**
- Movimiento fluido del jugador con teclado
- Rotación de cámara con flechas o ratón
- Texturas para paredes, suelo y techo
- Detección de colisiones
- Compatible con **Linux** y **macOS**


## ⚙️ Instalación

Clona el repositorio y compílalo con `make`:

```bash
git clone https://github.com/Pablo-VH/cub3d.git
cd cub3d
make && ./cub3D maps/map1.cub
```


## ▶️ Controles

### Teclado

- `W` – Avanzar  
- `S` – Retroceder  
- `A` – Mover a la izquierda  
- `D` – Mover a la derecha  
- `←` – Rotar cámara a la izquierda  
- `→` – Rotar cámara a la derecha  
- `ESC` – Salir del juego


### Ratón

- Mover ratón – Rotar la cámara


## 🧱 Estructura del proyecto

- `srcs/main.c` – Inicio del programa
- `srcs/ft_print_screen.c` – Algoritmo de renderizado 3D y dibujo de píxeles y texturas
- `srcs/parsing.c` – Lectura y validación del mapa
- `srcs/execute_init.c` – Manejo del teclado y hooks
- `MLX42/` – Librería gráfica MiniLibX


## 📦 Requisitos

- Sistema UNIX (Linux o macOS)
- `cc` y `make`

---

# cub3D 🇬🇧

cub3D is a project from School 42 that implements a 3D graphics engine using the raycasting technique, similar to that used in classic games such as Wolfenstein 3D. It is written in C and allows the player to explore a map in first person.


## 🧠 Description

The goal of this project is to create a simple 3D game that renders environments from a 2D map, using mathematical calculations to simulate perspective. The project provides a foundation for understanding how low-level graphics engines work, including movement, rotation, and collision detection.


## ✨ Main features

- 3D rendering engine based on **raycasting**
- Smooth player movement with keyboard
- Camera rotation with arrows or mouse
- Textures for walls, floor, and ceiling
- Collision detection
- Compatible with **Linux** and **macOS**


## ⚙️ Installation

Clone the repository and compile it with `make`:

```bash
git clone https://github.com/Pablo-VH/cub3d.git
cd cub3d
make && ./cub3D maps/map1.cub
```


## ▶️ Controls

### Keyboard

- `W` – Move forward  
- `S` – Move backward  
- `A` – Move left  
- `D` – Move right  
- `←` – Rotate camera left  
- `→` – Rotate camera right  
- `ESC` – Exit game


### Mouse

- Move mouse – Rotate camera


## 🧱 Project structure

- `srcs/main.c` – Program startup
- `srcs/ft_print_screen.c` – 3D rendering algorithm and drawing of pixels and textures
- `srcs/parsing.c` – Map reading and validation
- `srcs/execute_init.c` – Keyboard handling and hooks
- `MLX42/` – MiniLibX graphics library


## 📦 Requirements

- UNIX system (Linux or macOS)
- `cc` and `make`
