#include"Caesar.h"

void Caesar::setMsg(string message, int key)
{
  Encryption::setMsg(message);
 // setMsg(message);
 this->key =key;
  //cout<<"get the message";
}
int Caesar:: getKey()
{
 return key;
}
string Caesar::getMsg()
{
 return Encryption::getMsg();
}

string Caesar::encrypt()
{


 //cout<<endl<<"key is "<<key;
 //cout<<getMsg();
 // traverse text
    for (int i=0;i<getMsg().length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(getMsg()[i]))
            encryptMsg += char(int(getMsg()[i]+key-65)%26 +65);
    // Encrypt Lowercase letters
        else if(islower(getMsg()[i]))
        encryptMsg+= char(int(getMsg()[i]+key-97)%26 +97);
        else
        encryptMsg+=getMsg()[i];


    }


 // cout<<"Encrypted Message: "<<encryptMsg<<endl;
  return encryptMsg;
}


string Caesar:: decrypt(string sms1)
{
  string result;
  sms =sms1;
 // traverse text
    for (int i=0;i<sms.length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(sms[i]))
            result += char(int(sms[i]-key-65+26)%26 +65);
    // Encrypt Lowercase letters
        else if(islower(sms[i]))
        result += char(int(sms[i]-key-97+26)%26 +97);
        else
        result+=sms[i];


    }
    sms=result;
  //getMsg()=result;
 // cout<<endl<<"Decrypted Message: "<<result<<endl;
  return sms;
}
Caesar::~Caesar()
{
cout<<""<<endl;
}
