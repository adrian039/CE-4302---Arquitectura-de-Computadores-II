# Taller 2 - Arquitectura de Computadores II 

## Comandos para correr cada archivo

### SAXPY Serial
```bash
gcc -o saxpy -fopenmp saxpy.c
./saxpy
```
### SAXPY Parallel
Este algoritmo es el mismo que el anterior solo que utiliza los pragmas definidos por OPENMP para mejorar el rendimiento del programa.

```bash
gcc -o saxpy_par -fopenmp saxpy_par.c
./saxpy_par
```


### Multiplicación de Matrices Serial
Este programa lo que hace es calcular el producto de dos matrices de gran tamaño.

```bash
gcc -o RealMM -fopenmp RealMM.c
./RealMM
```

### Multiplicación de Matrices Parallel
Este algoritmo es el mismo que el anterior solo que utiliza los pragmas definidos por OPENMP para mejorar el rendimiento del programa.
```bash
gcc -o RealMM_par -fopenmp RealMM_par.c
./RealMM_par
