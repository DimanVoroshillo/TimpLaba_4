#pragma once
#include <iostream>
#include <string>
#include <exception>

class Replace
{
private:
  std::string expression;
  int range;
  std::string key;
  std::string english_abc = "abcdefghijklmnopqrstuvwxyz";

public:
  Replace(  std::string in);
  Replace();
  std::string encrypt(std::string in);
  std::string decrypt(std::string in);
  bool validate_key();
};

class ReplaceException:std::exception // класс-исключение
{
 public:
 const char* what() const noexcept
 {
   return "Shift cipher error";
 }
};
