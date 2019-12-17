#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include<sys/select.h>
#include<fstream>
#include"Caesar.h"

using namespace std;

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
ifstream input;
int key;
input.open("key.txt",ios::in);
try
{
if (!input)throw string ("No key provided!!!");
input>>key;
input.close();
}
catch(string errorMessage)
{
cout<<errorMessage<<endl;
exit(3);
}

  //create  a socket
  int listening = socket(AF_INET, SOCK_STREAM, 0);
  if (listening==-1)
  {
       cout<< "Can't create a socket!";
       return -1;
  }
  // bind the Socket to a IP port
  try{
  sockaddr_in hint;
  hint.sin_family = AF_INET;
  hint.sin_port =htons(54000);
  inet_pton(AF_INET,"0.0.0.0.", &hint.sin_addr);

  if (bind(listening,(sockaddr*)&hint, sizeof(hint))== -1) throw string("can't bind to IP/Port");

  }
  catch(string str)
  {
   cout << str;
    return -2;
  }
  //Mark the socket for listening in
  if (listen(listening, SOMAXCONN)==-1)
  {
       cout<<"Can't listen! ";
       return -3;
  }
  else
  {
  cout<<"Server is listening"<<endl;
 /*fd_set master;
  FD_ZERO(&master);
  FD_SET(listening,&master);*/
  }



  // accept a call
  sockaddr_in client;
  socklen_t clientSize = sizeof(client);
  char host[NI_MAXHOST];
  char svc[NI_MAXSERV];

  int clientSocket = accept(listening,
                           (sockaddr*)&client,
                           &clientSize
                           );
  if (clientSocket== -1)
  {
  cout<<"Problem with client connecting!";
  return -4;
  }
   //close the listening socket
  close (listening);
  memset(host,0,NI_MAXHOST);
  memset(svc,0, NI_MAXSERV);
  int result =getnameinfo((sockaddr*)&client,
                          sizeof(client),
                          host,
                          NI_MAXHOST,
                          svc,
                          NI_MAXSERV,
                          0);
 if ( result)
 {
 cout << host <<"connected on "<<svc <<endl;
 }
 else
 {
 inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
 cout<<host<<"connected on "<<ntohs(client.sin_port)<<endl;
 }




  //while receiving display message , echo message
  char buf[4096];



  while(true)
   {
   //clear the buffer
   memset(buf,0,4096);
   //wait for a message
   int bytesRecv = recv(clientSocket, buf , 4096,0);
   if (bytesRecv==-1)
   {cout << "There was a connection issue"<< endl;
   break;
   }
   if (bytesRecv == 0)
   {
   cout << "The client disconnected" << endl;
   break;
   }
   cout << "Received: " << string( buf,0,bytesRecv) <<endl;
   // resend message
   string  message =string( buf,0,bytesRecv);
  // encryptDecrypt(const_cast<char *>(message.c_str()));


 message = encryptDecrypt(const_cast<char *>(message.c_str()));
 cout<<"Xor decrypted: "<<message<<endl;

 Caesar msg(key , message);
 msg.setMsg(message,key);
 message =msg.decrypt(message);
  cout<<"Cypher decrypted: " << message <<endl;
 //send (clientSocket, message.c_str(), message.size()+1 ,0);
 string serverMsg;
 cout<<endl<<"Server> ";
 getline(cin, serverMsg);
 msg.setMsg(serverMsg,key);
 serverMsg = msg.encrypt();
 serverMsg = encryptDecrypt(const_cast<char *>(serverMsg.c_str()));
 send (clientSocket, serverMsg.c_str(), serverMsg.size()+1 ,0);
   }
  //close socket
  close (clientSocket);
  return 0;
}


