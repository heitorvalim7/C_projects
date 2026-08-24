#include <deque>
#include <list>
#include <string>
#include <string.h>

using namespace std;

int main(){
    deque <string> entregas;
    deque <string> forno;
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        char order[100];
        scanf("%s", order);
        if(strcmp(order, "PEDIDO")==0){
            char nome[100];
            scanf(" %s", nome);
            string n = string(nome);
            forno.push_back(n);
        }
        else if(strcmp(order, "FORNO_LIVRE")==0){
            string l = forno.front();
            forno.pop_front();
            entregas.push_back(l);
        }
        else if(strcmp(order, "MOTOBOY")==0){
            string l = entregas.front();
            entregas.pop_front();
            printf("ENTREGUE %s\n", l.c_str());
        }
        else if(strcmp(order, "INSPECAO_ENTREGA")==0){
            int n;
            scanf("%d", &n);
            string l = entregas[n];
            printf("%s\n", l.c_str());
        }
        else if(strcmp(order, "INSPECAO_FORNO")==0){
            int n;
            scanf("%d", &n);
            string l = forno[n];
            printf("%s\n", l.c_str());
        }
    }
}