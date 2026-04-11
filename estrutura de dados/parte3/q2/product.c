#include "product.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct product{
    char name[MAX_NAME_LENGTH];
    float price;
    int qtd;
    float discount;
    int sales;
};

Product *product_constructor(const char *name, float price, int qtd){
    Product *p = (Product*)calloc(1, sizeof(Product));
    strcpy(p->name, name);
    if(price < 0 || qtd < 0){
        printf("VALOR INVALIDO");
        return NULL;
    }
    p->price = price;
    p->qtd = qtd;
    p->discount = 0;
    p->sales = 0;

    return p;
}

const char *product_get_name(Product *product){
    return product->name;
}
float product_get_price(Product *product){
    return product->price;
}
float product_get_discount(Product *product){
    return product->discount;
}
int product_get_qtd(Product *product){
    return product->qtd;
}
int product_get_sales(Product *product){
    return product->sales;
}

void product_set_name(Product *product, const char *name){
    strncpy(product->name, name, sizeof(MAX_NAME_LENGTH+1));

}
void product_set_price(Product *product, float price){
    if(price < 0){
        printf("VALOR INVALIDO\n");
    }
    else product->price = price;
}
void product_set_discount(Product *product, float discount){
    if(discount < 0 || discount > 1){
        printf("VALOR INVALIDO\n");
    }
    else product->discount = discount;
}

void product_sell(Product *product, int quantity){
    if(quantity > product->qtd){
        printf("ESTOQUE INSUFICIENTE\n");
    }
    else if (quantity <0){
        printf("VALOR INVALIDO\n");
    }
    else {
        product->sales += quantity;
        product->qtd -= quantity;
    }
}
void product_buy(Product *product, int quantity){
    if (quantity <0){
        printf("VALOR INVALIDO\n");
    }
    else{
        product->qtd += quantity;
    }
}

float product_get_price_with_discount(Product *product){
    float price = product->price - (product->price * product->discount);
    return price;
}
void product_print(Product *product){
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n", 
        product->name, product->price, product->discount, product_get_price_with_discount(product), product->qtd, product->sales);
}

void product_destructor(Product *product){
    free (product);
}
int product_compare_name(const void* p1, const void* p2){
    Product *pr1 = *((Product**)p1);
    Product *pr2 = *((Product**)p2);

    return strcmp(pr1->name, pr2->name);
}

int product_compare_price(const void* p1, const void* p2){
    Product *pr1 = *((Product**)p1);
    Product *pr2 = *((Product**)p2);

    if(pr1->price > pr2->price){
        return 1;
    }
    if(pr1->price < pr2->price){
        return -1;
    }
   
    return 0;
    

}
int product_compare_sales(const void* p1, const void* p2){
    Product *pr1 = *((Product**)p1);
    Product *pr2 = *((Product**)p2);

    return pr1->sales - pr2->sales;
}
