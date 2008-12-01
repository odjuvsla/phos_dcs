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

#include "DatabaseDummy.h"


DatabaseDummy::DatabaseDummy(): PhosDcsBase()
{
  //  printf("\nWarning: you cannot call Database Dummy without parameters\n");
}


DatabaseDummy::~DatabaseDummy()
{

}


bool
DatabaseDummy::GetConfigComment(char *description, int id)
{
  bool found = false;
  char postfix[100]; 
  char configInfoFilename[200];
  SetPostfix(postfix, id);  
  char dummystring[2];
  sprintf(configInfoFilename,"%sconfiguration_%s_info.txt",  fDatabaseFolder, postfix);

  if(description != 0)
    {
      ScanTextFromFile(configInfoFilename, description, CONFIGINFO_MAX_SIZE);
      found = false;
    }
  else
    {
      found = false;
      printf("\ndescription is a ZERO POINTER\n");
    }
    return found;
}


int
DatabaseDummy::LoadApdConfig(char *description)

{
  int id = GetLatestConfigId();

  if(id <0)
    {
      printf("\nERROR ! ID file not found\n");
    }
  else
    {
      LoadApdConfig(description, id);
      cout << "DatabaseDummy::LoadApdConfig,   databaseFolderPtr = " <<fDatabaseFolder << endl;
      cout << "DatabaseDummy::LoadApdConfig,   sanboxFolderPtr = " << fSandboxFolder  << endl;
    }
  return id;
}


int
DatabaseDummy::LoadApdConfig(ConfigInfo_t *info, int configID)
{
  int id;
  
  if(configID > 0)
    {
      id = configID;
    }
  else
    {
      id = GetLatestConfigId();
    }

  if(id <0)
    {
      printf("\nERROR ! ID file not found\n");
    }
  else
    {
      LoadApdConfig(info->fInfo, id);
      info->fID = id;
      cout << "DatabaseDummy::LoadApdConfig(ConfigInfo_t *info, int configID), databaseFolderPtr = " <<fDatabaseFolder << endl;
      cout << "DatabaseDummy::LoadApdConfig(ConfigInfo_t *info, int configID), sanboxFolderPtr = " << fSandboxFolder  << endl;
      cout << "ID =" << info->fID << "  description = " << info->fInfo <<endl;
      info->fIDLimit = GetLatestConfigId();
    }
  
  return id;
}


int
DatabaseDummy::LoadApdConfig(char *description, int id)
{
  int tmpApdValue[32];
  char configFilename[200];
  char IdFilename[200];
  char tmpFilename[200];
  int module = 0;
  int rcu = 0;
  int branch = 0;
  int card = 0;
  int tmp = 0;

  char postfix[100]; 

  SetPostfix(postfix, id);
  sprintf(configFilename,"%sconfiguration_%s.txt",fDatabaseFolder, postfix);
  GetConfigComment(description, id);
  printf("\nDatabaseDummy::LoadApdConfig, descriptipn = %s\n", description);
  FILE *fp; 
  FILE *fpLoad; 

  if(CheckFile(configFilename, "r") == 0)
    {
      fpLoad=fopen(configFilename, "r");  
      printf("\nLoading configuration from file: %s\n", configFilename);
      fscanf(fpLoad, "Module:%d\tRCU:%d\tbranch:%d\tcard:%d\n", &module, &rcu, &branch, &card); 
      do
	{
	  sprintf(tmpFilename,"%s/module%d_RCU%d_Branch%d_card%d.txt", fSandboxFolder, module, rcu, branch, card);

	  if(CheckFile(tmpFilename, "w") == 0)
	    {
	      fp=fopen(tmpFilename, "w");
	      for(int i=0; i<32; i++)
		{
		  fscanf(fpLoad, "%d\n", &tmp);
		  fprintf(fp, "%d\n", tmp);
		}
	      fclose(fp);
	    }
      }
       
      while(fscanf(fpLoad,"Module:%d\tRCU:%d\tbranch:%d\tcard:%d\n", &module, &rcu, &branch, &card) !=EOF);    
      fclose(fpLoad);
    }  

}//end LoadApdConfig


