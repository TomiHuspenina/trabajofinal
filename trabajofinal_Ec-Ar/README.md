Integrantes: 

-Julian Irusta Roure.

-Gustavo Jara Ramirez.

-Sebastian Arcentales Arciniega.

-Tomás Huspenina.


Logica usada:
Creamos una struc llamada item, donde se pone cada una de sus caracteristicas y en el caso de depostio lo hicimos como lista, para almacenar cada deposito y luego es mas facil obtener su tyamaño con la funcion getTamanio()

     if(item.grupo=="") item.grupo = grupo;
        else grupo = item.grupo;
        
En esta seccion de codigo lo que hacemos es que si item.grupo es vacia, se va a llamar como el grupo anterior, sino se asigna un nuevo nombre de grupo a item.grupo

     while(getline(stream,var,',')){
            int deposito;
            try {deposito = std::stoi(var);}  // convertimos el valor del deposito a int
            catch(std::invalid_argument const &e){
                deposito=0;
            };
            item.depositos->insertarUltimo(deposito);  //almacenamos los depositos en la lista de depositos
        } 
        
En este while lo que hacemos es recorrer cada deposito, en el try pasar del caracter que day dentro del deposito a un numero entero, y en el caso de que sea null, asignarle 0.
Al final almacenamos la info que hay en el deposito 1 del articulo 1 a la lista de depositos y asi hasta recorrer todos los depositos de un mismo artriculo.

       bool esta_el_articulo_dentro_del_stock_seleccionado(int stock_articulo,int stock_seleccionado, bool es_menor){
           if(es_menor)return stock_articulo<=stock_seleccionado;
           return stock_articulo >= stock_seleccionado;
       }

Es una función de ayuda que hemos usado para poder filtrar los artículos en base a si son mayor o menor que el stock seleccionado. Esta función devuelve un booleano, retorna un verdadero cual es artículo está dentro del stock seleccionado y falso cuando no lo está.

    bool todos_depositos = (n_deposito==-1);
    bool depositoSeleccionado_fuera= datos.getDato(0).depositos->getTamanio()<= n_deposito;
    if(!todos_depositos &&depositoSeleccionado_fuera ){ // No se puede escoger ese numero de deposito
        item.articulo="Error";
        art_min_stock->insertarUltimo(item);
        return *art_min_stock;
    }

Se verifica si el parámetro "n_deposito" es igual a -1, lo que significa que no se ha seleccionado un depósito específico. Se establece una variable booleana llamada "todos_depositos" en "true" si no se ha seleccionado un depósito y en `false` en caso contrario.
Se verifica si "n_deposito" es válido. 

Por ultimo, la logica utilizada en el int main para los argumentos compararamos el argumento recibido con un argumento esperado, en el caso del primer argumento, o argv[0] siempre va a ser el nombre del ejecutable, seguido de argv[1] que es el nombre de la funcion.
Para comparar si el nombre de la funcion corresponde con la funcion se usa srtcmp, correspondiente a la libreria cstring, si eso es igual a 0, se ejecuta lo quye hay dentro del if, caso contrario arroja error.


