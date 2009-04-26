#ifndef PHOSCONST_H
#define PHOSCONST_H
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



namespace PhosConst
{
  
  const unsigned int DEBUG	=  0;  //0/1/2/3 - Level for debugging details
 
  const int RAMP_PATTERN = 0;
  const int SAWTOOTH_PATTERN = 1;
  const int G2_PATTERN = 2;

  const int DEFAULT_APD_DAC_VALUE = 512;
  const int EXIST = 0;
  const int NO_EXIST = -1;

  const int CONFIGINFO_MAX_SIZE = 4096;
  const unsigned int MAX_MESSAGE_SIZE = 512;

  //register types
  const unsigned int REGTYPE_ALTRO = 1;
  const unsigned int REGTYPE_BC    = 2;
  const unsigned int REGTYPE_RCU   = 3;
  const unsigned int REGTYPE_RCU_ACL = 4;
  const unsigned int REGTYPE_RCU_MEM = 5;
  const unsigned int REGTYPE_TRU     = 6;
  const unsigned int REGTYPE_TOR     = 7;
  const unsigned int REGTYPE_BUSY    = 8;

  //TRU registers
  const unsigned int TRU_SLOT  = 0;
  const unsigned int TRU_A  = 0;
  const unsigned int TRU_B = 16;
  const unsigned int TRUS_PER_RCU = 2;
  const unsigned long int TRU_REGS_BASE_ADDRESS = 0x72;
  const unsigned int N_TRU_REGS = 7;


  const unsigned int MAX_RESULT_BUFFER_SIZE = 8192;
  const unsigned int MAX_WORD_SIZE =  32; //maximum size in character  of one word in the RCU result buffer

  const int N_ZROWS_MOD      =  56;                    /**<Number of rows per module*/       
  const int N_XCOLUMNS_MOD   =  64;  

  const int N_ZROWS_BRANCH      =  N_ZROWS_BRANCH/2;                    /**<Number of rows per module*/       
  const int N_XCOLUMNS_BRANCH   =  N_XCOLUMNS_BRANCH/4;  

  const unsigned int PHOS_GAINS	= 2;  // Number of gains per one PHOS crystal
  const unsigned int HIGH_GAIN    =   1;
  const unsigned int LOW_GAIN     =   0;

 
  /*Geometrical constants*/
  const unsigned int MODULE_0     = 0;
  const unsigned int MODULE_1     = 1;
  const unsigned int MODULE_2     = 2;
  const unsigned int MODULE_3     = 3;
  const unsigned int MODULE_4     = 4;
  const unsigned int RCU_0       = 0;
  const unsigned int RCU_1       = 1;
  const unsigned int RCU_2       = 2;
  const unsigned int RCU_3       = 3;
  const unsigned int Z_0         = 0;
  const unsigned int Z_1         = 1;
  const unsigned int X_0         = 0;
  const unsigned int X_1         = 1;
  const unsigned int BRANCH_A    = 0;
  const unsigned int BRANCH_B    = 1;
 

  /*Electronics/Hardware constatns*/
  const unsigned int PHOS_MODS	= 5; // Number of PHOS modules
  const unsigned int TORS_PER_MODULE = 1;
  const unsigned int RCUS_PER_MODULE = 4;   ///// Number of RCUs per Module///
  const unsigned int BRANCHES_PER_RCU = 2;
  const unsigned int CARDS_PER_BRANCH  = 14; 	// Number of FECs per one RCU branch
  const unsigned int CARDS_PER_RCU  = BRANCHES_PER_RCU*CARDS_PER_BRANCH; // Number of FECs per one RCU 
  const unsigned int ALTROS_PER_FEE    = 4;
  const unsigned int CHANNELS_PER_ALTRO = 16;
  const unsigned int MAX_CARDS_PER_BRANCH = 16;
  const unsigned int MAX_CARDS_PER_RCU =  MAX_CARDS_PER_BRANCH*BRANCHES_PER_RCU;
  const unsigned int CSPS_PER_FEE    = 32;
  
  const unsigned int MAX_TRIALS  = 5;
  const unsigned int MAX_MESSAGE_LENGTH  = 150;
  const unsigned int MAX_LOGVIEWER_LINECOUNT = 300;
  
  const unsigned int TURN_ON = 0;
  const unsigned int TURN_OFF = 1;

  /*
  const signed  int APD_OK = 1;
  const signed  int APD_DEAD  = -1;
  const signed  int APD_ZERO  = -2;
  const signed  int APD_CRAZY = -3;
  const signed  int APD_UNKNOWN = 2;
  */
  
  const signed int REG_OK = 1;
  const signed int REG_DEAD  = -1;
  const signed int REG_ZERO  = -2;
  const signed int REG_CRAZY = -3;
  const signed int REG_UNKNOWN = 2;


  /*FEE state constants*/
  const unsigned int FEE_STATE_OFF = 1;
  const unsigned int FEE_STATE_ON  = 2;
  const unsigned int DCS_NOT_MASTER = 3;
  const unsigned int FEE_STATE_UNKNOWN  = 4;
  const unsigned int FEE_STATE_ERROR    = 5;
  const unsigned int UNKNOWN_PCMVERSION = 6;
  const unsigned int UNKNOWN_ERROR  = 7;
  const unsigned int FEE_STATE_WARNING = 8; 

  /*Firmware version of the PHOS boardcontroller*/
  const unsigned long int OLD_PCMVERSION = 0x34;
  const unsigned long int PCMVERSION = 0x35;

  /*Color constants (used only bt GUI)*/
  const unsigned long int SELECTED_COLOR  =  0x0000ff; //Blue
  const unsigned long int ON_COLOR        =  0x00ff00; //Green
  const unsigned long int OFF_COLOR       =  0xffffff; //White
  const unsigned long int ERROR_COLOR     =  0xff0000; //Red
  const unsigned long int UNKNOWN_COLOR   =  0xaaaaaa; //Gray
  const unsigned long int WARNING_COLOR   =  0xffff00; //Yellow
  

  const unsigned int MAX_ALTRO_SAMPLES = 1008;
  const unsigned int MAX_ALTRO_PRESAMPLES = 15; 
  const unsigned int MAX_ZEROSUPRESSION_THR = 500;
  const unsigned int MAX_ZEROSUPRESSION_MODE = 7;
  const unsigned int MAX_READOUT_MODE = 0xf; 

  const unsigned int FEC_RD = 0;

  const unsigned int FEC_CMD = 1;
  const unsigned int FEC_WR = 2;
  const unsigned int RCU_CMND = 3;

  const unsigned int CMD_TYPE = 20;   //20=Position of the Commmand type LS bit 
  const unsigned int PAR = 19;   //19=Position of the parity but
  const unsigned int BCAST = 18;   //18=Position of the broadcast register bit. Broadacst=1, no broadcast=0 (ms 20 bits) 
  const unsigned int BC_AL = 17;   //17=Position of command type bit. Boarcontroller=1, Altro=0
  const unsigned int BRANCH = 16;   //Branch A=0, Branch B=1 
  const unsigned int FAD = 12;   //Poistion of least significant bit of FEE adress register (most significant 20 bits)
  const unsigned int REGAD = 8;     //Position of least significant bit of CSP adress register (most significant 20 bits)

  const unsigned int CAD = 5;    //Position of least significant bit of CSP adress register (most significant 20 bits)
  const unsigned int CSPVAL = 0;   //Position of least significant bit of CSP value  register (least significant 20 bits)  

  const unsigned int REGVAL = 0;   //Position of least significant bit of CSP value  register (least significant 20 bits)  

};


#endif


