#pragma once
#include "item.h"

// Declaramos el struct para un nodo de la lista
struct linked_order_node;

// Definimos un alias para el struct nodo.
// La sintaxis es "typedef tipo alias"
typedef struct linked_order_node Order_node;

// Definimos el struct nodo
struct linked_order_node
{
  // El valor que guarda el nodo 
  Item* value;
  // Un puntero al siguiente nodo de la lista 
  Order_node* next;
};

// Declaramos el struct para la lista
struct linked_order;
// Definimos un alias para el struct lista
typedef struct linked_order Order;

// Definimos el struct lista
struct linked_order
{
  // El primer nodo de la lista 
  Order_node* head;
  // El último nodo de la lista 
  Order_node* tail;

  int nodes;
  
};

// Declaramos las funciones asociadas

// Inicializa una lista vacía 
Order* order_init();

// Inserta un nuevo elemento al final de la lista 
void order_append(Order* list, Item* value);