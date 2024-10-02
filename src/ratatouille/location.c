#include "location.h"
#include "table.h"

Location* location_init(int id, int n_tables)
    {
        Location* location = malloc(sizeof(Location));

        *location = (Location) {
            .id = id,
            .tables = malloc(sizeof(Table*)*n_tables),
            .n_tables = n_tables
        };
        return location;
    }