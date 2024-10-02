#pragma once
#include "item.h"

// Declaramos el struct para un nodo de la lista
struct linked_menu;

// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct linked_menu Menu;

// Definimos el struct nodo
struct linked_menu
{
  // El valor que guarda el nodo 
    Item** list_items;
};

Menu* menu_init(int n_items);