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

#include "Mapper.h"
#include "PhosDataTypes.h"
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "PhosDcsLogging.h"

Mapper::Mapper() : PhosDcsBase()
{
  //  printf("\nCreating new mapper\n");
  InitAltroMapping(0, 0); 
}



void 
Mapper::GenerateACL(const ReadoutRegion_t readoutregion, 
		    int acl[RCUS_PER_MODULE][RcuRegisterMap::Active_Channel_List_Length], 
		    unsigned long int afl[RCUS_PER_MODULE], const int modID) const 
{
  stringstream log;

  for(int i=0; i<RCUS_PER_MODULE; i++)
    {
      for(int j=0; j< RcuRegisterMap::Active_Channel_List_Length; j++)
	{
	  //	  acl[i][j] = 0;
	  acl[i][j] = 0xfff;
	}
    }

  int index;

  //  int aclIndex = 0;

  int aclIndex[RCUS_PER_MODULE];
  
  for(int i = 0; i < RCUS_PER_MODULE; i++ )

    {
      aclIndex[i] = 0;
    }


  int rcu = 99;
  int branch = 99;
  int card = 99;;
  int altro = 99;
  int channel = 99;
  int csp = 99;


  for(int i =  readoutregion.GetHGStartZ().GetIntValue(); i <=  readoutregion.GetHGEndZ().GetIntValue(); i++)
    {
      for(int j = readoutregion.GetHGStartX().GetIntValue(); j <=  readoutregion.GetHGEndX().GetIntValue(); j++)
 	{
	  log.str("");
	  log << "Mapper::GenerateACL: Adding crystal: x: " << j << " and z: " << i << endl;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_EXTREME_VERBOSE);

	  int k = HIGH_GAIN;

// 	  for(int k = PHOS_GAINS - 1  ; k > -1; k--)
// 	    {
	 
	      index = geo2hdw[modID][k][j][i]; 
	      rcu = ALTRO_MAP[index].rcu;
	      branch = ALTRO_MAP[index].branch;
	      card = ALTRO_MAP[index].card;
	      altro = ALTRO_MAP[index].chip;  
	      channel = ALTRO_MAP[index].chan;
	      csp = ALTRO_MAP[index].csp;
	 
	      if(altro > 0)
		{
		   altro = altro + 1; //to fix bug in mp
		}

	      ///OLD RCU FIRMWARE
	      // aclIndex = branch*128+(card +1)*8+altro;
	      // acl[rcu][aclIndex] =  acl[rcu][aclIndex] | 1<<channel;
	      

	      // NEW RCU FIRMWARE
   	      // altro channel relative to one FEE

	      unsigned long tmpGlobalFeeChannel = altro*CHANNELS_PER_ALTRO + channel;
	      acl[rcu][aclIndex[rcu]] = (branch << 11)  |((card+1) << 7) | (tmpGlobalFeeChannel) ;
	      //printf("acl[%d][%d] = 0x%x - Card %d\n", rcu, aclIndex[rcu], acl[rcu][aclIndex[rcu]], card+1);
	      aclIndex[rcu] ++;

	      afl[rcu] = (long int)afl[rcu] | (1<< ((long int)(card+1) +(long int)branch*MAX_CARDS_PER_BRANCH));
	      //	    }
	}
    }
  for(int i =  readoutregion.GetLGStartZ().GetIntValue(); i <=  readoutregion.GetLGEndZ().GetIntValue(); i++)
    {
      for(int j = readoutregion.GetLGStartX().GetIntValue(); j <=  readoutregion.GetLGEndX().GetIntValue(); j++)
 	{
	  log.str("");
	  log << "Mapper::GenerateACL: Adding crystal: x: " << j << " and z: " << i << endl;
	  PhosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_EXTREME_VERBOSE);

	  int k = LOW_GAIN;

// //FEE
//   for(int i = 0; i <=  55; i++)
//     {
//       for(int j = 0; j <= 63; j++)
// 	{
// 	  for(int k = PHOS_GAINS - 1  ; k > -1; k--)
// 	    {
	 
	      index = geo2hdw[modID][k][j][i]; 
	      rcu = ALTRO_MAP[index].rcu;
	      branch = ALTRO_MAP[index].branch;
	      card = ALTRO_MAP[index].card;
	      altro = ALTRO_MAP[index].chip;  
	      channel = ALTRO_MAP[index].chan;
	      csp = ALTRO_MAP[index].csp;
	 
	      if(altro > 0)
		{
		   altro = altro + 1; //to fix bug in mp
		}

	      ///OLD RCU FIRMWARE
	      // aclIndex = branch*128+(card +1)*8+altro;
	      // acl[rcu][aclIndex] =  acl[rcu][aclIndex] | 1<<channel;
	      

	      // NEW RCU FIRMWARE
   	      // altro channel relative to one FEE

	      unsigned long tmpGlobalFeeChannel = altro*CHANNELS_PER_ALTRO + channel;
	      acl[rcu][aclIndex[rcu]] = (branch << 11)  |((card+1) << 7) | (tmpGlobalFeeChannel) ;
	      //printf("acl[%d][%d] = 0x%x - Card %d\n", rcu, aclIndex[rcu], acl[rcu][aclIndex[rcu]], card+1);
	      aclIndex[rcu] ++;

	      afl[rcu] = (long int)afl[rcu] | (1<< ((long int)(card+1) +(long int)branch*MAX_CARDS_PER_BRANCH));
	      //	    }
	}
    }
  if(readoutregion.IsTruReadoutEnabled())
    {
      //TRU // TODO: need to configure region for TRUs as well
      for(int rcu = 0; rcu < RCUS_PER_MODULE; rcu++)
	{
	  for(int tru = 0; tru < 2; tru++) //TODO: don't use hardcoded values
	    {
	      for(int altro = 0; altro < 8; altro++)
		{
		  for(int channel = 0; channel < readoutregion.GetNumberOfTRUSamples(); channel++)
		    {
		      unsigned long tmpGlobalFeeChannel = altro*CHANNELS_PER_ALTRO + channel;
		      acl[rcu][aclIndex[rcu]] = (tru << 11)  | (tmpGlobalFeeChannel) ;
		      aclIndex[rcu] ++;
		      afl[rcu] = (long int)afl[rcu] | (1<< ((long int)(tru*(MAX_CARDS_PER_BRANCH-1)) +(long int)tru*MAX_CARDS_PER_BRANCH));
		    }
		}
	      //	  afl[rcu] = (long int)afl[rcu] | (1<< ((long int)(0) +(long int)branch*MAX_CARDS_PER_BRANCH));
	    }
	}
    }
}





