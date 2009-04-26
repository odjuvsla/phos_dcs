#ifndef DATABASEDUMMY_H
#define DATABASEDUMMY_H



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

#include "PhosDcsBase.h"
#include "PhosDataTypes.h"
struct ConfigInfo_t;


class DatabaseDummy : public PhosDcsBase
{

 public:
  DatabaseDummy();
  virtual ~DatabaseDummy();

  int LoadApdConfig(ConfigInfo_t *info, int = -1);
  int LoadApdConfig(char *description);
  int LoadApdConfig(char *description, int id);
  int SaveApdConfig(char *description);
  void SaveRadoutConfiguration(const ReadoutConfig_t rdoConfig, const ModNumber_t modNumber) const;
  void LoadReadoutConfiguration(ReadoutConfig_t *rdoConfig, const ModNumber_t modnumber_t) const;

  void SaveTruSettings(const TRUSettings_t t) const;
  void LoadTruSettings(TRUSettings_t *t)const;

  bool  GetConfigComment(char *description, int id);
  const int GetLatestConfigId() const;
 private:
  void SetPostfix(char *postfix, const int id) const;
};

#endif
