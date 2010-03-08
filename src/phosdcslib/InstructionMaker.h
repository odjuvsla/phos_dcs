#ifndef INSTRUCTIONMAKER_H
#define INSTRUCTIONMAKER_H

class InstructionMaker
  {
  public:

    InstructionMaker() {}
    ~InstructionMaker() {}

    /** changed for RCU_fw2 (maybe incomplete/incorrect) */
    static unsigned long  MakeMS20Instruction ( const int registerType, const bool read,
        const unsigned long reg, const unsigned long  branch = 0,
        const unsigned long card = 0, const unsigned long chip = 0, const unsigned long channel = 0 );


    /*
     * @param registerValue the value too write

    /** changed for RCU_fw2 (maybe incomplete/incorrect) */
    static unsigned long  MakeLS20Instruction ( const bool read,  const unsigned long registerValue );
    //static unsigned long  MakeLS20Instruction(const bool rw, const unsigned long pos, const unsigned long registerValue);
  };
#endif
