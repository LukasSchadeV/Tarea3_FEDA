#include <iostream> // Biblioteca estándar: std::cout y std::cin
#include <fstream>  // Operaciones de lectura y escritura del Archivo CSV
#include <sstream>  // permite trabajar con flujos de cadena de caracteres
                    // Se utiliza en el código para dividir el archivo CSV utilizando la función std::getline
#include <string>   // Otorga funciones y clases para el manejo de cadenas de caracteres
                    // Se utiliza para almacenar los valores extraídos del CSV

// Estructura de datos que almacena los campos de un usuario
// datos entregados en el CSV
struct UserData {
    std::string university;
    std::string user_id;
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;
    UserData* izq; // Puntero al nodo hijo izquierdo del árbol binario.
    UserData* der; // Puntero al nodo derecho.

    // Constructor de UserData
    UserData(const std::string& uid, const std::string& uname) : user_id(uid), user_name(uname), izq(nullptr), der(nullptr) {}
};

// Clase que representa el árbol binario de búsqueda
class ArbolBinarioBusqueda {
private: // Se declara la clase privada para poder controlar de mejor manera los datos y evitar problemas 
         // restrigiendo la modificación de los datos posteriormente se utiliza un public para acceder a los datos.
    UserData* raiz; // Puntero a la raíz o base del árbol

    // Función recursiva que agrega un nodo en el árbol (User ID)
    UserData* insertarNodoPorID(UserData* nodo, const std::string& uid, const std::string& uname) {
        if (nodo == nullptr) { // verifica si el nodo actual es nulo osea una hoja
            return new UserData(uid, uname);
        }
        if (uid < nodo->user_id) { // Si el User ID es menor que el User ID del nodo actual
            nodo->izq = insertarNodoPorID(nodo->izq, uid, uname); // Insertar en el subárbol izquierdo
        } else if (uid > nodo->user_id) { // Si el User ID es mayor que el User ID del nodo actual
            nodo->der = insertarNodoPorID(nodo->der, uid, uname); // Insertar en el subárbol derecho
        }
        return nodo;
    }

    // Función recursiva que agrega un nodo en el árbol (User name)
    UserData* insertarNodoPorNombre(UserData* nodo, const std::string& uid, const std::string& uname) {
        if (nodo == nullptr) {
            return new UserData(uid, uname);
        }
        if (uname < nodo->user_name) {
            nodo->izq = insertarNodoPorNombre(nodo->izq, uid, uname);
        } else if (uname > nodo->user_name) { 
            nodo->der = insertarNodoPorNombre(nodo->der, uid, uname);
        }
        return nodo;
    }

    // Función recursiva para buscar un nodo por User ID
    UserData* buscarNodoPorID(UserData* nodo, const std::string& uid) {
        if (nodo == nullptr || nodo->user_id == uid) { // Si el nodo es nulo o el User ID coincide, retornar el nodo
            return nodo;
        }

        if (uid < nodo->user_id) { // Si el User ID es menor que el User ID del nodo actual, buscar en el subárbol izquierdo
            return buscarNodoPorID(nodo->izq, uid);
        } else { // Si el User ID es mayor que el User ID del nodo actual, buscar en el subárbol derecho
            return buscarNodoPorID(nodo->der, uid);
        }
    }

    // Función recursiva para buscar un nodo por User Name
    UserData* buscarNodoPorNombre(UserData* nodo, const std::string& uname) {
        if (nodo == nullptr || nodo->user_name == uname) { // Si el nodo es nulo o el User Name coincide, retornar el nodo
            return nodo;
        }

        if (uname < nodo->user_name) { // Si el User Name es menor que el User Name del nodo actual, buscar en el subárbol izquierdo
            return buscarNodoPorNombre(nodo->izq, uname);
        } else { // Si el User Name es mayor que el User Name del nodo actual, buscar en el subárbol derecho
            return buscarNodoPorNombre(nodo->der, uname);
        }
    }

