#ifndef BINARIA_HPP
#define BINARIA_HPP

#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

class Record_bin {
public:
	string palavra;
	int value;
	int key;
};

class Tree_bin {
public:
	Record_bin reg;
	Tree_bin *esq, *dir;
	vector<int> auxBin;

	~Tree_bin() {}

	Tree_bin *createTreeClass();
	void insertItemClass(Tree_bin **t, Record_bin r);
	void pesquisaClass(Tree_bin **t, Tree_bin **aux, Record_bin r);

	void antecessorClass(Tree_bin **t, Tree_bin *aux);
	void removeItemClass(Tree_bin **t, Record_bin r);
	void freeRaiz_2(Tree_bin *t);

	void preordemClass(Tree_bin *t);
	void centralClass(Tree_bin *t);
	void posordemClass(Tree_bin *t);
};

#endif