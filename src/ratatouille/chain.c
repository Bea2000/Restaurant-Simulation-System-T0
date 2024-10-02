#include "chain.h"
#include <stdlib.h>
#include <stdio.h>
#include "location.h"

// Inicializa una lista vacía 
Chain* chain_init(int n_locations)
{
  Chain* chain = malloc(sizeof(Chain));
  

  *chain = (Chain) {
            .list_locations = malloc(sizeof(Location*)*n_locations),
        };

  return chain;
}