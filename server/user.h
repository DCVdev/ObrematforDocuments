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
    User(const std::string &name, const std::string &pass, const int &codus, const int &codrol): name_user(name), pass(password), codus(cod_user), codrol(cod_rol){}
    //Functions that add parameters
    void authenticate_user(const std::string &name, const std::string &pass, const int &codus, const int &codrol);

};

#endif
#endif // USER_H
