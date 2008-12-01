// $Id: rcu_issue.h,v 1.1.1.1 2006/05/01 19:52:47 perthi Exp $

/************************************************************************
**
**
** This file is property of and copyright by the Experimental Nuclear 
** Physics Group, Dep. of Physics and Technology
** University of Bergen, Norway, 2004
** This file has been written by Matthias Richter,
** Please report bugs to Matthias.Richter@ift.uib.no
**
** Permission to use, copy, modify and distribute this software and its  
** documentation strictly for non-commercial purposes is hereby granted  
** without fee, provided that the above copyright notice appears in all  
** copies and that both the copyright notice and this permission notice  
** appear in the supporting documentation. The authors make no claims    
** about the suitability of this software for any purpose. It is         
** provided "as is" without express or implied warranty.                 
**
*************************************************************************/
#ifndef __RCU_ISSUE_H
#define __RCU_ISSUE_H

#include <linux/types.h>   // for the __u32 type

/***************************************************************************
 * command interpretation for the RCU FeeServer
 *
 * this file describes the interface to the RCU-like FeeServer ControlEngine
 *
 * the 'issue' method of the CE API expects the input either as encoded in message buffer format or
 * as a ControlEngine command
 * All feeserver commands start with 0xf in there most significant bits, anything else will be interpreted as a 
 * BLOB encoded in the message buffer format. Look into dcscMsgBufferInterface/dcscMsgBufferInterface.h for detailed 
 * description of the message buffer interface to the RCU motherboard
 * FEESERVER_CMD is predefined as 0xf0000000 (dcscMsgBufferInterface/dcscMsgBufferInterface.h)
 *
 */

/*
 * the general structure of a FeeServer command is:
 * Bit 32 - 28 | 27 - 24 | 23 - 16 | 15 -0
 *     1 1 1 1   cmd id    sub id    parameter
 *                                      ^------- 16 bit user parameter passed to the handler function
 *                            ^-----------------  8 bit command sub id passed to the handler function
 *                   ^--------------------------  4 bit command id switches to the handler function
 *        ^-------------------------------------  4 bit code for FeeServer command
 *
 * a data block is following, its content depends on the command
 * the whole command is terminated by an end-marker, which also contains the version encoded in the
 * lower 16 bits
 */
#define CE_CMD_EM_MASK   0xffff0000
#define CE_CMD_VS_MASK   0x0000ffff
#define CE_CMD_VERSION   0x0001
#define CE_CMD_ENDMARKER 0xdd330000
#define CE_CMD_TAILER    (CE_CMD_ENDMARKER | CE_CMD_VERSION)
/*
 */
#define FEESERVER_CMD_MASK         0xf0000000
#define FEESERVER_CMD_ID_MASK      0x0f000000
#define FEESERVER_CMD_SUB_MASK     0x00ff0000
#define FEESERVER_CMD_PARAM_MASK   0x0000ffff
#define FEESERVER_CMD_BITSHIFT     28
#define FEESERVER_CMD_ID_BITSHIFT  24
#define FEESERVER_CMD_SUB_BITSHIFT 16
#define FEESERVER_CMD_PARAM_BTSHFT  0

// FEESERVER_CMD is defined in dcscMsgBufferInterface.h if the file is part of a project
// including the message buffer interface. If the latter header file is not available, 
// take the dafault value
#ifndef FEESERVER_CMD
#define FEESERVER_CMD 0xf0000000
#endif //FEESERVER_CMD 
/* command defines
 * the number of additional 32 bit data words is given in {}
 */ 

/* group 1: commands for the feeserver
 * 0xf1xxxxxx
 */
#define FEESERVER_CE_CMD  (0x01000000 | FEESERVER_CMD)
#define CEDBG_SET_BUF_PRINT_SIZE (0x010000 | FEESERVER_CE_CMD) // set the maximum size for the command buffer debug print, default 0 {1}
#define CEDBG_USE_SINGLE_WRITE   (0x020000 | FEESERVER_CE_CMD) // use single write for rcu memory writing {0}
#define CEDBG_EN_SERVICE_UPDATE  (0x030000 | FEESERVER_CE_CMD) // turn on/off the update of the services {0}
                                                               // parameter: 0x0 off, 0xffff all on, 0x<bitfield> selection on

#define CEDBG_SET_SERVICE_VALUE  (0x040000 | FEESERVER_CE_CMD) // set the value of a service {1}
#define           CEDBG_SSD_SERVICE_NO_MASK  0x00ff            // parameter: bit 0-7 service no 
#define           CEDBG_SSD_FEC_NO_MASK      0x1f00            //            bit 8-12 FEC no
#define           CEDBG_SSD_RCU_REG_MASK     0x2000            //            bit 13=1 rcu register (FEC no not valid)
#define CE_READ_DEFAULT_SERVICES (0x050000 | FEESERVER_CE_CMD) // returns a list of all possible services
#define CE_READ_VALID_FECS       (0x060000 | FEESERVER_CE_CMD) // returns a list of the valid Frontend cards
#define CE_RELAX_CMD_VERS_CHECK  (0x070000 | FEESERVER_CE_CMD) // relax the version checking for commands
#define CE_SET_LOGGING_LEVEL     (0x080000 | FEESERVER_CE_CMD) // set the logging level (refer to ce_base.h for levels)

