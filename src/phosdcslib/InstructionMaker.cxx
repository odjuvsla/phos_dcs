
#include "InstructionMaker.h"
#include "PhosConst.h"
#include "PhosDcsLogging.h"

using namespace PhosConst;

unsigned long 
InstructionMaker::MakeMS20Instruction(const int registerType,   const bool read,  
				    const unsigned long reg,  const unsigned long branch,  
				    const unsigned long card,  const unsigned long chip, 
				    const unsigned long channel)
{

  stringstream log;

  int tmp_bc_altro = 0;

  int tmpCommand = 0;


  int tmp_broadcast = 0;

  if(registerType == REGTYPE_BC || (registerType == REGTYPE_TRU) )
    {
      tmp_bc_altro = 1; 

    }
  else if (registerType ==  REGTYPE_ALTRO)
    {
      tmp_bc_altro = 0; 
 
      //CRAP PTH: if we are not reading then we are writing, and for the
      //moment the altro is always configured in broadcast mode
       
      if(read == false)
	{  
	  tmp_broadcast = 1;
	}
      
    }
 
  if(read == true)
    {
      tmpCommand = FEC_RD; 
    } 
 
  else if (read == false)
    {
      tmpCommand = FEC_WR;
    }
  
  // Calculating parity (1 if odd, 0 if even)
  unsigned int tmpInstruction = 0;
  int tmpParity = 0;
  tmpInstruction = ( tmp_bc_altro << BC_AL )|  (tmp_broadcast << BCAST) |  (branch<<BRANCH) | (card<<FAD) | (channel <<REGAD) | reg;

  int no_ones = 0;
  while (tmpInstruction)
    {
      no_ones++;  
      tmpInstruction = tmpInstruction & (tmpInstruction - 1);
    }
  tmpParity = no_ones & 1;

  int command = (tmpCommand << CMD_TYPE)| (tmpParity << PAR) | ( tmp_bc_altro << BC_AL )|  (tmp_broadcast << BCAST) |  (branch<<BRANCH) | (card<<FAD) | (channel <<REGAD) | reg;

  log.str("");
  log << hex << "InstructionMaker::MakeMS20Instruction: Command type: " << tmpCommand << ", parity: " << tmpParity << ", BC or ALTRO: " << tmp_bc_altro << ", broadcast: "
      << tmp_broadcast << ", branch: " << branch << ", card: " << card << ", channel: " << channel << ", register: " << reg << dec << endl;
  log << hex << "Command: " << command << endl;

  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_EXTREME_VERBOSE);


  return  (tmpCommand << CMD_TYPE)| (tmpParity << PAR) | ( tmp_bc_altro << BC_AL )|  (tmp_broadcast << BCAST) |  (branch<<BRANCH) | (card<<FAD) | (channel <<REGAD) | reg;

 
}


unsigned long 
InstructionMaker::MakeLS20Instruction(const bool read, const unsigned long registerValue) 
{
  int tmpCommand = 0; 
  //int tmp_rw = 0; 
 
  if(read == true)
    {
     tmpCommand  = FEC_RD ; 
    }
  else if (read == false)
    {
      tmpCommand =  FEC_WR;
    }

  return (tmpCommand << CMD_TYPE) | (registerValue << REGVAL);

}


 
