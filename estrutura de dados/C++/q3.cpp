#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;



int main(){
    stack <string> q;
    int n;
    scanf("%d", &n);
    for(int i =0; i<n; i++){
        char order[20];
        scanf("%s", order);
        if(strcmp(order, "PUSH")==0){
            char nome[100];
            scanf(" %s", nome);
            string s = string(nome);
            q.push(s);
        }
        if(strcmp(order, "POP")==0){
            string s = q.top();
            q.pop();
            printf("%s\n", s.c_str());
        }
        
    }
    
    
}    