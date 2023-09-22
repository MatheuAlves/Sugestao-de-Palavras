#include "hash.hpp"
#include "binaria.hpp"
#include "avl.hpp"
#include "huffman.hpp"
#define k 20

HashTable::HashTable() {}

struct greaters{
    bool operator()(const pair<string, int>& a,const pair<string, int>& b) const{
        return a.second>b.second;
    }
};

string HashTable::removeSpecialCharacters(string& word) {
    string cleanedWord = word;
    cleanedWord.erase(remove_if(cleanedWord.begin(), cleanedWord.end(), ::ispunct), cleanedWord.end());
    transform(cleanedWord.begin(), cleanedWord.end(), cleanedWord.begin(), ::tolower);
    return cleanedWord;
}


void HashTable::insertWord(string& word) {
    string cleanedWord = removeSpecialCharacters(word);

    if (!cleanedWord.empty()) {
        if (table.find(cleanedWord) == table.end()) {
            table[cleanedWord] = 1;
        } else {
            table[cleanedWord]++;
        }
    }
}

void HashTable::printOccurrences(){
    for (const auto& entry : table) {
        cout << entry.first << ": " << entry.second << " ocorrências" << endl;
    }
}

void HashTable::makeHeap() {
    sortedWords.clear();
    int contador = 0;

    for (auto entry = table.begin(); entry != table.end();) {
        sortedWords.emplace_back(entry->first, entry->second);
        auto aux = entry;
        entry++;
        table.erase(aux);
        if(contador == k - 1) {
            break;
        }
        else { 
            contador++;
        }
    }

    make_heap(sortedWords.begin(), sortedWords.end(), greaters());

    for (auto &entry : table) {
        if (entry.second >= sortedWords.front().second) {
            pop_heap(sortedWords.begin(), sortedWords.end(), greaters());
            sortedWords.pop_back();
            sortedWords.push_back(entry);
            push_heap(sortedWords.begin(), sortedWords.end(), greaters());
        }
    }

    printHeap();

    makeBinaria();
    makeAVL();
    makeHuffman();

}

void HashTable::separastopwords() {
    ifstream arq("dataset/stopwords.txt");
    string stopword;

    if (arq.is_open()) {
        while (getline(arq, stopword)) {
            stopword.erase(remove(stopword.begin(), stopword.end(), '\r'), stopword.end());
            pacote.push_back(stopword);
        }
        arq.close();
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

bool HashTable::stopwords(string& word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for (int i = 0; i < int(pacote.size()); ++i)
    {
        if (pacote[i] == word || "—" == word)
        {
            return true;
        }
    }
    return false;
}

int HashTable::stringToKey(string& word) {
    int key = 0;

    for (size_t i = 0; i < word.length(); i++) {
        key += static_cast<int>(word[i]) * (i + 1); // Usando o código ASCII multiplicado pela posição
    }

    return key;
}

void HashTable::printHeap() {
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);
    arquivoSaida << "\n\nTop " << k << " Palavras não ordenadas:\n" << endl;
    for (size_t i = 0; i < sortedWords.size(); ++i) {
        arquivoSaida << i + 1 << "\t" << sortedWords[i].first << ":\t" << sortedWords[i].second << " ocorrências" << endl;
    }
    arquivoSaida.close();
}

void HashTable::makeBinaria() {
    Tree_bin *raiz_bin;
	Record_bin rec_bin;
	raiz_bin = raiz_bin->createTreeClass();
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);

    arquivoSaida << "Ordem de input:{";
    for (size_t i = 0; i < sortedWords.size(); i++) {
        rec_bin.palavra = sortedWords[i].first;
        rec_bin.value = sortedWords[i].second;
		rec_bin.key = stringToKey(rec_bin.palavra);

        raiz_bin->insertItemClass(&raiz_bin, rec_bin);
		arquivoSaida << "["<< rec_bin.key << " " << rec_bin.palavra << " " << rec_bin.value << "]";
	}
    arquivoSaida << "}"<< endl;

    arquivoSaida << "Pre Ordem Binária: { ";
    arquivoSaida.close();
    raiz_bin->preordemClass(raiz_bin);
    arquivoSaida.open("dataset/output.txt", ios::app);
    arquivoSaida <<"}"<< endl;
    arquivoSaida.close();
    
}

void HashTable::makeAVL() {
    Tree_AVL* raiz_avl = createTree_AVL(); // Criar a raiz da árvore AVL com um ponteiro
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);

    for (size_t i = 0; i < sortedWords.size(); i++) {
        Record_AVL rec_avl;
        rec_avl.palavra = sortedWords[i].first;
        rec_avl.value = sortedWords[i].second;
        rec_avl.key = stringToKey(rec_avl.palavra);

        insertItem_AVL(raiz_avl, rec_avl); // Passar o ponteiro da raiz da árvore diretamente
    }

    arquivoSaida << "Pre Ordem AVL: { ";
    arquivoSaida.close();
    preordem_AVL(raiz_avl); // Chamar a função diretamente na raiz da árvore
    arquivoSaida.open("dataset/output.txt", ios::app);
    arquivoSaida << "}" << endl;
    arquivoSaida.close();
}

void HashTable::makeHuffman() {

    auto raiz_huffman = make_shared<Huffman_Tree>();
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::app);

    for (size_t i = 0; i < sortedWords.size(); i++) {
        raiz_huffman->insere(make_shared<NO_Huffman>(sortedWords[i].first,sortedWords[i].second));
	}

    raiz_huffman->constroi();
    arquivoSaida << "Pre Ordem Huffman: { ";
    arquivoSaida.close();
	raiz_huffman->preOrdem(raiz_huffman->getRaiz());
    arquivoSaida.open("dataset/output.txt", ios::app);
    arquivoSaida << "}" << endl;
    arquivoSaida << "-----------------------------------------------------------------------------" << endl;
    arquivoSaida.close();
}