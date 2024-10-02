#include "order.h"
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

// Inicializa una lista vacía 
Order* order_init()
{
  Order* list = malloc(sizeof(Order));
  list -> head = NULL;
  list -> tail = NULL;
  list -> nodes = 0;

  return list;
}

// Insertamos un nuevo elemento al final de la lista 
void order_append(Order* list, Item* value)
{
  Order_node* order_node = malloc(sizeof(Order_node));
  order_node -> value = value;
  order_node -> next = NULL;

  // Si la lista está vacía entonces queda como el primer elemento
  if(list -> head == NULL)
  {
    list -> head = order_node;
  }
  // Sino, se pone como el siguiente del ultimo
  else
  {
    list -> tail -> next = order_node;
  }
  // Luego se deja a este nodo como el último de la lista
  list -> tail = order_node;
}
