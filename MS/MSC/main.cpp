#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include<bits/stdc++.h>
#include<fstream>
#include"Caesar.h"

using namespace std;

//xor encryption

string encryptDecrypt(char inpString[])
{
    // Define XOR key
    // Any character value will work
    char xorKey = 'P';

    // calculate length of input string
    int len = strlen(inpString);

    // perform XOR operation of key
    // with every caracter in string
    for (int i = 0; i < len; i++)
    {
        inpString[i] = inpString[i] ^ xorKey;
        //printf("%c",inpString[i]);
    }
    return inpString;
}


int main()
 {
  int key;
  try{
      ifstream keyInput;
      keyInput.open("key.txt",ios::in);
      if(!keyInput) throw string("No such file!");
      else
      keyInput>>key;
    keyInput.close();
      }

    catch(string str)
    {
    cout<<str<<endl;
    }

      string message;

     //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    //string userInput1;
      string userInput;


    do {
        //		Enter lines of text
        cout << "> ";
        getline(cin, userInput);

//Caesar encryption
 Caesar cd(key,userInput) ;

  cd.setMsg(userInput,key);
   userInput=cd.encrypt();

	cout << "Encrypted message with Cypher: " << userInput<<endl;
//call Xor encryption
	encryptDecrypt(const_cast<char *>(userInput.c_str()));

	cout << "Encrypted message with Xor: " << userInput<<endl;

        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

//		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {

            message = string(buf, bytesReceived);
       cout <<endl;
       cout<<endl<< "Received "<< message<<endl;

       message = encryptDecrypt(const_cast<char *>(message.c_str()));
       cout<<"Xor decryption "<< message<< endl;
       cout <<"Cypher Decryped:"<<cd.decrypt(message)<<endl;




        }
    } while(true);

    //	Close the socket
    close(sock);
    return 0;
}