/* group 2: commands for the dcscMsgBufInterface library
 * 0xf2xxxxxx
 */
#define FEESVR_DCSC_CMD    (0x02000000 | FEESERVER_CMD)
#define DCSC_SET_OPTION_FLAG     (0x10000 | FEESVR_DCSC_CMD) // set a debug option flag of the dcscRCUaccess library {0}
                                                             // parameter: bitflied of flags
#define DCSC_CLEAR_OPTION_FLAG   (0x20000 | FEESVR_DCSC_CMD) // clear a debug option flag of the dcscRCUaccess library {0}
                                                             // parameter: bitflied of flags

/* group 3: command set for the RCU
 * 0xf3xxxxxx
 */
#define FEESVR_CMD_RCU    (0x03000000 | FEESERVER_CMD)
#define RCU_EXEC              (0x010000 | FEESVR_CMD_RCU) // send the execution command to run the sequence written to rcu instruction memory {0}
#define RCU_STOP_EXEC         (0x020000 | FEESVR_CMD_RCU) // stop the execution {0}
        // the following commands allow to write a block of data to rcu instruction or pattern memory
        // the number of 32 bit words is given by the command parameter
#define RCU_WRITE_INSTRUCTION (0x030000 | FEESVR_CMD_RCU) // write to rcu instruction memory {parameter}
#define RCU_EXEC_INSTRUCTION  (0x040000 | FEESVR_CMD_RCU) // write to rcu instruction memory and send the execution command {parameter}
#define RCU_WRITE_PATTERN8    (0x050000 | FEESVR_CMD_RCU) // write 8 bit data to rcu pattern memory {parameter}
#define RCU_WRITE_PATTERN16   (0x060000 | FEESVR_CMD_RCU) // write 16 bit data to rcu pattern memory {parameter}
#define RCU_WRITE_PATTERN32   (0x070000 | FEESVR_CMD_RCU) // write 32 bit data to rcu pattern memory {parameter}
#define RCU_WRITE_PATTERN10   (0x080000 | FEESVR_CMD_RCU) // write 10 bit compressed data to rcu pattern memory {parameter}
        // the following commands allow to read the content of the rcu instruction or pattern memory
        // the number of 32 bit words is given by the command parameter
#define RCU_READ_INSTRUCTION  (0x090000 | FEESVR_CMD_RCU) // read from rcu instruction memory {0}
#define RCU_READ_PATTERN      (0x0a0000 | FEESVR_CMD_RCU) // read from rcu pattern memory {0}
        // the following commands allow to read and write from/to an rcu memory location
        // parameter is a 16 bit address
#define RCU_READ_MEMORY       (0x0b0000 | FEESVR_CMD_RCU) // read from rcu memory location {0}
#define RCU_WRITE_MEMORY      (0x0c0000 | FEESVR_CMD_RCU) // write to rcu memory location {1}
#define RCU_WRITE_RESULT      (0x0d0000 | FEESVR_CMD_RCU) // write to rcu result memory {parameter}
#define RCU_READ_RESULT       (0x0e0000 | FEESVR_CMD_RCU) // read from rcu result memory {0}
#define RCU_WRITE_MEMBLOCK    (0x100000 | FEESVR_CMD_RCU) // write block to rcu memory {parameter+1}
        // the first 32 bit word of the data is the address to write to, the data is following
#define RCU_READ_MEMBLOCK     (0x110000 | FEESVR_CMD_RCU) // read block from rcu memory {1}
        // number of data words to read specified by parameter, address is the 32 bit word following the command id

/* group 4: command set for the RCU configuration
 * 0xf4xxxxxx
 */
#define FEESVR_CMD_RCUCONF  (0x04000000 | FEESERVER_CMD)
#define RCU_WRITE_FPGA_CONF   (0x010000 | FEESVR_CMD_RCU) // write a configuration to the RCU FPGA
#define RCU_READ_FPGA_CONF    (0x020000 | FEESVR_CMD_RCU) // read the configuration of the RCU FPGA
#define RCU_WRITE_FLASH       (0x030000 | FEESVR_CMD_RCU) // write a file to the Flash
#define RCU_READ_FLASH        (0x040000 | FEESVR_CMD_RCU) // write a file to the Flash

