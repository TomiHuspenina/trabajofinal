Integrantes: 
-Julian Irusta Roure
-Gustavo Jara Ramirez
-Sebastian Arcentales Arciniega
-Tomás Huspenina

Para empezar creamos una estructura llamada Item para agrupar las características del inventariado y poder regresar y acceder a todas las características más fácilmente. Luego en la función "Lista LeerCVS()" lo que hacemos es usar el tipo de dato "Lista" para cuando leamos el archivo CVS podamos almacenar los objetos en una lista item, luego creamos otra lista datos que dentro almacena todas las características de item , para luego retornarlo.
El uso de una lista en Lista<int> *depósitos = new Lista<int>(); permite mantener un seguimiento de las existencias en múltiples ubicaciones o depósitos para cada artículo.

Lista<Item> LeerCVS(){ Abre el archivo CSV especificado en la constante  'Archivo'.
    ifstream archivo(Archivo);
    string linea;

if (!archivo.is_open()) { //verifica si se abrio correctamente
        cerr << "Error al abrir el archivo." << endl;
    }

getline(archivo, linea); //Leemos la linea de encabezado

Lista<Item> *datos = new Lista<Item>(); //Hacemos una lista para almacenar los datos de los artículos.
 
 string grupo; //Variable para rastrear el grupo actual

while(getline(archivo, linea)){  // Lee las líneas del archivo CSV una por una.
        Item item; //definimos la struct dentro de esta funcion para acceder a sus objetos
std::stringstream stream(linea); //convierte la fila en cadena de caracteres

 getline(stream, item.grupo, ','); //obtiene en cadena de caracteres lo que hay en la primer columna

if(item.grupo == " ") { //si el casillero esta vacio significa que es del mismo grupo, por lo que lo almacena en la struct
                item.grupo = grupo; //hay un cambio de grupo
        } else {
            grupo = item.grupo;
        }
getline(stream, item.codigo_barras, ','); //obtiene en caracteres el codigo de barras
  getline(stream, item.articulo, ','); //obtiene en caracteres el nombre del deposito
 string var; //variable para los depósitos

 while(getline(stream, var, ',')){ //convierte a caracteres los casilleros de depósitos
int deposito;
try {deposito = std::stoi(var);} //convertimos el valor del depósito a int
 } catch(std::invalid_argument const &e){
                deposito = 0;   // Si la conversión falla, se establece en 0.
            }
datos->insertarUltimo(item); // Almacena la estructura 'item' en la lista 'datos'.

}

    archivo.close();  // Cierra el archivo CSV.

    return *datos;  // Retorna la lista con los datos de los artículos.
}

La función mostrar_item_partes se encarga de mostrar los detalles de un artículo, incluyendo su grupo, código de barras, nombre y las cantidades en los depósitos.

void mostrar_item_partes(Item item, bool grupo=false, bool codigo=false, bool nombre=false, bool depositos=false){
    if(grupo) cout << "Grupo: " << item.grupo << endl;
    if(codigo) cout << "Codigo de Barras: " << item.codigo_barras << endl;
    if(nombre) cout << "Articulo: " << item.articulo << endl;
    if(!depositos) return;

for(int i = 0; i < item.depositos->getTamanio(); i++){
        std::cout << " D" << i+1 << ": " << item.depositos->getDato(i) << "|";
    }
    cout << endl;
}

//Si depositos es true, muestra las cantidades en los depósitos. Para hacerlo, la función itera a través de la lista de depósitos del artículo y muestra cada cantidad con su respectivo número de depósito.






En mostrar_datos toma como argumento una referencia a una lista de estructuras Item llamada lista, a traves de un for recorre toda esta lista de estructuras y en cada iteracion llamamos a la funcion mostrar_item_partes que nos muestra todos los detalles de los artículos. 

Esta función facilita la visualización de los datos de múltiples artículos en el inventario de manera organizada y personalizable, ya que permite elegir qué detalles mostrar mediante los parámetros booleanos.

En la funcion total_art retornamos el tamaño de la lista con todos los datos de la struct item.

La función total_art_dif calcula la suma total de las cantidades en todos los depósitos de todos los artículos en la lista de estructuras Item. 

int total_art_dif(Lista<Item>& datos){
    int total = 0;  // Inicializa el contador total en 0.
    Item item;

    // Itera a través de la lista de artículos 'datos'.
    for(int i = 0; i < datos.getTamanio(); i++){
        item = datos.getDato(i);  // Obtiene un artículo de la lista.

        // Itera a través de los depósitos del artículo actual.
        for(int j = 0; j < item.depositos->getTamanio(); j++){
            total += item.depositos->getDato(j);  // Suma la cantidad en el depósito actual al total.
        }
    }

    return total;  // Retorna el total de cantidades en todos los depósitos de todos los artículos.
}

La función esta_el_articulo_dentro_del_stock_seleccionado se utiliza para determinar si la cantidad de un artículo (representada por stock_articulo) cumple con ciertos criterios de selección basados en una cantidad de stock deseada 

bool esta_el_articulo_dentro_del_stock_seleccionado(int stock_articulo, int stock_seleccionado, bool es_menor){
    if (es_menor) {
        // Si 'es_menor' es true, verifica si 'stock_articulo' es menor o igual a 'stock_seleccionado'.
        return stock_articulo <= stock_seleccionado;
    } else {
        // Si 'es_menor' es false, verifica si 'stock_articulo' es mayor o igual a 'stock_seleccionado'.
        return stock_articulo >= stock_seleccionado;
    }
}

esta_el_articulo_dentro_del_stock_seleccionado toma tres argumentos:

stock_articulo: La cantidad de stock de un artículo que se va a comparar.
stock_seleccionado: La cantidad de stock deseada que se utiliza como referencia para la comparación.
es_menor: Un valor booleano que determina la dirección de la comparación.

La función obtener_min_max_stock toma una lista de artículos (datos), un valor de stock deseado (n_stock), un valor booleano (es_menor), y un número de depósito opcional (n_deposito).

