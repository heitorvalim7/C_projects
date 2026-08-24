#include <vector>
#include <string>
#include <queue>
#include <string.h>

using namespace std;

struct programa{
    string nome;
    string tipo;
    int qtd;
    int prioridade;
    int carga;
    int ultimo_uso;
    int iteracao_inicial;
};

struct cmpSO{
    bool operator()(programa *a, programa *b){
        if(a->prioridade == b->prioridade){
            if(a->carga == b->carga){
                return a->nome < b->nome;
            }
            return a->carga < b->carga;
        }
        return a->prioridade < b->prioridade;
    }
};

struct cmpUSER{
     bool operator()(programa *a, programa *b){
        if(a->prioridade == b->prioridade){
            if(a->ultimo_uso == b->ultimo_uso){
                return a->nome < b->nome;
            }
            return a->ultimo_uso < b->ultimo_uso;
        }
        return a->prioridade < b->prioridade;
    }
};

programa *construct(string nome, string tipo, int prioridade, int carga, int iteracao_inicial){
    programa *p = new programa();
    p->carga = carga;
    p->nome = nome;
    p->tipo = tipo;
    p->prioridade = prioridade;
    p->iteracao_inicial = iteracao_inicial;
    
    return p;
}

int main(){
    vector<programa>rt;
    priority_queue<programa*, vector<programa*>, cmpSO> so;
    priority_queue<programa*, vector<programa*>, cmpUSER> user;
    vector <programa*>all; 
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char nome[64];
        char tipo[10];
        int prioridade, carga, iteracao_inicial;

        scanf(" %s %s %d %d %d", nome, tipo, &prioridade, &carga, &iteracao_inicial);
        
        string n = string(nome);
        string t = string(tipo);
        programa *p = construct(n, t, prioridade, carga, iteracao_inicial);
        all.push_back(p); 
    }
    while(all.size()>0 || rt.size() > 0 || !so.empty() || !user.empty()){
        for(int i = 0; i<all.size(); i++){

        }
    }
}