#include <forward_list>
#include <string>
#include <string.h>

using namespace std;

int main(){
    forward_list <string> f;
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char order[100];
        scanf(" %s", order);

        if(strcmp(order, "ADD_BEGIN")==0){
            char nome_m[100];
            scanf(" %s", nome_m);
            string nome_musica = string(nome_m);
            f.push_front(nome_m);
        }

        else if(strcmp(order, "ADD_AFTER")==0){
            char nome_m_after[100];
            char nome_m[100];
            scanf(" %s %s", nome_m_after, nome_m);

            string nome_musica_after = string(nome_m_after);
            string nome_musica = string(nome_m);
            auto pointer = f.begin();
            while(pointer != f.end()){
                string n = *pointer;
                if(n == nome_m_after){
                    f.insert_after(pointer, nome_musica);
                    break;
                }
                pointer++;
            }
           
        }

        else if(strcmp(order, "REMOVE")==0){
            char nome_r[100];
            scanf(" %s", nome_r);
            string nome_remove = string(nome_r);
            f.remove(nome_remove);
        }

    }
    auto pointer = f.begin();
    while(!f.empty()){
        string nome = *pointer;
        printf("%s\n", nome.c_str());
        pointer++;
        f.pop_front();
    }
}