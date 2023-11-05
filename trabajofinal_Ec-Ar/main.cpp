#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include<set>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#define Archivo "../Inventariado Fisico.csv"
#include "HashMap/HashMap.h"
#include "Lista/Lista.h"
#include "Arbol/ArbolBinario.h"
using namespace std;

struct Item {
    std::string grupo;
    std::string codigo_barras;
    std::string articulo;
    Lista<int> *depositos = new Lista<int>();
};


Lista<Item> LeerCVS(){

    ifstream archivo(Archivo);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
    }

    getline(archivo, linea);
    Lista<Item> *datos = new Lista<Item>();

    string grupo;
    while(getline(archivo, linea)){
        Item item;
        std::stringstream stream(linea);

        getline(stream, item.grupo, ',');
        if(item.grupo=="") item.grupo = grupo;
        else grupo =item.grupo;
        getline(stream, item.codigo_barras, ',');
        getline(stream, item.articulo, ',');

        string var;
        while(getline(stream,var,',')){
            int deposito;
            try {deposito = std::stoi(var);}
            catch(std::invalid_argument const &e){
                deposito=0;
            };
            item.depositos->insertarUltimo(deposito);
        }
        datos->insertarUltimo(item);
    }

    archivo.close();

    return *datos;
}


void mostrar_item_partes(Item item, bool grupo=false, bool codigo=false, bool nombre=false, bool depositos=false){
    if(grupo) cout<<"Grupo: "<<item.grupo<<endl;
    if(codigo) cout << "Codigo de Barras: " << item.codigo_barras << endl;
    if(nombre) cout << "Articulo: " << item.articulo << endl;
    if(!depositos) return;
    for(int i = 0;i<item.depositos->getTamanio();i++){
        std::cout<< " D"<<i+1<<": "<< item.depositos->getDato(i)<<"|";
    }
    cout<<endl;
}

void mostrar_datos(Lista<Item> &lista,bool grupo=false, bool codigo=false, bool nombre= false, bool depositos=false){
    int len = lista.getTamanio();
    for (int i=0;i<len;i++) {
        mostrar_item_partes(lista.getDato(i),grupo,codigo,nombre,depositos);
        std::cout << "=============================" << std::endl; // Separador
    }
}

int total_art(Lista<Item>& datos){
    // mostrar_datos(datos);
    return datos.getTamanio();
}

int total_art_dif(Lista<Item>& datos){
    int total=0;
    Item articulo;
    for( int i =0;i<datos.getTamanio();i++){
        articulo = datos.getDato(i);
        for(int j = 0;j<articulo.depositos->getTamanio();j++){
            total+=articulo.depositos->getDato(j);
        }
    }
    return total;
}

bool esta_el_articulo_dentro_del_stock_seleccionado(int stock_articulo,int stock_seleccionado, bool es_menor){
    if(es_menor)return stock_articulo<=stock_seleccionado;
    return stock_articulo >= stock_seleccionado;
}

Lista<Item> obtener_min_max_stock(Lista<Item>& datos, int n_stock,bool es_menor, int n_deposito=-1){
    Item item;
    Lista<Item> *art_min_stock = new Lista<Item>();
    int stock_articulo;

    bool todos_depositos = n_deposito==-1;

    bool depositoSeleccionado_fuera= datos.getDato(0).depositos->getTamanio()<= n_deposito;
    if(!todos_depositos &&depositoSeleccionado_fuera ){ // No se puede escoger ese numero de deposito
        item.articulo="Error";
        art_min_stock->insertarUltimo(item);
        return *art_min_stock;
    }

    for( int i =0; i < datos.getTamanio();i++){
        item= datos.getDato(i);
        stock_articulo=0;

        if(!todos_depositos){ //Si es que se ha seleccionado un deposito
            stock_articulo = item.depositos->getDato(n_deposito-1);
        }
        else{ //Si es que no se ha seleccionado un deposito
            for(int i =0; i<item.depositos->getTamanio();i++){
                stock_articulo+=item.depositos->getDato(i);
            }
        }
        if(esta_el_articulo_dentro_del_stock_seleccionado(stock_articulo,n_stock,es_menor)) art_min_stock->insertarUltimo(item);
    }
    return *art_min_stock;
}

