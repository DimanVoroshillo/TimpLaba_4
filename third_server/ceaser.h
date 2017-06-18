#pragma once
#include <string>
#include <exception>

class Ceaser
{
private:
  std::string expression;
  unsigned int key;

public:
  Ceaser(int key );
  Ceaser();
  std::string decrypt( std::string expression);
  std::string encrypt( std::string expression);
};
