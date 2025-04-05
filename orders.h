#ifndef ORDERS_H
#define ORDERS_H

//Tamaño máximo de una línea del archivo CSV
#define MAX_LINE 2048

//Tamaño máximo de una métrica (como fecha, nombre, etc.)
#define MAX_FIELD 256

//Estructura que representa una orden de pizza
struct order {
    int pizza_id;                            //ID de la pizza (un ID por tipo de pizza)
    int order_id;                            //ID de la orden (puede repetirse si contiene varias pizzas)
    char pizza_name_id[MAX_FIELD];           //ID del nombre de la pizza
    int quantity;                            //Cantidad de la pizza ordenada
    char order_date[MAX_FIELD];              //Fecha de la orden ("1/1/2015")
    char order_time[MAX_FIELD];              //Hora de la orden ("11:38:36")
    float unit_price;                        //Precio por unidad de pizza
    float total_price;                       //Precio total (unitario * cantidad)
    char pizza_size[MAX_FIELD];              //Tamaño de la pizza ("M", "L")
    char pizza_category[MAX_FIELD];          //Categoría de la pizza ("Classic", "Veggie")
    char pizza_ingredients[MAX_LINE];        //Lista de ingredientes de la pizza
    char pizza_name[MAX_LINE];               //Nombre de la pizza ("The Hawaiian Pizza")
    char blank[MAX_LINE];                    //Ajuste de formato para los ingredientes de la pizza
};

/*Función que carga las órdenes desde un archivo CSV, 
que recibe como parámetros la ruta del archivo y un puntero doble donde se guardarán las órdenes leídas*/
int load_orders(const char *filename, struct order **orders_out);

#endif