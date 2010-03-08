//#ifndef ALTROREGISTERMAP_H
#ifndef RCUREGISTERMAP_H

//#define ALTROREGISTERMAP_H
#define RCUREGISTERMAP_H

/**** Regsiter Access ****
 * R = Read
 * W = Write
 * R/W = Read/Write
 * T = Write triggered command (write any value too this register to execute the corresponding command)
*/

namespace RcuRegisterMap
  {

  /*
   * Global storage and command table
   */



  //name                     address    width  access     Description



  const unsigned long  AFL                    = 0x5100;  //32bit  R/W     // This register, updated by the Slow Control contains the
  // active front-end card list. The low 16bit correspond to
  // branch A, whereas the higher 16bit correspond to
  // branch B. A bit is set to "1" if a FEC is ON.
  const unsigned long  RDOL                   = 0x8001;                   // 32bit  R/W      N
  const unsigned long  DCSadd                 = 0x8007;  //16bit  ?       // DCS address field stored in each write transaction

  const unsigned long  RCU_version            = 0x5106;  //24bit  R/W     // RCU firmware version

  const unsigned long  backplane_version      = 0x5107;  //1bit   R/W     // TPC (0) or PHOS (1) version for the backplane
  const unsigned long  TTCclk_freq            = 0x800A;  //3bit   R       // Frequency of the TTC clk
  const unsigned long  DCS_ON                 = 0xE000;  //1bit   T       // By executing this command, the DCS card becomes
  // master of the RCU bus. (DCS access only)
  const unsigned long  DDL_ON                 = 0xF000;  //1bit   T       // By executing this command, the DDL becomes maste
  // of the RCU bus. Default condition. (DCS access only
  const unsigned long  L1_TTC                 = 0xE800;  //1bit   T       // Enables the L1 trigger coming from the TTC chip
  const unsigned long  SCLKsync               = 0x8020;  //1bit   T       // Re-synchronize the SCLK with the next L1TTC trigge
  const unsigned long  L1_aux                 = 0xF800;  //1bit   T       // Enables the L1 trigger coming from the dedicated connector
  const unsigned long  L1_CMD                 = 0xD800;  //1bit   T       // Enables the L1 trigger issued by a command (default)
  const unsigned long  L1                     = 0xD000;  //1bit   T       // Sends L1 trigger if L1_CMD has been previously set

  const unsigned long  GLB_RESET              = 0x5300;  //1bit   T       // Resets both RCU and FECs.
  const unsigned long  FEC_RESET              = 0x5301;  //1bit   T       // Resets only the FECs.
  const unsigned long  RCU_RESET              = 0x5302;  //1bit   T       // Resets only the RCU. It does not affect to the


  const unsigned long  TRCFG                   = 0x5102;  //17bit  R/W     // It contains the Trigger configuration and Trigger Status.

  const unsigned long RDOMOD                   = 0x5103;  //4bit   R/W     //Set the readout mode
  // [3] Mask  RDYRX ;Sparse readout enable $(B"a(B [2]; execute sequencer on SOE/EOE $(B"a(B [1] ; MEB mode [0].
  const unsigned long ALTROCFG1                = 0x5104;  //16bit R/W      //Copy of the ALTROCFG1 register of the ALTRO chip (see ALTRO manual pags. 36-37). The content of this register will be copied in one of the words of the event data block trailer

  const unsigned long ALTROCFG2                = 0x5105;   //18bit R/W     //+Copy of the ALTROCFG2 register of the ALTRO chip (see ALTRO manual pags. 36-37). The content of this register will be copied in one of the words of the event data block trailer


  //OD HACK
  // CRAP
  const unsigned long FEESERVER_CMD           = 0xf0000000;
  const unsigned long FEESVR_CMD_RCU          = 0x03000000 | FEESERVER_CMD;
  const unsigned long RCU_EXEC_INSTRUCTION    = 0x040000 | FEESVR_CMD_RCU;
  const unsigned long RCU_READ_MEMORY         = 0x0b0000 | FEESVR_CMD_RCU;
  const unsigned long RCU_WRITE_MEMORY        = 0x0c0000 | FEESVR_CMD_RCU;
  const unsigned long RCU_WRITE_MEMBLOCK      = 0x100000 | FEESVR_CMD_RCU;

  //  const unsigned long CE_CMD_VERSION          = 0x0007;
  //   const unsigned long CE_CMD_ENDMARKER        = 0xdd330000;
  const unsigned long CE_CMD_TRAILER        = 0xdd330000 | 0x0007;
  // \CRAP

  // AFL (0x8000) and Backplane_version (0x8009) registers
  //   WRD_RD         W     1bit 0x5xxx   Number of words to be read (in DDL access only)


  /*
   * ALTRO Interface Addressable Memories
   */

  //name                    address    width  access     Description

  const unsigned long  Instruction_MEM        = 0x0;  //24bit  R/W     // It contains the Instruction Sequence to be executed either in
  // configuration or readout (24bit x 256).
  const unsigned long  Instruction_MEM_length = 4095;


  const unsigned long  Pattern_MEM            = 0x6800;  //10bit  R/W     // Contains Pedestal values to be sent or compared (10bit x 1024).
  const unsigned long  Pattern_MEM_length     = 1024;


  const unsigned long  Result_MEM             = 0x2001;  //20bit  R/W     // The result of each ALTRO READ instruction is stored in this memory.
  const unsigned long  Result_MEM_length      = 8191;

  const unsigned long  Active_Channel_List    = 0x1000;  //16bit  R/W     // It contains the list, in a per channel basis, of all the
  // channels that will be readout. Each line corresponds to
  // an ALTRO, and each bit to a channel (16bit x 256).
  const unsigned long  Active_Channel_List_Length    = 4096;

  const unsigned long  Data_MEM1_Low          = 0x7400;  //20bit  R/W     // Low 20bit of data MEM 1 (20bit x 256)
  const unsigned long  Data_MEM1_Low_length   = 256;

  const unsigned long  Data_MEM1_High         = 0x7500;  //20bit  R/W     // High 20bit of data MEM 1(20bit x 256)
  const unsigned long  Data_MEM1_High_length  = 256;

  const unsigned long  Data_MEM2_Low          = 0x7C00;  //20bit  R/W     // Low 20bit of data MEM 2 (20bit x 256)
  const unsigned long  Data_MEM2_Low_length   = 256;

  const unsigned long  Data_MEM2_High         = 0x7D00;  //20bit  R/W     // High 20bit of data MEM 2 (20bit x 256)
  const unsigned long  Data_MEM2_High_lemgth  = 256;


  /*
   *   ALTRO Interface Register Table
   */

  //name                     address    width  access     Description
  const unsigned long  ERRST                   = 0x7800;  //32bit  R       // It contains the status and error information.
  const unsigned long  ERRST_PATTERN_ERROR     = 0;       //1bit   R       // This bit is set to "1" if there is a mismatch in the comparison of the PMREAD RCU instruction
  const unsigned long  ERRST_ABORT             = 1;       //1bit   R       // It signals that the instruction sequence has been aborted
  const unsigned long  ERRST_TIMEOUT           = 2;       //1bit   R       // This bit is set to "1" if the front-end cards do not respond within 32 clock cycles
  const unsigned long  ERRST_ALTRO_ERROR       = 3;       //1bit   R       // This bit corresponds to the errorb line of the ALTRO bus
  const unsigned long  ERRST_HVADD_ERROR       = 4;       //1bit   R       // This bits signals a mismatch between the channel address contained in
  // the data of a readout and the channel address requested in that readout
  const unsigned long  ERRST_RCU_HWADD         = 12;      //9bit   R/W     // These 9 bits have both WRITE/READ access and encode the RCU
  // hardware address: [2 0] N- partition; [8 3] N- sector.
  const unsigned long  ERRST_RCU_BUSY          = 1;       //1bit   R       // This bit indicates that the ALTRO Interface Module is busy and therefore
  // the instruction memory is inaccessible.



  const unsigned long  TRCFG_TW                = 0;       //13bit  R/W     // This register contains the number of clock cycles that the system waits
  // after the arrival of the L1 trigger and the issuing of the L2 trigger. Only
  // usable in trigger mode = 2
  const unsigned long  TRCFG_BMD               = 14;      //1bit   R/W     // Buffer Mode: "0" for 4 buffers and "1" for 8 buffers
  const unsigned long  TRCFG_MODE              = 15;      //2bit   R/W     // Trigger Mode:
  // 0 Software trigger (default)
  // 2 External L1 trigger and automatic generation of L2 after TW
  // 3 External L1 trigger and external L2 trigger
  const unsigned long  TRCFG_OPT               = 17;      //1bit   R/W     // This bit enables the readout optimization using the board controller
  const unsigned long  TRCFG_POP               = 18;      //1bit   R/W     // This bit enables a popped readout scheme controlled by an external
  // master e.g. USB or DCS


  const unsigned long  TRCNT                   = 0x7802;  //32bit  R       // It contains the counters of L1 triggers received and L1 triggers accepted.
  const unsigned long  LWADD                   = 0x7803;  //18bit  R       // It contains information used in popped readout mode.
  const unsigned long  IRADD                   = 0x7804;  //20bit  R       // It contains the address of the last instruction sent to the ALTROs.
  const unsigned long  IRDAT                   = 0x7805;  //20bit  R       // It contains the data of the last instruction sent to the ALTROs.
  const unsigned long  PMCFG                   = 0x7806;  //20bit  R/W     // It contains the configuration for the PMWRITE and PMREAD macros.
  const unsigned long  CHADD                   = 0x7807;  //24bit  R       // It contains the hardware address of the last channel being readout in both buffers.


  /*
   *   ALTRO Interface Commands
   */


  //name                     address    width  access     Description
  const unsigned long  RS_STATUS               = 0x6C01;   //1bit  T       // It resets the ERRST (status) register
  const unsigned long  RS_TRCFG                = 0x6C02;   //1bit  T       // It resets the TRCFG (trigger configuration) register
  const unsigned long  RS_TRCNT                = 0x6C03;   //1bit  T       // It resets the TRCNT (trigger counter) register
  const unsigned long  RS_BUF1                 = 0x6C04;   //1bit  T       // Resets readout buffer 1. (In popped readout mode only)
  const unsigned long  RS_BUF2                 = 0x6C05;   //1bit  T       // Resets readout buffer 2. (In popped readout mode only)

  // const unsigned long    EXEC =       W        0x00XX                      Starts the execution of a sequence in the instruction memory at
  //                                                                          the address specified in XX (8bits)


  //const unsigned long  EXEC                    = 0x0;      //1bit  T       // Starts the execution of a sequence in the instruction memory at
  // the address specified in XX (8bits)

  const unsigned long  EXEC                    = 0x5304;      //1bit  T       // Starts the execution of a sequence in the instruction memory at
  // the address specified in XX (8bits)

  const unsigned long  ABORT                   = 0x0800;   //1bit  T       // Aborts any sequence taking place on the instruction memory


  const unsigned long ALTROIF                  = 0x5101;   //18 bits W/R   //N samples/sampling/cstb delay


  /*
   *RCU commands (more too come)
   */

  //CRAP PTH
  // const unsigned long END                      = 0x390000;
  const unsigned long END                      = 0x380000;
  const unsigned long ENDMEM                   = 0x3f0000;

}


#endif
