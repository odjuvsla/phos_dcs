#ifndef ALTROREGISTERMAP_H
#define ALTROREGISTERMAP_H

/**** Regsiter Access ****
 * R = Read
 * W = Write
 * R/W = Read/Write
 * T = Write triggered command (write any value too this register to execute the corresponding command)
*/

namespace AltroRegisterMap
  {
  //name        address         width  access   Broadcast   Description
  /*************************/
  /* Per Channel Registers */
  /*************************/
  const unsigned long  K1         = 0x0;     //    16     R/W      Y           Filter Coefficient K1
  const unsigned long  K2         = 0x1;     //    16     R/W      Y           Filter Coefficient K2
  const unsigned long  K3         = 0x2;     //    16     R/W      Y           Filter Coefficient K3
  const unsigned long  L1         = 0x3;     //    16     R/W      Y           Filter Coefficient L1
  const unsigned long  L2         = 0x4;     //    16     R/W      Y           Filter Coefficient L2
  const unsigned long  L3         = 0x5;     //    16     R/W      Y           Filter Coefficient L3

  /*VFPED*/
  const unsigned long  VFPED      = 0x6;     //    20     R+R/W    Y           Variable / Fixed Pedestal Data
  const unsigned long  VPD        = 10;      //    10     R                    Self calibrated variable pedestal
  const unsigned long  FPD        = 0;       //    10     R/W                  Fixed  pedestal
  /*VFPED end*/

  const unsigned long  PMDTA      = 0x7;     //    10     R/W      Y           Ped. Mem. Data for a given address
  const unsigned long  ADEVL      = 0x11;    //    16     R        N/A         Chip Address + Event Length

  /*************************/
  /*   Global Registers    */
  /*************************/
  /*ZSTHR */
  const unsigned long  ZSTHR       = 0x8;    //    20     R/W      Y           Offset + Threshold ZS
  const unsigned long  OFFSET      = 10;     //    10     R/W      Y           Offest to be added to the signal
  const unsigned long  Z_THR       = 0;      //    10     R/W      Y           Zero supression treshold
  /*ZSTHR end*/

  /*BCTHR*/
  const unsigned long  BCTHR       = 0x9;    //    20     R/W      Y           Threshold HI + Threshold LO (MAU)
  const unsigned long  THR_LO      = 10;     //    10     R/W      Y           Upper treshold of acceptance window
  const unsigned long  THR_HI      = 0;      //    10     R/W      Y           Upper treshold of acceptance window
  /*BCTHR end*/

  /*  TRCFG  */
  const unsigned long  TRCFG       = 0xA;    //    20     R/W      Y           Trigger Delay + N. Samples/Event
  const unsigned long  ACQ_START   = 10;     //           R/W      Y           Number of cycles to wait before acquisition starts
  const unsigned long  ACQ_END     = 0;      //           R/W      Y           Number of cycles elapsed from trigger to acquisition end//
  /*  TRCFG end */

  /*****************************************************/
  /* DPCFG baseline correction configuration regsister  */
  /*****************************************************/
  /* The explanation below is taken from the ALTRO documentation*/
  /* Subtraction mode. In this mode of operation, the BC1 performs the subtraction */
  /*                   of spurious signals from the input-signal values. The subtracted signal can be */
  /*                   fixed (fixed subtraction mode), time-dependent (time-dependent subtraction */
  /*                   mode) or self-calibrated (self-calibrated subtraction mode). */
  /*
  /*                   In fixed-subtraction mode, the value to be subtracted from the input */
  /*                   signal is constant and stored in a configuration register. */
  /*
  /*                   In time-dependent subtraction mode, the time-dependent pedestal */
  /*                   values to be subtracted are stored in a memory (pedestal memory) that, */
  /*                   in this configuration, is addressed by a time counter started by the */
  /*                   trigger signal. */
  /*
  /*                   In self-calibrated subtraction mode, the value to be subtracted is */
  /*                   computed as cumulative average (self calibrated pedestal) of the */
  /*                   input signal outside the processing time window: */
  /*                   Upon the arrival of the first level trigger, the value of the self-calibrated */
  /*                   pedestal is frozen in a register. */
  /*                   While the fixed-mode and time-dependent-mode are exclusive, any of them */
  /*                   can be combined with the self-calibrated mode as shown in table1.1. */
  /**/
  /* Conversion mode.  The circuit can perform a memory (static) conversion of the */
  /*                   input signal of the type yn = F(xn). At any cycle n, the output yn depends at most */
  /*                   on the input sample xn at the same time, but not on past or future samples of the */
  /*                   input. The output values yn are stored in the baseline memory addressed, in this */
  /*                   case, by the input values xn. The conversion mode can work concurrently to the */
  /*                   self-calibrated subtraction mode and to the fixed subtraction mode. */
  /**/
  /* Test mode.        The LUT can be used to generate a pattern to be injected into the */
  /*                   processing chain for test purposes. On this test pattern, which is replacing the */
  /*                   input signal samples, can be performed the subtraction of a constant value. In */
  /*                   the latter case the pattern generated is a stream of zeros. */
  /*                   Finally, the BC1 circuit provide also the possibility of inverting the input signal polarity (1���s */
  /*                   complement). The pedestal memory is accessible, in write and read mode, throughout */
  /*                   three registers. */
  /*************************************************************************************************************************************/
  /*                 |                  | din-fpd | din-f(t)|din-scp-fpd | din-scp-f(t)| f(din) - fpd| f(din-scp) -fpd | f(t)- fpd     */
  /* Subtraction     |  Fixed           |    X    |         |    X       |             |      X      |        X        |               */
  /* Mode            |  Time-dependent  |         |   X     |            |       X     |             |                 |       X       */
  /*                 |  Self-calibrated |         |         |    X       |       X     |             |        X        |               */
  /*************************************************************************************************************************************/
  /*  Conversion Mode|                  |         |         |            |             |      X      |        X        |               */
  /*************************************************************************************************************************************/
  /*  Test Mode      |                  |         |         |            |             |             |                 |       X       */
  /*************************************************************************************************************************************/
  /*  din     =  data input samples*/
  /*  fpd     =  fixed pedestal data value*/
  /*  f(t)    =  time dependent LUT (Look Up Table) data */
  /*  scp     =  self calibrated pedestal data value */
  /*  f(din)  =  converted data */

  /*    Operating  modes first basline correction DPCFG[3:0]   */
  /*    0000      din - fpd                   */
  /*    0001      din - f(t)                  */
  /*    0010      din - f(din)                */
  /*    0011      din - f(din - vpd)          */
  /*    0100      din - vpd - fpd             */
  /*    0101      din - vpd - f(t)            */
  /*    0110      din - vpd - f(din)          */
  /*    0111      din - vpd - f(din - vpd)    */
  /*    1000      f(din) - fpd                */
  /*    1001      f(din - vpd) - fpd          */
  /*    1010      f(t) - fpd                  */
  /*    1011      f(t) - f(t)                 */
  /*    1100      f(din) - f(din)             */
  /*    1101      f(din - vpd) - f(din - vpd) */
  /*    1110      din - fpd                   */
  /*    1111      din - fpd                   */
  /********************************************/
  /*    Operating  modes od zero supression  DPCFG[13:12]   */
  /*      00      din - fpd                   */
  /*      01      din - f(t)                  */
  /*      10      din - f(din)                */
  /*      11      din - f(din - vpd)          */
  /********************************************/
  const unsigned long  DPCFG       = 0xB;    //    20     R/W      Y           ZSU + MAU + BSU configuration
  const unsigned long  BC1_CFG     = 0;      //     5     R/W      Y           3..0  First Baseline Correction Mode

  //                                Polarity. When set, the ADC data is inverted (1���s C)
  const unsigned long  BC2_CFG     = 5;      //     7                          6..5  Number of Presamples excluded from 2 Baseline Correction
  //                                10..7 Number of Postsamples excluded from 2 Baseline Correction
  //                                11   Enable Second Baseline Correction
  const unsigned long  ZS_CFG      = 12;     //     8                          13..12 Glitch Filter Configuration for Zero Suppression
  //                                16..14 Number of Postsamples excluded from suppression
  //                                18..17 Number of Presamples excluded from suppression
  //                                19   Enable Zero Suppression
  /* DPCFG end  */

  /* BFNPT */
  const unsigned long  DPCFG2      = 0xC;    //                                Filter Enable + Buffer. N. + Pre-trigger
  const unsigned long  PTRG        = 0;      //                                Number of Pretrigger Samples
  const unsigned long  NBUF        = 4;      //                                Number of Buffers in Data Memory (4 / 8)
  const unsigned long  FLT_EN      = 5;      //                                Enable the Digital Filter
  const unsigned long  PWSV        = 6;      //                                Power Save. When set, stops data processing outside trigger windows.
  /* BFNPT DPCFG2 end  */

  const unsigned long  ERSTR       = 0x10;   //    20     R        N/A         Error + Status Register
  const unsigned long  TRCNT       = 0x12;   //    16     R        N/A         Trigger Counter
  const unsigned long  PMADD       = 0xD;    //    10     R/W      Y           Pedestal Memory Address

  /* Global Commads, write triggered (T), (no physical register) */
  const unsigned long  WPINC       = 0x18;   //    N/A    T        Y           Write Pointer Increase
  const unsigned long  RPINC       = 0x19;   //    N/A    T        Y           Read Pointer Increase
  const unsigned long  CHRDO       = 0x1A;   //    N/A    T        N           Channel Readout
  const unsigned long  SWTRG       = 0x1B;   //    N/A    T        Y           Software Trigger
  const unsigned long  TRCLR       = 0x1C;   //    N/A    T        Y           Clear Trigger Counter
  const unsigned long  ERCLR       = 0x1D;   //    N/A    T        Y           Clear Error Flags

}



#endif
