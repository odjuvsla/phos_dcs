#include "PhosDcsBase.hpp"

using namespace std;

PhosDcsBase::PhosDcsBase()
{
  sprintf(fDatabaseFolder,"%s", CONFIG_BASE_PATH);
  sprintf(fSandboxFolder,"%s", APDVAL_BASE_PATH);
}


PhosDcsBase::~PhosDcsBase()
{

}



int
PhosDcsBase::CheckFile(const char *fileName, const char *opt)
{
  FILE *fp = fopen(fileName, opt);

  if(fp == 0)
    {
      cout <<"Error: from" << typeid(*this).name()  <<"could not open file: "<< fileName <<endl; 
      return NO_EXIST;
    }
  else
    {
     fclose(fp); 
     return EXIST;
    }
}

