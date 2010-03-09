#ifndef PEDESTALVALUES_H
#define PEDESTALVALUES_H

#include "PhosDataTypes.h"

#include <vector>

class PedestalValues
  {
     public:
	
	/** Constructor must specify module and RCU */
	PedestalValues(const ModNumber_t modId, const RcuNumber_t rcuId);
	
	/** Destructor */
	~PedestalValues();
	
	/** Get the pedestal values */
	std::vector<unsigned long> GetPedestalValues();
	
	/** Get the HW addresses */
	std::vector<unsigned long> GetHWAddresses();

	/** Get the registers (value, address) */
	std::vector<Register> GetRegisters();

	/** Get the instructions, and the instruction memory addresses */
	int GetInstructions(std::vector<unsigned long> &values, std::vector<unsigned long> &regAdds);
	
	/** Set the pedestal values */
	void SetPedestalValues(std::vector<unsigned long> pedValues) { fPedestalValues = pedValues; }
	
	/** Set the HW addresses */
	void SetHWAddresses(std::vector<unsigned long> hwAdds) { fHWAddresses = hwAdds; }
	
	/** Set the regiser values */
	void SetRegisters(std::vector<Register> regs);
	
     private:
	
	/** Default constructor prohibited */
	PedestalValues();

	/** The module ID */
	ModNumber_t fModuleID; 
	
	/** The RCU ID */
	RcuNumber_t fRcuID;
	
	/** The pedestal values for this RCU */
	std::vector<unsigned long> fPedestalValues;
	
	/** The corresponding hardware addresses */
	std::vector<unsigned long> fHWAddresses;
	
	/** The registers (val, add) */
	std::vector<Register> fRegisters;
  };

#endif // PEDESTALVALUES_H
