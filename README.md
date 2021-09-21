# Laberinto_Threads-Forks
Este primer proyecto tiene como finalidad desarrollar una aplicación que simule un Laberinto. Cada laberinto que se ejecute tendrá 2 versiones. Una con hilos y otra con foks. En ambas se aplicará la misma lógica y al finalizar se evaluará cual de las 2 dio mejores resultados en cuanto a eficiencia.

## Directorios
En la carpeta Documentación se encuentran la documentación del programa y el archivo con las instrucciones de la tarea.

En la carpeta maze-threads-forks se encuentra el código con la solución del programa dentro de la subcarpeta src, y los laberintos se encuentran en la subcarpeta maps dentro de la carpeta files.

```bash
.
├── Documentación
│   ├── Documentación-Proyecto1-Laberintos.pdf
│   └── Especificaciones-Laberinto.pdf
├── maze-threads-forks
│   ├── files
│   │   ├── maps
│   │   │   ├── lab1.txt
│   │   │   ├── lab2.txt
│   │   │   ├── lab3.txt
│   │   │   ├── prueba1.txt
│   │   │   ├── prueba2.txt
│   │   │   ├── prueba3.txt
│   │   │   └── prueba4.txt
│   │   └── solutions
│   │       ├── 1_map.txt
│   │       ├── 1_stats.txt
│   │       ├── 2_map.txt
│   │       ├── 2_stats.txt
│   │       └── count.txt
│   └── src
│       ├── loader
│       │   ├── loader.c
│       │   └── loader.h
│       ├── main.c
│       ├── Makefile
│       ├── memo
│       │   ├── memo.c
│       │   └── memo.h
│       ├── program
│       ├── solver
│       │   ├── solver.c
│       │   └── solver.h
│       ├── timer
│       │   ├── timer.c
│       │   └── timer.h
│       └── utils
│           ├── file_handler.c
│           ├── file_handler.h
│           ├── maze_utils.c
│           ├── maze_utils.h
│           ├── walker_utils.c
│           └── walker_utils.h
└── README.md
```

## Ejecución 
Para ejecutar y compilar el programa es necesario estar bajo el ambiente de linux.
También para mayor facilidad a la hora de compilar y ejecutar es necesario tener instalado make.

Al tener make instalado, es necesario dirigirse la la carpeta src e ingresar el comando make.

```bash
cd maze-threads-forks/src/
make
```
