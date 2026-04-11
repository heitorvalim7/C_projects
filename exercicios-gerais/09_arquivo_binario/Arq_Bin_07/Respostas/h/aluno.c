#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno{
    char nome[50];
    char data[12];
    char curso[42];
    float percent;
    float cf;
};

/**
 * @brief Cria um novo aluno.
 * @param nome Nome do aluno.
 * @param dataNascimento Data de nascimento do aluno.
 * @param curso Curso do aluno.
 * @param prctConclusao Percentual de conclusão do curso.
 * @param cfRendimento Coeficiente de rendimento do aluno.
 * @return Um ponteiro para a estrutura do aluno criada. Caso a alocação falhe, a função termina o programa.
 */
tAluno *CriaAluno(char *nome, char *dataNascimento, char *curso, float prctConclusao, float cfRendimento){
    tAluno *a = (tAluno*)calloc(1, sizeof(tAluno));
    strcpy(a->nome, nome);
    strcpy(a->data, dataNascimento);
    strcpy(a->curso, curso);
    a->percent = prctConclusao;
    a->cf = cfRendimento;

    return a;
}

/**
 * @brief Destroi um aluno.
 * @param aluno Ponteiro para a estrutura do aluno a ser destruída.
 */
void DestroiAluno(tAluno *aluno){
    free(aluno);
}

/**
 * @brief Lê um aluno da entrada padrão.
 * @return Um ponteiro para a estrutura do aluno lida.
 */
tAluno *LeAluno(){
    char nome[50], data[12], curso[50];
    float percent, cf;
    scanf(" %[^\n]", nome);
    scanf(" %[^\n]", data);
    scanf(" %[^\n]", curso);
    scanf("%f\n", &percent);
    scanf("%f\n", &cf);

    return CriaAluno(nome, data, curso, percent, cf);
}

/**
 * @brief Compara o nome de dois alunos.
 * @param aluno1 Ponteiro para a estrutura do primeiro aluno.
 * @param aluno2 Ponteiro para a estrutura do segundo aluno.
 * @return Um inteiro indicando o resultado da comparação, conforme a função strcmp.
 */
int ComparaNomeAluno(tAluno *aluno1, tAluno *aluno2){
    return strcmp(aluno1->nome, aluno2->nome);
}

/**
 * @brief Salva um aluno em um arquivo binário.
 * @param aluno Ponteiro para a estrutura do aluno a ser salva.
 * @param file Ponteiro para o arquivo onde o aluno será salvo.
 * @return Um inteiro indicando o número de bytes salvos deste aluno.
 */
int SalvaAluno(tAluno *aluno, FILE *file){
    return fwrite(aluno, sizeof(tAluno), 1, file) * sizeof(tAluno)+2;
}

/**
 * @brief Carrega um aluno de um arquivo binário.
 * @param aluno Ponteiro para a estrutura do aluno a ser carregada.
 * @param file Ponteiro para o arquivo de onde o aluno será carregado.
 * @return Um inteiro indicando o número de bytes lidos deste aluno.
 */
int CarregaAluno(tAluno *aluno, FILE *file){
    return fread (aluno, sizeof(tAluno), 1, file) * sizeof(tAluno)+2;
}

/**
 * @brief Imprime o nome de um aluno na saída padrão.
 * @param aluno Ponteiro para a estrutura do aluno cujo nome será impresso.
 */
void ImprimeNomeAluno(tAluno *aluno){
    printf("%s\n", aluno->nome);
}