void 
DatabaseDummy::SaveRadoutConfiguration(const ReadoutConfig_t rdoConfig) const
{
 

  int id=GetLatestConfigId();
  char fileName[200];
  char postfix[50];
  SetPostfix(postfix, id);
  sprintf(fileName, "%sconfiguration_%s_readoutsettings.txt", fDatabaseFolder, postfix);
  FILE *fp;

  //  cout << "DatabaseDummy::SaveRadoutConfiguration, filename ="  <<  fileName << endl,
  printf("\nDatabaseDummy::SaveRadoutConfiguration, filename = %s\n", fileName);

  if( CheckFile(fileName, "w") == 0 )
    {
      fp = fopen(fileName, "w");
      fprintf(fp, "samples:\t %d\n",  rdoConfig.GetAltroConfig().GetNSamples().GetIntValue());
      fprintf(fp, "presamples:\t %d\n", rdoConfig.GetAltroConfig().GetNPreSamples().GetIntValue());
      fprintf(fp, "startZ:\t %d\n",  rdoConfig.GetReadoutRegion().GetStartZ().GetIntValue());
      fprintf(fp, "endZ:\t %d\n",   rdoConfig.GetReadoutRegion().GetEndZ().GetIntValue());
      fprintf(fp, "startX:\t %d\n",  rdoConfig.GetReadoutRegion().GetStartX().GetIntValue());
      fprintf(fp, "endX:\t %d\n",   rdoConfig.GetReadoutRegion().GetEndX().GetIntValue());
      fclose(fp);
    }
}

void 
DatabaseDummy::SaveTruSettings(const TRUSettings_t t) const
{
  int id=GetLatestConfigId();
  char fileName[200];
  char postfix[50];
  SetPostfix(postfix, id);
  sprintf(fileName, "%sconfiguration_%s_trusettings.txt", fDatabaseFolder, postfix);
  FILE *fp; 
  
  printf("\nDatabaseDummy::SaveTruSettings, filename = %s\n", fileName);

  if( CheckFile(fileName, "w") == 0 )
    {
      fp = fopen(fileName, "w"); 
      int cnt = t.GetRegisterCount();
      
      fprintf(fp, "%d\n", cnt);


      for(int i=0; i< cnt; i++)
	{
	  fprintf(fp, "%s\t0x%x\t0x%x\n", 
		  t.GetRegister(i).GetName(), 
		  t.GetRegister(i).GetAddress(), 
		  t.GetRegister(i).GetIntValue());
	}

      fclose(fp);	 
    }
}

void
DatabaseDummy::LoadReadoutConfiguration(ReadoutConfig_t *rdoConfig) const
{
  int id=GetLatestConfigId();
  char fileName[200];
  char postfix[50];
  SetPostfix(postfix, id);
  sprintf(fileName, "%sconfiguration_%s_readoutsettings.txt", fDatabaseFolder, postfix);
  FILE *fp = 0;

  if( CheckFile(fileName, "r" ) == 0 )
    {
      fp = fopen(fileName, "r");
      
      unsigned long int tmpNSamples = 0;
      unsigned long int tmpNPreSamples = 0;

      fscanf(fp, "samples:\t %d\n", &tmpNSamples);
      fscanf(fp, "presamples:\t %d\n", &tmpNPreSamples);
      NSamples_t     *nsamples = new NSamples_t(tmpNSamples);
      NPreSamples_t  *npresamples = new NPreSamples_t(tmpNPreSamples);
      AltroConfig_t *altroconf = new AltroConfig_t(*nsamples, *npresamples);
      rdoConfig->SetAltroConfig(*altroconf);	
      delete nsamples;
      delete npresamples;
      delete altroconf;

      int tmpStartZ = 0;
      int tmpEndZ = 0;
      int tmpStartX = 0;
      int tmpEndX = 0;  
      
      fscanf(fp, "startZ:\t %d\n", &tmpStartZ);
      fscanf(fp, "endZ:\t %d\n", &tmpEndZ); 
      fscanf(fp, "startX:\t %d\n", &tmpStartX);
      fscanf(fp, "endX:\t %d\n", &tmpEndX); 

      StartZ_t *startz = new StartZ_t(tmpStartZ);
      EndZ_t *endz = new EndZ_t(tmpEndZ);
      StartX_t *startx = new StartX_t(tmpStartX);
      EndX_t *endx = new EndX_t(tmpEndX);
      
      ReadoutRegion_t *rdoregion = new ReadoutRegion_t(*startz, *endz, *startx, *endx);
      rdoConfig->SetReadoutRegion(*rdoregion);

      delete  startz;
      delete  endz;
      delete  startx;
      delete  endx;
      delete  rdoregion;
      fclose(fp);
    }
}



