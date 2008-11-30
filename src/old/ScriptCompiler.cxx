/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2006                                       *
 *                                                                        * 
 * Author: Per Thomas Hille perthi@fys.uio.no for the ALICE DCS Project.  *
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to perthi@fys.uio.no                                * 
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

#include "ScriptCompiler.h"
#include <iostream>
#include "CommonDefs.h"

using std::cout;
using std::endl;

int ScriptCompiler::scriptAdress;
int ScriptCompiler::crystAdress[32];

ScriptCompiler::ScriptCompiler() 
{
  Init();
}

void 
ScriptCompiler::MakeReadouRegionScript(char *filename, unsigned long& afl, int acl[256])
{
  int adress = ACL_BASE_ADRESS;
  int counter;
  FILE *fp;
  fp = fopen(filename, "w");
  fprintf(fp, "w 0x%x  256 0x0\n",ACL_BASE_ADRESS);
  fprintf(fp, "wait 100 us\n");
  for(int i= 0; i<256; i++)
    {
      if(acl[i] != 0)
	{ 
	  //	  printf("\nacl[%d] = acl[%d]\n", i, acl[i]);
	  fprintf(fp,"w 0x%x 0x%x\n", adress, acl[i]);
	} 
      adress ++;
   }
  fprintf(fp, "wait 10000 us\n");
  fprintf(fp, "r 0x6400 256\n");
  fclose(fp);
}

void 
ScriptCompiler::MakeTriggerConfigScript(char *filename, int triggerType, int triggerDelay, int preSamples, int nSamples)
{
  FILE *fp;
  fp=fopen(filename, "w");
  int tmp;

  fprintf(fp, "w 0x7000 0x64000a\n");
  tmp = 0x700000 | nSamples;
  fprintf(fp, "w 0x7001 0x%x\n", tmp);
  fprintf(fp, "w 0x7002 0x64000b\n");
  fprintf(fp, "w 0x7003 0x700000\n");
  fprintf(fp, "w 0x7004 0x64000c\n");
  tmp = 0x700000 | preSamples;
  fprintf(fp, "w 0x7005 0x%x\n", tmp);
  fprintf(fp, "w 0x7006 0x390000\n");
  fprintf(fp, "w 0x0 0x0\n");
  fprintf(fp, "wait 200 us\n");
  
  tmp = 0x10000 | triggerDelay;

  //fprintf(fp, "w 0x8001 0x7ffe7ffe\n");
  fprintf(fp, "w 0x7801 0x%x\n", tmp);
  //fprintf(fp, "r 0x7800\n");
  fclose(fp);
}

APD_cmd
ScriptCompiler::MakeApdWriteCmd(int feenr,int crystalAdr,int csp_value,int branch)
{
  struct APD_cmd tmp;
  tmp.MS_20=(1<<CMD_TYPE)|(1<<BC_AL)|(1<<RW)|(0<<POS)|(branch<<BRANCH)|(feenr<<FAD)|(crystalAdr<<CAD);
  tmp.LS_20=(1<<CMD_TYPE)|(1<<RW)|(1<<POS)|(csp_value<<CSPVAL);
  return tmp;
}

APD_cmd
ScriptCompiler::MakeApdReadCmd(int feenr, int crystalAdr, int branch)
{
  struct APD_cmd tmp;
  tmp.MS_20=(1<<CMD_TYPE)|(1<<BC_AL)|(0<<RW)|(1<<POS)|(branch<<BRANCH)|(feenr<<FAD)|(crystalAdr<<CAD);
  return tmp;
}

void
ScriptCompiler::MakeReadPcmVersionScript(char *fileName, int branch, int card)
{
  FILE *fp;
 long command;
  char commandString[100];
  fp=fopen(fileName, "w");
  fprintf(fp, "w 0x6000 0xffff\n");
  command =(1<<CMD_TYPE)|(1<<BC_AL)|(0<<RW)|(1<<POS)|(branch<<BRANCH)|(card<<FAD)|0x20;
  sprintf(commandString, "w 0x7000 0x%x\n", command);
  fprintf(fp, "%s", commandString);
  fprintf(fp, "w 0x7001 0x390000\n");
  fprintf(fp, "w 0x0 0x0\n");
  fprintf(fp, "wait 100 us\n");
  fprintf(fp, "r 0x6000 1\n");
  fclose(fp);
}

