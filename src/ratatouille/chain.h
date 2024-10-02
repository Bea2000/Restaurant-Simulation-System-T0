#pragma once
#include "location.h"

// Declaramos el struct para un nodo de la lista
struct linked_chain;

// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct linked_chain Chain;

// Definimos el struct nodo
struct linked_chain
{
  // El valor que guarda el nodo 
  Location** list_locations;

};

Chain* chain_init(int n_locations);