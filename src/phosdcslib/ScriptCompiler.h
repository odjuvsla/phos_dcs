#ifndef SCRIPTCOMPILER_H
#define SCRIPTCOMPILER_H

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



/* The mapping between the crystals  and the adress for the
 corresponding CSP on the board controller is given 
below. The crystals is numbered concecutively starting from
the upper left corner of a 2x16 matrix for convinient handling 
in ROOT. The numbering is sown below as seen from the front.
The corresponding CSP and BC adresses matrixes are shown to the 
right for convienience. The mapping is done both with respect
to the CSPs and with respect to the crystals (the latter is in 
principle redundant)

Mapping as seen from the back (from the electronics)

2x16 matrix   |     2x16 matrix of    |   2x16 matrix of Board
of crystals   |     CSP/APDs          |   Controller adresses
------------------------------------------------------------------
0     1       |     CSP 0    CSP 16   |   0x48    0x47
2     3       |     CSP 1    CSP 17   |   0x49    0x46
4     5       |     CSP 2    CSP 18   |   0x4A    0x45
6     7       |     CSP 3    CSP 19   |   0x4B    0x44 
8     9       |     CSP 4    CSP 20   |   0x4C    0x43
10    11      |     CSP 5    CSP 21   |   0x4D    0x42
12    13      |     CSP 6    CSP 22   |   0x4E    0x41
14    15      |     CSP 7    CSP 23   |   0x4F    0x40
16    17      |     CSP 8    CSP 24   |   0x50    0x5F
18    19      |     CSP 9    CSP 25   |   0x51    0x5E
20    21      |     CSP 10   CSP 26   |   0x52    0x5D
22    23      |     CSP 11   CSP 27   |   0x53    0x5C
24    25      |     CSP 12   CSP 28   |   0x54    0x5B
26    27      |     CSP 13   CSP 29   |   0x55    0x5A
28    29      |     CSP 14   CSP 30   |   0x56    0x59
30    31      |     CSP 15   CSP 31   |   0x57    0x58

*/

//#ifndef SCRIPTCOMPILER_H
//#define SCRIPTCOMPILER_H
//#ifndef APDINPUT_H
//#define APDINPUT_H
//#define CE_CMD_EM_MASK        0xffff0000


#define CE_CMD_VS_MASK        0x0000ffff
#define CE_CMD_VERSION        0x0001
#define CE_CMD_ENDMARKER      0xdd330000
#define CE_CMD_TAILER        (CE_CMD_ENDMARKER | CE_CMD_VERSION)
#define FEESRV_RCUSH_SCRIPT   0xf7040000


// /*
//  * Mnemnoics for RCU_FW2
//  */

// #define FEC_RD   0 

// //#define FEC_RD   0xf 

// #define FEC_CMD  1
// #define FEC_WR   2
// #define RCU_CMND 3

// #define OTHER_CMD 0xf


// #define CMD_TYPE        20   //20=Position of the Commmand type LS bit 
// //#define RW              21   //21=Position of the RW bit, Write=1, Read=0
// //#define POS             20   //20=Position of the position bit 0=most sign. 20 bit, 1=least sign. 20 bits
// #define PAR             19   //19=Position of the parity but
// #define BCAST           18   //18=Position of the broadcast register bit. Broadacst=1, no broadcast=0 (ms 20 bits) 
// #define BC_AL           17   //17=Position of command type bit. Boarcontroller=1, Altro=0
// #define BRANCH          16   //Branch A=0, Branch B=1 
//#define FAD             12   //Poistion of least significant bit of FEE adress register (most significant 20 bits)

//#define REGAD           9     //Position of least significant bit of CSP adress register (most significant 20 bits)
//#define REGAD           5     //Position of least significant bit of CSP adress register (most significant 20 bits)
// #define REGAD           8     //Position of least significant bit of CSP adress register (most significant 20 bits)

// #define CAD             5    //Position of least significant bit of CSP adress register (most significant 20 bits)
// #define CSPVAL          0    //Position of least significant bit of CSP value  register (least significant 20 bits)  

//   //#define REGAD           0    //Position of least significant bit of CSP adress register (most significant 20 bits)
//   //#define REGAD           9     //Position of least significant bit of CSP adress register (most significant 20 bits)
// #define REGVAL          0    //Position of least significant bit of CSP value  register (least significant 20 bits)  


