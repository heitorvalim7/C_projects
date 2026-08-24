#include <unordered_map>
#include <string>
#include <string.h>

using namespace std;

int main(){
    int n, size;
    scanf("%d %d", &n, &size);

    unordered_map<string, string>sistema(size);
    
    for(int i = 0; i<n; i++){
        char order[100];
        scanf(" %s", order);
        if(strcmp(order, "SET")==0){
            char nome[65];
            char msg[129];

            scanf(" %s %[^\n]", nome, msg);

            string nome_aluno = string(nome);
            string mensagem = string(msg);
            sistema[nome_aluno] = mensagem;

        }
        if(strcmp(order, "GET")==0){
            char nome[65];
            scanf(" %s", nome);
            string nome_aluno = string(nome);
            int qtd = sistema.count(nome_aluno);
            if(qtd != 0){
                printf(" %s\n", sistema[nome_aluno].c_str());
            }
        }
    }
    
}