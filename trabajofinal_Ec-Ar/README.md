Integrantes: 

-Julian Irusta Roure.

-Gustavo Jara Ramirez.

-Sebastian Arcentales Arciniega.

-Tomás Huspenina.



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
             try {deposito = std::stoi(var); //convertimos el valor del depósito a int
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
 Su objetivo principal es seleccionar y devolver una lista de artículos que cumplen con ciertos criterios de stock en función de los parámetros proporcionados. Los criterios dependen de si es_menor es verdadero o falso.

    Lista<Item> obtener_min_max_stock(Lista<Item>& datos, int n_stock, bool es_menor, int n_deposito = -1) {
       Item item;
       Lista<Item> *art_min_stock = new Lista<Item>();  // Crear una nueva lista para     almacenar los artículos que cumplen con los criterios
       int stock_articulo;

       // Verificar si se deben considerar todos los depósitos o si se ha seleccionado un depósito específico
       bool todos_depositos = n_deposito == -1;

       // Verificar si el número de depósito seleccionado es válido (mayor que 0) y si está dentro de los depósitos disponibles
       bool depositoSeleccionado_fuera = datos.getDato(0).depositos->getTamanio() <= n_deposito;

       if (!todos_depositos && depositoSeleccionado_fuera) {
           // No se puede seleccionar ese número de depósito, por lo que agregamos un artículo especial "Error" a la lista y la devolvemos
           item.articulo = "Error";
           art_min_stock->insertarUltimo(item);
           return *art_min_stock;
       }

       // Recorrer la lista de artículos uno por uno
       for (int i = 0; i < datos.getTamanio(); i++) {
           item = datos.getDato(i);
           stock_articulo = 0;  // Inicializar el stock del artículo

           // Determinar el stock del artículo en función de si se consideran todos los depósitos o se ha seleccionado un depósito específico
           if (!todos_depositos) {
               stock_articulo = item.depositos->getDato(n_deposito - 1);
           } else {
               // Sumar el stock de todos los depósitos del artículo
               for (int i = 0; i < item.depositos->getTamanio(); i++) {
                   stock_articulo += item.depositos->getDato(i);
               }
           }

          // Verificar si el artículo cumple con los criterios de stock en función de la función esta_el_articulo_dentro_del_stock_seleccionado
          if (esta_el_articulo_dentro_del_stock_seleccionado(stock_articulo, n_stock, es_menor)) {
              // Agregar el artículo a la lista art_min_stock si cumple con los criterios
              art_min_stock->insertarUltimo(item);
          }
       }

       // Devolver la lista art_min_stock que contiene los artículos que cumplen con los criterios de stock
       return *art_min_stock;
    }



La función obtener_articulo_codigo, busca un artículo en una lista de artículos en función de su código de barras.
 
    Item obtener_articulo_codigo(Lista<Item>& datos, string codigo_barra) {
       Item item; 
       // Crear una variable Item para almacenar el artículo encontrado o un artículo especial "Error"

       // Recorrer la lista de artículos uno por uno para encontrar un artículo con el código de barras correspondiente
       for (int i = 0; i < datos.getTamanio(); i++) {
           item = datos.getDato(i);

           // Compara el código de barras del artículo actual con el código de barras proporcionado
           if (codigo_barra.compare(item.codigo_barras) == 0) {
              // Se ha encontrado un artículo con el código de barras coincidente, por lo que se devuelve este artículo
              return item;
           }
       }
       // Si no se encontró ningún artículo con el código de barras proporcionado, se establece el artículo como "Error"
       item.articulo = "Error";
       return item;
    }

Esta función, obtener_articulo_nombre, busca un artículo en una lista de artículos en función de su nombre.

    Item obtener_articulo_nombre(Lista<Item>& datos, string nombre_articulo) {
        Item item;  // Crear una variable Item para almacenar el artículo encontrado o un artículo especial "Error"

        // Recorrer la lista de artículos uno por uno para encontrar un artículo con el nombre correspondiente
        for (int i = 0; i < datos.getTamanio(); i++) {
            item = datos.getDato(i);   
            // Compara el nombre del artículo actual con el nombre proporcionado
            if (nombre_articulo.compare(item.articulo) == 0) {
               // Se ha encontrado un artículo con el nombre coincidente, por lo que se devuelve este artículo
               return item;
            }
         }

        // Si no se encontró ningún artículo con el nombre proporcionado, se establece el artículo como "Error"
        item.articulo = "Error";
        return item;
    }





    int stock(Lista<Item>& datos, string nombre_articulo, bool codigo_barras, int n_deposito = -1) {
       // Declara una variable 'articulo' de tipo 'Item' para almacenar la información del artículo.
       Item articulo;

       // Comprueba si el artículo se busca por código de barras o por nombre.
       if (codigo_barras) {
           //Llama a la función 'obtener_articulo_codigo' para obtener el artículo por su código de barras.
           articulo = obtener_articulo_codigo(datos, nombre_articulo);
       } else {
           //Llama a la función 'obtener_articulo_nombre' para obtener el artículo por su nombre.
           articulo = obtener_articulo_nombre(datos, nombre_articulo);
       }

       // Comprueba si el artículo se encontró (o si se produjo un error).
       if (articulo.articulo == "Error") {
           // Si el artículo no se encontró, muestra un mensaje de error y devuelve -1.
           std::cout << "Articulo no Encontrado" << endl;
           return -1;
       }

       // Comprueba si se debe calcular el stock total (n_deposito == -1) o el stock de un depósito específico.
       bool todos_depositos = n_deposito == -1;  
       // Si se debe calcular el stock total:
       if (todos_depositos) {
           int stock = 0; // Inicializa la variable 'stock' en 0.
           // Itera a través de todos los depósitos del artículo y suma el stock de cada depósito.
           for (int i = 0; i < articulo.depositos->getTamanio(); i++) {
               stock += articulo.depositos->getDato(i); // Suma el stock del depósito al total.
           }
           // Devuelve el stock total.
           return stock;
       }
       // Si se debe calcular el stock de un depósito específico:
       // Utiliza 'n_deposito' para acceder al valor de stock de ese depósito en particular.
       return articulo.depositos->getDato(n_deposito - 1);
    }


    int stock(Lista<Item>& datos, string nombre_articulo, bool codigo_barras, int n_deposito = -1) {
       // Declara una variable 'articulo' de tipo 'Item' para almacenar la información del artículo.
       Item articulo;
       // Comprueba si el artículo se busca por código de barras o por nombre.
       if (codigo_barras) {
          // Llama a la función 'obtener_articulo_codigo' para obtener el artículo por su código de barras.
          articulo = obtener_articulo_codigo(datos, nombre_articulo);
       } else {
          // Llama a la función 'obtener_articulo_nombre' para obtener el artículo por su nombre.
          articulo = obtener_articulo_nombre(datos, nombre_articulo);
       }
  
       // Comprueba si el artículo se encontró (o si se produjo un error).
       if (articulo.articulo == "Error") {
          // Si el artículo no se encontró, muestra un mensaje de error y devuelve -1.
          std::cout << "Articulo no Encontrado" << endl;
          return -1;
       }
       // Comprueba si se debe calcular el stock total (n_deposito == -1) o el stock de un depósito específico.
       bool todos_depositos = n_deposito == -1;

       // Si se debe calcular el stock total:
       if (todos_depositos) {
          int stock = 0; // Inicializa la variable 'stock' en 0.

          // Itera a través de todos los depósitos del artículo y suma el stock de cada depósito.
          for (int i = 0; i < articulo.depositos->getTamanio(); i++) {
              stock += articulo.depositos->getDato(i); // Suma el stock del depósito al total.
          }
          // Devuelve el stock total.
          return stock;
       }

       // Si se debe calcular el stock de un depósito específico:
       // Utiliza 'n_deposito' para acceder al valor de stock de ese depósito en particular.
       return articulo.depositos->getDato(n_deposito - 1);
     }



