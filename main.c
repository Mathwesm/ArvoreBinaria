#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};


struct No* novoNo(int valor) {
    struct No* raiz = (struct No*)malloc(sizeof(struct No));
    raiz->valor = valor;
    raiz->esquerda = NULL;
    raiz->direita = NULL;
    return raiz;
}


struct No* inserir(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return novoNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}


struct No* buscar_no(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar_no(raiz->esquerda, valor);
    }
    return buscar_no(raiz->direita, valor);
}


struct No* encontreMinimo(struct No* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}


struct No* remover_no(struct No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (valor < raiz->valor) {
        raiz->esquerda = remover_no(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover_no(raiz->direita, valor);
    } else {

        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
        if (raiz->esquerda == NULL) {
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        }

        if (raiz->direita == NULL) {
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        if (raiz->esquerda != NULL && raiz->direita != NULL) {
            struct No* minimo_no = encontreMinimo(raiz->direita);
            raiz->valor = minimo_no->valor;
            raiz->direita = remover_no(raiz->direita, minimo_no->valor);
        }
    }
    return raiz;
}

void emOrdem(struct No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void preOrdem(struct No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void posOrdem(struct No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

void liberarArv(struct No* raiz) {
    if (raiz != NULL) {
        liberarArv(raiz->esquerda);
        liberarArv(raiz->direita);
        free(raiz);
    }
}

int main(void) {
    struct No* raiz = NULL;
    raiz = inserir(raiz, 10);
    inserir(raiz, 5);
    inserir(raiz, 15);
    inserir(raiz, 6);
    inserir(raiz, 9);
    inserir(raiz, 3);
    inserir(raiz, 12);
    inserir(raiz, 13);
    inserir(raiz, 16);

    printf("Percorrendo: ");
    emOrdem(raiz);
    printf("\n");

    raiz = remover_no(raiz, 3);
    printf("Apos remover o valor 3: ");
    emOrdem(raiz);
    printf("\n");

    liberarArv(raiz);

    return 0;
}
