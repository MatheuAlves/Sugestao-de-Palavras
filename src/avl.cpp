#include "avl.hpp"

#include <iostream>

Tree_AVL* createTree_AVL() {
    return nullptr;
}

void insertItem_AVL(Tree_AVL*& t, const Record_AVL& item) {
    if (t == nullptr) {
        t = new Tree_AVL;
        t->esq = nullptr;
        t->dir = nullptr;
        t->item = item;
        t->peso = 0;
    } else if (item.key < t->item.key) {
        insertItem_AVL(t->esq, item);

        if (getPeso(t->esq) - getPeso(t->dir) == 2) {
            if (item.key < t->esq->item.key)
                rotacaoSimplesDireita_AVL(t);
            else
                rotacaoDuplaDireita_AVL(t);
        }
    } else if (item.key > t->item.key) {
        insertItem_AVL(t->dir, item);

        if (getPeso(t->dir) - getPeso(t->esq) == 2) {
            if (item.key > t->dir->item.key)
                rotacaoSimplesEsquerda_AVL(t);
            else
                rotacaoDuplaEsquerda_AVL(t);
        }
    }
    t->peso = getMaxPeso(getPeso(t->esq), getPeso(t->dir)) + 1;
}

void antecessor_AVL(Tree_AVL*& t, Tree_AVL* aux) {
    if (t->dir != nullptr) {
        antecessor_AVL(t->dir, aux);
        return;
    }
    aux->item = t->item;
    aux = t;
    t = t->esq;
    delete aux;
}

void rebalancear_AVL(Tree_AVL*& t) {
    int delta;

    delta = getPeso(t->esq) - getPeso(t->dir);

    if (delta == 2) {
        if (getPeso(t->esq->esq) >= getPeso(t->esq->dir)) {
            rotacaoSimplesDireita_AVL(t);
        } else {
            rotacaoDuplaDireita_AVL(t);
        }
    } else if (delta == -2) {
        if (getPeso(t->dir->dir) >= getPeso(t->dir->esq)) {
            rotacaoSimplesEsquerda_AVL(t);
        } else {
            rotacaoDuplaEsquerda_AVL(t);
        }
    }
}

void preordem_AVL(const Tree_AVL* t) {
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
    if (t != nullptr) {
        arquivoSaida << "["<< t->item.key << " " << t->item.palavra << " " << t->item.value << "]";
        preordem_AVL(t->esq);
        preordem_AVL(t->dir);
    }
    arquivoSaida.close();
}

void central_AVL(const Tree_AVL* t) {
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
    if (t != nullptr) {
        central_AVL(t->esq);
        arquivoSaida<< t->item.key;
        central_AVL(t->dir);
    }
    arquivoSaida.close();
}

void posordem_AVL(const Tree_AVL* t) {
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
    if (t != nullptr) {
        central_AVL(t->esq);
        central_AVL(t->dir);
        arquivoSaida << t->item.key;
    }
    arquivoSaida.close();
}

int getPeso(const Tree_AVL* t) {
    return (t == nullptr) ? -1 : t->peso;
}

int getMaxPeso(int left, int right) {
    return (left > right) ? left : right;
}

void rotacaoSimplesDireita_AVL(Tree_AVL*& t) {
    Tree_AVL* aux;

    aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
    t->peso = getMaxPeso(getPeso(t->esq), getPeso(t->dir)) + 1;
    aux->peso = getMaxPeso(getPeso(aux->esq), t->peso) + 1;
    t = aux;
}

void rotacaoSimplesEsquerda_AVL(Tree_AVL*& t) {
    Tree_AVL* aux;

    aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
    t->peso = getMaxPeso(getPeso(t->esq), getPeso(t->dir)) + 1;
    aux->peso = getMaxPeso(getPeso(aux->dir), t->peso) + 1;
    t = aux;
}

void rotacaoDuplaDireita_AVL(Tree_AVL*& t) {
    rotacaoSimplesEsquerda_AVL(t->esq);
    rotacaoSimplesDireita_AVL(t);
}

void rotacaoDuplaEsquerda_AVL(Tree_AVL*& t) {
    rotacaoSimplesDireita_AVL(t->dir);
    rotacaoSimplesEsquerda_AVL(t);
}

void removeItem_AVL(Tree_AVL*& t, Tree_AVL*& f, const Record_AVL& item) {
    Tree_AVL* aux;

    if (t == nullptr) {
        cout << "Nao foi possivel encontrar o valor: " << item.key << endl;
        return;
    }

    if (item.key < t->item.key) {
        removeItem_AVL(t->esq, t, item);
        return;
    }
    if (item.key > t->item.key) {
        removeItem_AVL(t->dir, t, item);
        return;
    }

    if (t->dir == nullptr) {
        aux = t;
        t = t->esq;
        delete aux;
        rebalancear_AVL(f);
        return;
    }

    if (t->esq != nullptr) {
        antecessor_AVL(t->esq, t);
        rebalancear_AVL(f);
        rebalancear_AVL(t);
        return;
    }

    aux = t;
    t = t->dir;
    delete aux;
    rebalancear_AVL(f);
    rebalancear_AVL(t);
}

void free_AVL(Tree_AVL*& t) {
    if (t != nullptr) {
        free_AVL(t->esq);
        free_AVL(t->dir);
        delete t;
    }
}