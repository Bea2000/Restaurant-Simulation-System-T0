#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "table.h"

// Declaramos el struct para la locacion
struct location;
// Definimos un alias para el struct locacion.
// La sintaxis es "typedef tipo alias"
typedef struct location Location;

// Definimos el struct locacion y sus componentes.
// En python esto lo conocemos como los atributos de un objeto.
struct location
{
  // id de locacion
  int id;
  // mesas
  Table** tables;

  int n_tables;
};

Location* location_init(int id, int n_tables);

// Declaramos las funciones asociadas

// Inicializa una casa con las indicaciones utilizando malloc
//House* house_init_malloc(int streetNumber, int people, int width);

// Inicializa una casa con las indicaciones utilizando malloc
// con notación un poco distinta_2
// House* house_init_malloc_2(int streetNumber, int people, int width);

// Inicializa una casa con las indicaciones utilizando calloc
// House* house_init_calloc(int streetNumber, int people, int width);

// Imprime una casa y su información
// void print_house(House* house);

// Se libera la memoria utilizada por la casa
// void destroy_house(House* house);