void
ScriptCompiler::MakeActivateFeeScript(char *scriptFilename, unsigned long& activeFeeList, int branch, int cardIndex, int onOff)
{
  FILE *fp;
  fp=fopen(scriptFilename, "w");

  char commandString[100];
  long command;
  unsigned long int  tmpFeeList;
  int shift;
  //int cardNumber = cardIndex +1;
  int cardNumber = cardIndex;    // This is a modification in order to cooporate with two different type of GTL bus board.

  if(branch == 0)
    {
      shift = 0;
    } 
  else if(branch == 1)
    {
      shift = 16;
    } 
  else
    {   
     printf("\nERROR in activating card, branch has invalid value:%d\n", branch);
    }
  tmpFeeList = 1<<(cardNumber+shift);

  std::cout<<WHERE<<" activeFeeList === 0x"<<std::hex<<activeFeeList<<std::dec<<std::endl;

  if(onOff == TURN_OFF)
   {
     if(activeFeeList & tmpFeeList)
       {
	 activeFeeList = (activeFeeList ^ tmpFeeList);  
       }
   }

  else if(onOff == TURN_ON)
    {
      activeFeeList = (activeFeeList | tmpFeeList);
   }

  std::cout<<WHERE<<" activeFeeList --> 0x"<<std::hex<<activeFeeList<<std::dec<<std::endl;

  fprintf(fp,"w 0x8000 0x%x\n", activeFeeList);
  fprintf(fp, "wait 200000 us\n");  
  fprintf(fp, "w 0x8001 0x%x\n", activeFeeList);
  fprintf(fp, "wait 200000 us\n");
  fprintf(fp, "w 0x2001 0x0\n");
  fprintf(fp, "wait 100000 us\n");  
  fprintf(fp, "w 0x2001 0x0\n");
  fprintf(fp, "wait 100000 us\n");
  fprintf(fp, "w 0x6000 0xffff\n");
  command =(1<<CMD_TYPE)|(1<<BC_AL)|(0<<RW)|(1<<POS)|(branch<<BRANCH)|(cardNumber<<FAD)|0x20;
  sprintf(commandString, "w 0x7000 0x%x\n", command);
  fprintf(fp, "%s", commandString);
  fprintf(fp, "w 0x7001 0x390000\n");
  fprintf(fp, "w 0x0 0x0\n");
  fprintf(fp, "wait 10000 us\n");
  fprintf(fp, "r 0x6000 1\n");

  fclose(fp);
}

void
ScriptCompiler::MakeApdScript(char *scriptFilename, int *apdValue, int branch, int card)
{
  FILE *fp;
  fp= fopen(scriptFilename,"w"); 
  long int execute_LS20;
  long int execute_MS20;
      
  for(int i=0;i<N_APDs;i++)
    {
      APD_cmd cmd = MakeApdWriteCmd(card,crystAdress[i],apdValue[i], branch);    

      if(i !=0) putc('\n',fp);
      
      fprintf(fp,"w 0x%x 0x%x\n", scriptAdress,cmd.MS_20);
      scriptAdress++;
      fprintf(fp,"w 0x%x 0x%x", scriptAdress,cmd.LS_20); 
      scriptAdress++;
    }
  execute_MS20=(1<<CMD_TYPE)|(1<<BC_AL)|(1<<RW)|(0<<POS)|(branch<<BRANCH)|(card<<FAD)|(0x1E);
  execute_LS20=(1<<CMD_TYPE)|(1<<RW)|(1<<POS)|(0x00);


  fprintf(fp,"\nw 0x%x 0x%x\n",scriptAdress,execute_MS20);
  scriptAdress++;
  fprintf(fp,"w 0x%x 0x%x",scriptAdress,execute_LS20);
  scriptAdress++;
  fprintf(fp,"\nw 0x%x 0x390000",scriptAdress);
  fprintf(fp,"\nw 0x0 0x0\n");
  scriptAdress=DCS_BASEADRESS;
  fclose(fp);
}

void
ScriptCompiler::MakeApdVerifyScript(char *fName, int branch, int card)
{
  FILE *fp;
  fp= fopen(fName,"w"); 
  long int execute_LS20;
  long int execute_MS20;
  fprintf(fp,"w 0x6000 60 0xdead\n"); // clear result memory before reading back 

  for(int i=0;i<N_APDs;i++)
    {
      APD_cmd cmd = MakeApdReadCmd(card,crystAdress[i], branch);      
      if(i !=0) putc('\n',fp);
      fprintf(fp,"w 0x%x 0x%x", scriptAdress,cmd.MS_20);
      scriptAdress++;
    }
  fprintf(fp,"\nw 0x%x 0x390000",scriptAdress);
  fprintf(fp,"\nw 0x0 0x0");
  fprintf(fp,"\nwait 10 us");
  fprintf(fp,"\nr 0x7800");
  fprintf(fp,"\nwait 10 us");
  fprintf(fp,"\nr 0x6000 32\n");
  scriptAdress=DCS_BASEADRESS;
  fclose(fp);
}

void
ScriptCompiler::SetHeader()
{

}

void
ScriptCompiler::SetTrailer()
{

}

void
ScriptCompiler::Init()
{
  scriptAdress=DCS_BASEADRESS;

  crystAdress[0] = 0x48;  //Left as seen from back
  crystAdress[1] = 0x47;  //Right as seen from back

  crystAdress[2] = 0x49;  //Left
  crystAdress[3] = 0x46;  //Right

  crystAdress[4] = 0x4A;  //...etc
  crystAdress[5] = 0x45;

  crystAdress[6] = 0x4B;
  crystAdress[7] = 0x44;

  crystAdress[8] = 0x4C;
  crystAdress[9] = 0x43;  

  crystAdress[10] = 0x4D;
  crystAdress[11] = 0x42;

  crystAdress[12] = 0x4E;
  crystAdress[13] = 0x41;

  crystAdress[14] = 0x4F;
  crystAdress[15] = 0x40;

  crystAdress[16] = 0x50;
  crystAdress[17] = 0x5F;  

  crystAdress[18] = 0x51;
  crystAdress[19] = 0x5E;

  crystAdress[20] = 0x52;
  crystAdress[21] = 0x5D;

  crystAdress[22] = 0x53;
  crystAdress[23] = 0x5C;

  crystAdress[24] = 0x54;
  crystAdress[25] = 0x5B;  

  crystAdress[26] = 0x55;
  crystAdress[27] = 0x5A;

  crystAdress[28] = 0x56;
  crystAdress[29] = 0x59;

  crystAdress[30] = 0x57;
  crystAdress[31] = 0x58; 
}//end Init()