void 
Mapper::AddCsp(int csp, int chip, int chHi, int chLo, int numHi, int numLo)
{
  // Find row & col by CSP
  int col = csp / 16;
  int row = csp % 16;
  //In 2004 beam test was also: if(row>7)row=23-row;
  // Check if arguments Ok
  assert((col>=0)&&(col<2));
  assert((row>=0)&&(row<16));
  assert((csp>=0)&&(csp<32));
  assert((numHi>=0)&&(numHi<64));
  assert((numLo>=0)&&(numLo<64));
  assert((chHi>=0)&&(chHi < N_ZROWS_MOD <  CHANNELS_PER_ALTRO));
  assert((chLo>=0)&&(chLo <  CHANNELS_PER_ALTRO));
  assert((chip>=0)&&(chip <  ALTROS_PER_FEE ));
  // Fill CSP array
  CSP_MAP[chip][chHi].row=row;	CSP_MAP[chip][chLo].row=row;
  CSP_MAP[chip][chHi].col=col;	CSP_MAP[chip][chLo].col=col;
  CSP_MAP[chip][chHi].gain=1;	CSP_MAP[chip][chLo].gain=0;
  CSP_MAP[chip][chHi].csp=csp;	CSP_MAP[chip][chLo].csp=csp;
  CSP_MAP[chip][chHi].num=numHi;	CSP_MAP[chip][chLo].num=numLo;
}

 /////////////////////////////////////////////////////////////////
 // Initialize CSP mapping table.
 // Note we use (0,1,2,3) instead of (0,2,3,4) ALTRO chip numbers.
 // So strange numbers we have due to well known RCU firmware bug.
 /////////////////////////////////////////////////////////////////

