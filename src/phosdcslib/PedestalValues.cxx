
#include "PedestalValues.h"
#include "PhosDcsLogging.h"
#include "AltroRegisterMap.h"
#include "RcuRegisterMap.h"

PedestalValues::PedestalValues ( const ModNumber_t modId, const RcuNumber_t rcuId ) :
fModuleID(-1)
,fRcuID(-1)
,fPedestalValues(0)
,fHWAddresses(0)
{

}

PedestalValues::~PedestalValues()
{

}

std::vector< unsigned long> PedestalValues::GetPedestalValues()
{
   if(fPedestalValues.size() == fHWAddresses.size())
   {
      return fPedestalValues;
   }
   else
   {
      stringstream log;
      log << "PedestalValues::GetPedestalValues: Module #: " << fModuleID.GetIntValue() << ", RCU #: " << fRcuID.GetIntValue()<< ": difference in number of HW addresses and number of values";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
   }
}

std::vector< unsigned long> PedestalValues::GetHWAddresses()
{
   if(fPedestalValues.size() == fHWAddresses.size())
   {
      return fHWAddresses;
   }
   else
   {
      stringstream log;
      log << "PedestalValues::GetPedestalValues: Module #: " << fModuleID.GetIntValue() << ", RCU #: " << fRcuID.GetIntValue() << ": difference in number of HW addresses and number of values";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
   }
   return fHWAddresses;
}

std::vector< Register> PedestalValues::GetRegisters()
{
   std::vector<Register> tmpVector;
   
   if(fPedestalValues.size() == fHWAddresses.size())
   {
      Register tmpReg;
      unsigned long currentAdd = RcuRegisterMap::Instruction_MEM;
      vector<unsigned long>::iterator itVal;
      vector<unsigned long>::iterator itAdd;
      
      for ( itVal=fPedestalValues.begin(), itAdd = fHWAddresses.begin() ; itVal < fPedestalValues.end(); itVal++, itAdd++ )
      {
	tmpReg.fValue = *itAdd << 5 | AltroRegisterMap::VFPED | 2 << CMD_TYPE;
	 tmpReg.fAddress = currentAdd;
	 tmpVector.push_back(tmpReg);
	 currentAdd++;
	 tmpReg.fValue = *itVal| 2 << CMD_TYPE;
	 tmpReg.fAddress = currentAdd;
	 tmpVector.push_back(tmpReg);
	 currentAdd++;
      }
      fRegisters = tmpVector;
   }
   else
   {
      stringstream log;
      log << "PedestalValues::GetRegisters: Module #: " << fModuleID.GetIntValue() << ", RCU #: " << fRcuID.GetIntValue() << ": difference in number of HW addresses and number of values";
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
   }
   return tmpVector;
}


int PedestalValues::GetInstructions ( std::vector< unsigned long >& values, std::vector< unsigned long >& regAdds )
{
  GetRegisters();
   vector<Register>::iterator regsIt;
      stringstream log;
      log << "PedestalValues::GetInstructions: Number of entries in register vector: " << fRegisters.size();
      PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO);

      regAdds.push_back(0);
   for (regsIt = fRegisters.begin(); regsIt < fRegisters.end(); regsIt++)
   {

      values.push_back((*regsIt).fValue);
      //      cout << "GetInstructions: Value (command): " << hex << values.back() << dec << ", reg address: " << regAdds.back() << endl;
      //regAdds.push_back((*regsIt).fAddress);
      //      values.push_back((*regsIt).fAddress);
      //      cout << "GetInstructions: Value (value): " << values.back() << ", reg address: " << regAdds.back() << endl;
   }
   return 0;
}


void PedestalValues::SetRegisters ( vector< Register > regs )
{
   fPedestalValues.clear();
   fHWAddresses.clear();   
   
   vector<Register>::iterator itReg;
   for(itReg = regs.begin(); itReg < regs.end(); itReg++)
   {
      fPedestalValues.push_back((*itReg).fValue);
      fHWAddresses.push_back((*itReg).fAddress);
   }
}
