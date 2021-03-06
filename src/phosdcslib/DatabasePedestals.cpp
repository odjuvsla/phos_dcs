
#include "DatabasePedestals.h"
#include <fstream>
#include <cmath>
#include <cstdlib>
//#include <svncpp/status.hpp>
//#include <svncpp/client.hpp>
//#include <svncpp/info.hpp>
//#include <svncpp/context.hpp>
//#include <svncpp/url.hpp>
//#include <subversion-1/svn_client.h>

DatabasePedestals::DatabasePedestals() : DatabaseSVN()
,fPedestalFileName("pedestals.dat")
{
   for(int m = 0; m < PHOS_MODS; m++)
   {
      for(int r = 0; r < RCUS_PER_MODULE; r++)
      {
	fPedestalValues[m][r] = 0;
      }
   }
}

DatabasePedestals::DatabasePedestals ( std::string repoPath, std::string destPath ) : DatabaseSVN ( repoPath, destPath )
,fPedestalFileName("pedestals.dat")
{
   for(int m = 0; m < PHOS_MODS; m++)
   {
      for(int r = 0; r < RCUS_PER_MODULE; r++)
      {
	fPedestalValues[m][r] = 0;
      }
   }
   
}

DatabasePedestals::~DatabasePedestals()
{
   
}

int DatabasePedestals::Initialise()
{

   int res = -2;
   //printf("%d\n", svn::Url::isValid("file:///home/odjuvsla/test/test/	repos/"));
   //   svn::Client cl;
   //svn::Path tmpPath("file:///home/odjuvsla/test/test/repos");
   //vector<svn::Status> ss = cl.status("/home/odjuvsla/test/repos/pedestals/pedestals.dat");

   //   printf("%d\n", cl.getContext());
//   printf("%d\n", ss.size());
//   cl.info(tmpPath);

// //   cl.checkout("/home/odjuvsla/test/test/repos/", svn::Path("."), -1, true);
   
//   if(fRepoPath.length() > 0 && fDestinationPath.length() > 0)
//   {
      //svn::Status *status  =
   //      printf("%s\n",fRepoPath.c_str());
      //fSvnClient.status(fRepoPath.c_str()); 
      //if(status->IsVersioned())
   //      {
//	   res = CheckoutRevision();
//      }
//   }
   return res;

}


int DatabasePedestals::LoadValues(bool loadFromFile)
{

   std::ifstream infile;

   infile.open(fPedestalFileName.c_str(), ifstream::in);
   
   unsigned long hwAddress;
   unsigned long pedValue;
   
   std::string modString;
   std::string rcuString;
   
   int currentModule = -1;
   int currentRcu = -1;

   while(1)
   {
      infile >> modString >> rcuString;
      if(!infile.good()) break;

      if(modString.substr(0, 6) == "Module")
      {
	 currentModule = atof(modString.substr(7,1).c_str());
	 currentRcu = atof(rcuString.substr(4,1).c_str());
	 
	 fPedestalsVectors[currentModule][currentRcu].clear();
	 fPedestalsVectors[currentModule][currentRcu].resize(0);
	 
	 fHWAddressVectors[currentModule][currentRcu].clear();
	 fHWAddressVectors[currentModule][currentRcu].resize(0);

	 continue;
      }
      
//       fHWAddressVectors[currentModule][currentRcu].push_back(ceil(atof(modString.c_str())));
//       fPedestalsVectors[currentModule][currentRcu].push_back(ceil(atof(rcuString.c_str())));
      if(1)//atof(rcuString.c_str()) < 1023) //TODO: testing for noisy channels
	{
	  	  fHWAddressVectors[currentModule][currentRcu].push_back((atof(modString.c_str())));
		  //fHWAddressVectors[currentModule][currentRcu].push_back(ceil(atof(modString.c_str())));
	  if(loadFromFile)
	    {
	      	      fPedestalsVectors[currentModule][currentRcu].push_back((atof(rcuString.c_str())));
		      //fPedestalsVectors[currentModule][currentRcu].push_back(ceil(atof(rcuString.c_str())));
	    }
	  else
	    {
	      fPedestalsVectors[currentModule][currentRcu].push_back(0);
	    }

	  //            cout << "Mod: " << currentModule << ", RCU: " << currentRcu << endl;
	  //            cout << "HW add: " << fHWAddressVectors[currentModule][currentRcu].back() << " , pedestal value: " << rcuString << " /  " << fPedestalsVectors[currentModule][currentRcu].back() << endl;
	}
   }
   cout << "Number of entries in vectors for module 2, rcu 0: " << fPedestalsVectors[2][0].size() << endl;
   for(int m = 0; m < PHOS_MODS; m++)
   {
      for(int r = 0; r < RCUS_PER_MODULE; r++)
      {
	if( fHWAddressVectors[m][r].size() > 0)
	  {
	    if(!fPedestalValues[m][r]) fPedestalValues[m][r]= new PedestalValues(m, r);
	    fPedestalValues[m][r]->SetHWAddresses(fHWAddressVectors[m][r]);  //SetHWAddresses(fHWAddressVectors);
	    fPedestalValues[m][r]->SetPedestalValues(fPedestalsVectors[m][r]);
	  }
      }
   }
   ofstream outfile;
   outfile.open("pedestals.out", ofstream::out);

   for(int m = 0; m < PHOS_MODS; m++)
   {
      for(int r = 0; r < RCUS_PER_MODULE; r++)
      {
	outfile << "Module:" << m << "   RCU:" << r << endl;
	if( fHWAddressVectors[m][r].size() > 0)
	  {
	    for(int n = 0; n < fHWAddressVectors[m][r].size(); n++)
	      {
		outfile << fHWAddressVectors[m][r].at(n);
		outfile << "  " << fPedestalsVectors[m][r].at(n) << endl;
	      }
	  }
      }
   }
   outfile.close();
   return 0;
}

int DatabasePedestals::LoadZeros()
{
  
   for(int m = 0; m < PHOS_MODS; m++)
   {
      for(int r = 0; r < RCUS_PER_MODULE; r++)
      {
	for(int n = 0; n < N_ZROWS_MOD*N_XCOLUMNS_MOD*PHOS_GAINS; n++)
	  {
	    fHWAddressVectors[m][r].push_back(0);
	    fPedestalsVectors[m][r].push_back(0);
	  }
	if( fHWAddressVectors[m][r].size() > 0)
	  {
	    if(!fPedestalValues[m][r]) fPedestalValues[m][r]= new PedestalValues(m, r);
	    fPedestalValues[m][r]->SetHWAddresses(fHWAddressVectors[m][r]);  //SetHWAddresses(fHWAddressVectors);
	    fPedestalValues[m][r]->SetPedestalValues(fPedestalsVectors[m][r]);
	  }
      }
   }
  
  return 0;
}
