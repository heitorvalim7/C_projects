#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[100];
    char cpf[12];
}Atendimento;

int main(){
    Atendimento fila[10];
    int idxInicio = 0;
    int idxFim = 0;
    int tamFila = 0;
    int n;
    char ordem[10];
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        scanf("\n%s", ordem);

        if(strcmp(ordem, "CHAMAR")==0){
            if(tamFila > 0){
                printf("%s\n", fila[idxInicio].nome);
                idxInicio++;
                if(idxInicio > 9){
                    idxInicio = idxInicio % 10;
                }
                tamFila--;
            }
            else if(tamFila == 0){
                printf("FILA VAZIA\n");
            }
            
        }
        if(strcmp(ordem, "ADICIONAR")==0 ){
            if(tamFila < 10){
                scanf("\n%s %s", fila[idxFim].nome, fila[idxFim].cpf);
                idxFim++;
                if(idxFim > 9){
                    idxFim = idxFim % 10;
                }
                tamFila++;
            }
            else if(tamFila == 10){
                printf("FILA CHEIA\n");
                scanf("%*s %*s");
            }
        }
    }

    return 0;
}