void 
Mapper::InitAltroCspMapping(ModNumber_t modID)
{
  if(modID.GetIntValue() == 4)
    {
      // T1  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	0,	1,	10,	11,	26,	27);
      AddCsp(	1,	1,	14,	15,	30,	31);
      AddCsp(	2,	1,	5,	4,	21,	20);
      AddCsp(	3,	1,	1,	0,	17,	16);
      AddCsp(	4,	2,	1,	0,	33,	32);
      AddCsp(	5,	2,	5,	4,	37,	36);
      AddCsp(	6,	2,	14,	15,	46,	47);
      AddCsp(	7,	2,	10,	11,	42,	43);
      // T2  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	8,	0,	10,	11,	10,	11);
      AddCsp(	9,	0,	14,	15,	14,	15);
      AddCsp(	10,	0,	5,	4,	5,	4);
      AddCsp(	11,	0,	1,	0,	1,	0);
      AddCsp(	12,	3,	1,	0,	49,	48);
      AddCsp(	13,	3,	5,	4,	53,	52);
      AddCsp(	14,	3,	14,	15,	62,	63);
      AddCsp(	15,	3,	10,	11,	58,	59);
      // T3  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	16,	1,	8,	9,	24,	25);
      AddCsp(	17,	1,	12,	13,	28,	29);
      AddCsp(	18,	1,	7,	6,	23,	22);
      AddCsp(	19,	1,	3,	2,	19,	18);
      AddCsp(	20,	2,	3,	2,	35,	34);
      AddCsp(	21,	2,	7,	6,	39,	38);
      AddCsp(	22,	2,	12,	13,	44,	45);
      AddCsp(	23,	2,	8,	9,	40,	41);
      // T4 	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	24,	0,	8,	9,	8,	9);
      AddCsp(	25,	0,	12,	13,	12,	13);
      AddCsp(	26,	0,	7,	6,	7,	6);
      AddCsp(	27,	0,	3,	2,	3,	2);
      AddCsp(	28,	3,	3,	2,	51,	50);
      AddCsp(	29,	3,	7,	6,	55,	54);
      AddCsp(	30,	3,	12,	13,	60,	61);
      AddCsp(	31,	3,	8,	9,	56,	57);
    }
  else
    {
      // T1  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	0,	1,	10,	11,	26,	27);
      AddCsp(	1,	1,	14,	15,	30,	31);
      AddCsp(	2,	1,	5,	4,	21,	20);
      AddCsp(	3,	1,	1,	0,	17,	16);
      AddCsp(	4,	2,	1,	0,	33,	32);
      AddCsp(	5,	2,	5,	4,	37,	36);
      AddCsp(	6,	2,	14,	15,	46,	47);
      AddCsp(	7,	2,	10,	11,	42,	43);
      // T2  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	8,	0,	8,	9,	8,	9); 
      AddCsp(	9,	0,	12,	13,	12,	13);
      AddCsp(	10,	0,	7,	6,	7,	6); 
      AddCsp(	11,	0,	3,	2,	3,	2); 
      AddCsp(	12,	3,	3,	2,	51,	50);
      AddCsp(	13,	3,	7,	6,	55,	54);
      AddCsp(	14,	3,	12,	13,	60,	61);
      AddCsp(	15,	3,	8,	9,	56,	57);
      // T3  	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	16,	1,	8,	9,	24,	25);
      AddCsp(	17,	1,	12,	13,	28,	29);
      AddCsp(	18,	1,	7,	6,	23,	22);
      AddCsp(	19,	1,	3,	2,	19,	18);
      AddCsp(	20,	2,	3,	2,	35,	34);
      AddCsp(	21,	2,	7,	6,	39,	38);
      AddCsp(	22,	2,	12,	13,	44,	45);
      AddCsp(	23,	2,	8,	9,	40,	41);
      // T4 	csp	chip	chHi	chLo	numHi	numLo
      AddCsp(	24,	0,	10,	11,	10,	11);
      AddCsp(	25,	0,	14,	15,	14,	15);
      AddCsp(	26,	0,	5,	4,	5,	4); 
      AddCsp(	27,	0,	1,	0,	1,	0); 
      AddCsp(	28,	3,	1,	0,	49,	48);
      AddCsp(	29,	3,	5,	4,	53,	52);
      AddCsp(	30,	3,	14,	15,	62,	63);
      AddCsp(	31,	3,	10,	11,	58,	59);
    }
} 

