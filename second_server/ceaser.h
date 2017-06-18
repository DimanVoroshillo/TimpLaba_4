#pragma once
#include <string>
#include <exception>

class Ceaser
{
private:
  std::string expression;
  unsigned int key;

public:
  Ceaser( std::string in);
  Ceaser();
  std::string decrypt( int key);
  std::string encrypt( int key);
};
