#include "binaria.hpp"

Tree_bin *Tree_bin::createTreeClass() {
	return NULL;
}

void Tree_bin::freeRaiz_2(Tree_bin *t) {
	if (t != NULL) {
		freeRaiz_2(t->esq);
		freeRaiz_2(t->dir);
		free(t);
	}
}

void Tree_bin::insertItemClass(Tree_bin **t, Record_bin r) {
    if (*t == NULL) {
        *t = new Tree_bin;  // Aloca memória para um novo nó
        (*t)->esq = NULL;
        (*t)->dir = NULL;
        (*t)->reg = r;
    } else {
        if (r.key < (*t)->reg.key)
            insertItemClass(&(*t)->esq, r);
        else if (r.key > (*t)->reg.key)
            insertItemClass(&(*t)->dir, r);
    }
}


void Tree_bin::pesquisaClass(Tree_bin **t, Tree_bin **aux, Record_bin r) {
	if (*t == NULL) {
		printf("[ERRO]: Node not found!\n");
		return;
	}

	if ((*t)->reg.key < r.key) { pesquisaClass(&(*t)->esq, aux, r); return; }
	if ((*t)->reg.key > r.key) { pesquisaClass(&(*t)->dir, aux, r); return; }

	*aux = *t;
}

void Tree_bin::antecessorClass(Tree_bin **t, Tree_bin *aux) {
	if ((*t)->dir != NULL) {
		antecessorClass(&(*t)->dir, aux);
		return;
	}

	aux->reg = (*t)->reg;
	aux = *t;
	*t = (*t)->esq;
	free(aux);
}

void Tree_bin::removeItemClass(Tree_bin **t, Record_bin r) {
	Tree_bin *aux;

	if (*t == NULL) {
		printf("[ERROR]: Record_bin not found!!!\n");
		return;
	}

	if ((*t)->reg.key > r.key) { removeItemClass(&(*t)->esq, r); return; }
	if ((*t)->reg.key < r.key) { removeItemClass(&(*t)->dir, r); return; }

	if ((*t)->dir == NULL) {
		aux = *t;
		*t = (*t)->esq;
		free(aux);
		return;
	}

	if ((*t)->esq != NULL) {
		antecessorClass(&(*t)->esq, *t);
		return;
	}

	aux = *t;
	*t = (*t)->dir;
	free(aux);
}

void Tree_bin::preordemClass(Tree_bin *t) {
	ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
	if (!(t == NULL)) {
		arquivoSaida << "["<< t->reg.key << " " << t->reg.palavra << " " << t->reg.value << "]";
		preordemClass(t->esq);
		preordemClass(t->dir);
	}
	arquivoSaida.close();
}

void Tree_bin::centralClass(Tree_bin *t) {
	ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
	if (!(t == NULL)) {
		centralClass(t->esq);
		arquivoSaida << t->reg.key << " ";
		centralClass(t->dir);
	}
	arquivoSaida.close();
}

void Tree_bin::posordemClass(Tree_bin *t) {
	ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
	if (!(t == NULL)) {
		posordemClass(t->esq);
		posordemClass(t->dir);
		arquivoSaida << t->reg.key << " ";
	}
	arquivoSaida.close();
}
