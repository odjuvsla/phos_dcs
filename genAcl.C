#include "src/Mapper.h"
#include "src/PhosConst.h"

void InitAltroMapping ( int t = 0 );
void InitAltroCspMapping();

struct FEE_CSP_MAP
  {
    int row;
    int col;
    int gain;
    int csp;
    int num;
  };

struct ALTRO_GEO_MAP
  {
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

int Geo2hid ( int mod, int gain, int row, int col )
{
  return mod*100000+gain*10000+row*100+col;
}

FEE_CSP_MAP CSP_MAP[ALTROS_PER_FEE ][CHANNELS_PER_ALTRO];
void AddCsp ( int csp, int chip, int chHi, int chLo, int numHi, int numLo )
{
  // Find row & col by CSP
  int col = csp / 16;
  int row = csp % 16;
  //In 2004 beam test was also: if(row>7)row=23-row;
  // Check if arguments Ok
  assert ( ( col>=0 ) && ( col<2 ) );
  assert ( ( row>=0 ) && ( row<16 ) );
  assert ( ( csp>=0 ) && ( csp<32 ) );
  assert ( ( numHi>=0 ) && ( numHi<64 ) );
  assert ( ( numLo>=0 ) && ( numLo<64 ) );
  assert ( ( chHi>=0 ) && ( chHi < N_ZROWS_MOD <  CHANNELS_PER_ALTRO ) );
  assert ( ( chLo>=0 ) && ( chLo <  CHANNELS_PER_ALTRO ) );
  assert ( ( chip>=0 ) && ( chip <  ALTROS_PER_FEE ) );
  // Fill CSP array
  CSP_MAP[chip][chHi].row=row;
  CSP_MAP[chip][chLo].row=row;
  CSP_MAP[chip][chHi].col=col;
  CSP_MAP[chip][chLo].col=col;
  CSP_MAP[chip][chHi].gain=1;
  CSP_MAP[chip][chLo].gain=0;
  CSP_MAP[chip][chHi].csp=csp;
  CSP_MAP[chip][chLo].csp=csp;
  CSP_MAP[chip][chHi].num=numHi;
  CSP_MAP[chip][chLo].num=numLo;
}


int hdw2geo[ PHOS_MODS][ RCUS_PER_MODULE][  BRANCHES_PER_RCU][ CARDS_PER_BRANCH][ALTROS_PER_FEE][CHANNELS_PER_ALTRO];
int geo2hdw[ PHOS_MODS][ PHOS_GAINS][ N_XCOLUMNS_MOD][ N_ZROWS_MOD];
ALTRO_GEO_MAP ALTRO_MAP[ PHOS_MODS * RCUS_PER_MODULE *  BRANCHES_PER_RCU * CARDS_PER_BRANCH *ALTROS_PER_FEE *CHANNELS_PER_ALTRO];

int index = 0;

int genAcl()
{

  InitAltroMapping();
  int rcu = 99;
  int branch = 99;
  int card = 99;;
  int altro = 99;
  int channel = 99;
  int csp = 99;
  int modID = 1;

  ofstream asciifile ( "acl.txt" );

  for ( int i = 0; i <  28; i++ )
    {
      for ( int j = 0; j < 32; j++ )
        {
          index = geo2hdw[modID][1][j][i];
          rcu = ALTRO_MAP[index].rcu;
          branch = ALTRO_MAP[index].branch;
          card = ALTRO_MAP[index].card;
          altro = ALTRO_MAP[index].chip;
          channel = ALTRO_MAP[index].chan;
          csp = ALTRO_MAP[index].csp;

          if ( altro > 0 )
            {
              altro = altro + 1; //to fix bug in mp
            }

          ///OLD RCU FIRMWARE
          // aclIndex = branch*128+(card +1)*8+altro;
          // acl[rcu][aclIndex] =  acl[rcu][aclIndex] | 1<<channel;


          // NEW RCU FIRMWARE
          // altro channel relative to one FEE

          unsigned long tmpGlobalFeeChannel = altro*CHANNELS_PER_ALTRO + channel;
          asciifile << hex << ( ( branch << 11 )  | ( ( card+1 ) << 7 ) | ( tmpGlobalFeeChannel ) ) << endl;;


          index = geo2hdw[modID][0][j][i];
          rcu = ALTRO_MAP[index].rcu;
          branch = ALTRO_MAP[index].branch;
          card = ALTRO_MAP[index].card;
          altro = ALTRO_MAP[index].chip;
          channel = ALTRO_MAP[index].chan;
          csp = ALTRO_MAP[index].csp;

          if ( altro > 0 )
            {
              altro = altro + 1; //to fix bug in mp
            }

          ///OLD RCU FIRMWARE
          // aclIndex = branch*128+(card +1)*8+altro;
          // acl[rcu][aclIndex] =  acl[rcu][aclIndex] | 1<<channel;


          // NEW RCU FIRMWARE
          // altro channel relative to one FEE

          unsigned long tmpGlobalFeeChannel = altro*CHANNELS_PER_ALTRO + channel;
          asciifile << hex << ( ( branch << 11 )  | ( ( card+1 ) << 7 ) | ( tmpGlobalFeeChannel ) ) << endl;;

        }
    }

  return 0;
}

void InitAltroMapping ( int saveMapping )
{
  //
  // Init CSP mapping first.
  //
  InitAltroCspMapping();
  //

  // Clear index arrays
  //
  for ( int m=0; m<PHOS_MODS; m++ )
    for ( int g=0; g<PHOS_GAINS;g++ )
      for ( int r=0; r < N_XCOLUMNS_MOD; r++ )
        for ( int c=0; c < N_ZROWS_MOD; c++ )
          {
            geo2hdw[m][g][r][c]=-1;
          }

  for ( int m=0; m<PHOS_MODS;   m++ )
    for ( int r=0; r< RCUS_PER_MODULE;    r++ )
      for ( int b=0; b< BRANCHES_PER_RCU; b++ )
        for ( int f=0; f< CARDS_PER_BRANCH;    f++ )
          for ( int a=0; a< ALTROS_PER_FEE ;  a++ )
            for ( int c=0; c< CHANNELS_PER_ALTRO;   c++ )
              {
                hdw2geo[m][r][b][f][a][c]=-1;
              }
  //
  // Fill all FEE cards via formula
  //
  int index=0;
  for ( int m=0; m < PHOS_MODS;   m++ )
    for ( int r=0; r< RCUS_PER_MODULE;    r++ )
      for ( int b=0; b< BRANCHES_PER_RCU; b++ )
        for ( int f=0; f< CARDS_PER_BRANCH;    f++ )
          for ( int a=0; a< ALTROS_PER_FEE ;  a++ )
            for ( int c=0; c< CHANNELS_PER_ALTRO;   c++ )
              {
                int row  = ( r/2 ) *32 + b*16 + CSP_MAP[a][c].row;
                int col  = ( r%2 ) *28 + f*2  + CSP_MAP[a][c].col;
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
                ALTRO_MAP[index].hid=Geo2hid ( m,gain,row,col );
                hdw2geo[m][r][b][f][a][c]=index;
                if ( ( row>=0 ) && ( row<  N_XCOLUMNS_MOD ) )
                  if ( ( col>=0 ) && ( col<  N_ZROWS_MOD ) )
                    if ( ( gain>=0 ) && ( gain< PHOS_GAINS ) ) geo2hdw[m][gain][row][col]=index;
                index++;
              }

  //
  // Check if geo2hdw map table is filled
  //
  for ( int m=0; m< PHOS_MODS; m++ )
    for ( int g=0; g< PHOS_GAINS;g++ )
      for ( int r=0; r < N_XCOLUMNS_MOD; r++ )
        for ( int c=0; c < N_ZROWS_MOD; c++ )
          {
            assert ( geo2hdw[m][g][r][c] >= 0 );
          }
  //
  // Check if hdw2geo map table is filled
  //
  for ( int m=0; m< PHOS_MODS;   m++ )
    for ( int r=0; r< RCUS_PER_MODULE;    r++ )
      for ( int b=0; b< BRANCHES_PER_RCU; b++ )
        for ( int f=0; f< CARDS_PER_BRANCH;    f++ )
          for ( int a=0; a< ALTROS_PER_FEE ;  a++ )
            for ( int c=0; c< CHANNELS_PER_ALTRO;   c++ )
              {
                assert ( hdw2geo[m][r][b][f][a][c] >= 0 );
              }
}

void InitAltroCspMapping()
{
  // T1	csp	chip	chHi	chLo	numHi	numLo
  AddCsp (	0,	1,	10,	11,	26,	27 );
  AddCsp (	1,	1,	14,	15,	30,	31 );
  AddCsp (	2,	1,	5,	4,	21,	20 );
  AddCsp (	3,	1,	1,	0,	17,	16 );
  AddCsp (	4,	2,	1,	0,	33,	32 );
  AddCsp (	5,	2,	5,	4,	37,	36 );
  AddCsp (	6,	2,	14,	15,	46,	47 );
  AddCsp (	7,	2,	10,	11,	42,	43 );
  // T2	csp	chip	chHi	chLo	numHi	numLo
  AddCsp (	8,	0,	10,	11,	10,	11 );
  AddCsp (	9,	0,	14,	15,	14,	15 );
  AddCsp (	10,	0,	5,	4,	5,	4 );
  AddCsp (	11,	0,	1,	0,	1,	0 );
  AddCsp (	12,	3,	1,	0,	49,	48 );
  AddCsp (	13,	3,	5,	4,	53,	52 );
  AddCsp (	14,	3,	14,	15,	62,	63 );
  AddCsp (	15,	3,	10,	11,	58,	59 );
  // T3	csp	chip	chHi	chLo	numHi	numLo
  AddCsp (	16,	1,	8,	9,	24,	25 );
  AddCsp (	17,	1,	12,	13,	28,	29 );
  AddCsp (	18,	1,	7,	6,	23,	22 );
  AddCsp (	19,	1,	3,	2,	19,	18 );
  AddCsp (	20,	2,	3,	2,	35,	34 );
  AddCsp (	21,	2,	7,	6,	39,	38 );
  AddCsp (	22,	2,	12,	13,	44,	45 );
  AddCsp (	23,	2,	8,	9,	40,	41 );
  // T4	csp	chip	chHi	chLo	numHi	numLo
  AddCsp (	24,	0,	8,	9,	8,	9 );
  AddCsp (	25,	0,	12,	13,	12,	13 );
  AddCsp (	26,	0,	7,	6,	7,	6 );
  AddCsp (	27,	0,	3,	2,	3,	2 );
  AddCsp (	28,	3,	3,	2,	51,	50 );
  AddCsp (	29,	3,	7,	6,	55,	54 );
  AddCsp (	30,	3,	12,	13,	60,	61 );
  AddCsp (	31,	3,	8,	9,	56,	57 );
}
