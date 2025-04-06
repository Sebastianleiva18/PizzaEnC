#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"

//Función que carga todas las órdenes desde un archivo CSV
int load_orders(const char *filename, struct order **orders_out) {
    //Abrir el archivo en modo lectura
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo archivo"); //Mensaje en caso de que falle
        return 0;
    }

    //Leer y descartar la primera línea (estructura de una orden)
    char line[MAX_LINE];
    fgets(line, MAX_LINE, file);

    //Reservar memoria para 100 órdenes
    int capacidad = 100;
    int cantidad = 0;
    struct order *orders = malloc(capacidad * sizeof(struct order));

    //Leer línea por línea el archivo
    while (fgets(line, MAX_LINE, file)) {
        //Si se excede la capacidad, duplicar el espacio reservado
        if (cantidad >= capacidad) {
            capacidad *= 2;
            orders = realloc(orders, capacidad * sizeof(struct order));
        }

        //Apuntar a la orden actual
        struct order *o = &orders[cantidad];

        //Guardar cada campo separado por comas
        char *token = strtok(line, ",");
        o->pizza_id = atoi(token); //ID de la pizza

        token = strtok(NULL, ",");
        o->order_id = atoi(token); //ID de la orden

        token = strtok(NULL, ",");
        strncpy(o->pizza_name_id, token, MAX_FIELD); //ID del nombre de la pizza

        token = strtok(NULL, ",");
        o->quantity = atoi(token); //Cantidad de la pizza ordenada

        token = strtok(NULL, ",");
        strncpy(o->order_date, token, MAX_FIELD); //Fecha de la orden

        token = strtok(NULL, ",");
        strncpy(o->order_time, token, MAX_FIELD); //Hora de la orden

        token = strtok(NULL, ",");
        o->unit_price = atof(token); //Precio por unidad de pizza

        token = strtok(NULL, ",");
        o->total_price = atof(token); //Precio total

        token = strtok(NULL, ",");
        strncpy(o->pizza_size, token, MAX_FIELD); //Tamaño de la pizza

        token = strtok(NULL, ",");
        strncpy(o->pizza_category, token, MAX_FIELD); //Categoría de la pizza

        token = strtok(NULL, "\"");
        strncpy(o->pizza_ingredients, token, MAX_LINE); //Lista de ingredientes de la pizza

        token = strtok(NULL, ",");
        strncpy(o->blank, token, MAX_LINE); //Ajuste de formato para los ingredientes de la pizza

        token = strtok(NULL, "\"");
        strncpy(o->pizza_name, token, MAX_LINE); //Nombre de la pizza

        cantidad++; //Pasar a la siguiente orden
    }

    //Cerrar archivo y devolver puntero al arreglo de órdenes
    fclose(file);
    *orders_out = orders;
    return cantidad;
}