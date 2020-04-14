#ifndef USER_H_
#define USER_H_
#include<bits/stdc++.h>
using namespace std ;
string Login[50][2] ;

class User
{
protected:
    string FirstName = "user",LastName = "user",UserName, PassWord, Role  ;
public:
    static int ID ;
    User (string name,string family,string user,string pass)
    {
        ID ++ ;
        FirstName = name ;
        LastName = family ;
        UserName = user ;
        PassWord = pass ;
        Login[ID-1][0]=UserName ;
        Login[ID-1][1]=PassWord ;
    }
    void GettingData()
    {
        cout<<FirstName<<endl<<LastName<<endl<<UserName<<endl<<PassWord<<endl<<Role<<endl;
    }
    void FirstNameSetter(string name)
    {
        FirstName = name ;
    }
    void LastNameSetter(string name)
    {
        LastName = name ;
    }
    // all Getters //
    string FirstNameGetter()
    {
        return FirstName ;
    }
    string LastNameGetter()
    {
        return LastName ;
    }
    string UserNameGetter()
    {
        return UserName ;
    }
    string PassWordGetter()
    {
        return PassWord ;
    }
    string RoleGetter()
    {
        return Role ;
    }
    void ViewUser()
    {
        cout.width(18);
        cout << left << FirstName;
        cout.width(18);
        cout << left << LastName;
        cout.width(18);
        cout << left << UserName;
        cout.width(18);
        cout << left << Role << endl;
    }
    //----------------------------------------------------------------------------//
    bool Passing()
    {
        bool returning ;
        Temp1 = Role ;
        transform(Temp1.begin(), Temp1.end(), Temp1.begin(), ::toupper);
        if(Temp1=="ADMIN")
        {
            returning = true ;
        }
        else if(Temp1 == "PLAYER")
        {
            returning = false ;
        }

        return returning ;
    }
    bool operator==(string user)
    {
        string temp ;
        temp = UserName ;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        if (temp == user)
        {
            return true;
        }
        return false ;
    }

};



//==============================================================//
int User::ID = 0 ;
// Player Class //
class Player : public User
{
public :
    Player(string name,string family, string user,string pass):User(name,family,user,pass)
    {
        FirstName=name ;
        LastName = family ;
        UserName = user ;
        PassWord = pass ;
        Role = "Player" ;
    }
};
// ===========================================================//
//  AdmIn Class //
class Admin : public User
{
public :
    Admin(string name,string family, string user,string pass):User(name,family,user,pass)
    {
        FirstName=name ;
        LastName = family ;
        UserName = user ;
        PassWord = pass ;
        Role = "Admin" ;
    }

};

#endif // USER_H_