//void
//Mapper::GeomToAFL(int startZ, int endZ, int startX, int endX, int rcuZ, int rcuX)
//{
//  
//
//}

inline int 
Mapper::Geo2hid(int mod, int gain, int row, int col)
{ 
  return mod*100000+gain*10000+row*100+col; 
}

inline int 
Mapper::Hid2mod(int hid)	
{ 
  return hid/100000;		
}


inline int 
Mapper::Hid2gain(int hid)	
{ 
  return (hid/10000)%10;	
}

inline int 
Mapper::Hid2row(int hid)	
{ 
  return (hid/100)%100;		
}

inline int 
Mapper::Hid2col(int hid)	
{ 
  return hid%100;  
}

////////////////////////////////////////////////////////////////////////
// ALTRO mapping first time initialization (do it once in startup time).
////////////////////////////////////////////////////////////////////////



void 
//Mapper::initAltroMapping(int saveMapping=0)
//       initAltroMapping(int)'
Mapper::InitAltroMapping(int saveMapping, ModNumber_t modID)
{
  //
  // Init CSP mapping first.
  //
  InitAltroCspMapping(modID);
  //

  // Clear index arrays
  //
  for(int m=0; m<PHOS_MODS; m++)
    for(int g=0; g<PHOS_GAINS;g++)
      for(int r=0; r < N_XCOLUMNS_MOD; r++)
	for(int c=0; c < N_ZROWS_MOD; c++)
	  {	
	    geo2hdw[m][g][r][c]=-1; 
	  }
  
  for(int m=0; m<PHOS_MODS;   m++)
    for(int r=0; r< RCUS_PER_MODULE;    r++)
      for(int b=0; b< BRANCHES_PER_RCU; b++)
	for(int f=0; f< CARDS_PER_BRANCH;    f++)
	  for(int a=0; a< ALTROS_PER_FEE ;  a++)
	    for(int c=0; c< CHANNELS_PER_ALTRO;   c++)
	      { 
		hdw2geo[m][r][b][f][a][c]=-1; 
	      }
  //
  // Fill all FEE cards via formula 
  // Be aware of crazyness! When we talk of rows and columns here it is oppisite of what is defined in 
  // the module
  //
  int index=0;
  for(int m=0; m < PHOS_MODS;   m++)
    for(int r=0; r< RCUS_PER_MODULE;    r++)
      for(int b=0; b< BRANCHES_PER_RCU; b++)
	for(int f=0; f< CARDS_PER_BRANCH;    f++)
	  for(int a=0; a< ALTROS_PER_FEE ;  a++)
	    for(int c=0; c< CHANNELS_PER_ALTRO;   c++)
	      {
		//		int row  = (r/2)*32 + b*16 + CSP_MAP[a][c].row;
		//		int col  = (r%2)*28 + f*2  + CSP_MAP[a][c].col;
		int row  = r*N_XCOLUMNS_MOD/RCUS_PER_MODULE + CSP_MAP[a][c].row; // New RCU geometrical configuration
		int col  = b*CARDS_PER_BRANCH*2 + f*2  + CSP_MAP[a][c].col; // New RCU geometrical configuration
 		int gain = CSP_MAP[a][c].gain;
		int csp  = CSP_MAP[a][c].csp;
		int num  = CSP_MAP[a][c].num;
		ALTRO_MAP[index].mod=m;
		ALTRO_MAP[index].row=row;
		ALTRO_MAP[index].col=col;
		ALTRO_MAP[index].gain=gain;
		ALTRO_MAP[index].rcu=r;
		ALTRO_MAP[index].branch=b;
		ALTRO_MAP[index].card=f;
		ALTRO_MAP[index].chip=a;
		ALTRO_MAP[index].chan=c;
		ALTRO_MAP[index].csp=csp;
		ALTRO_MAP[index].num=num;
		ALTRO_MAP[index].hid=Geo2hid(m,gain,row,col);
		hdw2geo[m][r][b][f][a][c]=index;

		if((row>=0)&&(row<  N_XCOLUMNS_MOD ))
		    if((col>=0)&&(col<  N_ZROWS_MOD ))
			if((gain>=0)&&(gain< PHOS_GAINS)) 
			  {
			    geo2hdw[m][gain][row][col]=index;
			  }
		index++;
	      }
  //
  // Check if geo2hdw map table is filled
  //
  for(int m=0; m< PHOS_MODS; m++)
    for(int g=0; g< PHOS_GAINS;g++)
      for(int r=0; r < N_XCOLUMNS_MOD; r++)
	for(int c=0; c < N_ZROWS_MOD; c++) 
	  {
	    //	    cout << "Module: " << m << " - Gain: " << g << " - X: " << r << " - Z: " << c << " - index: ";
	    // cout << geo2hdw[m][g][r][c] << endl;
	    assert(geo2hdw[m][g][r][c] >= 0);
	  }
  //
  // Check if hdw2geo map table is filled
  //
  for(int m=0; m< PHOS_MODS;   m++)
    for(int r=0; r< RCUS_PER_MODULE;    r++)
      for(int b=0; b< BRANCHES_PER_RCU; b++)
	for(int f=0; f< CARDS_PER_BRANCH;    f++)
	  for(int a=0; a< ALTROS_PER_FEE ;  a++)
	    for(int c=0; c< CHANNELS_PER_ALTRO;   c++) 
	      {
		assert(hdw2geo[m][r][b][f][a][c] >= 0);
	      }
}

