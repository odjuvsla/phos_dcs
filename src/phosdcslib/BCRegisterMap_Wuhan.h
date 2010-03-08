#ifndef BCREGISTERMAP_H
#define BCREGISTERMAP_H
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

// Register  Itnerface for the Bergen boar controller (BC),  PHOS BC specification_v3.4
// Thsi definition file describes egisters that can be accessed externally. Note:
// The registers marked with
//���R(W)��� and Broadcast ���Yes*��� can be written to when unlock bit (register 0x0)is set.
// T = write trigger (no physical register)

namespace BCRegisterMap
  {
//Register name                      Addr.   range      Type       Allow Brcast    Description

  const unsigned long  UNLOCK       = 0x0;   //[1:0]      RW         Yes            One bit unlock register for writing to read
  //                                                                                only regs for testing.
  //                                                                                0: Locked
  //                                                                                1: Unlocked
  const unsigned long  L0CNT        = 0x0B;  //[15:0]      R(W)      Yes*           Number of L0 triggers received
  const unsigned long  L2CNT        = 0x0C;  //[15:0]      R(W)      Yes*           Number of L2a triggers received
  const unsigned long  SCLKCNT      = 0x0D;  //[15:0]      R(W)      Yes*           Sampling clock counter
  const unsigned long  SLOWCTR_ERR  = 0x0E;  //[7:0]       R         No             Number of timeout situations in Slow Control

  /**CSR0 interface*/
  const unsigned long  CSR0         = 0x11;  //[11:0]      RW        Yes            Interrupt Mask Register:
  const unsigned long  HV_UM        = 11;                            //             Default value = 0x1FF
  //   [11]      HV Update Mode.
  //             0 = The BC updates DAC with
  //             update_hv command.
  //             1 = The BC continuously updates DACs
  const unsigned long  CONV_MOD     = 10;                            //   [10]      Conversion Mode.//             0 = The BC reads the content of
  //             the monitor ADC with the STCNV
  //             command (1B)
  //             1 = monitor ADC converts continuously
  const unsigned long  ERR_MASK     = 8;                             //   [9:8]     Error Mask. These two bits
  //             mask the assertion of the Error
  //             line. This line is asserted with the
  //             flags registered in CSR1[9:8]
  //             0 = the error is masked
  //             1 = the error asserts the line
  const unsigned long  INT_MASK     = 0;                             //   [7:0]     Interrupt Mask. These bits mask
  //             the bits of CSR1 [7:0] for the
  /**CSR1 interface*/                                                                   //             assertion of the Interrupt line
  const unsigned long  CSR1          = 0x12; //[13:0]      R         N/A            Error Status Register: Default value = 0x0000
  const unsigned long  SC_INTVAL     = 13;                           //   [13]      Value of Slow Control Interrupt line
  const unsigned long  ALTRO_BE      = 12;                           //   [12]      Value of ALTRO bus Error line
  const unsigned long  SC_INSTERR    = 11;                           //   [11]      Slow Control Instruction Error
  const unsigned long  ALTRO_ERR     = 10;                           //   [10]      ALTRO error: Registered value of ALTRO bus error line
  const unsigned long  ALTRO_IERR    = 9;                            //   [9]       ALTRO bus Instruction Error (to BC)
  const unsigned long  ALTRO_PARERR  = 8;                            //   [8]       Parity error of ALTRO bus 20 MSB
  const unsigned long  MISS_SCLK     = 7;                            //   [7]       Missing Sampling Clock
  const unsigned long  ALTRO_PE      = 6;                            //   [6]       ALTRO Power, Digital 4.2V & 3.3V and Bias Supply Error
  const unsigned long  SHAPER_PE     = 5;                            //   [5]       Shaper +6.0V Power Supply Error
  const unsigned long  DIG_CURROTH   = 4;                            //   [4]       4.2 V or 3.3 V digital current is higher than thresholds.
  const unsigned long  DIG_VOLOTH    = 3;                            //   [3]       4.2 V or 3.3 V digital voltage is lower than thresholds.
  const unsigned long  ANA_CURROTH   = 2;                            //   [2]       4.0 V, +6.0 V, -6.0 V, 13.5 V analog current higher than threshold.
  const unsigned long  ANA_CVOLOTH   = 1;                            //   [1]       4.0 V, +6.0 V, -6.0 V, 13.5 V analog voltage lower than threshold.
  const unsigned long  TEMPOTH       = 0;                            //   [0]       Temp1, Temp2 or Temp3 higher than threshold.

  /**CSR2 interface*/
  const unsigned long  CSR2          = 0x13; // [15:0]     RW        Yes            Status and Configuration Default value = 0x013F
  const unsigned long  HARD_ADDR     = 11;                           //   [15:11]   Hardware Address (read only)
  const unsigned long  CARD_ISOL     = 10;                           //   [10]      Card Isolated
  const unsigned long  ADC_NVIOL_THR = 8;                            //   [9:8]     Number of times a ADC threshold violation must occur before it is reported
  //   [7]       Not Used
  const unsigned long  HAMMING_EN    = 6;                            //   [6]       Enables Hamming correction on HVDAC values and Thresholds.
  const unsigned long  DACCLCK_EN    = 5;                            //   [5]       Enables DAC clock
  const unsigned long  SCLCK_EN      = 4;                            //   [4]       Enables Sampling Clock
  const unsigned long  RDOCLCK_EN    = 3;                            //   [3]       Enables Readout Clock
  const unsigned long  SP_SWITCH     = 2;                            //   [2]       Power Switch for Shaper Power Regulator
  const unsigned long  BIASP_SWITCH  = 1;                            //   [1]       Power switch for Bias Power Regulator
  const unsigned long  ALTROP_SWITCH = 0;                            //   [0]       Power switch for ALTRO Power Regulator

  /**CSR2 interface*/
  const unsigned long  CSR3          = 0x14; // [15:0]     RW        Yes            Status and Configuration Default value = 0x2220
  const unsigned long  BCTR_COMPL    = 15;                           //   [15]      This bit is set to 1 when the BC has completed the transaction
  //             with the mADC. It is reset at the beginning of every transaction.
  const unsigned long  SCEVL_TOUT    = 8;                            //   [14:8]    Scevl timeout value. Max num of clks for each transaction on the
  //             ALTRO bus when BC is master.
  const unsigned long  CLK_WRATIO    = 0;                            //   [7:0]     rdclk / sclk warning ratio
  const unsigned long  DEBUG         = 0x15;  // [1:0]     R         No   [1]       Value of Slow Control data line
  //   [0]       Value of test_mg input

  const unsigned long  CNTLAT        = 0x16;  //           T         Yes            Latch L0, L2, SCLK counters
  const unsigned long  CNTCLR        = 0x17;  //           T         Yes            Clear L0, L2, SCLK counters
  const unsigned long  CSR1CLR       = 0x18;  //           T         Yes            Clear Error Status Register
  const unsigned long  ALRST         = 0x19;  //           T         Yes            Reset all the ALTROs
  const unsigned long  BCRST         = 0x1A;  //           T         Yes            Reset Board Controller to default values
  const unsigned long  STCNV         = 0x1B;  //           T         Yes            Start Conversion / Readout monitor ADC
  const unsigned long  SCEVL         = 0x1C;  //           T         Yes            Scan Event-length registers in all ALTRO channels
  const unsigned long  EVLRDO        = 0x1D;  //           T         Yes            Start readout of Event Length Hitmap register.
  const unsigned long  UPDATEHV      = 0x1E;  //           T         Yes            Update HV
  const unsigned long  BCVERSION     = 0x70;  // [15:0]    R         N/A            Board Controller Version

  /*VTS_HIGH interface*/
  const unsigned long  VTS_HIGH      = 0x21;   // [14:0]   R(W)      Yes*           Voltage Temperature Status register:
  const unsigned long  TEMP1_OTHR    = 0;                            //   [0]       TEMP1 over th
  const unsigned long  D4V0_OTHR     = 1;                            //   [1]       D4V0 over th
  const unsigned long  D4V0C_OTHR    = 2;                            //   [2]       D4V0C over th
  const unsigned long  D3V3_OTHR     = 3;                            //   [3]       D3V3 over th
  const unsigned long  D3V3C_OTHR    = 4;                            //   [4]       D3V3C over th
  const unsigned long  TEMP2_OTHR    = 5;                            //   [5]       TEMP2 over th
  const unsigned long  A6nV0_OTHR    = 6;                            //   [6]       A6nV0 over th
  const unsigned long  A6nV0C_OTHR   = 7;                            //   [7]       A6nV0C over th
  const unsigned long  A6pV0_OTHR    = 8;                            //   [8]       A6pV0 over th
  const unsigned long  A6pV0C_OTHR   = 9;                            //   [9]       A6pV0C over th
  const unsigned long  TEMP3_OTHR    = 10;                           //   [10]      TEMP3 over th
  const unsigned long  A3V3_OTHR     = 11;                           //   [11]      A3V3 over th
  const unsigned long  A3V3C_OTHR    = 12;                           //   [12]      A3V3C over th
  const unsigned long  A13V0_OTHR    = 13;                           //   [13]      A13V0 over th
  const unsigned long  A13V0C_OTHR   = 14;                           //   [14]      A13V0C over th

  /*VTS_LOW interface*/
  const unsigned long  VTS_LOW       = 0x22;   // [14:0]   R(W)      Yes*           Voltage Temperature Status register:
  const unsigned long  TEMP1_UTHR    = 0;                            //   [0]       TEMP1 under th
  const unsigned long  D4V0_UTHR     = 1;                            //   [1]       D4V0 under th
  const unsigned long  D4V0C_UTHR    = 2;                            //   [2]       D4V0C under th
  const unsigned long  D3V3_UTHR     = 3;                            //   [3]       D3V3 under th
  const unsigned long  D3V3C_UTHR    = 4;                            //   [4]       D3V3C under th
  const unsigned long  TEMP2_UTHR    = 5;                            //   [5]       TEMP2 under th
  const unsigned long  A6nV0_UTHR    = 6;                            //   [6]       A6nV0 under th
  const unsigned long  A6nV0C_UTHR   = 7;                            //   [7]       A6nV0C under th
  const unsigned long  A6pV0_UTHR    = 8;                            //   [8]       A6pV0 under th
  const unsigned long  A6pV0C_UTHR   = 9;                            //   [9]       A6pV0C under th
  const unsigned long  TEMP3_UTHR    = 10;                           //   [10]      TEMP3 under th
  const unsigned long  A3V3_UTHR     = 11;                           //   [11]      A3V3 under th
  const unsigned long  A3V3C_UTHR    = 12;                           //   [12]      A3V3C under th
  const unsigned long  A13V0_UTHR    = 13;                           //   [13]      A13V0 under th
  const unsigned long  A13V0C_UTHR   = 14;                           //   [14]      A13V0C under th
  /*********************/

  const unsigned long  TH_HMGERR_HIG = 0x23;   // [14:0]   R(W)      Yes*           Double hamming errors found in ADC   high threshold memory .
  const unsigned long  TH_HMGERR_LOW = 0x24;   // [14:0]   R(W)      Yes*           Double hamming errors found in ADC low threshold memory.
  const unsigned long  HV_FB1        = 0x25;   // [15:0]   R(W)      Yes*           Compared outputs from DAC for CSP
  // [7:0]                             CSP 16  %G�–%@ CSP 23
  // [15:8]                            CSP 7 %G�–%@ CSP 0
  //                                   0: DAC not set/Wrong
  //                                   1: DAC set/Correct
  const unsigned long HV_FB2         = 0x26;   // [15:0]   R(W)      Yes*           Compared outputs from DAC for CSP
  //                                   [7:0] CSP 15 %G�–%@ CSP 8
  //                                   [15:8] CSP 24 %G�–%@ CSP 31
  //                                   0: DAC not set/Wrong
  //                                   1: DAC set/Correct
  const unsigned long HV_HVHMGERR1   = 0x27;   // [15:0]   R(W)      Yes*           Double hamming errors for the following:
  //                                   [7:0]  CSP 16 %G�–%@ CSP 23
  //                                   [15:8] CSP 7 %G�–%@ CSP 0
  const unsigned long HV_HVHMGERR2   = 0x28;   // [15:0]   R(W)      Yes*           Double hamming errors for the following:
  //                                   [7:0] CSP 15 %G�–%@ CSP 8
  //                                   [15:8] CSP 24 %G�–%@ CSP 31
  const unsigned long ADC_DIFF       = 0x29;   // [14:0]   RW        Yes            Sets which ADC values that should be
  //                                   treated as currents in the ADC value and
  //                                   ADC threshold memory. In practice this is
  //                                   a diff between Vprev and Vcurrent Default Value: 0x5294

  const unsigned long ADC_DIFF_DIR   = 0x2A;   // [14:0]    R(W)      Yes*           Sets the expected direction of the current
  //                                   for the current measurements given by ADC_DIFF register.
  //                                   0: Current = Vpreviou - Vcurrent
  //                                   1: Current = Vcurrent %G�–%@ Vpreviou
  //                                   Default Value: 0x0080
  const unsigned long TRANS_CNT      = 0x2B;   // [15:0]   R         No             [15:8]   Number of acks sent to RCU
  //                                   [7:0]    Number of strobes received from RCU

  const unsigned long LAST_ADDR_MSB  = 0x2C;   // [7:0]    R         No             [7:4]    MSB of last valid address received.
  //                                   [3:0]    MSB of last not valid address received
  const unsigned long LAST_VALID_ADDR =0x2D;   // [15:0]   R         No             LSB of last valid address received at the FEC
  const unsigned long LAST_NOTVALID_ADDR = 0x2E;  //[15:0] R         No             LSB of the last not valid address received at the FEC.
  const unsigned long ADC_Min_Threshold[15] = {0x30,
      0x31,
      0x32,
      0x33,
      0x34,
      0x35,
      0x36,
      0x37,
      0x38,
      0x39,
      0x3A,
      0x3B,
      0x3C,
      0x3D,
      0x3E
                                              }; // [14:0] RW   Yes            Min Threshold for the ADCs
  //                            [15:11] Hamming code
  //                            [10]     0: Threshold for Voltage
  //                            1: Threshold for Current
  //                            [9:0]    Data value
  const unsigned long ADC_Max_Threshold[15] = {0x40,
      0x41,
      0x42,
      0x43,
      0x44,
      0x45,
      0x46,
      0x47,
      0x48,
      0x49,
      0x4A,
      0x4B,
      0x4C,
      0x4D,
      0x4E
                                              }; // [14:0] RW   Yes            Max Threshold for the ADCs
  //                            [15:11] Hamming code
  //                            [10] 0: Threshold for Voltage
  //                            1: Threshold for Current
  //                            [9:0]    Data value
  const unsigned long ADC_Data_mem[15]     = {0x50,
      0x51,
      0x52,
      0x53,
      0x54,
      0x55,
      0x56,
      0x57,
      0x58,
      0x59,
      0x5A,
      0x5B,
      0x5C,
      0x5D,
      0x5E
                                             };   // [9:0]
  //        RW   Yes            Data values from the ADCs


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
  0     1       |     CSP 0    CSP 16   |   0x68    0x67
  2     3       |     CSP 1    CSP 17   |   0x69    0x66
  4     5       |     CSP 2    CSP 18   |   0x6A    0x65
  6     7       |     CSP 3    CSP 19   |   0x6B    0x64
  8     9       |     CSP 4    CSP 20   |   0x6C    0x63
  10    11      |     CSP 5    CSP 21   |   0x6D    0x62
  12    13      |     CSP 6    CSP 22   |   0x6E    0x61
  14    15      |     CSP 7    CSP 23   |   0x6F    0x60
  16    17      |     CSP 8    CSP 24   |   0x70    0x7F
  18    19      |     CSP 9    CSP 25   |   0x71    0x7E
  20    21      |     CSP 10   CSP 26   |   0x72    0x7D
  22    23      |     CSP 11   CSP 27   |   0x73    0x7C
  24    25      |     CSP 12   CSP 28   |   0x74    0x7B
  26    27      |     CSP 13   CSP 29   |   0x75    0x7A
  28    29      |     CSP 14   CSP 30   |   0x76    0x79
  30    31      |     CSP 15   CSP 31   |   0x77    0x78
  */
  const unsigned long HV_DAC_settings[32]  = {0x48,
      0x47,
      0x49,
      0x46,
      0x4A,
      0x45,
      0x4B,
      0x44,
      0x4C,
      0x43,
      0x4D,
      0x42,
      0x4E,
      0x41,
      0x4F,
      0x40,
      0x50,
      0x5F,
      0x51,
      0x5E,
      0x52,
      0x5D,
      0x53,
      0x5C,
      0x54,
      0x5B,
      0x55,
      0x5A,
      0x56,
      0x59,
      0x57,
      0x58
                                             };//[14:0]    RW   Yes            High voltage bias value for CSPs
  //                              0x60-0x67: CSP 23 down to CSP 16
  //                              0x68-0x6F: CSP 0 to CSP 7
  //                              0x70-0x77: CSP 8 to CSP 15
  //                              0x78-0x7F: CSP 31 down to CSP 24
  //                              [15:11] Hamming code
  //                              [10]     Don���t care (not used)
  //                              [9:0]    Value to Write


  /*** Sensor tresholds ***/
  const unsigned long TEMP1_MIN_TH  = 0x30; //                                      Minimum Temperature Threshold for ADC IC13
  //                                      Default Data Value: 0x0 (disabled)
  const unsigned long D4V0_MIN_TH   = 0x31; //                                      Minimum 4.0V Digital Voltage Threshold
  //                                      Default Data Value: 0x1D8 (= 3.8 V)
  const unsigned long D4V0C_MIN_TH  = 0x32; //                                      Minimum 4.0V Digital Current Threshold
  //                                      Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc.

  const unsigned long D3V3_MIN_TH   = 0x33; //                                      Minimum 3.3V Digital Voltage Threshold
  //                                      Default Data Value: 0x1C2 (= 2.9 V)

  const unsigned long D3V3C_MIN_TH  = 0x34; //                                      Minimum 3.3V Digital Current Threshold
  //                                      Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc.

  const unsigned long TEMP2_MIN_TH  = 0x35; //                                      Minimum Temperature Threshold for ADC IC15
  //                                      Default Value: 0x0 (disabled)

  const unsigned long A6nV0_MIN_TH  = 0x36; //                                      Minimum -6.0V Analog Voltage Threshold
  //                                      Default Data Value: 0x170 (= -6.4 V)
  const unsigned long A6nV0C_MIN_TH = 0x37; //                                      Minimum -6.0V Analog Current Threshold
  //                                      Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long A6pV0_MIN_TH  = 0x38; //                                      Minimum 6.0V Analog Voltage Threshold
  //                                      Default Data Value: 0x1E8 (= 5.6 V)
  const unsigned long A6pV0C_MIN_TH = 0x39; //                                      Minimum 6.0V Analog Current Threshold
  //                                      Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long TEMP3_MIN_TH  = 0x3A; //                                      Minimum Temperature Threshold for ADC IC14
  //                                      Default Value: 0x0 (disabled)
  const unsigned long A3V3_MIN_TH   = 0x3B; //                                      Minimum. 3.3V Analog Voltage Threshold
  //                                      Default Value: 0x1C2 (= 2.9 V)
  const unsigned long A3V3C_MIN_TH  = 0x3C; //                                      Minimum 3.3V Analog Current Threshold
  //	                                    Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc
  const unsigned long A13V0_MIN_TH  = 0x3D; //                                      Minimum 13.0V Analog Voltage Threshold
  //                                      Default Value: 0x1D6 (= 12.6 V)
  const unsigned long A13V0C_MIN_TH = 0x3E; //                                      Minimum 13.0V Analog Current Threshold
  //                                      Default Value: 0x0 (disabled)
  //                                      Alternatively Voltage level used for current calc
  const unsigned long TEMP1_MAX_TH  = 0x40; //                                      Maximum Temperature Threshold for ADC IC13
  //                                      Default Data Value: 0xA0 (= 40��C)
  const unsigned long D4V0_MAX_TH   = 0x41; //                                      Maximum 4.0V Digital Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long D4V0C_MAX_TH  = 0x42; //                                      Maximum 4.0V Digital Current Threshold
  //                                      Default Value: 0x00C (=0.36 A)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long D3V3_MAX_TH   = 0x43; //                                      Maximum 3.3V Digital Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long D3V3C_MAX_TH  = 0x44; //                                      Maximum 3.3V Digital Current Threshold
  //                                      Default Value: 0x011 (= 0.73 A)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long TEMP2_MAX_TH  = 0x45; //                                      Maximum Temperature Threshold for ADC IC15
  //                                      Default Data Value: 0xA0 (= 40��C)
  const unsigned long A6nV0_MAX_TH  = 0x46; //                                      Maximum -6.0V Analog Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long A6nV0C_MAX_TH = 0x47; //                                      Maximum -6.0V Analog Current Threshold
  //                                      Default Value: 0x00F (=0.44 A)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long A6pV0_MAX_TH  = 0x48; //                                      Maximum 6.0V Analog Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long A6pV0C_MAX_TH = 0x49; //                                      Maximum 6.0V Analog Current Threshold
  //                                      Default Value: 0x016 (= 0.764 A)
  //                                      Alternatively Voltage level used for current calc.
  const unsigned long TEMP3_MAX_TH  = 0x4A; //                                      Maximum Temperature Threshold for ADC IC14
  //                                      Default Data Value: 0xA0 (= 40��C)
  const unsigned long A3V3_MAX_TH   = 0x4B; //                                      Maximum. 3.3V Analog Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long A3V3C_MAX_TH  = 0x4C; //                                      Maximum 3.3V Analog Current Threshold
  //                                      Default value: 0x014 (= 0.858 A)
  //                                      Alternatively Voltage level used for current calc
  const unsigned long A13V0_MAX_TH  = 0x4D; //                                      Maximum 13.0V Analog Voltage Threshold
  //                                      Default Value: 0x0 (disabled)
  const unsigned long A13V0C_MAX_TH = 0x4E; //                                      Maximum 13.0V Analog Current Threshold
  //                                      Default Value: 0x00F (= 0.334 A)
  //                                      Alternatively Voltage level used for current calc

  /*** Temperatur current and voltage sensors ****/
  const unsigned long TEMP1         = 0x50; //                                      Temperature for ADC IC13  0.25��C   *  ADC counts
  const unsigned long D4V0          = 0x51; //                                      4.0V Digital Voltage      8.04mV   *  ADC counts
  const unsigned long D4V0C         = 0x52; //                                      4.0V Digital Current      29.8mA   *  ADC counts
  const unsigned long D3V3          = 0x53; //                                      3.3V Digital Voltage      6.44 mV  *  ADC counts
  const unsigned long D3V3C         = 0x54; //                                      3.3V Digital Current      42.9 mA  *  ADC counts
  const unsigned long TEMP2         = 0x55; //                                      Temperature for ADC IC15  0.25��C   *  ADC counts
  const unsigned long A6nV0         = 0x56; //                                      -6.0V Analog Voltage      4.88mV   *  ADC counts / 1000 -8.2V
  const unsigned long A6nV0C        = 0x57; //                                      -6.0V Analog Current      29.3mA   *  ADC counts
  const unsigned long A6pV0         = 0x58; //                                      6.0V Analog Voltage       11.4 mV  *  ADC counts   Default Data Value: 0x1E8 (= 5.6 V)
  const unsigned long A6pV0C        = 0x59; //                                      6.0V Analog Current       34.73 mA *  ADC counts
  const unsigned long TEMP3         = 0x5A; //                                      Temperature for ADC IC14  0.25��C   *  ADC counts
  const unsigned long A3V3          = 0x5B; //                                      3.3V Analog Voltage       6.44 mV  *  ADC counts
  const unsigned long A3V3C         = 0x5C; //                                      3.3V Analog Current       42.9 mA  *  ADC counts
  const unsigned long A13V0         = 0x5D; //                                      13.0V Analog Voltage      26.8 mV  *  ADC counts
  const unsigned long A13V0C        = 0x5E; //                                      13.0V Analog Current      22.3 mA  *  ADC counts
}


#endif

