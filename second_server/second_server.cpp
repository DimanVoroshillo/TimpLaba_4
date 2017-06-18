#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <memory.h>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <iostream>

#include "ceaser.h"

using namespace std;

class Server
{
private:
  int init_socket, s_worker;
  sockaddr_in *client_addr, *server_addr;
  int rc;
  void setup_server();
  void listening();
  void send_string();

public:
  Server();
};

Server::Server()
{
  // Иницилизация соrета
  this->init_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (this->init_socket == -1)
  {
    exit(0);
  }

  setup_server();
  listening();

};

// Параметры сервера

void Server::setup_server()
{

  server_addr = new (sockaddr_in);
  server_addr->sin_family = AF_INET;
  server_addr->sin_port = htons((unsigned int)4747);
  server_addr->sin_addr.s_addr = htonl((127<<24)+1); // 127.0.0.1 - LOCALHOST
  this->rc=bind(this->init_socket,(const sockaddr*)server_addr,sizeof(sockaddr_in));

    if (this->rc == -1)
    {
      cout << endl;
      exit(0);
    }

    this->rc = listen(this->init_socket, 5);
    if (rc == -1)
    {
      cout << endl;
      exit(0);
    }


    listening();
    close(this->init_socket);
};

// Параметры сервера

void Server::listening()
{
  while (true)
  {

    client_addr = new (sockaddr_in);
    socklen_t addrlen=sizeof (sockaddr_in);
    this->s_worker = accept(this->init_socket,(struct sockaddr*)client_addr,&addrlen);
    if (s_worker == -1)
    {

      exit(4);
    }

    send_string();
    close(s_worker);
  }
};

void Server::send_string()
{
  // Получение строки
  char * buffer = new char[257];
  int rc = recv(this->s_worker, (void*)buffer, 256, 0);
  string str = string(buffer);
  // Применение ROT13
  Ceaser this_ceaser(str);
  str = this_ceaser.encrypt(13);
  // Отправка строки
  rc = send(this->s_worker,(const void*)str.data(),str.size(),0);

  if (rc == -1)
  {

    abort();
  }
};

int main(int argc, char ** argv)
{
  Server new_server;
  return 0;
}