/*
#define CMD_TYPE        22   //22=Position of the Commmand type bit 0=RCU, 1=Altro command
#define RW              21   //21=Position of the RW bit, Write=1, Read=0
#define POS             20   //20=Position of the position bit 0=most sign. 20 bit, 1=least sign. 20 bits
#define PAR             19   //19=Position of the parity but (most significant 20 bits)
#define BCAST           18   //18=Position of the broadcast register. Broadacst=1, no broadcast=0 (ms 20 bits) 
#define BC_AL           17   //17=Position of command type bit. Boarcontroller=1, Altro=0
#define BRANCH          16   //Branch A=0, Branch B=1 
#define FAD             12   //Poistion of least significant bit of FEE adress register (most significant 20 bits)
#define CAD             0    //Position of least significant bit of CSP adress register (most significant 20 bits)
#define CSPVAL          0    //Position of least significant bit of CSP value  register (least significant 20 bits)  
#define REGAD           0    //Position of least significant bit of CSP adress register (most significant 20 bits)
#define REGVAL          0    //Position of least significant bit of CSP value  register (least significant 20 bits)  
*/


#include <vector>
#include "PhosDcsBase.h"
#include "PhosDataTypes.h"


using std::vector;




class ScriptCompiler : public PhosDcsBase
{
 public:
  ScriptCompiler();

  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static void MakeActivateFeeScript(const char *scriptFilename, const unsigned long activeFeeList, 
				    const unsigned long branch, const unsigned long card, const int onOff);

  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static void MakeActivateTruScript(const char *scriptFilename, const unsigned long activeFeeList);

  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static void MakeDeActivateTruScript(const char *scriptFilename, const unsigned long activeFeeList);


  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static void MakeTriggerConfigScript(const char *filename,  TriggerMode_t triggerMode, const AltroConfig_t altroconfig);   

  void MakeWriteReadRegisterScript(const int registerType, const char *fileName, const unsigned long *reg, 
				   const unsigned long *value, const bool *verify, const int N, const unsigned long branch = 0, 
				   const unsigned long card = 0,  const unsigned long chip = 0, const unsigned long channel = 0, const bool setZeroes = true) const;

  void MakeReadRegisterScript(const int registerType, const char *fileName, const unsigned long *reg, 
			      const int N, const unsigned long branch = 0, const unsigned long card = 0,  
			      const unsigned long chip = 0, const unsigned long channel = 0) const;


  /*
   *@param registerType either altro or boradcontroller (BC)
   *@param read if true its is a read command, if false it is a write command
   */

   /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static unsigned long  MakeMS20Instruction(const int registerType, const bool read,
					    const unsigned long reg, const unsigned long  branch = 0, 
					    const unsigned long card = 0, const unsigned long chip = 0, const unsigned long channel = 0); 


  /*
   * @param registerValue the value too write

  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  static unsigned long  MakeLS20Instruction(const bool read,  const unsigned long registerValue);
  //static unsigned long  MakeLS20Instruction(const bool rw, const unsigned long pos, const unsigned long registerValue);

 private:
  /** changed for RCU_fw2*/
  void MakeWriteReadFeeRegisterScript(const int registerType, const char *fileName, const unsigned long *registers, 
				      const unsigned long *values, const bool *verify, const int N, const unsigned long branch = 0, 
				      const unsigned long card = 0,  const unsigned long chip = 0, const unsigned long channel = 0, 
				      const bool setZeroes = true) const;

  void MakeWriteReadRcuRegisterScript(const int registerType, const char *fileName, 
				      const unsigned long *registers, const unsigned long *values, 
				      const bool *verify, const int N, const bool setZeroes = true) const ;
  
  void MakeReadFeeRegisterScript(const int registerType, const char *fileName, const unsigned long *registers, 
				 const int N, const unsigned long  branch = 0, const unsigned long card = 0,
				 const unsigned long chip = 0, const unsigned long channel = 0) const ;
 
  void MakeReadRcuRegisterScript(const int registerType, const char *fileName,  unsigned long basAddress, int N) const;
  
  
  void MakeG2PatternScript();
  void MakeRampPatternScript();
  void MakeSawtoothPatternScript();



};


#endif
