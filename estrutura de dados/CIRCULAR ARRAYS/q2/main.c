#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char idvideo[50];
    int id;
    float timeStamp;
}frame;

int main(){
    frame fila[20];
    int idxInicio = 0;
    int idxFim = 0;
    int tamFila = 0;
    int n;
    char ordem[10];
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        scanf("\n%s", ordem);

        if(strcmp(ordem, "PLAY")==0){
            if(tamFila >= 5){
                for(int j = 0; j<5; j++){
                    printf("ID: %d, Timestamp: %.2f\n", fila[idxInicio].id, fila[idxInicio].timeStamp);
                    idxInicio++;
                    if(idxInicio > 19){
                        idxInicio = idxInicio % 20;
                    }
                    tamFila--;
                }
            }
            else if(tamFila < 5){
                printf("AGUARDE\n");
            }
            
        }
        if(strcmp(ordem, "ADICIONAR")==0 ){
            if(tamFila < 20){
                scanf("\n%s %d %f", fila[idxFim].idvideo, &fila[idxFim].id, &fila[idxFim].timeStamp);
                idxFim++;
                if(idxFim > 19){
                    idxFim = idxFim % 20;
                }
                tamFila++;
            }
            else if(tamFila == 20){
                printf("FILA CHEIA\n");
                scanf("%*s %*d %*f ");
            }
        }
    }

    return 0;
}