void 
DatabaseDummy::LoadTruSettings(TRUSettings_t *t)const
{
  int id=GetLatestConfigId();
  char fileName[200];
  char postfix[50];
  SetPostfix(postfix, id);
  sprintf(fileName, "%sconfiguration_%s_trusettings.txt", fDatabaseFolder, postfix);
  //  sprintf(fileName, "%sconfiguration_%s_readoutsettings.txt", fDatabaseFolder, postfix);

  FILE *fp = 0;
 
  if( CheckFile(fileName, "r" ) == 0 )
    {
      fp = fopen(fileName, "r");
      int cnt = 0;
      fscanf(fp, "%d\n", &cnt);


      char tmpname[100];
      unsigned long tmpaddress = 0;
      unsigned long tmpvalue = 0;
      
      t->Reset();
      //  TRURegister_t::TRURegister_t(const unsigned long address, const unsigned long value, const char *name);
      for(int i=0; i < cnt; i++)
	{
	  fscanf(fp, "%s\t0x%x\t0x%x\n", tmpname, &tmpaddress, &tmpvalue);
	  TRURegister_t *r = new  TRURegister_t(tmpaddress, tmpvalue, tmpname);

	  t->AddRegister(*r);

	}

      fclose(fp);
    }
}


int
DatabaseDummy::SaveApdConfig(char *description)
{
  FILE *fp; 
  FILE *fpConf; 
  FILE *fpId;
  int tmpApdValue[32];
  char configFilename[100];
  char configInfoFilename[100]; 
  char IdFilename[100];
  char tmpFilename[100];
  char postfix[20];
  int configId=0;

  sprintf(IdFilename, "%s/Id.txt", fDatabaseFolder);
  configId=GetLatestConfigId()+1;
  
  if( CheckFile(IdFilename, "w") == 0)
    {
      fpId = fopen(IdFilename, "w");
      fprintf(fpId, "%d", configId);
      fclose(fpId);
    } 

  SetPostfix(postfix, configId);
  sprintf(configFilename, "%s/configuration_%s.txt",  fDatabaseFolder , postfix);
  sprintf(configInfoFilename, "%s/configuration_%s_info.txt",  fDatabaseFolder, postfix);

  if(description !=0)
    {
      FILE *fp = fopen(configInfoFilename, "w");

      if(fp != 0)
	{
	  fprintf(fp, "%s\n", description);
	  fclose(fp);
	}
      else
	{
	  printf("\nDatabaseDummy::SaveApdConfig(), error, couldn open file %s\n", configInfoFilename); 
	}
      
    }
  else
    {
      printf("\ncould not save config info because text pointer is ZERO\n");
    }


  if(CheckFile( configFilename, "w") == 0)
    {
      fpConf = fopen( configFilename, "w");
      
      for(int mod=0; mod<5; mod++)
	{
	  for(int rcu=0; rcu<4; rcu++)
	    {
	      for(int branch=0; branch<2; branch++)
		{
		  for(int card=1; card<15; card++)
		    {
		      sprintf(tmpFilename,"%s/module%d_RCU%d_Branch%d_card%d.txt", fSandboxFolder , mod, rcu, branch, card);
		      //		      cout << "DatabaseDummy::SaveApdConfig tmpFileName = " <<tmpFilename  << endl;

		      if(CheckFile(tmpFilename, "r") == 0)
			{
			  fprintf(fpConf, "Module:%d\tRCU:%d\tbranch:%d\tcard:%d\n", mod, rcu, branch, card);
			  fp=fopen(tmpFilename, "r");

			  for(int i=0;i<32;i++)
			    {
			      fscanf(fp,"%d\n",&tmpApdValue[i]);
			      fprintf(fpConf, "%d\n", tmpApdValue[i]);
			    }
			  fclose(fp);
			}
		      
		    } //card
		}//branch
	    }//rcu
	}//mod
      
      fclose(fpConf);
    }

  return configId;
}


void
DatabaseDummy::SetPostfix(char *postfix, const int id) const
{
  if(id < 10)    
    {
      sprintf(postfix, "000%d", id); 
    }	
  else if(id < 100)
    {   
      sprintf(postfix, "00%d", id);
    }  
  else  if(id < 1000)  
    {
      sprintf(postfix, "0%d", id);  
    }
  else
    {
      sprintf(postfix, "%d", id);
    }
}


const int
DatabaseDummy::GetLatestConfigId() const
{

  FILE *fp;
  char IdFilename[256];
  int configId=0;
  sprintf(IdFilename, "%sId.txt",  fDatabaseFolder);

  if(CheckFile(IdFilename, "r") == 0)
    {
      fp = fopen(IdFilename, "r");
      fscanf(fp, "%d", &configId);
      fclose(fp);
      return configId;  
    }
  else
    {
      return -1;
    }
}
