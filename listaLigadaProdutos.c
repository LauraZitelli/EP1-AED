/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**                                                                 **/
/**   EP 1 - Lista Ligada de Produtos                               **/
/**                                                                 **/
/**   Laura Zitelli de Souza                                        **/
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#define NUMTIPOS 10
#define true 1
#define false 0

typedef int bool;

typedef struct aux {
    int id;
    int quantidade;
    int valorUnitario;
    struct aux* proxProd;
} REGISTRO, * PONT;


typedef struct {
    PONT LISTADELISTAS[NUMTIPOS];
} LISTADEPRODUTOS, * PLISTA;



PLISTA criarLista();

int tamanho(PLISTA l);

int consultarValorUnitario(PLISTA l, int id);

PONT buscarID(PLISTA l, int id);

PONT buscarIDTipo(PLISTA l, int id, int tipo);




bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor);

bool atualizarValorDoProduto(PLISTA l, int id, int valor);

bool removerItensDeUmProduto(PLISTA l, int id, int quantidade);


PLISTA criarLista(){
    PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
    int x;
    for (x=0;x<NUMTIPOS;x++){
        res->LISTADELISTAS[x] = (PONT) malloc(sizeof(REGISTRO));
        res->LISTADELISTAS[x]->id = -1;
        res->LISTADELISTAS[x]->quantidade = 0;
        res->LISTADELISTAS[x]->valorUnitario = 0;
        res->LISTADELISTAS[x]->proxProd = NULL;
    }
    return res;
}


int tamanho(PLISTA l){
    int tam = 0;
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual) {
            atual = atual->proxProd;
            tam++;
        }
    }
    return tam;
}

PONT buscarID(PLISTA l, int id){
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual) {
            if (atual->id == id) return atual;
            atual = atual->proxProd;
        }
    }
    return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
    if (tipo<0 || tipo>=NUMTIPOS) return NULL;
    PONT atual = l->LISTADELISTAS[tipo]->proxProd;
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proxProd;
    }
    return NULL;
}

void exibirLog(PLISTA f){
    int numElementos = tamanho(f);
    printf("Log lista [elementos: %i]\n", numElementos);
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        printf("  #TIPO: %i -> ", x);
        atual = f->LISTADELISTAS[x]->proxProd;
        while (atual){
            printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
            atual = atual->proxProd;
        }
        printf("\n");
    }
    printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual) {
            if (atual->id == id) return atual->valorUnitario;
            atual = atual->proxProd;
        }
    }
    return 0;
}


/* ------------ Funções auxiliares criadas -------------- */

PONT buscaIdERetornaAnterior(PLISTA l, int id, PONT *ant) {
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        atual = l->LISTADELISTAS[x]->proxProd;
        *ant = l->LISTADELISTAS[x];
        while (atual) {
            if (atual->id == id) {
                return atual;
            };
            *ant = atual;
            atual = atual->proxProd;
        }
    }
    return NULL;
}

int buscaTipoPorID(PLISTA l, int id) {
    int x;
    PONT atual;
    for (x=0;x<NUMTIPOS;x++){
        atual = l->LISTADELISTAS[x]->proxProd;
        while (atual) {
            if (atual->id == id) return x;
            atual = atual->proxProd;
        }
    }
    return -1;
}

bool reorganizaLista(PLISTA l, int tipo, PONT novo){
    if((novo->id < 0 || novo->quantidade < 0 || novo->valorUnitario < 0) || (tipo < 0 || tipo > NUMTIPOS-1)) {
        return false;
    } else {
        PONT cabeca = l->LISTADELISTAS[tipo];
        PONT atual = cabeca;
        PONT ant = atual;

        int valorTotalNovo = novo->quantidade * novo->valorUnitario;

        //verifica caso de lista vazia
        if(tamanho(l) == 0) {
            cabeca->proxProd = novo;
            novo->proxProd = NULL;
        } else {
            while(atual) {
                int valorTotalAtual = atual->quantidade * atual->valorUnitario;
                if(valorTotalNovo > valorTotalAtual) {
                    ant = atual;
                    atual = atual->proxProd;
                } else {
                    ant->proxProd = novo;
                    novo->proxProd = atual;
                    return true;
                }
            }
            if(ant->proxProd == NULL) {
                ant->proxProd = novo;
                novo->proxProd = NULL;
            }
        }
        return true;
    }
}

/* ------------------------------------------------------------ */


bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
    PONT verificaId = buscarID(l, id);
    if( verificaId != NULL || (id < 0 || quantidade < 0 || valor < 0) || (tipo < 0 || tipo > NUMTIPOS-1)) {
        return false;
    } else {
        PONT cabeca = l->LISTADELISTAS[tipo];
        PONT atual = cabeca;
        PONT ant = atual;

        // cria novo registro com os valores passados
        PONT novo = (PONT) malloc(sizeof(REGISTRO));
        novo->valorUnitario = valor;
        novo->id = id;
        novo->quantidade = quantidade;
        int valorTotalNovo = novo->quantidade * novo->valorUnitario;

        //verifica caso de lista vazia
        if(tamanho(l) == 0) {
            cabeca->proxProd = novo;
            novo->proxProd = NULL;
        } else {
            while(atual) {
                int valorTotalAtual = atual->quantidade * atual->valorUnitario;
                if(valorTotalNovo > valorTotalAtual) {
                    ant = atual;
                    atual = atual->proxProd;
                } else {
                    ant->proxProd = novo;
                    novo->proxProd = atual;
                    return true;
                }
            }
            if(ant->proxProd == NULL) {
                ant->proxProd = novo;
                novo->proxProd = NULL;
            }
        }
        return true;
    }
}


bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
    PONT ant;
    // encontra o produto a ser removido e seu anterior
    PONT produto = buscaIdERetornaAnterior(l, id, &ant);

    if(produto == NULL || quantidade <= 0 || produto->quantidade < quantidade){
        return false;
    } else {
        // se a nova quantidade do produto for igual a 0, remove o produto da lista
        if(quantidade == produto->quantidade) {
            ant->proxProd = produto->proxProd;
            free(produto);
        } else {
            // modifica a quantidade do produto
            produto->quantidade -= quantidade;

            int totalProduto = produto->quantidade * produto->valorUnitario;
            int totalAnterior = ant->quantidade * ant->valorUnitario;

            // caso o novo valor total do produto seja menor que a do seu antecessor, reorganiza a lista
            if(totalProduto <= totalAnterior) {
                int produtoTipo = buscaTipoPorID(l, id);
                ant->proxProd = produto->proxProd;
                reorganizaLista(l, produtoTipo, produto);
            }
        }
    }
    return true;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){
    PONT ant;
    // encontra o produto a ser atualizado e seu anterior
    PONT produto = buscaIdERetornaAnterior(l, id, &ant);
    // encontra o tipo do produto a ser atualizado
    int produtoTipo = buscaTipoPorID(l, id);

    if(produto == NULL || valor <= 0){
        return false;
    } else {
        // atualiza o valor unitário do produto e reorganiza a lista
        produto->valorUnitario = valor;
        ant->proxProd = produto->proxProd;
        reorganizaLista(l, produtoTipo, produto);
    }
    return true;
}



int main() {
    PLISTA f = criarLista();
    int id;
    int tipo;
    int quantidade;
    int valor;
    bool res;

    printf("################# INSERINDO #######################\n");

    exibirLog(f);
    res = inserirNovoProduto(f, 2, 1, 22, 23);
    if(res) printf("Insercao retornou true (1)\n");
    else printf("Insercao retornou false (1)\n");
    exibirLog(f);
    res = inserirNovoProduto(f, 4, 4, 4, 4);
    if(res) printf("Insercao retornou true (2)\n");
    else printf("Insercao retornou false (2)\n");
    exibirLog(f);
    res = inserirNovoProduto(f, 6, 1, 8, 9);
    if(res) printf("Insercao retornou true (3)\n");
    else printf("Insercao retornou false (3)\n");
    exibirLog(f);
    res = inserirNovoProduto(f, 3, 1, 22, 23);
    if(res) printf("Insercao retornou true (4)\n");
    else printf("Insercao retornou false (4)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, -5, 6, 7, 8);
    if(res) printf("Insercao retornou true (5)\n");
    else printf("Insercao retornou false (5)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, -6, 7, 8);
    if(res) printf("Insercao retornou true (6)\n");
    else printf("Insercao retornou false (6)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, 6, -7, 8);
    if(res) printf("Insercao retornou true (7)\n");
    else printf("Insercao retornou false (7)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 5, 6, 7, -8);
    if(res) printf("Insercao retornou true (8)\n");
    else printf("Insercao retornou false (8)\n");
    exibirLog(f);

    res = inserirNovoProduto(f, 3, 1, 9, 9);
    if(res) printf("Insercao retornou true (9)\n");
    else printf("Insercao retornou false (9)\n");
    exibirLog(f);


    printf("################# REMOVENDO #######################\n");
    res = removerItensDeUmProduto(f, 4, 1);
    if(res) printf("Remocao retornou true (1)\n");
    else printf("Remocao retornou false (1)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 2, 1);
    if(res) printf("Remocao retornou true (2)\n");
    else printf("Remocao retornou false (2)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 3, 22);
    if(res) printf("Remocao retornou true (3)\n");
    else printf("Remocao retornou false (3)\n");
    exibirLog(f);


    res = removerItensDeUmProduto(f, 20, 1);
    if(res) printf("Remocao retornou true (4)\n");
    else printf("Remocao retornou false (4)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 5, 10);
    if(res) printf("Remocao retornou true (5)\n");
    else printf("Remocao retornou false (5)\n");
    exibirLog(f);

    res = removerItensDeUmProduto(f, 4, 0);
    if(res) printf("Remocao retornou true (6)\n");
    else printf("Remocao retornou false (6)\n");
    exibirLog(f);



    printf("################# ATUALIZANDO VALOR #######\n");

    res = atualizarValorDoProduto(f, 6, 1);
    if(res) printf("Atualizacao retornou true (1)\n");
    else printf("Atualizacao retornou false (1)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 600);
    if(res) printf("Atualizacao retornou true (2)\n");
    else printf("Atualizacao retornou false (2)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, 20);
    if(res) printf("Atualizacao retornou true (3)\n");
    else printf("Atualizacao retornou false (3)\n");
    exibirLog(f);


    res = atualizarValorDoProduto(f, 6, 0);
    if(res) printf("Atualizacao retornou true (4)\n");
    else printf("Atualizacao retornou false (4)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 6, -100);
    if(res) printf("Atualizacao retornou true (5)\n");
    else printf("Atualizacao retornou false (5)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 61, 600);
    if(res) printf("Atualizacao retornou true (6)\n");
    else printf("Atualizacao retornou false (6)\n");
    exibirLog(f);



    res = atualizarValorDoProduto(f, 6, 3);
    if(res) printf("Atualizacao retornou true (7)\n");
    else printf("Atualizacao retornou false (7)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 4, 200);
    if(res) printf("Atualizacao retornou true (8)\n");
    else printf("Atualizacao retornou false (8)\n");
    exibirLog(f);

    res = atualizarValorDoProduto(f, 2, 20);
    if(res) printf("Atualizacao retornou true (9)\n");
    else printf("Atualizacao retornou false (9)\n");
    exibirLog(f);




    return 0;
}