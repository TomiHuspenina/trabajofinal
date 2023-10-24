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


int cant_depositos(int& depositos) {
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
    ifstream archivo(Archivo);
    string linea, nom_articulo, columnas;
    int i, cant_columnas=0;

    getline(archivo, linea);//encabezado
    stringstream stream(linea);
    while(getline(stream, columnas, ',')){
        cant_columnas++;
    }

    while (getline(archivo, linea)) {
        stringstream stream_(linea);
        string palabra;
        int num = 0, cant_articulos = 0;
        for (i = 0; i < cant_columnas; i++) {
            getline(stream_, palabra, ',');
            if (i == 2) {
                nom_articulo = palabra;
            }
            if (i > 2) {
                try {
                    num = stoi(palabra);
                    if (num > 0) {
                        cant_articulos += num;
                    }
                } catch (const invalid_argument &e) {}
            }
        }
    }
    archivo.close();
}

void min_stock_depo(int n, int depo) {
    ifstream archivo(Archivo);
    string linea;
    int c;
    string nom_articulo;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea); //ignorar el encabezado

    while (getline(archivo, linea)) {

        stringstream stream(linea);
        string palabra;
        int cant_articulos = 0;

        for (int i = 0; i < cant_depositos(c)+2; i++) {
            getline(stream, palabra, ',');
            if (i == 2) {
                nom_articulo = palabra;
            }
            if (i == depo + 2) {
                try {
                    cant_articulos = stoi(palabra);
                } catch (const invalid_argument &e) {}
            }
        }
        if(cant_articulos<=n){
            cout<<"nombre del articulo: "<<nom_articulo<<endl;
            cout<<"cantidad: "<<cant_articulos<<endl;
        }
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
    int depositos, m, n, depo;
    string art;

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    //mostrarCVS();

    cout<<"cantidad de articulos: "<<total_art(m)<<endl;

    //total_art_dif();

    cout<<"cantidad de depositos: "<<cant_depositos(depositos)<<endl;

    //cout<<"minimo stock: "<<endl;
    //min_stock(5);

    cout<<"minimo stock en deposito: "<<endl;
    min_stock_depo(5,3);

    //cout<<"stock de articulo: "<<endl;
    //stock_articulo(art);

    //cout<<"stock de deposito: "<<endl;
    //stock_articulo_deposito(art, depo);

    //cout<<"maximo stock: "<<endl;
    //min_stock(n);

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs  " << elapsed_secs << "\n" << std::endl;
    return 0;
}