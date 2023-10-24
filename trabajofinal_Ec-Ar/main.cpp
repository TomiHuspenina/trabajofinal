#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include<set>
#define Archivo "../Inventariado Fisico.csv"
#include "HashMap/HashMap.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinario.h"
using namespace std;


int total_art(int& cant_total){

    ifstream archivo(Archivo);
    string linea;
    cant_total=0;

    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){
       cant_total++;
    }

    archivo.close();

    return cant_total;
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

    archivo.close();

    return depositos;
}

void total_art_dif(){
    int cant_art_dif=0, n;
    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){
        stringstream stream(linea);
        string deposito;

        if(getline(stream,deposito,delimitador)){
            cant_art_dif=stoi(deposito);
        }

    }

    cout<<"cantidad de articulos diferentes: "<<cant_art_dif<<endl;

    archivo.close();
}

void min_stock(int n){
    cout<<"ingrese la cantidad de productos minimos: "<<endl;
    cin>>n;

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

    }

    archivo.close();
}

void min_stock_depo(int n, int depo){
    cout<<"ingrese la cantidad de productos minimos: "<<endl;
    cin>>n;
    cout<<"ingrese el deposito: "<<endl;
    cin>>depo;

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

    }


    archivo.close();
}

void stock_articulo(string articulo){
    cout<<"ingrese el nombre del articulo: "<<endl;
    cin>>articulo;

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

    }


    archivo.close();
}

void stock_articulo_deposito(string articulo, int depo){
    cout<<"ingrese el nombre del articulo: "<<endl;
    cin>>articulo;
    cout<<"ingrese el deposito: "<<endl;
    cin>>depo;

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

    }


    archivo.close();
}

void max_stock(int n){
    cout<<"ingrese la cantidad de productos maximos: "<<endl;
    cin>>n;

    ifstream archivo(Archivo);
    string linea;
    char delimitador = ',';

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while(getline(archivo, linea)){

    }

    archivo.close();
}


/*void mostrarCVS(){

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

}*/


int main() {
    int depositoss, m, n, depo;
    string art;

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    //mostrarCVS();

    cout<<"cantidad de articulos: "<<total_art(m)<<endl;

    total_art_dif();

    cout<<"cantidad de depositos: "<<cantDepositos(depositoss)<<endl;

    cout<<"minimo stock: "<<endl;
    min_stock(n);

    cout<<"minimo stock en deposito: "<<endl;
    min_stock_depo(n, depo);

    cout<<"stock de articulo: "<<endl;
    stock_articulo(art);

    cout<<"stock de deposito: "<<endl;
    stock_articulo_deposito(art, depo);

    cout<<"maximo stock: "<<endl;
    min_stock(n);

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs  " << elapsed_secs << "\n" << std::endl;
    return 0;
}