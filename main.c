#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int RA;
    int idade;
    float notas[4];
    char nome[50];
    struct no *esquerda;
    struct no *direita;
} No;

void Menu(void)
{
    printf("Escolha uma opcao:\n");
    printf("1- Inserir alunos\n");
    printf("2- Buscar alunos por RA\n");
    printf("3- Exibir arvore\n");
    printf("4- Excluir alunos\n");
    printf("5- Apagar arvore\n");
    printf("0- Sair do programa\n");
}

No *criar_no(int RA, int idade, float notas[], char nome[])
{
    No *novo_no = calloc(sizeof(No));
    if (novo_no == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    novo_no->RA = RA;
    novo_no->idade = idade;
    memcpy(novo_no->notas, notas, sizeof(float) * 4);
    strcpy(novo_no->nome, nome);
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

No *inserir(No *raiz, int RA, int idade, float notas[], char nome[])
{
    if (raiz == NULL)
    {
        return criar_no(RA, idade, notas, nome);
    }

    if (RA < raiz->RA)
    {
        raiz->esquerda = inserir(raiz->esquerda, RA, idade, notas, nome);
    }
    else if (RA > raiz->RA)
    {
        raiz->direita = inserir(raiz->direita, RA, idade, notas, nome);
    }
    else
    {
        printf("RA ja existe\n");
    }
    return raiz;
}

No *buscar(No *no, int RA)
{
    if (no == NULL || no->RA == RA)
    {
        return no;
    }

    if (RA < no->RA)
    {
        return buscar(no->esquerda, RA);
    }
    else
    {
        return buscar(no->direita, RA);
    }
}

void imprimir_arvore(No *raiz, int distancia)
{
    if (raiz == NULL)
    {
        return;
    }

    imprimir_arvore(raiz->direita, distancia + 1);
    for (int i = 0; i < distancia; i++)
    {
        printf("      ");
    }

    printf("| ");
    printf("RA: %d |\n", raiz->RA);
    imprimir_arvore(raiz->esquerda, distancia + 1);
}

No *remover(No *raiz, int RA)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    if (RA < raiz->RA)
    {
        raiz->esquerda = remover(raiz->esquerda, RA);
    }
    else if (RA > raiz->RA)
    {
        raiz->direita = remover(raiz->direita, RA);
    }
    else
    {
        if (raiz->esquerda == NULL)
        {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No *sucessor = raiz->direita;

        while (sucessor->esquerda != NULL)
        {
            sucessor = sucessor->esquerda;
        }

        raiz->RA = sucessor->RA;
        raiz->idade = sucessor->idade;
        memcpy(raiz->notas, sucessor->notas, sizeof(float) * 4);
        strcpy(raiz->nome, sucessor->nome);

        raiz->direita = remover(raiz->direita, sucessor->RA);
    }
    return raiz;
}

void apagar_arvore(No *raiz)
{
    if (raiz != NULL)
    {
        apagar_arvore(raiz->esquerda);
        apagar_arvore(raiz->direita);
        free(raiz);
    }
}

int main()
{
    int opcao = 0;
    No *raiz = NULL;
    int RA, Idade;
    float notas[4];
    char nome[50];

    do
    {
        Menu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            printf("RA: ");
            scanf("%d", &RA);
            printf("Idade: ");
            scanf("%d", &Idade);
            printf("Notas (separadas por espaco): ");
            scanf("%f%f%f%f", &notas[0], &notas[1], &notas[2], &notas[3]);
            printf("Nome: ");
            scanf("%s", nome);
            raiz = inserir(raiz, RA, Idade, notas, nome);
            break;
        case 2:
            system("cls");
            No *temp = NULL;
            printf("Digite o RA do aluno que deseja buscar:\n");
            scanf("%i", &RA);
            temp = buscar(raiz, RA);
            if (temp)
            {
                printf("Nome:%s\nRa:%i\n", temp->nome, temp->RA);
            }
            else
                printf("Aluno nao encontrado\n");
            break;
        case 3:
            system("cls");
            if (raiz)
            {
                imprimir_arvore(raiz, 0);
                break;
            }
            printf("Nenhum aluno cadastrado.\n");
            break;
        case 4:
            system("cls");
            if (raiz)
            {
                imprimir_arvore(raiz, 0);
                printf("Digite o RA do aluno a ser removido:\n");
                scanf("%i", &RA);
                raiz = remover(raiz, RA);
                break;
            }
            printf("Nenhum aluno cadastrado.\n");
            break;
        case 5:
            system("cls");
            apagar_arvore(raiz);
            raiz = NULL;
            printf("Arvore apagada com sucesso!\n");
            break;
        default:
            break;
        }
    } while (opcao != 0);
    
    apagar_arvore(raiz);
    
    return 0;
}