////////////////////////////////////////////////////////////////////////
// Return histogramm id from histogramm name or -1 on error.
// extractHid("hMax011426")=11426;
////////////////////////////////////////////////////////////////////////
inline int 
Mapper::ExtractHid(char *objName){
  char *perr=NULL;
  if(strlen(objName)<7) return -1;
  int hid=strtol(&objName[strlen(objName)-6],&perr,10);
  if(strlen(perr))return -1;
  return hid;
}

////////////////////////////////////////////////////////////////////////
// Print geometry and hardware information for given histogramm
// printHistMapInfo("hMax011426");
// hid     mod     gain    row     col     rcu     bran    fee     chip    chan    csp     num
// 011426  0       1       14      26      0       0       13      3       14      14      62
////////////////////////////////////////////////////////////////////////
inline void 
Mapper::PrintHistMapInfo(char *objName){
  int hid=ExtractHid(objName);
  if(hid>=0){
    int mod=Hid2mod(hid);
    int gain=Hid2gain(hid);
    int row=Hid2row(hid);
    int col=Hid2col(hid);
    int index=geo2hdw[mod][gain][row][col]; assert(index>=0);
    int rcu  = ALTRO_MAP[index].rcu;
    int bran = ALTRO_MAP[index].branch;
    int fec  = ALTRO_MAP[index].card;
    int chip = ALTRO_MAP[index].chip;
    int chan = ALTRO_MAP[index].chan;
    int csp  = ALTRO_MAP[index].csp;
    int num  = ALTRO_MAP[index].num;
    printf("%s attributes:\nhid\tmod\tgain\trow\tcol\trcu\tbran\tfee\tchip\tchan\tcsp\tnum\n",objName);
    printf("%06d\t%d\t%d\t%02d\t%02d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",hid,mod,gain,row,col,rcu,bran,fec,chip,chan,csp,num);
  }
}
