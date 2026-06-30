#include "atendimento.h"
#include "frame.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char tipo[10];
    int n;

    scanf("%s", tipo);
    scanf("%d", &n);

    if(strcmp(tipo, "SENHAS") == 0){
        Queue *q = queue_constructor(10);
        char ordem[20];
        for(int i = 0; i<n; i++){
            scanf("%s", ordem);
            if(strcmp(ordem, "CHAMAR") == 0){
                if(!queue_is_empty(q)){
                    Atendimento *atendimento = (Atendimento*)queue_remove(q);
                    printf("%s\n", atendimento_get_nome(atendimento));
                    atendimento_destroy(atendimento);
                }
                else{
                    printf("FILA VAZIA\n");
                }
            }
            if(strcmp(ordem, "ADICIONAR")==0){
                char nome[50], cpf[12];
                scanf("%s %s", nome, cpf);
                if(queue_is_full(q)){
                    printf("FILA CHEIA\n");
                }
                else{
                    Atendimento *atendimento = atendimento_constructor(nome, cpf);
                    queue_add(q, atendimento);
                }
                

            }
        }
        if(!queue_is_empty(q)){
            int tam = queue_size(q);
            for(int i = 0; i<tam; i++){
                Atendimento *atendimento = (Atendimento*)queue_remove(q);
                atendimento_destroy(atendimento);
            }
        }
        queue_destroy(q);
    }
    if(strcmp(tipo, "STREAMING") == 0){
        Queue *q = queue_constructor(20);
        char ordem[20];
        for(int i = 0; i<n; i++){
            scanf("%s", ordem);
            if(strcmp(ordem, "PLAY") == 0){
                if(queue_size(q)>=5){
                    for(int j = 0; j<5; j++){
                        Frame *frame = (Frame*)queue_remove(q);
                        printf("ID: %d, Timestamp: %.2f\n", frame_get_frame_id(frame), frame_get_timestamp(frame));
                        frame_destroy(frame);
                    }
                }
                else{
                    printf("AGUARDE\n");
                }
            }
            if(strcmp(ordem, "ADICIONAR")==0){
                char frame_id[50];
                int id;
                float timestamp;

                scanf("%s %d %f", frame_id, &id, &timestamp);
                if(queue_is_full(q)){
                    printf("FILA CHEIA\n");
                }
                else{
                    Frame *frame = frame_constructor(frame_id, id, timestamp);
                    queue_add(q, frame);
                }
                

            }
        }
        if(!queue_is_empty(q)){
            int tam = queue_size(q);
            for(int i = 0; i<tam; i++){
                Frame *frame = (Frame*)queue_remove(q);
                frame_destroy(frame);
            }
        }
        queue_destroy(q);
    }
    
    return 0;

}