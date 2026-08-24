#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

typedef struct Process{
    string nome;
    string categoria;
    int identificador;
    int prioridade;
}Process;

Process *construct(char *nome, char *categoria, int identificador, int prioridade){
    Process *p = new Process();
    p->nome = string (nome);
    p->categoria = string (categoria);
    p->identificador = identificador;
    p->prioridade = prioridade;
    return p;
}

class cmpPRO{
public:
    const bool operator()(const Process *a, const Process *b){
        return a->prioridade < b->prioridade;
    }
};

int main(){
    priority_queue <Process*, vector<Process*>, cmpPRO> q;
    int n;
    scanf("%d", &n);
    for(int i =0; i<n; i++){
        char nome[32];
        char categoria[32];
        int identificador;
        int prioridade;        
        scanf(" %s %s %d %d", nome, categoria, &identificador, &prioridade);
        Process *pr = construct(nome, categoria, identificador, prioridade);
        q.push(pr);
    }
    while(!q.empty()){
        Process *p = q.top();
        printf("%s %s %d %d\n", p->nome.c_str(), p->categoria.c_str(), p->identificador, p->prioridade);
        q.pop();
    }
    
}    