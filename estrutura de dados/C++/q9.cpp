#include <unordered_map>
#include <string>
#include <string.h>

using namespace std;

typedef struct Disciplina{
    string nome;
    float faltas;
    float nota;
}Disciplina;

typedef struct Aluno{
   unordered_map<string, Disciplina> materias;
}Aluno;

int main(){
    unordered_map<string, Aluno> alunos;
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        char nome[100];
        int materias;

        scanf(" %s %d", nome, &materias);
        string nome_aluno = string(nome);
        alunos[nome_aluno];

        for(int j = 0; j<materias;j++){
            char nome_m[100];
            float falta;
            float nota;
            scanf(" %s %f %f", nome_m, &falta, &nota);
            string nome_materia = string(nome_m);
            alunos[nome_aluno].materias[nome_materia].faltas = falta;
            alunos[nome_aluno].materias[nome_materia].nota = nota;
            alunos[nome_aluno].materias[nome_materia].nome = nome;
        }
    }
    int consultas;
    scanf("%d", &consultas);
    for(int i = 0; i<consultas; i++){
        char nome[100], materia[100];
        scanf(" %s %s", nome, materia);
        string nome_aluno = string(nome);
        string materia_aluno = string(materia);
        int qtd = alunos[nome_aluno].materias.count(materia_aluno);
        if(qtd == 0){
            printf("NAO_CURSOU\n");
        } else {
            float falta = alunos[nome].materias[materia].faltas;
            float nota = alunos[nome].materias[materia].nota;
            if(falta <= 0.25 && nota >= 7){
                printf("APROVADO\n");
            }  else {
                printf("REPROVADO\n");
            }
        }
    }
}