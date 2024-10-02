#include "menu.h"
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

// Inicializa una lista vacía 
Menu* menu_init(int n_items)
{
  Menu* menu = malloc(sizeof(Menu));

  *menu = (Menu) {
            .list_items = calloc(n_items,sizeof(Item*)),
        };

  return menu;
}