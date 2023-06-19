#include <iostream>   // Entrada y salida estándar
#include <fstream>    // Manipulación de archivos
#include <string>     // Para la cadenas de caracteres
#include <vector>     // Contenedor de arrays dinámicos
#include <math.h>     // Funciones matemáticas

using namespace std;
// Se utilizo como ejemplo el hash_funtions.cpp que se entrego por canvas del curso
struct UserData {
    std::string university;
    std::string user_id;
    std::string user_name;
    int number_tweets;
    int friends_count;
    int followers_count;
    std::string created_at;

    // Constructor de UserData
    UserData(const std::string& uid, const std::string& uname) : user_id(uid), user_name(uname) {}
};

/*** Funciones hash***/
// Método de la división
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
int h1(int k, int n) {
    return k % n;
}
// Método de la multiplicación
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
int h2(int k, int n) {
    float a = (float)k * ((sqrt(5) - 1) / 2);
    a -= (int)a;
    return n * a;
}
// Se utiliza el codigo ASCII para de esta manera tranformar las letras y simbolos a numeros
int sumASCII(const std::string& key) {
    int hashValue = 0;
    for (char c : key) {
        hashValue += static_cast<int>(c);
    }
    return hashValue;
}

// Double hashing
// k: clave a la cual aplicaremos la función hash
// n: tamaño de la tabla hash
// i: número del intento
int double_hashing(const std::string& key, int n) {
    int hashValue = sumASCII(key); // Se aplica el ASCII
    int index1 = h1(hashValue, n); // indice de la divisionm
    int index2 = 1 + h2(hashValue, n - 2); // indice de la multiplicacion
    int index = (index1 + index2) % n;// se juntan ambos metodos para obtener el resultado de indice
    return index;
}

int main() {
    std::string csvFileName = "universities_followers_2022.csv"; // Nombre del archivo .CSV a leer
    std::vector<std::vector<UserData>> hashTable(1000); // Asigna el tamaño de la tabla (1000)

    std::ifstream file(csvFileName); // Objeto ifstream para leer el archivo
    std::string line;

    //Para probar si la función cumple con lo solicitado se utilizará el siguiente usuario:
    std::string userIdToFind = "132911019"; // Probar la función hash para user_ID
    int indexToFind = double_hashing(userIdToFind, hashTable.size()); // Obtener el valor del índice
    std::cout << "Usuario con ID '" << userIdToFind << "' encontrado en el índice: " << indexToFind << std::endl;// Imprimir los resultados

    std::string userNameToFind = "cmolinaponce"; // Probar la función hash para user_name
    int indexToFindByName = double_hashing(userNameToFind, hashTable.size());
    std::cout << "Usuario con nombre '" << userNameToFind << "' encontrado en el índice: " << indexToFindByName << std::endl;// Imprimir los resultados
    
    file.close(); // Cerrar el archivo
    return 0;
}
