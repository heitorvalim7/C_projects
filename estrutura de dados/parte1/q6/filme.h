#ifndef FILME_H
#define FILME_H

typedef struct filme filme;

filme* criaFilme(char *nome, float *notas, int n);
filme* leFilme();
float calculaMedia(float *notas, int n);
float retornaMedia(filme *f);
void imprimeFilme(filme *f);
void desaloca(filme **f, int n);
#endif