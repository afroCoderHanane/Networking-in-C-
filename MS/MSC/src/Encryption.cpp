 #include"Encryption.h"
void Encryption::print()const
{
  cout<<" Message to encrypt: "<<message<<endl;
}
Encryption::Encryption(string message):message(message){}
Encryption::Encryption():message(""){};
void Encryption:: setMsg(string message)
{
  this->message= message;
}
string Encryption:: getMsg()
{
 return message ;
}
