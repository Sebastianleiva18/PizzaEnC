#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"
#include "metrics.h"

typedef char* (*MetricaFuncion)(int*, struct order*);

typedef struct {
    char *codigo;
    MetricaFuncion funcion;
} Metrica;

int main(int argc, char *argv[]) {
    //Se verifíca que el usuario entregue el archivo CSV y almenos una métrica
    if (argc < 3) {
        printf("Uso: %s archivo.csv metrica1 [metrica2 ...]\n", argv[0]);
        return 1;
    }

    //Se guarda el nombre del archivo
    const char *archivo_csv = argv[1];
    struct order *ordenes = NULL;

    //Se cargan las órdenes desde el CSV
    int cantidad = load_orders(archivo_csv, &ordenes);
    if (cantidad == 0) {
        printf("Error al leer el archivo o archivo vacio.\n");
        return 1;
    }

    //Se define un arreglo con todas las métricas disponibles
    Metrica metricas_disponibles[] = {
        { "pms", pms },     //Pizza más vendida
        { "pls", pls },     //Pizza menos vendida
        { "dms", dms },     //Fecha con más ventas en dinero
        { "dls", dls },     //Fecha con menos ventas en dinero
        { "dmsp", dmsp },   //Fecha con más pizzas vendidas
        { "dlsp", dlsp },   //Fecha con menos pizzas vendidas
        { "apo", apo },     //Promedio de pizzas por orden
        { "apd", apd },     //Promedio de pizzas por día
        { "ims", ims },     //Ingrediente más vendido
        { "hp", hp }        //Cantidad de pizzas por categoría vendidas
    };

    //Se calcula cuántas métricas hay en total
    int total_metricas = sizeof(metricas_disponibles) / sizeof(Metrica);

    //Se recorre cada argumento entregado por consola desde el segundo
    for (int i = 2; i < argc; i++) {
        int encontrada = 0;

        //Se busca si el código de la métrica entregado coincide con alguna función disponible
        for (int j = 0; j < total_metricas; j++) {
            if (strcmp(argv[i], metricas_disponibles[j].codigo) == 0) {
                //Se ejecuta la función correspondiente a la métrica
                char *resultado = metricas_disponibles[j].funcion(&cantidad, ordenes);
                printf("%s\n", resultado);
                encontrada = 1;
                break;
            }
        }

        //Si no se encontró la métrica, informar al usuario
        if (!encontrada) {
            printf("Metrica '%s' no reconocida.\n", argv[i]);
        }
    }

    //Liberar memoria utilizada para las órdenes
    free(ordenes);
    return 0;
}
