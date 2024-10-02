#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "location.h"
#include "table.h"
#include "client.h"
#include "order.h"
#include "item.h"
#include "chain.h"
#include "menu.h"

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");


  char command[32];


  /* Leemos la cantidad de restaurantes y de mesas en cada uno*/
  int N_LOCATIONS;
  fscanf(input_file, "%d", &N_LOCATIONS);

  int N_TABLES;
  Chain* chain = chain_init(N_LOCATIONS);

  for (int s = 0; s < N_LOCATIONS; s++)
  {
    fscanf(input_file, "%d", &N_TABLES);
    /*  [Por implementar] Debes crear el restaurante con su numero correspondiente de mesas */
    
    Location* location = location_init(s, N_TABLES);
    
    chain -> list_locations[s] = location;
  }

  int TOTAL_TABLES;
  fscanf(input_file, "%d", &TOTAL_TABLES);


  /*EVENTO OPEN TABLE*/

  int location_id, table_id, capacity;
  for (int s = 0; s < TOTAL_TABLES; s++)
  {
      fscanf(input_file, "%s %d %d %d", command, &location_id, &table_id, &capacity);
      /* Evento de apertura de mesa en un restaurant con su respectiva capacidad */
      Table* table = table_init(table_id, true, capacity);
      chain->list_locations[location_id]->tables[table_id] = table;

  }



  /* EVENTO MENU-ITEM*/
  int N_ITEMS;
  fscanf(input_file, "%d", &N_ITEMS);
  /*  [Por implementar] Debes crear los items del menu correspondientes */
  Menu* menu = menu_init(N_ITEMS);

  int item_id, price;
  for (int s = 0; s < N_ITEMS; s++)
  {
      fscanf(input_file, "%s %d %d", command, &item_id, &price);
      /* Evento de creacion de un plato (Todos los restaurantes comparten el mismo menu) */
          Item* item = item_init(item_id, price);

          menu -> list_items[s] = item;
  }


  /* String para guardar la instrucción actual*/

  /* Leemos la primera instrucción */
  fscanf(input_file, "%s", command);

  /* Mientras la instrucción sea distinta a END */
  while(!string_equals(command, "END"))
  {
    /* [Por implementar] A continuación debes implementar cada evento */
   if (string_equals(command, "CUSTOMER")) {
      int location_id, table_id, customer_id;
      fscanf(input_file, "%d %d %d", &location_id, &table_id, &customer_id);

      /* Evento de llegada de un cliente a una mesa abierta en algun restaurante especifico */
      bool capacidad = false;
      bool ocupado = false;
      
      for (int i = 0; i < chain->list_locations[location_id]->tables[table_id]->capacity; i++) {
        if (chain->list_locations[location_id]->tables[table_id]->seats[i] == NULL && !ocupado) {
          Client* client = client_init(customer_id);
          client->order = order_init();
          chain->list_locations[location_id]->tables[table_id]->seats[i] = client;
          capacidad = true;
          ocupado = true;
        }
      }
      if(!capacidad) {
        fprintf(output_file,"TABLE %i:%i FULL\n", location_id,table_id);
      }
      
    }
    else if (string_equals(command, "TABLE-STATUS"))
    {
      int location_id, table_id;
      fscanf(input_file, "%d %d", &location_id, &table_id);
      fprintf(output_file,"ESTADO MESA %i:%i\n",location_id,table_id);
      fprintf(output_file,"	%i\n",chain->list_locations[location_id]->tables[table_id]->capacity);
      int clients = 0;
      for(int i =0; i < chain->list_locations[location_id]->tables[table_id]->capacity; i++){
        if(chain->list_locations[location_id]->tables[table_id]->seats[i] != NULL){
          clients = clients + 1;
        }
      }
      int dif = chain->list_locations[location_id]->tables[table_id]->capacity-clients;
      fprintf(output_file,"	%i\n",dif);
      fprintf(output_file,"	CLIENTES\n");
      for(int i =0; i < chain->list_locations[location_id]->tables[table_id]->capacity; i++){
        if(chain->list_locations[location_id]->tables[table_id]->seats[i] != NULL){
          fprintf(output_file,"		%i\n",chain->list_locations[location_id]->tables[table_id]->seats[i]->id);
        }
        if(chain->list_locations[location_id]->tables[table_id]->seats[i] == NULL){
          fprintf(output_file,"		_\n");
        }
      }
      fprintf(output_file,"FIN ESTADO\n");

    }
    else if (string_equals(command, "ORDER-CREATE"))
    {
      int location_id, table_id, customer_id, item_id;
      fscanf(input_file, "%d %d %d %d", &location_id, &table_id, &customer_id, &item_id);
      for(int i = 0; i < N_ITEMS; i++){
        if(menu->list_items[i]->id == item_id){
          for(int j = 0; j < chain->list_locations[location_id]->tables[table_id]->capacity; j++){
            if(chain->list_locations[location_id]->tables[table_id]->seats[j] != NULL){
              if(chain->list_locations[location_id]->tables[table_id]->seats[j]->id == customer_id){
                order_append(chain->list_locations[location_id]->tables[table_id]->seats[j]->order,menu->list_items[i]);
                chain->list_locations[location_id]->tables[table_id]->seats[j]->order->nodes = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->nodes + 1;
              }
            }
          }
        }
      }

    }
    else if (string_equals(command, "ORDER-CANCEL"))
    {
      int location_id, table_id, customer_id;
      fscanf(input_file, "%d %d %d", &location_id, &table_id, &customer_id);
      for(int j =0; j < chain->list_locations[location_id]->tables[table_id]->capacity; j++){
        if(chain->list_locations[location_id]->tables[table_id]->seats[j] != NULL){
          if(chain->list_locations[location_id]->tables[table_id]->seats[j]->id == customer_id){
            Order_node* curr = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head;
            Order_node* prev;
            if(curr->next == NULL){
              fprintf(output_file,"DEVOLUCION %i\n",curr->value->id);
              curr = NULL;
              chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head = NULL;
            }else if(curr->next->next == NULL){
              fprintf(output_file,"DEVOLUCION %i\n",curr->next->value->id);
              curr->next = NULL;
              chain->list_locations[location_id]->tables[table_id]->seats[j]->order->tail = curr;
            }else{
              while(curr->next != NULL){
                prev = curr;
                curr = curr->next;
              }
              fprintf(output_file,"DEVOLUCION %i\n",curr->value->id);
              curr = NULL;
              chain->list_locations[location_id]->tables[table_id]->seats[j]->order->tail = prev;
            }
            chain->list_locations[location_id]->tables[table_id]->seats[j]->order->nodes = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->nodes - 1;
          }
        }
      }

    }
    else if (string_equals(command, "BILL-CREATE"))
    {
      int location_id, table_id;
      fscanf(input_file, "%d %d", &location_id, &table_id);
      fprintf(output_file,"BOLETA MESA %i:%i\n",location_id,table_id);
      fprintf(output_file,"\tPEDIDOS\n");
      bool asignado = false;
      int mas_platos;
      int mas_gasto;
      int gasto_mayor;
      int menos_gasto;
      int mayor_platos;
      int gasto_menor;
      int total_mesa = 0;

      for(int i=0; i < chain->list_locations[location_id]->tables[table_id]->capacity; i++){
        if(chain->list_locations[location_id]->tables[table_id]->seats[i] != NULL){
          fprintf(output_file,"\t\tPERSONA %i\n", chain->list_locations[location_id]->tables[table_id]->seats[i]->id);
          Order_node* current = chain->list_locations[location_id]->tables[table_id]->seats[i]->order->head;
          int total = 0;
          for(int j=0; j<chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes; j++){
            if(current != NULL){
              total = total + current->value->price;
              fprintf(output_file,"\t\t\t%i %i\n",current->value->id,current->value->price);
              current = current->next;
            }
          }
          fprintf(output_file,"\t\t%i\n",total);
          total_mesa = total_mesa + total;
          if(!asignado){
            mayor_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes;
            mas_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
            mas_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
            gasto_mayor = total;
            menos_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
            gasto_menor = total;
            asignado = true;
          }
          else {
            if(chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes > mayor_platos){
              mas_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
              mayor_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes;
            }else if(chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes == mayor_platos){
              if(chain->list_locations[location_id]->tables[table_id]->seats[i]->id < mas_platos){
                mas_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
                mayor_platos = chain->list_locations[location_id]->tables[table_id]->seats[i]->order->nodes;
              }
            }
            if(total > gasto_mayor){
              gasto_mayor = total;
              mas_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
            }else if(total == gasto_mayor){
              if(chain->list_locations[location_id]->tables[table_id]->seats[i]->id < mas_gasto){
                mas_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
              }
            }
            if(total < gasto_menor){
              gasto_menor = total;
              menos_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
            }else if(total == gasto_menor){
              if(chain->list_locations[location_id]->tables[table_id]->seats[i]->id < menos_gasto){
                menos_gasto = chain->list_locations[location_id]->tables[table_id]->seats[i]->id;
              }
            }
          }
          fprintf(output_file,"\t\tFIN PERSONA\n");
        }
      }
      fprintf(output_file,"\tFIN PEDIDOS\n");
        fprintf(output_file,"\tEL CLIENTE %i PIDIO MAS PLATOS\n",mas_platos);
        fprintf(output_file,"\tEL CLIENTE %i GASTO MAS\n",mas_gasto);
        fprintf(output_file,"\tEL CLIENTE %i GASTO MENOS\n",menos_gasto);
        fprintf(output_file,"\tTOTAL %i\n",total_mesa);
        fprintf(output_file,"FIN BOLETA\n");
    }

    else if (string_equals(command, "CHANGE-SEATS"))
    {
      int location_id, first_table_id, first_customer_id, last_table_id, last_customer_id;
      Client* first_client;
      Client* last_client;
      int first_seat;
      int last_seat;
      fscanf(input_file, "%d %d %d %d %d", &location_id, &first_table_id, &first_customer_id, &last_table_id, &last_customer_id);
      for(int j =0; j < chain->list_locations[location_id]->tables[first_table_id]->capacity; j++){
        if(chain->list_locations[location_id]->tables[first_table_id]->seats[j] != NULL){
          if(chain->list_locations[location_id]->tables[first_table_id]->seats[j]->id == first_customer_id){
            first_client = chain->list_locations[location_id]->tables[first_table_id]->seats[j];
            first_seat = j;
          }
        }
      }
      for(int i =0; i < chain->list_locations[location_id]->tables[last_table_id]->capacity; i++){
        if(chain->list_locations[location_id]->tables[last_table_id]->seats[i] != NULL){
          if(chain->list_locations[location_id]->tables[last_table_id]->seats[i]->id == last_customer_id){
            last_client = chain->list_locations[location_id]->tables[last_table_id]->seats[i];
            last_seat = i;
          }
        }
      }
      chain->list_locations[location_id]->tables[first_table_id]->seats[first_seat] = last_client;
      chain->list_locations[location_id]->tables[last_table_id]->seats[last_seat] = first_client;
    }

    else if (string_equals(command, "PERROU-MUERTO"))
    {
      int location_id, table_id, customer_id;
      fscanf(input_file, "%d %d %d", &location_id, &table_id, &customer_id);
      for(int j =0; j < chain->list_locations[location_id]->tables[table_id]->capacity; j++){
        if(chain->list_locations[location_id]->tables[table_id]->seats[j] != NULL){
          if(chain->list_locations[location_id]->tables[table_id]->seats[j]->id == customer_id){
            Order_node* curr = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head;
            while(curr){
              order_append(chain->list_locations[location_id]->tables[table_id]->seats[0]->order,curr->value);
              chain->list_locations[location_id]->tables[table_id]->seats[0]->order->nodes = chain->list_locations[location_id]->tables[table_id]->seats[0]->order->nodes+1;
              curr = curr->next;
            }
            if(chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head->next == NULL){
              chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head = NULL;
            }else{
              Order_node* curr_free = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head->next;
              Order_node* prev = chain->list_locations[location_id]->tables[table_id]->seats[j]->order->head;
              while(curr_free != NULL){
                prev = NULL;
                prev = curr_free;
                curr_free = curr_free->next;
              }
              prev = NULL;
            }
            chain->list_locations[location_id]->tables[table_id]->seats[j]->order = NULL;
            chain->list_locations[location_id]->tables[table_id]->seats[j] = NULL;
          }
        }
      }
    }
    /* Leemos la siguiente instrucción */
    fscanf(input_file, "%s", command);
  }
  /*  [Por implementar] Generar el estado de todas las mesas en todos los restaurantes */
    for(int i = 0;i<N_LOCATIONS;i++){ 
      for(int j=0;j<chain->list_locations[i]->n_tables;j++){
        fprintf(output_file,"ESTADO MESA %i:%i\n",i,j);
        fprintf(output_file,"	%i\n",chain->list_locations[i]->tables[j]->capacity);
        int clients = 0;
        for(int k =0; k < chain->list_locations[i]->tables[j]->capacity; k++){
          if(chain->list_locations[i]->tables[j]->seats[k] != NULL){
            clients = clients + 1;
          }
        }
        int dif = chain->list_locations[i]->tables[j]->capacity-clients;
        fprintf(output_file,"	%i\n",dif);
        fprintf(output_file,"	CLIENTES\n");
        for(int k =0; k < chain->list_locations[i]->tables[j]->capacity; k++){
          if(chain->list_locations[i]->tables[j]->seats[k] != NULL){
            fprintf(output_file,"		%i\n",chain->list_locations[i]->tables[j]->seats[k]->id);
          }
          if(chain->list_locations[i]->tables[j]->seats[k] == NULL){
            fprintf(output_file,"		_\n");
          }
        }
        fprintf(output_file,"FIN ESTADO\n");
      }
    }

  /*  [Por implementar] Liberamos nuestras estructuras */

  fclose(input_file);
  fclose(output_file);

  return 0;
}