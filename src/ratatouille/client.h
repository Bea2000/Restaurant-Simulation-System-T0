#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "order.h"

// Declaramos el struct para la locacion
struct client;
// Definimos un alias para el struct locacion.
// La sintaxis es "typedef tipo alias"
typedef struct client Client;

// Definimos el struct locacion y sus componentes.
// En python esto lo conocemos como los atributos de un objeto.
struct client
{
  // pedidos del cliente
  Order* order;

  int id;
};

Client* client_init(int id);