#include "PhosDcsBase.h"
#include "unistd.h"
#include "PhosConst.h"
#include <cstdlib>
#include <cstring>


using namespace std;

bool PhosDcsBase::fParamIsSet = false;
char PhosDcsBase::fDatabaseFolder[1024];
char PhosDcsBase::fSandboxFolder[1024];
char PhosDcsBase::fPhosDcsDir[1024];

//char PhosDcsBase::fPhosDcsScriptDir[1024];


PhosDcsBase::PhosDcsBase()
{
  if (fParamIsSet == false)
    {
      char *tmpDcsDir = getenv("PHOS_DCS_DIR");
      char *tmpConfigDataDir = getenv("PHOS_DCS_CONFIGDATA");  

      if(tmpDcsDir != 0)
	{
	  sprintf(fPhosDcsDir, "%s", tmpDcsDir);
	}
      else
	{
	  cout <<"WARNING: environment variable PHOS_DCS_DIR not set "<< endl;
	  cout <<"assuming the DCS directory is "<< getenv("HOME") <<endl;
	  sprintf(fPhosDcsDir, "%s", getenv("HOME"));
	}

      if(tmpConfigDataDir != 0) 
	{
	  sprintf(fDatabaseFolder, "%s",tmpConfigDataDir);
	}
      else
	{
	  sprintf(fDatabaseFolder, "%s/data/",getenv("PWD"));
	  cout <<"WARNING: environment variable PHOS_DCS_CONFIGDATA not set "<< endl;
	  cout <<"assuming the data is contained in directory"<< fDatabaseFolder <<endl; 
	}
      
      sprintf(fSandboxFolder,"%s/APD_settings/", fDatabaseFolder);
      strcat(fDatabaseFolder,  "/ConfigurationFiles/");

      //      sprintf(fPhosDcsScriptDir, "%s/scripts/",fPhosDcsDir);

      fParamIsSet = true;  
    }

}


PhosDcsBase::~PhosDcsBase()
{

}

/*
void
PhosDcsBase::SetScriptDir(char *dir)
{
  sprintf(fPhosDcsScriptDir, getenv("PWD"));
  printf("\nPhosDcsBase::SetScriptDir,fPhosDcsScriptDir set to %s\n", fPhosDcsScriptDir);

}
 */

int
PhosDcsBase::ScanTextFromFile(const char *fileName, char *description, const int maxSize)
{
  char dummystring[10];

  if(CheckFile(fileName, "r") == EXIST)
    {
      FILE *fp = fopen(fileName, "r");
      char c =0;   
      int cnt = 0;
      
      if(fileName != 0 && maxSize != 0)
	{
	  sprintf(description, "%c",'\0');

	  while( (( c = getc(fp) ) != EOF)  && cnt < maxSize )
	    {
	      sprintf(dummystring, "%c", c);
	      strcat(description, dummystring);
	      cnt ++;
	    }

	  fclose(fp);
	}
    }
}




int
PhosDcsBase::CheckFile(const char *fileName, const char *opt) const
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

