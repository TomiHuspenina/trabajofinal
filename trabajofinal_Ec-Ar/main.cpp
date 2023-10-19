#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#define Archivo "../Inventariado Fisico.csv"
#include "HashMap/HashMap.h"
#include "Lista/Lista.h"
using namespace std;

int main() {

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';
    int n=0;

    Lista<int> *L1 = new Lista<int>;
    Lista<int> *L2 = new Lista<int>;
    Lista<int> *L3 = new Lista<int>;
    Lista<int> *L4 = new Lista<int>;
    Lista<int> *L5 = new Lista<int>;
    int i=0;



    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    getline(archivo, linea);

    while(getline(archivo, linea)){

        stringstream stream(linea);
        string grupo, codigo_barras, articulo, dep1, dep2, dep3, dep4, dep5;

        getline(stream, grupo, delimitador);
        getline(stream, articulo, delimitador);
        getline(stream, codigo_barras, delimitador);
        getline(stream, dep1, delimitador);
        getline(stream, dep2, delimitador);
        getline(stream, dep3, delimitador);
        getline(stream, dep4, delimitador);
        getline(stream, dep5, delimitador);

        cout << "==================" << endl;
        cout << "grupo: " << grupo << endl;
        cout << "articulo: " << articulo << endl;
        cout << "codigo de barras: " << codigo_barras << endl;
        cout << "deposito 1: " << dep1 << endl;
        cout << "deposito 2: " << dep2 << endl;
        cout << "deposito 3: " << dep3 << endl;
        cout << "deposito 4: " << dep4 << endl;
        cout << "deposito 5: " << dep5 << endl;

        n++;
        
    }

    cout<<"cantidad de archivos: "<<n<<endl;

    archivo.close();






    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}
