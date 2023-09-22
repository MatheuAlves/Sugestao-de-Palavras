// avl.hpp
#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Record_AVL {
    string palavra;
    int value;
    int key;
};

struct Tree_AVL {
    Record_AVL item;
    Tree_AVL *esq, *dir;
    int peso;
};

Tree_AVL* createTree_AVL();
void insertItem_AVL(Tree_AVL*& t, const Record_AVL& item);
void removeItem_AVL(Tree_AVL*& t, const Record_AVL& item);
void preordem_AVL(const Tree_AVL* t);
void central_AVL(const Tree_AVL* t);
void posordem_AVL(const Tree_AVL* t);
void free_AVL(Tree_AVL*& t);
void rotacaoSimplesDireita_AVL(Tree_AVL*& t);
void rotacaoSimplesEsquerda_AVL(Tree_AVL*& t);
void rotacaoDuplaDireita_AVL(Tree_AVL*& t);
void rotacaoDuplaEsquerda_AVL(Tree_AVL*& t);
int getMaxPeso(int left, int right);
int getPeso(const Tree_AVL* t);


#endif
