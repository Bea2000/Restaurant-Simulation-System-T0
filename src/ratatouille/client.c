#include "order.h"
#include <stdbool.h>
#include "client.h"

Client* client_init(int id)
    {
        Client* client = malloc(sizeof(Client));

        *client = (Client) {
            .id = id,
            .order = malloc(sizeof(Order*)),
        };
        return client;
    }