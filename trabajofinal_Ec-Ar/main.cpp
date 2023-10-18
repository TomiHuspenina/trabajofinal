#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#define Archivo "../hojadeprueba.csv"
#include "HashMap/HashMap.h"
using namespace std;



int main() {
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();


    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';
    string nom[100], ma[100], doc[100];
    int n=0, i=0;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    getline(archivo, linea);

    while(getline(archivo, linea)){

        stringstream stream(linea);
        string nombre, mail, documento;

        getline(stream, nombre, delimitador);
        getline(stream, mail, delimitador);
        getline(stream, documento, delimitador);

        nom[i]=nombre;
        doc[i]=documento;
        ma[i]=mail;

        cout << "==================" << endl;
        cout << "nombre: " << nombre << endl;
        cout << "mail: " << mail << endl;
        cout << "Documento: " << documento << endl;

        n+=1;
        i+=1;
    }
    archivo.close();

    HashMap<string, string> *H = new HashMap<string, string>(n);

    for(i=0; i<n; i++){
        H->put(nom[i], doc[i]);
    }

    H->print();






    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}
