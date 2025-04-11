#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    Quantidade maxima de alunos da estrutura
*/
#define MAX 50


/*
    Criação da estrutura de dados onde as infomações de cada aluno serão armazenadas
*/
typedef struct {
    char nome[30];
    char turma[10];
    float nota1, nota2, nota3, media;
    char situacao[10];
} Aluno;

/*
    Definição do vetor de struct
    Permite armazenar informações de diversos alunos
*/
Aluno *alunos[MAX]; 

/*
    Criação do ponteiro de arquivo a ser usado para manipular "alunos.txt"
*/
FILE *arq;

/*
    Função: carregarArquivo

    Abre o arquivo e imprime o seu conteudo na tela
    Caso o arquivo não exista, o programa encerra com erro
 */
void carregarArquivo() {
    arq = fopen("alunos.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    
    char linha[100];
    while (fgets(linha, 100, arq) != NULL) {
        printf("%s", linha);
    }
    
    fclose(arq);
}

/*
    Função: adicionarInformacao

    Lê os dados de um numero determinado pelo usuario de alunos 
    e os grava na estrutura "Aluno" e no arquivo
 */
void adicionarInformacao() {
    int quantidadeDeAlunos, i;
    char nomeDigitado[30], turmaDigitada[10];

    printf("Quantos alunos voce quer cadastrar? ");
    scanf("%d", &quantidadeDeAlunos);

    arq = fopen("alunos.txt", "a");

    for (i = 0; i < quantidadeDeAlunos; i++) {
        alunos[i] = (Aluno *)malloc(sizeof(Aluno));
        if (alunos[i] == NULL) {
            printf("Erro ao alocar memoria");
            exit(1);
        }

        printf("Aluno %d:\n", i + 1);
        
        printf("Nome: ");
        scanf("%s", nomeDigitado);
        strcpy(alunos[i]->nome, nomeDigitado);
        fprintf(arq, "\nNome: %s\n", alunos[i]->nome);
        
        printf("Turma: ");
        scanf("%s", turmaDigitada);
        strcpy(alunos[i]->turma, turmaDigitada);
        fprintf(arq, "Turma: %s\n", alunos[i]->turma);

        printf("Nota 1: ");
        scanf("%f", &alunos[i]->nota1);
        fprintf(arq, "Nota 1: %.2f\n", alunos[i]->nota1);

        printf("Nota 2: ");
        scanf("%f", &alunos[i]->nota2);
        fprintf(arq, "Nota 2: %.2f\n", alunos[i]->nota2);

        printf("Nota 3: ");
        scanf("%f", &alunos[i]->nota3);
        fprintf(arq, "Nota 3: %.2f\n", alunos[i]->nota3);

        alunos[i]->media = (alunos[i]->nota1 + alunos[i]->nota2 + alunos[i]->nota3) / 3;
        fprintf(arq, "Media: %.2f\n", alunos[i]->media);

        if (alunos[i]->media >= 6) { 
            strcpy(alunos[i]->situacao, "Aprovado");
            fprintf(arq, "Situacao: %s\n", alunos[i]->situacao);
        } else {
            strcpy(alunos[i]->situacao, "Reprovado");
            fprintf(arq, "Situacao: %s\n", alunos[i]->situacao);
        }
    }
    fclose(arq);
}

/*
    Função: menuPrincipal
 
    Permite que o usuário escolha uma funcionalidade
 */
void menuPrincipal() {
    int opcao = 0;

    while (true) {
        printf("\nDigite 1 para carregar o arquivo, 2 para cadastrar alunos e 3 para sair do programa: ");
        scanf("%d", &opcao);

        if (opcao == 1)
            carregarArquivo();
        else if (opcao == 2)
            adicionarInformacao();
        else if (opcao == 3)
            break;
        else
            printf("Opcao invalida");
    }
}

/*
    Função: main

    Função principal (usada para chamar o menu)
 */
int main() {
    menuPrincipal();
    return 0;
}
