#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <string>

using namespace std;



int main(){
    queue <string> q;
    int n;
    scanf("%d", &n);
    for(int i =0; i<n; i++){
        char order[20];
        scanf("%s", order);
        if(strcmp(order, "ENQUEUE")==0){
            char nome[100];
            scanf(" %s", nome);
            string s = string(nome);
            q.push(s);
        }
        if(strcmp(order, "DEQUEUE")==0){
            string s = q.front();
            q.pop();
            printf("%s\n", s.c_str());
        }
        
    }
    
    
}    