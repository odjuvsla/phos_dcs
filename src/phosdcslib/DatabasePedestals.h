#ifndef DATABASEPEDESTALS_H
#define DATABASEPEDESTALS_H

#include "DatabaseSVN.h"
#include "PhosConst.h"
#include "PhosDataTypes.h"
#include "PedestalValues.h"

using namespace PhosConst;

class DatabasePedestals : public DatabaseSVN
  {
     public:
	
	/** Default constructor */
    DatabasePedestals();

    /** Constructor */
    DatabasePedestals ( std::string repoPath, std::string destPath );
    
    /** Destructor */
    virtual ~DatabasePedestals();
    
    /** Initialise the database */
    virtual int Initialise();    
    
    /** Load values from file */
    virtual int LoadValues(bool loadFromFile = true);
    
    /** Get the values for the given module / RCU */
    vector<unsigned long> GetPedestals(ModNumber_t modId, RcuNumber_t rcuId) 
      {
	//	cout << "GetPedestals: Size of pedestals vector for module " << modId.GetIntValue() << ", RCU " << rcuId.GetIntValue() << " : " << fPedestalsVectors[modId.GetIntValue()][rcuId.GetIntValue()].size() << endl;
	cout << "GetPedestals: Size of pedestals vector for module " << modId.GetIntValue() << ", RCU " << rcuId.GetIntValue() << " : " << fPedestalsVectors[2][0].size() << endl;
	return fPedestalsVectors[modId.GetIntValue()][rcuId.GetIntValue()] ; 
      }
    
    /** Get the addresses for the given module / RCU */
    vector<unsigned long> GetHWAddresses(ModNumber_t modId, RcuNumber_t rcuId) { return fHWAddressVectors[modId.GetIntValue()][rcuId.GetIntValue()] ; }
    
    int LoadZeros();
    
     private:
	
	const std::string fPedestalFileName;
	
	PedestalValues *fPedestalValues[PHOS_MODS][RCUS_PER_MODULE];
	
	vector<unsigned long> fPedestalsVectors[PHOS_MODS][RCUS_PER_MODULE]; 
	vector<unsigned long> fHWAddressVectors[PHOS_MODS][RCUS_PER_MODULE]; 
    
  };

#endif // DATABASEPEDESTALS_H
