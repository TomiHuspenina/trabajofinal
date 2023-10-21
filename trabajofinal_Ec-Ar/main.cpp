#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include<set>
#define Archivo "../Inventariado Fisico.csv"
#include "HashMap/HashMap.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinario.h"
using namespace std;


int total_art_dif(int& cant_art_dif){
    cant_art_dif=0;
    ifstream archivo(Archivo);
    char delimitador = ',';
    string linea;
    std::set<std::string> grupos;

    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

        std::stringstream lineStream(linea);
        std::string grupo;

        getline(lineStream, grupo, delimitador);
        grupos.insert(grupo);

    }

    archivo.close();

    cant_art_dif=grupos.size();

    return cant_art_dif-1;
}

int total_art(int& cant_total){

    ifstream archivo(Archivo);
    string linea;
    cant_total=0;

    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){
        cant_total++;
    }

    return cant_total-1;
}


int cantDepositos(int& depositos) {
    depositos=0;
    wchar_t delimiter = L',';
    std::wifstream archivo(L"../Inventariado Fisico.csv");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return -1;
    }

    archivo.imbue(std::locale(""));

    std::wstring linea;

    if (std::getline(archivo, linea)) {
        std::wstringstream headerStream(linea);
        std::wstring header;
        while (std::getline(headerStream, header, delimiter)) {
            if (header.find(L"deposito") != std::wstring::npos) {
                depositos++;
            }
        }
    }

    return depositos;
}


void mostrarCVS(){

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }

    getline(archivo, linea);

    while(getline(archivo, linea)){

        stringstream stream(linea);
        string grupo, codigo_barras, articulo;

        getline(stream, grupo, delimitador);
        getline(stream, codigo_barras, delimitador);
        getline(stream, articulo, delimitador);

        cout << "==================" << endl;
        cout << "grupo: " << grupo << endl;
        cout << "articulo: " << articulo << endl;
        cout << "codigo de barras: " << codigo_barras << endl;
    }

    archivo.close();

}


int main() {

    int depositos, n, m;

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    mostrarCVS();

    cout<<"cantidad de articulos: "<<total_art(n)<<endl;

    cout<<"cantidad de articulos diferentes: "<<total_art_dif(m)<<endl;

    cout<<"cantidad de depositos: "<<cantDepositos(depositos)<<endl;



    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs  " << elapsed_secs << "\n" << std::endl;
    return 0;
}
