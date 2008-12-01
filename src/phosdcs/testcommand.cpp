#include "RcuRegisterMap.h"
#include "PhosDataTypes.h"

#include "ScriptCompiler.h"
//#include "RcuRegisterMap.h"
#include "AltroRegisterMap.h"
#include "BCRegisterMap.h"
#include "PhosDataTypes.h"
#include "RcuRegisterMap.h"
#include <iostream>

using namespace std;


int main()
{
  
  // Calculating parity (1 if odd, 0 if even)
  unsigned int tmpInstruction = 0;
  int tmpParity = 0;
  tmpInstruction = (tmpParity << PAR) | ( 1 << BC_AL )|  (0 << BCAST) |  (0<<BRANCH) | (1<<FAD) | (0 <<REGAD) | (0x68);

  int no_ones = 0;
  while (tmpInstruction)
    {
      no_ones++;  
      tmpInstruction = tmpInstruction & (tmpInstruction - 1);
    }
  tmpParity = no_ones & 1;
  
  int t =  (2 << CMD_TYPE)| (tmpParity << PAR) | ( 1 << BC_AL )|  (0 << BCAST) |  (0<<BRANCH) | (1<<FAD) | (0 <<REGAD) | 0x68;

  cout << hex << t << endl;

}
