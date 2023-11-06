Integrantes: 
-Julian Irusta Roure
-Gustavo Jara Ramirez
-Sebastian Arcentales Arciniega
-Tomás Huspenina

Para empezas creamos una struc llamada Item para agrupar las caracteristicas del inventariado y poder retornar y acceder a todas las caracteristicas mas facilmente.
Luego en la funcion "Lista<Item> LeerCVS()" lo que hacemos es usar el tipo de dato "Lista<Item>" para cuando leamos el archivo CVS podamos almacenar los objetos en una lista item, luego creamos otra lista datos que dentro almacena todas las caracteristicas de item, para luego retornarlo. 

    ifstream archivo(Archivo);  ---> abrimos el archivo denomidando Archivo
    string linea;
    if (!archivo.is_open()) {   --->verificamos que se haya abierto
        cerr << "Error al abrir el archivo." << endl;
    }
    getline(archivo, linea);    ---> recorre la primer fila (denominada linea) para ignorar el encabezado
    string grupo;
    while(getline(archivo, linea)){
        Item item;              ---> definimos la struct dentro de esta funcion para acceder a sus objetos
        std::stringstream stream(linea);    ---> convierte la fila en cadena de caracteres

        getline(stream, item.grupo, ',');    ---> obtiene en cadena de caracteres lo que hay en la primer columna
        if(item.grupo=="") item.grupo = grupo;   --->si el casillero esta vacio significa que es del mismo grupo, por lo que lo almacena en la struct
        else grupo = item.grupo;  ---> hay un cambio de grupo
        getline(stream, item.codigo_barras, ',');  ---> obtiene en caracteres el codigo de barras
        getline(stream, item.articulo, ',');    ---> obtiene en caracteres el nombre del deposito
        
        string var;                        --->variable para los depositos
        while(getline(stream,var,',')){    --->convierte a caracteres los casilleros de depositos
            int deposito;
            try {deposito = std::stoi(var);}     --->convertimos el valor del deposito a int
            catch(std::invalid_argument const &e){
                deposito=0;
            };
            item.depositos->insertarUltimo(deposito);  --->almacenamos los depositos en la lista de depositos dentro de Item
        }
        datos->insertarUltimo(item);    ---> almacenamos en una lista todo lo que pertenece a la struct item
    }
De esa forma leimos el archivo CVS y lo almacenamos en una lista datos, ademas de almacenar los depositos en otra lista pero dentro de la struct Item.

Luego para verificar la cantidad de articulos diferentes que hay lo que hacemos es que pasamos por parametro la lista datos creada anteriormente y obtenemos su tamanio con "getTamanio()".
