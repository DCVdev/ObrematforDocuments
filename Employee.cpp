
#include "empleado.h"

void add_employee(Employee &emp, int id, std::string &user, std::string &password){
    std::cout << "Recuerda que los numeros que empiezan en el id es el tipo de empleado que vas a crear"<<std::endl;
    std::cout << "0. Es el cajero\n1. Es el gerente\n2. Es el administrador\n3. Es el economista"<<std::endl;
    std::cout << "Anade los datos del empleado"<<std::endl;
    std::cout << "Id: ";
    std::cin >> id;
    std::cin.ignore();//Ignora el salto de linea que puede cometer a la ingesta de datos
    std::cout << "Usuario: ";
    std::getline(std::cin,user);
    std::cout << "Password: ";
    std::getline(std::cin, password);
    emp.id = id;
    emp.user = user;
    emp.password = password;
}
