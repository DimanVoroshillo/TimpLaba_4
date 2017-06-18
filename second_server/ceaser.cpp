#include "ceaser.h"
#include <iostream>
#include <string>
using namespace std;

Ceaser::Ceaser( std::string in)
{
  this->expression = in;

};

string Ceaser::encrypt(int key)
{
  this->key = key;
  for (int i = 0; i < expression.size(); i++)
  {
    if ((this->expression[i] > 64) && (this->expression[i]<91))
    {
      this->expression[i] += this->key;
      if (this->expression[i] > 90) {
        this->expression[i] = 65 + this->expression[i] % 91 ;
      }
    }
    else if ((this->expression[i] > 96) && (this->expression[i]<120))
      {
        this->expression[i] = this->expression[i] + this->key;
        if (this->expression[i] > 120) {
          this->expression[i] = 97 + this->expression[i] % 121;
        }
      }

      }
    return this->expression;
};

string Ceaser::decrypt(int key)
{
  this->key = key;
  for (int i = 0; i < expression.size(); i++)
  {
    if ((this->expression[i] > 62) && (this->expression[i]<91))
    {
      this->expression[i] -= key;
      if (this->expression[i] < 65) {
        this->expression[i] = 90 - key + ((this->expression[i] + key) % 64) ;
      }
    }
    if ((this->expression[i] > 94) && (this->expression[i]<123))
    {
      this->expression[i] -= key;
      if (this->expression[i] < 97) {
        this->expression[i] = 122 - key + ((this->expression[i] + key) % 96) ;
      }
    }
  }
  return this->expression;
};
