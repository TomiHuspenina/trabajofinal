#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include <list>
#define Archivo "Inventariado Fisico.csv"
#include "HashMapList/HashMapList.h"
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
        std::stringstream stream(linea); // convierte linea en cadena de caracteres

        getline(stream, item.grupo, ',');
        if(item.grupo=="") item.grupo = grupo;
        else grupo = item.grupo;
        getline(stream, item.codigo_barras, ',');
        getline(stream, item.articulo, ',');

        string var;
        while(getline(stream,var,',')){
            int deposito;
            try {deposito = std::stoi(var);}  // convertimos el valor del deposito a int
            catch(std::invalid_argument const &e){
                deposito=0;
            };
            item.depositos->insertarUltimo(deposito);  //almacenamos los depositos en la lista de depositos
        }
        datos->insertarUltimo(item); // almacenamos en una lista todo lo que pertenece a la struct item
    }

    archivo.close();

    return *datos;  // retornamos la lista con los datos de struct
}


void mostrar_item_partes(Item item, bool grupo=false, bool codigo=false, bool nombre=false, bool depositos=false){
    if(grupo) std::cout<<"Grupo: "<<item.grupo<<endl;
    if(codigo) std::cout << "Codigo de Barras: " << item.codigo_barras << endl;
    if(nombre) std::cout << "Articulo: " << item.articulo << endl;
    if(!depositos) return;
    for(int i = 0;i<item.depositos->getTamanio();i++){
        std::cout<< " D"<<i+1<<": "<< item.depositos->getDato(i)<<"|";
    }
    std::cout<<endl;
}

void mostrar_datos(Lista<Item> &lista,bool grupo=false, bool codigo=false, bool nombre= false, bool depositos=false){
    int len = lista.getTamanio();
    for (int i=0;i<len;i++) {
        mostrar_item_partes(lista.getDato(i),grupo,codigo,nombre,depositos);
        std::cout <<i+1<< "=============================" << std::endl; // Separador
    }
}

int total_art(Lista<Item>& datos){
    return datos.getTamanio();  //retornamos el tamaño de la lista con todos los datos de la struct item
}

int total_art_dif(Lista<Item>& datos){
    int total=0;
    Item item;
    for( int i =0;i<datos.getTamanio();i++){
        item = datos.getDato(i);
        for(int j = 0;j<item.depositos->getTamanio();j++){
            total+=item.depositos->getDato(j);  //suma los numeros de cada deposito
        }
    }
    return total;
}

bool esta_el_articulo_dentro_del_stock_seleccionado(int stock_articulo,int stock_seleccionado, bool es_menor){
    if(es_menor)return stock_articulo<=stock_seleccionado;
    return stock_articulo >= stock_seleccionado;
}

Lista<Item> obtener_min_max_stock(Lista<Item>& datos, int n_stock,bool es_menor, int n_deposito=-1){ //si es -1 no se ha escogido un deposito
    Item item;
    Lista<Item> *art_min_stock = new Lista<Item>();
    int stock_articulo;

    bool todos_depositos = (n_deposito==-1);

    bool depositoSeleccionado_fuera= datos.getDato(0).depositos->getTamanio()<= n_deposito;
    if(!todos_depositos &&depositoSeleccionado_fuera ){ // No se puede escoger ese numero de deposito
        item.articulo="Error";
        art_min_stock->insertarUltimo(item);
        return *art_min_stock;
    }

    for( int i = 0; i < datos.getTamanio() ; i++){
        item = datos.getDato(i);
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
    Item articulo;
    if(codigo_barras){
        articulo = obtener_articulo_codigo(datos, nombre_articulo);
    }else{
        articulo = obtener_articulo_nombre(datos, nombre_articulo);
    }

    if(articulo.articulo == "Error"){ // No existe el articulo
        std::cout<<"Articulo no Encontrado"<<endl;
        return -1;
    }
    bool todos_depositos = n_deposito==-1;
    if(todos_depositos){
        int stock=0;

        for(int i=0; i<articulo.depositos->getTamanio(); i++){
            stock+=articulo.depositos->getDato(i);  //sumamos el stock
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


int main(int argc, char **argv) {

    clock_t begin;
    std::cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();



    Lista<Item> datos = LeerCVS();
    string articulo_ej="GVB-ZBAJOPIL-BLANCO";


    std::cout<<"cantidad de argumentos: "<<argc<<endl;
    Item item;

    std::cout<<"argumento 1: "<<argv[0]<<endl;

    if(strcmp(argv[1],"-total_art_dif")==0){
        cout<<"Total: "<<total_art_dif(datos)<<endl;
    }

    if(strcmp(argv[1],"-total_art")==0){
        cout<<"Total: "<<total_art(datos)<<endl;
    }

    if(strcmp(argv[1],"-min_stock")==0){
        int num_stock=std::stoi(argv[2]);
        int num_dep=-1;

        if(argc==4){
            num_dep=std::stoi(argv[3]);
        }
        if(num_stock<0 || num_dep< -2 || (num_dep!=-1 && num_dep<item.depositos->getTamanio())){
            cerr<<"numero no valido"<<endl;
            return 1;
        }
        Lista<Item> min_stock_deposito = obtener_min_max_stock(datos,num_stock,true,num_dep);
        mostrar_datos(min_stock_deposito,false,false,true,true);
    }

    if(strcmp(argv[1],"-stock")==0){
        string nom_articulo = argv[2];
        int num_deposito = -1;
        if(argc==4) num_deposito = std::stoi(argv[3]);
        int stock_ = stock(datos,nom_articulo,false,num_deposito);
        cout<<"Stock :"<<stock_<<endl;

    }
    if(strcmp(argv[1],"-max_stock")==0){

        int num_stock;
        num_stock=std::stoi(argv[2]);
        int num_dep =-1;
        if(argc==4){
            num_dep=std::stoi(argv[3]);
        }
        if(num_stock<0 || num_dep< -2 || (num_dep!=-1 && num_dep<item.depositos->getTamanio())){
            cerr<<"numero no valido"<<endl;
            return 1;
        }
        Lista<Item> max_stock = obtener_min_max_stock(datos,num_stock,false,num_dep);
        mostrar_datos(max_stock,false,false,true,true);
    }



    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    std::cout<<" "<<endl;
    std::cout << "Tardo elapsed_secs  " << elapsed_secs << "\n" << std::endl;
    return 0;

}