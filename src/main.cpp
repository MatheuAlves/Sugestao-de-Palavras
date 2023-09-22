#include "hash.hpp"

using namespace std;

int main() {

    HashTable hashTable;
    string line, word;
    vector<string> palavras;
    int num_files = 6;
    int contem_palavra = 0;

    // inicia vetor stopwords
    hashTable.separastopwords();
    
    // entrada
    string arquivoEntrada = "input.data";
    ifstream arquivo("dataset/"+ arquivoEntrada);
    if (!arquivo.is_open()) {
        cerr << "Não abriu o arquivo input.data!" << endl;
        return 1;
    }

    // coloca no vector palavras
    while (getline(arquivo, line)) {
        istringstream iss(line);
        while (iss >> word) {
            palavras.push_back(word);
        }
    }
    arquivo.close();

    // lê o texto
    ofstream arquivoSaida;
    arquivoSaida.open("dataset/output.txt", ios::trunc);
    arquivoSaida.close();
    for(vector<string>::size_type i = 0; i < palavras.size(); i++) {
        for (int j = 0; j < num_files; j++) {
            string file_name = "txt" + to_string(j+1) + ".txt";
            ifstream file("dataset/"+file_name);
    
            if (!file.is_open()) {
                cerr << "Failed to open the file." << endl;
                return 1;
            }

            // coloca na hash
            while (getline(file, line)) {
                istringstream iss(line);
                while (iss >> word) {
                    if(hashTable.stopwords(word) != true){
                        hashTable.insertWord(word);
                    }
                    if(word == palavras[i]){
                        contem_palavra++;
                    }
                }
            }
            //coloca na arvore
                if (contem_palavra > 0){
                    arquivoSaida.open("dataset/output.txt", ios::app);
                    arquivoSaida << "Arquivo: txt" << j+1 << " | Palavra: " << palavras[i] << endl;
                    arquivoSaida << "-----------------------------------------------------------------------------" << endl;
                    arquivoSaida << "Heap: " << j+1 << endl;
                    arquivoSaida.close();
                    hashTable.makeHeap();    
                }
                else{
                    arquivoSaida.open("dataset/output.txt", ios::app);
                    arquivoSaida << "O arquivo txt" << j+1 << " não contém a palavra " << palavras[i] << endl;
                    arquivoSaida << "-----------------------------------------------------------------------------" << endl;
                    arquivoSaida.close();
                }
                contem_palavra = 0;
            arquivo.close();
        }
        
        
    }
    return 0;
}
