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

//#ifndef COMMONDEFSX_H
//#define COMMONDEFSX_H


#ifndef PHOSCONST_H
#define PHOSCONST_H


//#define APDVAL_BASE_PATH       "../data/APD_settings/"
//#define CONFIG_BASE_PATH       "../data/ConfigurationFiles/"
//#define APDSCRIPT_BASE_PATH   "../data/APD_scripts/"

namespace PhosConst
{
  const int ALTRO_MAX_SAMPLES = 1008;
  const int ALTRO_MAX_PRESAMPLES = 15;
  const int MAX_ZEROSUPRESSION_TRESHOLD = 512; 

  const int DEFAULT_APD_DAC_VALUE = 512;
  const int EXIST = 0;
  const int NO_EXIST = -1;

  const char APDVAL_BASE_PATH[]   =    "../data/APD_settings/";
  const char CONFIG_BASE_PATH[]    =   "../data/ConfigurationFiles/";
  const char APDSCRIPT_BASE_PATH[]  =  "../data/APD_scripts/";

  //  const char *APDVAL_BASE_PATH   =    "../data/APD_settings/";

  const unsigned long int  AFL =  0x8000;
  const unsigned long int  RDOL = 0x8001;
  //register typs
  const unsigned int REGTYPE_ALTRO = 1;
  const unsigned int REGTYPE_BC    = 2;
  const unsigned int REGTYPE_RCU   = 3;
  const unsigned int REGTYPE_RCU_ACL = 4;
  const unsigned int REGTYPE_TRU     = 5;
  const unsigned int REGTYPE_TOR     = 6;
  const unsigned int REGTYPE_BUSY    = 7;


  const unsigned int TRU_SLOT  = 0;
  const unsigned int TRU_A  = 0;
  const unsigned int TRU_B = 16;

  const unsigned int TRUS_PER_RCU = 2;
  const unsigned int MAX_MESSAGE_SIZE = 512;
  const unsigned int ACL_SIZE  = 256; 

  const unsigned long int ACL_BASE_ADDRESS  = 0x6400;
  const unsigned long int RCU_BASEADRESS = 0x7000;
  const unsigned long int RCU_RESULT_BASE = 0x6000;
  const unsigned long int TRU_REGS_BASE_ADDRESS = 0x72;

  const unsigned int N_TRU_REGS = 7;
  const unsigned int MAX_RESULT_BUFFER_SIZE = 8192;
  const unsigned int MAX_WORD_SIZE =  32; //maximum size in character  of one word in the RCU result buffer

  //  char *APDVAL_BASE_PATH     =  "../data/APD_settings/";
  //  char *CONFIG_BASE_PATH     =  "../data/ConfigurationFiles/";
  //  char *APDSCRIPT_BASE_PATH  = "../data/APD_scripts/";
  const unsigned int DEBUG	=  0;  //0/1/2/3 - Level for debugging details
  const unsigned int PHOS_ROWS	= 64;  // Number of rows per one PHOS module
  const unsigned int PHOS_COLS	= 56;   // Number of columns per one PHOS module
  const unsigned int PHOS_GAINS	= 2;  // Number of gains per one PHOS crystal
  const unsigned int HIGH_GAIN    =   1;
  const unsigned int LOW_GAIN     =   0;
  const unsigned long int MAX_TRIGGER_DELAY  = 0x3fff;
  const unsigned int PHOS_MODS	= 5; // Number of PHOS modules
  const unsigned int MODULE_0     = 0;
  const unsigned int MODULE_1     = 1;
  const unsigned int MODULE_2     = 2;
  const unsigned int MODULE_3     = 3;
  const unsigned int MODULE_4     = 4;
  const unsigned int RCUS_PER_MODULE = 4;   ///// Number of RCUs per Module///
  const unsigned int CSPS_PER_FEE    = 32;
  const unsigned int RCU_0       = 0;
  const unsigned int RCU_1       = 1;
  const unsigned int RCU_2       = 2;
  const unsigned int RCU_3       = 3;
  const unsigned int CARDS_PER_RCU  = 28;
  const unsigned int MAX_CARDS_PER_RCU = 32;
  const unsigned int CARDS_PER_BRANCH  = 14;
  const unsigned int BRANCHES_PER_RCU = 2;
  const unsigned int BRANCH_A     = 0;
  const unsigned int BRANCH_B    = 1;
  const unsigned int Z_0         = 0;
  const unsigned int Z_1         = 1;
  const unsigned int X_0         = 0;
  const unsigned int X_1         = 1;
  const unsigned int FEE_CHANS	= 16;	// Number of ALTRO channels per one ALTRO chip
  const unsigned int FEE_ALTROS	= 4;	// Number of ALTRO chips per one FEC (Front End Card)
  const unsigned int FEE_FECS	= 14;	// Number of FECs per one RCU branch
  const unsigned int FEE_BRANCHS	 = 2;	// Number of RCU branchs per one RCU
  const unsigned int FEE_RCUS	= 4;	// Number of RCUs per one PHOS module !!redundant
  
  const unsigned int MAX_TRIALS  = 5;
  const unsigned int MAX_MESSAGE_LENGTH  = 150;
  const unsigned int MAX_LOGVIEWER_LINECOUNT = 300;
  
  const unsigned int TURN_ON = 0;
  const unsigned int TURN_OFF = 1;

  const signed  int APD_OK = 1;
  const signed  int APD_DEAD  = -1;
  const signed  int APD_ZERO  = -2;
  const signed  int APD_CRAZY = -3;
  const signed  int APD_UNKNOWN = 2;
  
  const signed int REG_OK = 1;
  const signed int REG_DEAD  = -1;
  const signed int REG_ZERO  = -2;
  const signed int REG_CRAZY = -3;
  const signed int REG_UNKNOWN = 2;

  const unsigned int FEE_STATE_OFF = 1;
  const unsigned int FEE_STATE_ON  = 2;
  const unsigned int DCS_NOT_MASTER = 3;
  const unsigned int FEE_STATE_UNKNOWN  = 4;
  const unsigned int FEE_STATE_ERROR    = 5;
  const unsigned int UNKNOWN_PCMVERSION = 6;
  const unsigned int UNKNOWN_ERROR  = 7;
  const unsigned int FEE_STATE_WARNING = 8; 
  const unsigned long int OLD_PCMVERSION = 0x12;
  const unsigned long int PCMVERSION = 0x20;
  const unsigned long int SELECTED_COLOR  =  0x0000ff; //Blue
  const unsigned long int ON_COLOR        =  0x00ff00; //Green
  const unsigned long int OFF_COLOR       =  0xffffff; //White
  const unsigned long int ERROR_COLOR     =  0xff0000; //Red
  const unsigned long int UNKNOWN_COLOR   =  0xaaaaaa; //Gray
  const unsigned long int WARNING_COLOR   =  0xffff00; //Yellow
  
};


#endif


