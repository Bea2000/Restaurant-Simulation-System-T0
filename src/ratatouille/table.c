#include "table.h"
#include <stdbool.h>
#include "client.h"


Table* table_init(int id, bool state, int capacity)
    {
        Table* table = malloc(sizeof(Table));

        table -> id = id;
        table -> state = state;
        table -> capacity = capacity;
        table -> seats = calloc(capacity,sizeof(Client*));

        return table;
    }