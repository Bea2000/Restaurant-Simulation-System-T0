#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "client.h"

// Declaramos el struct para la locacion
struct table;
// Definimos un alias para el struct locacion.
// La sintaxis es "typedef tipo alias"
typedef struct table Table;

// Definimos el struct locacion y sus componentes.
// En python esto lo conocemos como los atributos de un objeto.
struct table
{
  // id de table
  int id;
  // estado
  bool state;
  // capacidad
  int capacity;
  // clientes
  Client** seats;
};

Table* table_init(int id, bool state, int capacity);