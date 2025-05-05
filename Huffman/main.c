#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define TAM 256

typedef struct no
{
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;

}No; // apelido para nao ter que chamar struct no


typedef struct{

    No *inicio;
    int tam;

}Lista;

void criar_lista(Lista *lista){

    lista->inicio = NULL;
    lista->tam = 0;

}

void inserir_ordenado(Lista *lista, No *no){
    No *aux; // usado para percorrer a lista

    // lista vazia?
    if(lista->inicio == NULL){
        lista->inicio = no;
    } 
    // frequencia menor que o inicio
    else if (no->frequencia < lista->inicio->frequencia){
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else {
        aux = lista->inicio;
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia) 
        {
            aux = aux->proximo;
        }

        no->proximo = aux->proximo;
        aux ->proximo = no;
        
    }
    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
    int i;
    No *novo;
    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            novo = malloc(sizeof(No));
            if (novo)
            {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = NULL;
                novo->esq = NULL;
                novo->proximo = NULL;

                inserir_ordenado(lista, novo);

            } else {
                printf("Erro ao alocar memória em preencher lista\n");
                break;
            }
            
        }
        
    }
    
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;

    printf("\tLista ordenada:\n");
    while (aux)
    {
        printf("\tCaracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
    
}

void inicializa_tabela_com_zero(unsigned int tab[]){
    int i;
    for(i = 0; i < TAM; i ++){
        tab[i] = 0;
    }
}

void preenche_tab_frequencia(unsigned char texto[], unsigned int tab[]){

    int i = 0;

    while (texto[i] != '\0')
    {
        tab[texto[i]]++;
        i++;
    }
    
}

void  imprime_tab_frequencia(unsigned int tab[]){
    int i;

    printf("\tTabela frequencia\n");
    for(i = 0; i < TAM; i++){
        if (tab[i] > 0)
        {
            printf("\t%d = %u = %c\n", i, tab[i], i);
        }

    }
}

// montando a arvore ou seja remover da lista e colocar na arvore

No* remove_no_inicio(Lista * lista){
    No *aux = NULL;

    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;

}


No* montar_arvore(Lista *lista){
    No *primeiro, *segundo, *novo;
    
    while (lista->tam > 1)
    {
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if (novo){
        novo->caracter = '+'; 
        novo->frequencia = primeiro->frequencia + segundo->frequencia;

        //inicio da arvore
        novo->esq = primeiro;
        novo->dir = segundo;
        novo->proximo = NULL;

        inserir_ordenado(lista, novo);

        } else{
            printf("\nErro ao alocar memoria ao montar a arvore");
            break;
        }

    } 
    
    return lista->inicio;
    
}


void imprimir_arvore(No *raiz, int tam){
    // imprimir apenas nos folhas atraves da chamada recursiva
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        printf("/tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    } else {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
    
}

int altura_arvore(No *raiz){
    int esq, dir;
    if (raiz == NULL)
    {
        return -1;
    } else {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if (esq > dir)
        {
            return esq;
        } else {
            return dir;
        }
        
    }
    
}

char** aloca_dicionario(int colunas){
    char **dicionario;
    int i;

    dicionario = malloc(sizeof(char*) * TAM);

    for (i = 0; i < TAM; i++)
    {
        dicionario[i] = calloc(colunas, sizeof(char));
        // calloc aloca e limpa a memoria
    }
    
    return dicionario;

}

void gerar_dicionario(char **dicionario, No * raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];

    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        strcpy(dicionario[raiz->caracter], caminho);
    } else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
    
}

void imprimir_dicionario(char **dicionario){
    int i;
    printf("\tDicionario");
    for (i = 0; i < TAM; i++)
    {
        if (strlen(dicionario[i]) > 0)
        {
            printf("\t%3d: %s\n", i, dicionario[i]);
        }
        
    }
}

int calcula_tamanho_string(char **dicionario, unsigned char *texto){
    int i = 0, tam = 0;

    while (texto[i] != '\0')
    {
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }
    
    return tam + 1;
}

char * codificar(char **dicionario, unsigned char *texto){

    int i = 0, tam = calcula_tamanho_string(dicionario, texto);

    char *codigo = calloc(tam, sizeof(char));

    while (texto[i] != '\0')
    {
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    
    return codigo;
}

int main() {

    unsigned char texto[] =  "Vamos aprendér a programa";
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas;
    char **dicionario;
    char *codificado;

    setlocale(LC_ALL, "Portuguese");

    // imprimindo a tabela de frequencia
    inicializa_tabela_com_zero(tabela_frequencia);
    preenche_tab_frequencia(texto, tabela_frequencia);
    imprime_tab_frequencia(tabela_frequencia);

    // ordenando a lista (podemos inserir e ordenar depois ou inserir de forma ordenada)
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);

    // arvore
    arvore = montar_arvore(&lista);
    printf("\nÁrvore\n");
    imprimir_arvore(arvore, 0);

    //dicionario
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprimir_dicionario(dicionario);

    //codificar
    codificado = codificar(dicionario, texto);
    printf("\nTexto Codificado: %s", codificado);
    return 0;
}