Item obtener_articulo_codigo(Lista<Item>& datos, string codigo_barra){
    Item item;
    for(int i =0; i<datos.getTamanio();i++){
        item=datos.getDato(i);
        if (codigo_barra.compare(item.codigo_barras) ==0) return item;
    }
    item.articulo="Error";
    return item;

}

Item obtener_articulo_nombre(Lista<Item>& datos, string nombre_articulo){
    Item item;
    for(int i =0; i<datos.getTamanio();i++){
        item=datos.getDato(i);
        if (nombre_articulo.compare(item.articulo) ==0) return item;
    }
    item.articulo="Error";
    return item;

}
int stock(Lista<Item>& datos, string nombre_articulo, bool codigo_barras,int n_deposito=-1){
    Item articulo =  codigo_barras?obtener_articulo_codigo(datos,nombre_articulo):obtener_articulo_nombre(datos,nombre_articulo);
    if(articulo.articulo == "Error"){ // No existe el articulo
        cout<<"Articulo no Encontrado"<<endl;
        return -1;
    }
    bool todos_depositos = n_deposito==-1;
    if(todos_depositos){
        int stock=0;

        for(int i=0; i<articulo.depositos->getTamanio(); i++){
            stock+=articulo.depositos->getDato(i);
        }
        return stock;
    }
    return articulo.depositos->getDato(n_deposito-1);
}


int obtener_clave_hash(string codigo){
    int ascii=-1;
    string articulo;
    int grupo=-1;
    int ascii_int;
    for(char c: codigo){
        if(c=='-'){
            if(grupo==-1){
                grupo=ascii;
                ascii=0;
                continue;
            }
            continue;
        }
        ascii_int = static_cast<int>(c);

        ascii+=ascii_int;
    }
    string respuesta= to_string(grupo)+to_string(ascii);
    return stoi(respuesta);
}


int main() {

    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();


    Lista<Item> datos = LeerCVS();

    /*HashMap<int, Item> *tabla_hash = new HashMap<int, Item>(datos.getTamanio());
    for(int i =0; i<datos.getTamanio();i++){
        Item item = datos.getDato(i);
        tabla_hash->put(obtener_clave_hash(item.codigo_barras),item);
    }*/

    string articulo_ej="GVB-ZBAJOPIL-BLANCO";

    cout << "Datos :"<<endl;
    mostrar_datos(datos);
    cout<<endl;

    int total_art_mostrar = total_art_dif(datos);
    cout << "Total Art: "<<total_art_mostrar<<endl;
    cout<<"Total grupos: "<< total_art(datos)<<endl;
    cout<<endl;

    int stock_min_ej = 5;
    Lista<Item> min_stock = obtener_min_max_stock(datos,stock_min_ej,true);
    cout<< "Articulos Con Stock menor que "<<stock_min_ej<<": "<<endl;
    mostrar_datos(min_stock,false,false,true,true);
    cout<<endl;

    int n_deposito_ej= 3;
    Lista<Item> min_stock_deposito_3 = obtener_min_max_stock(datos,stock_min_ej,true,n_deposito_ej);
    cout<<"Articulos Stock <= "<<stock_min_ej<<" en el dep :"<<n_deposito_ej<<endl;
    mostrar_datos(min_stock_deposito_3,false,false,true,true);
    cout<<endl;

    int stock_ = stock(datos,articulo_ej,true);
    cout<<"Stock de "<<articulo_ej<<" : "<<stock_<<endl;
    cout<<endl;

    int stock_deposito = stock(datos,articulo_ej,true,n_deposito_ej);
    cout<<"Stock de "<<articulo_ej<<" en Dep 3: "<<stock_deposito<<endl;
    cout<<endl;

    int stock_max_ej=5;
    Lista<Item> max_stock = obtener_min_max_stock(datos,stock_max_ej,false);
    cout<< "Articulos Con Stock mayor o igual que "<<stock_max_ej<<": "<<endl;
    mostrar_datos(max_stock,0,0,1,1);
    cout<<endl;



    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout<<" "<<endl;
    cout << "Tardo elapsed_secs  " << elapsed_secs << "\n" << std::endl;
    return 0;

}