/**************************************************************************
 *                                                                        * 
 * Author: htorii@hiroshima-u.ac.jp for the ALICE DCS Project.  *
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to perthi@fys.uio.no                                * 
 *                                                                        *
 **************************************************************************/


#include "ConvertAPDBias.h"
#include <stdio.h>
#include <iostream>

int ConvertAPDBias(char* configFilename, char *sandboxFolderPtr)
{
  int tmpApdValue[32];
  char IdFilename[200];
  char tmpFilename[200];
  int module;
  int rcu;
  int branch;
  int card;
  int tmp;

  FILE *fp; 
  FILE *fpLoad; 
  std::cout<<" ConvertAPDBias::Loading APD configuration: "<<configFilename<<std::endl;
  fpLoad=fopen(configFilename, "r");  

  if(fpLoad !=0)
    {
      fscanf(fpLoad, "Module:%d\tRCU:%d\tbranch:%d\tcard:%d\n", &module, &rcu, &branch, &card); 
      do
	{
	  sprintf(tmpFilename,"%s/module%d_RCU%d_Branch%d_card%d.txt",sandboxFolderPtr, module, rcu, branch, card);
	  std::cout<<" ConvertAPDBias() Writing into "<<tmpFilename<<std::endl;
	  fp=fopen(tmpFilename, "w");

	  for(int i=0; i<32; i++)
	    {
	      fscanf(fpLoad, "%d\n", &tmp);
	      fprintf(fp, "%d\n", tmp);
	    }
	    fclose(fp);
      }

      while(fscanf(fpLoad,"Module:%d\tRCU:%d\tbranch:%d\tcard:%d\n", &module, &rcu, &branch, &card) !=EOF);    
    }  
  else
    {
      std::cout<<" ConvertAPDBias::Error!!! Config file not found"<<std::endl;
    }
}
//