/* group 5 set the value for a data point in the Fee
 * 0xf5xxxxxx
 * set the data for a corresponding service
 * the handler function has to be specified during the registration of the service
 * the payload is expected to be a 8, 16, or 32 bit value followed by the name of the corresponding service
 * the length of the string (including the terminating 0!) is specified as parameter in the lower 16 bit
 * the string should be aligned to 4 by adding additional zeros
 */
#define FEESVR_SET_FERO_DATA  (0x05000000 | FEESERVER_CMD)
#define FEESVR_SET_FERO_DATA8   (0x010000 | FEESVR_SET_FERO_DATA)
#define FEESVR_SET_FERO_DATA16  (0x020000 | FEESVR_SET_FERO_DATA)
#define FEESVR_SET_FERO_DATA32  (0x030000 | FEESVR_SET_FERO_DATA)
#define FEESVR_SET_FERO_DFLOAT  (0x040000 | FEESVR_SET_FERO_DATA)

/* group 6
 * 0xf6xxxxxx
 * data readout from the rcu data buffer
 */
#define FEESVR_CMD_DATA_RO    (0x06000000 | FEESERVER_CMD)

/* group 7: shell execution
 * 0xf7xxxxxx
 * the lower 16 bit, the parameter, gives the size of that command buffer in BYTE
 */
#define FEESVR_CMD_SHELL    (0x07000000 | FEESERVER_CMD)
#define FEESRV_EXECUTE_PGM    (0x010000 | FEESVR_CMD_SHELL) // execute a script/program on the DSC board
        // the remaining data is interpreted as a char string containing shell command and arguments
#define FEESRV_EXECUTE_SCRIPT (0x020000 | FEESVR_CMD_SHELL) // send a script down and execute it
        // the remaining data is interpreted as a char buffer containing the script
#define FEESRV_BINARY_PGM     (0x030000 | FEESVR_CMD_SHELL) // send a binary program to the DCS board and execute it
        // the remaining data is interpreted as a char buffer which contains the binary program
#define FEESRV_RCUSH_SCRIPT   (0x040000 | FEESVR_CMD_SHELL) // send a script down and execute it with rcu-sh
        // the remaining data is interpreted as a char buffer which contains the script

/* groups 8 and 9: reserved
 * 0xf8xxxxxx / 0xf9xxxxxx
 */
#define FEESVR_RSVD8_CMD    (0x08000000 | FEESERVER_CMD)
#define FEESVR_RSVD9_CMD    (0x09000000 | FEESERVER_CMD)

/* group 10 to 15: user defined function codes
 * introduce convenient define-ids if appropriate!
 * 
 * 0xfaxxxxxx to 0xffxxxxxx
 */
#define FEESVR_CMD_TPC  (0x0a000000 | FEESERVER_CMD) // command set for the TPC CE
#define FEESVR_CMD_PHOS (0x0b000000 | FEESERVER_CMD) // command set for the PHOS CE
//#define FEESVR_USER3   (0x0c000000 | FEESERVER_CMD)
//#define FEESVR_USER4   (0x0d000000 | FEESERVER_CMD)


/*******************************************************************************************
 * helper functions
 */

/* mask a value and shift it according to the mask
 */
int MASK_SHIFT(int val, int mask);

/* check if the proveided header represents FeeServer command or not
 * result: 1 yes, 0 no
 */
int checkFeeServerCommand(__u32 header);

/* extract command id from the provided header
 * result: 0 - 15 command id
 *         -1 no FeeServer command
 */
int extractCmdId(__u32 header);

/* extract command sub id from the provided header
 * result: 0 - 255 command id
 *         -1 no FeeServer command
 */
int extractCmdSubId(__u32 header);

/*******************************************************************************************
 * API function entries
 */

/* issue handler for the RCU like CE
 */
int RCUce_Issue(char* command, char** result, int* size);

/* internal cleanup of the issue handler
 */
int RCUce_CleanIssue();

/* set the result pointer of the durrent ce issue process
 * parameter:
 *    buffer - pointer to result data
 *    size   - size of the buffer
 *    bClone - if 1, the result buffer is automatically duplicated and thus made persistent,
 *             all memory handling is carried out by the function and the framework
 */
int RCUce_IssueResult(char* buffer, int size, int bDuplicate);

/* wrapper to the above IssueResult method for static result buffers
 * the provided buffer has to be valid at least until the next call of issue by the Feeserver 
 * core
 * parameter:
 *    buffer - pointer to result data
 *    size   - size of the buffer
 */
int RCUce_SetResult(char* buffer, int size);

/* wrapper to the above IssueResult method for volatile result buffers
 * the provided buffer will be duplicated
 * core
 * parameter:
 *    buffer - pointer to result data
 *    size   - size of the buffer
 */
int RCUce_CloneResult(char* buffer, int size);

/* return result buffer and size
 * result: >0 valid buffer with size n
 *         =0 no result buffer
 *         <0 error code 
 */
int RCUce_GetResult(const char** target);

#endif //__RCU_ISSUE_H
