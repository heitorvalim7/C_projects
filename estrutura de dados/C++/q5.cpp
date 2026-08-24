#include <map>
#include <string>


using namespace std;

int main(){
    map<string, int> bt;
    int n;
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        char palavra [100];
        scanf(" %s", palavra);
        string s = string(palavra);
        bt[s]++;
    }   
    for(auto pair : bt){
        printf("%s", pair.first.c_str());
        printf(" %d\n", pair.second);
    }
}