#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

#define MAX_PIZZAS 500
#define MAX_DATES 500
#define MAX_CATEGORIES 100
#define MAX_ORDERS 1000
#define MAX_INGREDIENTS 1000

typedef struct {
    char nombre[MAX_LINE];
    int cantidad;
} PizzaContador;

typedef struct {
    char fecha[MAX_FIELD];
    float total;
    int cantidad_pizzas;
} FechaVenta;

typedef struct {
    char categoria[MAX_FIELD];
    int cantidad;
} CategoriaContador;


//pms: Pizza más vendida
char* pms(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    PizzaContador conteo[MAX_PIZZAS];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(conteo[j].nombre, orders[i].pizza_name) == 0) {
                conteo[j].cantidad += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(conteo[total].nombre, orders[i].pizza_name);
            conteo[total].cantidad = orders[i].quantity;
            total++;
        }
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (conteo[i].cantidad > conteo[max].cantidad) max = i;
    }

    snprintf(resultado, MAX_LINE, "Pizza mas vendida: %s", conteo[max].nombre);
    return resultado;
}

//pls: Pizza menos vendida
char* pls(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    PizzaContador conteo[MAX_PIZZAS];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(conteo[j].nombre, orders[i].pizza_name) == 0) {
                conteo[j].cantidad += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(conteo[total].nombre, orders[i].pizza_name);
            conteo[total].cantidad = orders[i].quantity;
            total++;
        }
    }

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (conteo[i].cantidad < conteo[min].cantidad) min = i;
    }

    snprintf(resultado, MAX_LINE, "Pizza menos vendida: %s", conteo[min].nombre);
    return resultado;
}

//dms: Fecha con más ventas en dinero
char* dms(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    FechaVenta fechas[MAX_DATES];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j].fecha, orders[i].order_date) == 0) {
                fechas[j].total += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[total].fecha, orders[i].order_date);
            fechas[total].total = orders[i].total_price;
            total++;
        }
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (fechas[i].total > fechas[max].total) max = i;
    }

    snprintf(resultado, MAX_LINE, "Fecha con mas ventas ($): %s con %.2f dolares", fechas[max].fecha, fechas[max].total);
    return resultado;
}

//dls: Fecha con menos ventas en dinero
char* dls(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    FechaVenta fechas[MAX_DATES];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j].fecha, orders[i].order_date) == 0) {
                fechas[j].total += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[total].fecha, orders[i].order_date);
            fechas[total].total = orders[i].total_price;
            total++;
        }
    }

    if (total == 0) {
        snprintf(resultado, MAX_LINE, "No hay ventas registradas.");
        return resultado;
    }

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (fechas[i].total < fechas[min].total) {
            min = i;
        }
    }

    snprintf(resultado, MAX_LINE, "Fecha con menos ventas ($): %s con %.2f dolares", fechas[min].fecha, fechas[min].total);
    return resultado;
}

//dms: Fecha con más ventas en dinero
char* dmsp(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    FechaVenta fechas[MAX_DATES];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j].fecha, orders[i].order_date) == 0) {
                fechas[j].cantidad_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[total].fecha, orders[i].order_date);
            fechas[total].cantidad_pizzas = orders[i].quantity;
            fechas[total].total = 0;
            total++;
        }
    }

    if (total == 0) {
        snprintf(resultado, MAX_LINE, "No hay ventas registradas.");
        return resultado;
    }

    int max = 0;
    for (int i = 1; i < total; i++) {
        if (fechas[i].cantidad_pizzas > fechas[max].cantidad_pizzas) {
            max = i;
        }
    }

    snprintf(resultado, MAX_LINE, "Fecha con mas pizzas vendidas: %s con %d pizzas",
             fechas[max].fecha, fechas[max].cantidad_pizzas);
    return resultado;
}

//dls: Fecha con menos ventas en dinero
char* dlsp(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    FechaVenta fechas[MAX_DATES];
    int total = 0;

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total; j++) {
            if (strcmp(fechas[j].fecha, orders[i].order_date) == 0) {
                fechas[j].cantidad_pizzas += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(fechas[total].fecha, orders[i].order_date);
            fechas[total].cantidad_pizzas = orders[i].quantity;
            fechas[total].total = 0; // no lo usamos aquí
            total++;
        }
    }

    if (total == 0) {
        snprintf(resultado, MAX_LINE, "No hay ventas registradas.");
        return resultado;
    }

    int min = 0;
    for (int i = 1; i < total; i++) {
        if (fechas[i].cantidad_pizzas < fechas[min].cantidad_pizzas) {
            min = i;
        }
    }

    snprintf(resultado, MAX_LINE, "Fecha con menos pizzas vendidas: %s con %d pizzas",
             fechas[min].fecha, fechas[min].cantidad_pizzas);
    return resultado;
}

