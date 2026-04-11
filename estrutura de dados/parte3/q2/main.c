#include "product.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int n;
    char c;
    char nome[MAX_NAME_LENGTH];
    float price;
    int qtd, sales;
    scanf("%d", &n);
    Product **lista = (Product**)calloc(n, sizeof(Product*));

    for(int i = 0; i<n; i++){
        scanf("\n%[^\n]", nome);
        scanf("%f", &price);
        scanf("%d", &qtd);
        scanf("%d", &sales);
        lista[i] = product_constructor(nome, price, qtd);
        product_sell(lista[i], sales);
    }
    scanf("\n%c", &c);
    if(c == 'N'){
        qsort(lista, n, sizeof(Product*), product_compare_name);
    }
    if(c == 'P'){
        qsort(lista, n, sizeof(Product*), product_compare_price);
    }
    if(c == 'S'){
        qsort(lista, n, sizeof(Product*), product_compare_sales);
    }
    for(int i = 0; i<n; i++){
        product_print(lista[i]);
    }

    for(int i = 0; i<n; i++){
        product_destructor(lista[i]);
    }
    free(lista);
}