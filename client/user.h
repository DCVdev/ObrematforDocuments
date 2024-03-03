#ifndef USER_H
#define USER_H

#include <string>

class User{
public:
    std::string name_user;
    std::string password;
    int cod_user;
    int cod_rol;
    //Constructor
    User(){}
    //Functions that add parameters
    void set_nameuser(const std::string &name){
        name_user = name;
    }
    void set_password(const std::string &pass){
        password = pass;
    }
    void set_coduser(const int &codus){
        cod_user = codus;
    }
    void set_codrol(const int &codrol){
        cod_rol = codrol;
    }
};

#endif
