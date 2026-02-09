#include "database.h"
#include "vector.h"
#include "aluno.h"
#include "professor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Database{
    Vector *professores;
    Vector *alunos;
    int totall;
    int totals
};

/**
 * @brief Cria um nova database.
 * @return Um ponteiro para a estrutura database criada. Caso a alocação falhe, a função termina o programa.
 */
tDatabase *CriaDatabase(){
    tDatabase *d = (tDatabase*)calloc(1, sizeof(tDatabase));
    d->alunos = VectorConstruct();
    d->professores = VectorConstruct();

    return d;
}

/**
 * @brief Destroi uma database.
 * @param db Ponteiro para a estrutura da database a ser destruída.
 */
void DestroiDatabase(tDatabase *db){
    VectorDestroy(db->alunos, DestroiAluno);
    VectorDestroy(db->professores, DestroiProfessor);
    free(db);
}

/**
 * @brief Lê uma database da entrada padrão.
 * @param db Ponteiro para a estrutura da database a ser lida.
 */
void LeDatabase(tDatabase *db){
    int qtda;
    scanf("%d", &qtda);
    for(int i = 0; i<qtda; i++){
        VectorPushBack(db->alunos, LeAluno());
    }
    int qtdp;
    scanf("%d", &qtdp);
    for(int i = 0; i<qtdp; i++){
        VectorPushBack(db->professores, LeProfessor());
    }
}

/**
 * @brief Ordena uma database, primeiro os alunos e depois os professores, de acordo com o nome.
 * @param db Ponteiro para a estrutura da database a ser ordenada.
 */
void OrdenaDatabase(tDatabase *db){
    for(int i = 0; i < VectorSize(db->professores); i++){
        for(int j = 0; j < VectorSize(db->professores) - 1; j++){
            if(ComparaNomeProfessor((tProfessor*)VectorGet(db->professores, j), 
                                   (tProfessor*)VectorGet(db->professores, j+1)) > 0){
                VectorSwap(db->professores, j, j+1);
            }
        }
    }
    for(int i = 0; i < VectorSize(db->alunos); i++){
        for(int j = 0; j < VectorSize(db->alunos) - 1; j++){
            if(ComparaNomeAluno((tAluno*)VectorGet(db->alunos, j), 
                               (tAluno*)VectorGet(db->alunos, j+1)) > 0){
                VectorSwap(db->alunos, j, j+1);
            }
        }
    }
}

/**
 * @brief Salva uma database em um arquivo binário.
 * @param db Ponteiro para a estrutura da database a ser salva.
 * @param file Ponteiro para o arquivo onde a database será salva.
 * @return Um inteiro indicando o total de bytes salvos.
 */
int SalvarDatabase(tDatabase *db, FILE *file){
    db->totals = 0;
    int numA = VectorSize(db->alunos);
     int numP = VectorSize(db->professores);

    fwrite(&numA, sizeof(int), 1, file);
    db->totals += sizeof(int);
    for(int i = 0; i<VectorSize(db->alunos); i++){
        db->totals +=SalvaAluno((tAluno*)VectorGet(db->alunos, i), file);
    }
    fwrite(&numP, sizeof(int), 1, file);
    db->totals += sizeof(int);
    for(int i = 0; i<VectorSize(db->professores); i++){
        db->totals +=SalvaProfessor((tProfessor*)VectorGet(db->professores, i), file);
    }

    return db->totals;
}

/**
 * @brief Carrega uma database de um arquivo binário.
 * @param db Ponteiro para a estrutura da database a ser carregada.
 * @param file Ponteiro para o arquivo de onde a database será carregada.
 * @return Um inteiro indicando o total de bytes lidos.
 */
int CarregaDatabase(tDatabase *db, FILE *file){
    db->totall = 0;
    int numA;
    int numb;
    fread(&numA, sizeof(int), 1, file);
    db->totall += sizeof(int);
    for(int i = 0; i < numA; i++){
        db->totall += CarregaAluno((tAluno*)VectorGet(db->alunos, i), file);
    }
    fread(&numb, sizeof(int), 1, file);
    db->totall += sizeof(int);
    for(int i = 0; i < numb; i++){
        db->totall += CarregaProfessor((tProfessor*)VectorGet(db->professores, i), file);
    }

    return db->totall;
}

/**
 * @brief Imprime uma database, primeiro os alunos e depois os professores. Apenas os nomes são impressos.
 * @param db Ponteiro para a estrutura da database a ser impressa.
 */
/**
 * @brief Imprime uma database, primeiro os alunos e depois os professores.
 */
void ImprimeDatabase(tDatabase *db){
    // 2. Imprime a lista de Alunos
    printf("Alunos:\n");
    for(int i = 0; i < VectorSize(db->alunos); i++){
        ImprimeNomeAluno((tAluno*)VectorGet(db->alunos, i));
    }
    
    // 3. Quebra de linha entre as categorias
    printf("\n");

    // 4. Imprime a lista de Professores
    printf("Professores:\n");
    for(int i = 0; i < VectorSize(db->professores); i++){
        ImprimeNomeProfessor((tProfessor*)VectorGet(db->professores, i));
    }
}