    // Función para destruir el árbol recursivamente
    void destruirArbol(UserData* nodo) { // La funcion destruir no es obligatoria para el correcto funcionamiento
                                         // pero ayuda a liberar memoria asignada a los nodos
        if (nodo != nullptr) {
            destruirArbol(nodo->izq); // Destruir el subárbol izquierdo
            destruirArbol(nodo->der); // Destruir el subárbol derecho
            delete nodo; // Eliminar el nodo actual
        }
    }

public: // Se utiliza una clase public para declarar los usarios para que de esta manera se puedan interartuar con ellos
        // ya que despues en la funcion main buscamos un usario que se enceuntra dentro de los arboles creados.
    // Constructor de ArbolBinarioBusqueda
    ArbolBinarioBusqueda() : raiz(nullptr) {}

    ~ArbolBinarioBusqueda() {// Destructor de ArbolBinarioBusqueda
        destruirArbol(raiz);
    }
    void insertarPorID(const std::string& uid, const std::string& uname) { // Insertar un nodo por User ID
        raiz = insertarNodoPorID(raiz, uid, uname);
    }

    void insertarPorNombre(const std::string& uid, const std::string& uname) { // Insertar un nodo por User Name
        raiz = insertarNodoPorNombre(raiz, uid, uname);
    }
    UserData* buscarPorID(const std::string& uid) { // Busca un nodo usario por ID
        return buscarNodoPorID(raiz, uid);
    }
    UserData* buscarPorNombre(const std::string& uname) { // Busca un nodo usario por name
        return buscarNodoPorNombre(raiz, uname);
    }
};
int main() {
    std::string csvFileName = "universities_followers_2022.csv"; // Nombre del archivo .CSV a leer
    std::ifstream file(csvFileName); // Objeto ifstream para leer el archivo

    ArbolBinarioBusqueda arbPorID; // Árbol binario de búsqueda por ID
    ArbolBinarioBusqueda arbPorNombre; // Árbol binario de búsqueda por nombre

    std::string line; // Separar el archivo linea por linea
    while (std::getline(file, line)) {
        // Separar los campos de la línea utilizando el delimitador ";"
        std::istringstream iss(line); // Objeto istringstream para separar los campos
        std::string university;
        std::string user_id;
        std::string user_name;
        std::string number_tweets;
        std::string friends_count;
        std::string followers_count;
        std::string created_at;
        // obtener cada campo segun su respectivo uisario
        std::getline(iss, university, ';'); 
        std::getline(iss, user_id, ';'); 
        std::getline(iss, user_name, ';'); 
        std::getline(iss, number_tweets, ';'); 
        std::getline(iss, friends_count, ';'); 
        std::getline(iss, followers_count, ';'); 
        std::getline(iss, created_at, ';'); 

        // Insertar el nodo en los árboles por User ID y User Name
        arbPorID.insertarPorID(user_id, user_name); // Por ID
        arbPorNombre.insertarPorNombre(user_id, user_name); // Por nombre
    }
    file.close(); // Cerrar el archivo después de leerlo

    // Probar el correcto funcionamiento del codigo :buscar un usuario por ID
    std::string usuarioBuscadoID = "115099532";
    // uvalpochile;58334111;mriost;
    UserData* nodoBuscadoID = arbPorID.buscarPorID(usuarioBuscadoID); // Buscar el nodo por ID
    if (nodoBuscadoID != nullptr) {
        std::cout << "Usuario encontrado por ID: " << nodoBuscadoID->user_name << std::endl;
    } else {
        std::cout << "Usuario no encontrado" << std::endl;
    }
    // Por otro lado buscar por el nombre
    std::string usuarioBuscadoNombre = "cmolinaponce";
    //usantamaria;132911019;cmolinaponce
    //std::string usuarioBuscadoNombre = "cmolinapon";
    //Prueba con un usario que no existe
    UserData* nodoBuscadoNombre = arbPorNombre.buscarPorNombre(usuarioBuscadoNombre); // Buscar el nodo por nombre
    if (nodoBuscadoNombre != nullptr) {
        std::cout << "Usuario encontrado por nombre: " << nodoBuscadoNombre->user_id << std::endl;
    } else {
        std::cout << "Usuario no encontrado" << std::endl;
    }
    return 0;
}
