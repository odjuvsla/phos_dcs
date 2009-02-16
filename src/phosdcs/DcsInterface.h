#ifndef DCSINTERFACE_H
#define DCSINTERFACE_H


/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
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

#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
#include <vector>
#include <string>
class FeeCard;
class PhosDetector;
class PhosModule;
class DatabaseDummy;
class Rcu;
class FeeServer;



struct ConfigInfo_t;

class DcsInterface : public PhosDcsBase
{
 public:
                  DcsInterface();
  virtual         ~DcsInterface();

  int             Init(vector<FeeServer> feeServers);
  int             DeInit();

  void            ApplyApdSettings(const int modID, const int rcuId, const int branch, const int card) const;
  void            ApplyTruSettings(int modID, int RcuID, char *Mesbuf, unsigned long *regAddr, unsigned long *regVal, bool *verify, int nTruRegs);
  //  void            ApplyTruSettings(int modID, int RcuID, char *Mesbuf, unsigned long *regAddr, unsigned long *regVal, bool *verify, int nTruRegs);


  int             ArmTrigger(const int modID) const;
  unsigned int    CheckFeeState(const int mod,  const int rcu , const int branch , const int cardId);
 
  void            DisArmTrigger(const int modID, const int RcuID) const;
 
  void            EnableTrigger(int modID);
  void            EnableTrigger_ttcrx(int modID);  
  unsigned long*  GetApdValues(const int mod, const int rcu, const int branch, const int card);
  void            GetConfigComment(char *text, const int id);
  FeeCard*        GetFeeCard(const int mod, const int rcu, const int branch, const int cardId) const;
  int             GetLatestConfigId();
  std::string     GetLogViewerString();
  Rcu*            GetRcuPtr(const int modID, const int rcuID) const;

  void            LoadApdConfig(ConfigInfo_t *info);
  void            LoadApdConfig(ConfigInfo_t *info, int id);
  void            LoadApdValues(int modID);
  void            LoadReadoutConfiguration(ReadoutConfig_t *rdoconfigPtr) const; 
  void            SaveReadoutConfiguration(const ReadoutConfig_t rdoconfig) const;

  void            SaveTRUSettings(const TRUSettings_t trusettings);
  void            LoadTruSettings(TRUSettings_t *trusettings) const;

  int             SaveApdConfig(char *description);
  void            SetAllApds(const int modID, const int apdValue);
  void            SetAllApds(const int modID, const int rcuId, const int apdValue);
  void            SetAllApds(const int modID, const int rcuId, const int branch, const int card, const int apdValue);
  void            SetApdValues(const int mod, const int rcu, const int branch, const int card, const unsigned long *values);
  void            SetPhosBit(const int modID) const;
  void            SetReadoutConfig(const ModNumber_t modID, const ReadoutConfig_t rdoConfig) const;


  unsigned int    ToggleOnOffFee(const int mod,  const int rcu , const int branch , const int cardId, const unsigned int currentstate,  unsigned int tmpStates[CARDS_PER_RCU]);
  void            TurnOnAllFee(const int  modID, const int rcuId) const ;
  void            TurnOnAllTru( const int  modID, const int rcuId, char *message = 0) const; 
  //unsigned int    TurnOnFee (const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage);
  unsigned int    TurnOnFee (const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU]) {}
  //unsigned int    TurnOnTru (const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU], char *tmpMessage);
  unsigned int    TurnOnTru (const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU]) {}
  void            TurnOffAllFee(const int modID, const int rcuId) const;
  void            TurnOffAllTru(const int  modID, const int rcuId, char *message = 0) const; 
  unsigned int    TurnOffFee(const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU]) {}
  unsigned int    TurnOffTru(const int mod,  const int rcu , const int branch , const int cardSlot, unsigned int tmpStates[CARDS_PER_RCU]) {}
  void            UpdateAFL(const int mod, const int rcu) const;
  vector<int>     UpdateFeeStatus(const int mod, const int rcu);

 private:
  DatabaseDummy   *fDatabasePtr;
  PhosDetector    *fPhosDetectorPtr; /**<Pointer to the one and only PHOS detector */ 
};


#endif
