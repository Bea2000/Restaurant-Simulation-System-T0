#include <stdbool.h>
#include "item.h"

Item* item_init(int id, int price)
    {
        Item* item = malloc(sizeof(Item));

        *item = (Item) {
            .id = id,
            .price = price,
        };
        return item;
    }