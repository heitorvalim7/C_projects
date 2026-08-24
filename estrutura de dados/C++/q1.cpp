#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

typedef struct produtos{
    string nome;
    float preco;
    int estoque;
    int vendas;
}produtos;

produtos *construct(char* nome, float preco, int estoque, int vendas){
    produtos *p = new produtos();
    p->estoque = estoque;
    p->preco = preco;
    p->vendas = vendas;
    p->nome = string(nome);

    return p;
}

bool cmp_vendas(const produtos *p1, const produtos *p2){
    return p1->vendas < p2->vendas;
}
bool cmp_preco(const produtos *p1, const produtos *p2){
    return p1->preco < p2->preco;
}
bool cmp_nome(const produtos *p1, const produtos *p2){
    return p1->nome < p2->nome;
}



int main(){
    vector<produtos*> p;
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char nome[100];
        float preco;
        int estoque;
        int vendas;
        scanf(" %[^\n]", nome);
        scanf("%f", &preco);
        scanf("%d", &estoque);
        scanf("%d", &vendas);
        produtos *pr = construct(nome, preco, estoque, vendas);
        p.push_back(pr);
    }
    char c;
    scanf(" %c", &c);
    if(c == 'S'){
        sort(p.begin(), p.end(), cmp_vendas);
    }
    if(c == 'P'){
        sort(p.begin(), p.end(), cmp_preco);
    }
    if(c == 'N'){
        sort(p.begin(), p.end(), cmp_nome);
    }

    for(produtos* pr : p){
        printf("Product(%s, %.2f, 0.00, %.2f, %d, %d)\n", pr->nome.c_str(), pr->preco, pr->preco, pr->estoque - pr->vendas, pr->vendas);
        delete pr;
    }
    
}    