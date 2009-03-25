#ifndef MAPPER_H
#define MAPPER_H

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

//#include "PhosFeeClient.h"

//#include <assert.h>
//#include "CommonDefs.h"
#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
#include "RcuRegisterMap.h"

class Mapper : public PhosDcsBase
{
 public:
  Mapper();
  struct FEE_CSP_MAP{ 
    int row;
    int col;
    int gain;
    int csp;
    int num;
  };

  struct ALTRO_GEO_MAP{ 
    int mod;
    int gain;
    int row;
    int col;
    int rcu;
    int branch;
    int card;
    int chip;
    int chan;
    int csp;
    int num;
    int hid;
  };


  void AddCsp(int csp, int chip, int chHi, int chLo, int numHi, int numLo);

 
  /** changed for RCU_fw2 (maybe incomplete/incorrect) */
  void GenerateACL(ReadoutRegion_t, int acl[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length], 
		   unsigned long int afl[RCUS_PER_MODULE], const int modId = MODULE_2) const;

  void InitAltroCspMapping();

  inline int Geo2hid(int mod, int gain, int row, int col);
  inline int Hid2mod(int hid);
  inline int Hid2gain(int hid);
  inline int Hid2row(int hid);
  inline int Hid2col(int hid);
  inline int ExtractHid(char *objName);  

  inline void InitAltroMapping(int saveMapping);
  inline void PrintHistMapInfo(char *objName);

  FEE_CSP_MAP CSP_MAP[ALTROS_PER_FEE ][CHANNELS_PER_ALTRO];
  ALTRO_GEO_MAP ALTRO_MAP[ PHOS_MODS * RCUS_PER_MODULE *  BRANCHES_PER_RCU * CARDS_PER_BRANCH *ALTROS_PER_FEE *CHANNELS_PER_ALTRO];  
  int hdw2geo[ PHOS_MODS][ RCUS_PER_MODULE][  BRANCHES_PER_RCU][ CARDS_PER_BRANCH][ALTROS_PER_FEE][CHANNELS_PER_ALTRO];
  int geo2hdw[ PHOS_MODS][ PHOS_GAINS][ N_XCOLUMNS_MOD][ N_ZROWS_MOD];  

 private:



};

#endif