//apo: Promedio de pizzas por orden
char* apo(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    int total_pizzas = 0;
    int ordenes_distintas[MAX_ORDERS] = {0};
    int total_ordenes = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        int orden_id = orders[i].order_id;
        if (orden_id >= 0 && orden_id < MAX_ORDERS && ordenes_distintas[orden_id] == 0) {
            ordenes_distintas[orden_id] = 1;
            total_ordenes++;
        }
    }

    float promedio = total_ordenes > 0 ? (float)total_pizzas / total_ordenes : 0;
    snprintf(resultado, MAX_LINE, "Promedio de pizzas por orden: %.2f", promedio);
    return resultado;
}

//apd: Promedio de pizzas por día
char* apd(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    int total_pizzas = 0;
    char fechas_unicas[MAX_DATES][MAX_FIELD];
    int total_fechas = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        int ya_existe = 0;
        for (int j = 0; j < total_fechas; j++) {
            if (strcmp(fechas_unicas[j], orders[i].order_date) == 0) {
                ya_existe = 1;
                break;
            }
        }

        if (!ya_existe) {
            strncpy(fechas_unicas[total_fechas], orders[i].order_date, MAX_FIELD);
            total_fechas++;
        }
    }

    float promedio = total_fechas > 0 ? (float)total_pizzas / total_fechas : 0;
    snprintf(resultado, MAX_LINE, "Promedio de pizzas por dia: %.2f", promedio);
    return resultado;
}

//ims: Ingrediente más vendido
char* ims(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    struct {
        char nombre[MAX_FIELD];
        int cantidad;
    } ingredientes[MAX_INGREDIENTS];

    int total_ingredientes = 0;

    for (int i = 0; i < *size; i++) {
        char ingredientes_linea[MAX_LINE];
        strncpy(ingredientes_linea, orders[i].pizza_ingredients, MAX_LINE);

        char *token = strtok(ingredientes_linea, ",");
        while (token != NULL) {
            while (*token == ' ') token++;
            int found = 0;

            for (int j = 0; j < total_ingredientes; j++) {
                if (strcmp(ingredientes[j].nombre, token) == 0) {
                    ingredientes[j].cantidad += orders[i].quantity;
                    found = 1;
                    break;
                }
            }

            if (!found && total_ingredientes < MAX_INGREDIENTS) {
                strncpy(ingredientes[total_ingredientes].nombre, token, MAX_FIELD);
                ingredientes[total_ingredientes].cantidad = orders[i].quantity;
                total_ingredientes++;
            }

            token = strtok(NULL, ",");
        }
    }

    if (total_ingredientes == 0) {
        snprintf(resultado, MAX_LINE, "No hay ingredientes registrados.");
        return resultado;
    }

    int max = 0;
    for (int i = 1; i < total_ingredientes; i++) {
        if (ingredientes[i].cantidad > ingredientes[max].cantidad) {
            max = i;
        }
    }

    snprintf(resultado, MAX_LINE, "Ingrediente mas vendido: %s (%d unidades)",
             ingredientes[max].nombre, ingredientes[max].cantidad);
    return resultado;
}

//hp: Cantidad de pizzas por categoría
char* hp(int *size, struct order *orders) {
    static char resultado[MAX_LINE];
    struct {
        char categoria[MAX_FIELD];
        int cantidad;
    } categorias[MAX_CATEGORIES];

    int total_categorias = 0;
    resultado[0] = '\0';

    for (int i = 0; i < *size; i++) {
        int found = 0;
        for (int j = 0; j < total_categorias; j++) {
            if (strcmp(categorias[j].categoria, orders[i].pizza_category) == 0) {
                categorias[j].cantidad += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found && total_categorias < MAX_CATEGORIES) {
            strncpy(categorias[total_categorias].categoria, orders[i].pizza_category, MAX_FIELD);
            categorias[total_categorias].cantidad = orders[i].quantity;
            total_categorias++;
        }
    }

    strcat(resultado, "Cantidad de pizzas por categoria:\n");
    for (int i = 0; i < total_categorias; i++) {
        char linea[100];
        snprintf(linea, sizeof(linea), "- %s: %d\n", categorias[i].categoria, categorias[i].cantidad);
        strcat(resultado, linea);
    }

    return resultado;
}