#ifndef CAESAR_H
#define CAESAR_H

#include"Encryption.h"
#include<iostream>
#include<fstream>
using namespace std;

class Caesar:public Encryption
{
  private:

  int key;
  string encryptMsg;
  string sms;
  public:
  Caesar( int key, string message):Encryption( message)
  {

  this-> key= key;
  //this->encryptMsg=encryptMsg;
  }

  virtual string encrypt()override;
  virtual void setMsg(string message, int key);
  int getKey();
  virtual string getMsg()override;
  //void getKey();
  virtual string decrypt(string)override;
  ~Caesar();


};
#endif // CAESAR_H
