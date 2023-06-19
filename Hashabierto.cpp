#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

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
// Función hash abierta
float A = (std::sqrt(5) - 1) / 2;
int hashFunction(const std::string& key, int tableSize) {
    float hashValue = 0;

    // Sumar los códigos ASCII de los caracteres en la cadena
    for (char c : key) { // lee el codigo ASCII
        hashValue += static_cast<int>(c); // los suma para de esta manera obtener un valor
    }
    // Se utilizo el metodo de la multiplicacion
    float multiplied = hashValue * A;
    multiplied -= std::floor(multiplied);
    int index = static_cast<int>(tableSize * multiplied); // se calcula el indice
    return index; // se envia como resultado
}

int main() {
    // Notar que se puede usar la misma funcion para el Id y name ya que el codigo ASCII posee
    // los numeros, letras y simbolos entre sus caracteres.
    std::string csvFileName = "universities_followers_2022.csv"; // Nombre del archivo .CSV a leer
    std::vector<std::vector<UserData>> hashTable(1000); // Asigna el tamaño de la tabla (1000)

    std::ifstream file(csvFileName); // Objeto ifstream para leer el archivo
    std::string line;
    //Para probar si la funcion comple con lo solicitado se utilizara el siguiente usario:
    std::string userIdToFind = "132911019"; //Provando la funcion hash para user_ID
    //usantamaria;132911019;cmolinaponce
    int indexToFind = hashFunction(userIdToFind, hashTable.size()); // entre el valor del incide
    // teniendo este valor se podria preguntar por cualquiera de sus datos.
    std::cout << "Usuario con ID '" << userIdToFind << "' encontrado en el índice: " << indexToFind << std::endl; // Imprimir los resultados

    std::string userNameToFind = "cmolinaponce"; //Provando la funcion hash para user_name
    int indexToFindByName = hashFunction(userNameToFind, hashTable.size());
    std::cout << "Usuario con nombre '" << userNameToFind << "' encontrado en el índice: " << indexToFindByName << std::endl; // Imprimir los resultados

    file.close();// Cerrar el archivo
    return 0;
}
