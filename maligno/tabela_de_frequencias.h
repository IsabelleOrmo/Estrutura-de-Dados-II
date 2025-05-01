#ifndef TABELA_DE_FREQUENCIAS
#define TABELA_DE_FREQUENCIAS
#include "meustiposonlinegdb.h"

typedef struct {
    U8* byte; // ponteiro que guarda o byte
    U64 frequencia; // guarda  a frenquencia desse byte
} Elemento;

typedef struct Struct_do_no_de_arvore_binaria { // um nó da arvore
    struct Struct_do_no_de_arvore_binaria* esquerda;
    Elemento informacao;
    struct Struct_do_no_de_arvore_binaria* direita;
} Struct_do_no_de_arvore_binaria;

typedef Struct_do_no_de_arvore_binaria* Ptr_de_no_de_arvore_binaria;

typedef struct {
    Ptr_de_no_de_arvore_binaria vetor [256]; // possivel valor do byte
    U16 quantidade_de_posicoes_preenchidas;
} Tabela_de_frequencias;

void nova_tabela_de_frequencias (Tabela_de_frequencias* tab /* por referência */);
boolean inclua_byte (U8 byte /* por valor */,
                     Tabela_de_frequencias* tab /* por referencia */);
void junte_nodos_no_inicio_do_vetor (Tabela_de_frequencias* tab /* por referencia */)

#endif