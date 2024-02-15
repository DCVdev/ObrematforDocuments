#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
#include <iostream>
//Creo la estructura del empleado
struct Employee{
    int id;
    std::string user;
    std::string password;
};
//Creo la función que añade el empleado
void add_employee(Employee &emp, int id, std::string &user, std::string &password);


#endif
