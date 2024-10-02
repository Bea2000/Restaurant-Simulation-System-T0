#pragma once
#include <stdlib.h>
#include <stdio.h>

// Declaramos el struct para la locacion
struct item;
// Definimos un alias para el struct locacion.
// La sintaxis es "typedef tipo alias"
typedef struct item Item;

// Definimos el struct locacion y sus componentes.
// En python esto lo conocemos como los atributos de un objeto.
struct item
{
  // id de locacion
  int id;
  // precio
  int price;

};

Item* item_init(int id, int price);