#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <memory.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <iostream>

#include "ceaser.h"
#include "replace.h"

using namespace std;

class Server
{
private:
  int init_socket, client_socket;
  sockaddr_in *client_addr, *server_addr;
  int rc;
  void setup_server();
  void lisening();
  void process();



public:
  Server();
  int send_string(string switch_str);
  string get_string();
};

Server::Server()
{
  // Иницилизация сокета
  this->init_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (this->init_socket == -1)
  {
    perror("[err] Some trables with socket.");
    exit(0);
  }
  setup_server();

  lisening();

  close(this->init_socket);
};

// Параметры сервера

void Server::setup_server()
{
    server_addr = new (sockaddr_in);
    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(4747);
    server_addr->sin_addr.s_addr = htonl((127<<24)+1); // 127.0.0.1 - LOCALHOST
    rc=bind(this->init_socket,(const sockaddr*)server_addr,sizeof(sockaddr_in));

    if (rc == -1)
    {
      perror("[err] Error binding on server side: ");
      exit(0);
    }

    rc = listen(this->init_socket, 25);
    if (rc == -1)
    {
      perror("[err] Error lisening: ");
      exit(0);
    }
};

// Режим прослушивания

void Server::lisening()
{
  while(true)
  {
    client_addr = new (sockaddr_in);
    socklen_t addrlen=sizeof (sockaddr_in);
    this->client_socket = accept(this->init_socket,(struct sockaddr*)client_addr,&addrlen);

    process();


    if (client_socket == -1)
    {
      perror("[err] Error binding on server side: ");
      exit(0);
    }
  }
};

int Server::send_string(string switch_str)
{
  return send(client_socket,(const void*)switch_str.data(),switch_str.size(),0);
};

string Server::get_string()
{
  char * buffer = new char[257];
  int rc = recv(client_socket, (void*)buffer, 256, 0);
  if (buffer[0] == '\n')
      return string();
  if (rc == -1 )
  {
    perror("[err] Error sending string: ");
    exit(0);
  }
  return string(buffer);
};

void Server::process()
{



    string switch_str, str;
    string dict;
    int key;

    send_string( "EN/DE CRYPT \n" );
    switch_str = get_string();

    switch (switch_str[0]) {
      case 'e':
      {
        send_string( "CEASER/REPLACE" );
        switch_str = get_string();


        switch (switch_str[0]) {
          case 'c':
          {
            send_string( "STRING" );
             str = get_string();
            send_string( "KEY" );
             key = atoi(get_string().c_str());

            Ceaser chipher_new(key);
            send_string(  chipher_new.encrypt(str) );
            break;
          }
          case 'r':
          {
            send_string( "STRING" );
             str = get_string();
            send_string( "KEY" );
             dict = get_string();

            Replace chipher_new(dict);
            send_string(  chipher_new.encrypt(str) );
          }
        }
        break;
      }
      case 'd':
      {
        send_string( "CEASER/REPLACE" );
        switch_str = get_string();

        switch (switch_str[0]) {
        case 'c':
        {
          send_string( "STRING" );
           str = get_string();
          send_string( "KEY" );
           key = atoi(get_string().c_str());

          Ceaser chipher_new(key);
          send_string(  chipher_new.decrypt(str) );
          break;
        }
        case 'r':
        {
          send_string( "STRING" );
           str = get_string();
          send_string( "KEY" );
           dict = get_string();

          Replace chipher_new(dict);
          send_string(  chipher_new.decrypt(str) );
          break;
        }
        break;
      }
      break;
      }
    }


  close(client_socket);


};

int main(int argc, char ** argv)
{
  Server new_server;

  return 0;
}
