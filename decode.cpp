#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "decode.hpp"

using namespace std;

int classify_type(const ALL_Types);

unsigned int getPCData(ifstream & in, unsigned int pc) {
  unsigned int addr, data;
  while ((in >> addr) && addr != pc) {
    in >> data;
  } 
  if (in >> data) {
    cout << hex << addr << ":     ";
    return data;
  }
  else {
    cout << "BAD PC" << endl;
    exit(1);
  }

}

unsigned int getNextValidInstr(ifstream & in) {
  unsigned int addr, data;
  while (in >> addr >> data && data > 0x10000) {
  }
  if (addr != 0xda) {
    cout << hex << addr << ":     ";
  }
  return data;
}

Register pc;
Options opts;

int main(int argc, char ** argv) {
  unsigned int addr, data;
  int c;
  string s, filename;
  ALL_Types temp;
  while ((c = getopt(argc, argv, "pdiwsc:f:")) != -1) {
    switch(c) {
#if 0 // will include later in lab 6
      case 'p':
        opts.program = true;
        break;
      case 'd':
        opts.dump = true;
        break;
      case 'i':
        opts.instrs = true;
        break;
      case 'w':
        opts.writes = true;
        break;
      case 's':
        opts.stats = true;
        break;
      case 'c':
        //caches = Caches(atoi(optarg));
        break;
#endif
      case 'f':
        filename = optarg;
        break;
    }
  }

  if (filename == "") {
    cerr << "ERROR: no source file specified; "
      << "run this program with -f filename" << endl;
    exit(1);
  }  
  ifstream in(filename.c_str());
  in >> hex;                    // in takes hex numbers
  in >> s;
  if (s != "PC") {
    cout << "Invalid .sim file" << endl;
    exit(1);
  }
  in >> addr;
  pc = addr;
  in >> s;
  in >> s;
  cout << "Starting at PC " << hex << pc << endl;
  data = getPCData(in, pc);
  temp = ALL_Types(data);
  classify_type(temp);

  while(data = getNextValidInstr(in)) {
    temp = ALL_Types(data);
    if (classify_type(temp) == -1) 
      break;
  }
  return 0;
}

int classify_type(const ALL_Types data) {
  /* The following need to be completed
  if (data.type.alu.instr.class_type.type_check == ALU_TYPE) {
    if (data.type.alu.instr.lsli.op == ALU_LSLI_OP) {
    }
    else if (data.type.alu.instr.lsri.op == ALU_LSRI_OP) {
    }
    else if (data.type.alu.instr.asri.op == ALU_ASRI_OP) {
    }
    else if (data.type.alu.instr.addr.op == ALU_ADDR_OP) {
    }
    else if (data.type.alu.instr.subr.op == ALU_SUBR_OP) {
    }
    else if (data.type.alu.instr.add3i.op == ALU_ADD3I_OP) {
    }
    else if (data.type.alu.instr.sub3i.op == ALU_SUB3I_OP) {
    }
    else if (data.type.alu.instr.add8i.op == ALU_ADD8I_OP) {
    }
    else if (data.type.alu.instr.sub8i.op == ALU_SUB8I_OP) {
    }
    else if (data.type.alu.instr.cmp.op == ALU_CMP_OP) {
    }
    else if (data.type.alu.instr.mov.op == ALU_MOV_OP) {
    }
    //return ALU_TYPE;
  }
  else if (data.type.dp.instr.class_type.type_check == DP_TYPE) {
    //return DP_TYPE;
  }
  else if (data.type.sp.instr.class_type.type_check == SP_TYPE) {
    //return SP_TYPE;
  }
  else if (data.type.uncond.instr.class_type.type_check == UNCOND_TYPE) {
    //return UNCOND_TYPE;
  }
  else */
  // after you've complete the above insn types, you can put this
  // following if statement into the preceeding else to make an "else if"
  if (data.type.misc.instr.class_type.type_check == MISC_TYPE) {
    // There are more than these two MISC_TYPES,
    // You'll need to complete them here.
    if (data.type.misc.instr.push.op == MISC_PUSH_OP) {
      cout << "push ";
      cout << "{";
      if (data.type.misc.instr.push.reg_list & 1) {
        cout << "r0, ";
      }
      if (data.type.misc.instr.push.reg_list & 2) {
        cout << "r1, ";
      }
      if (data.type.misc.instr.push.reg_list & 4) {
        cout << "r2, ";
      }
      if (data.type.misc.instr.push.reg_list & 8) {
        cout << "r3, ";
      }
      if (data.type.misc.instr.push.reg_list & 16) {
        cout << "r4, ";
      }
      if (data.type.misc.instr.push.reg_list & 32) {
        cout << "r5, ";
      }
      if (data.type.misc.instr.push.reg_list & 64) {
        cout << "r6, ";
      }
      if (data.type.misc.instr.push.reg_list & 128) {
        cout << "r7, ";
      }
      cout << "lr}" << endl;
    }
    else if (data.type.misc.instr.sub.op == MISC_SUB_OP) {
      cout << "sub sp, #";
      cout << setbase(10) << (static_cast<unsigned int>(data.type.misc.instr.sub.imm)<< 2) << endl;
    }
    return MISC_TYPE;
  }

  // Complete the rest of these
  else if (data.type.cond.instr.class_type.type_check == COND_TYPE) {
    //return COND_TYPE;
  }
  else if (data.type.ldm.instr.class_type.type_check == LDM_TYPE) {
    //return LDM_TYPE;
  }
  else if (data.type.stm.instr.class_type.type_check == STM_TYPE) {
    //return STM_TYPE;
  }
  else if (data.type.ldrl.instr.class_type.type_check == LDRL_TYPE) {
    //return LDRL_TYPE;
  }
  else if (data.type.addsp.instr.class_type.type_check == ADD_SP_TYPE) {
    //return ADD_SP_TYPE;
  }
  else {
    // Complete the rest of these instruction classes
    if (data.type.ld_st.instr.class_type.opA == LD_ST_REG_OPA) {
    }
    else if (data.type.ld_st.instr.class_type.opA == LD_ST_IMM_OPA) {
      if (data.type.ld_st.instr.class_type.opB == LD_ST_OPB_STR) {
      }
      else if (data.type.ld_st.instr.class_type.opB == LD_ST_OPB_LDR) {
      }
    }
    else if (data.type.ld_st.instr.class_type.opA == LD_ST_IMMB_OPA) {
    }
    else if (data.type.ld_st.instr.class_type.opA == LD_ST_IMMH_OPA) {
    }
    else if (data.type.ld_st.instr.class_type.opA == LD_ST_IMMSP_OPA) {
    }
    else {
      cout << "NOT A VALID INSTRUCTION" << endl;
    }
  }
  cout << "NO TYPE FOUND" << endl;

  return -1; // Error
}
