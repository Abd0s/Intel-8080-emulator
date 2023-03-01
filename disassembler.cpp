#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream is(argv[1], ifstream::binary); // make stream object

    if (!is) { // Check if any errors occured in opening file
        cout << "Cannot open file!" << endl;
        return 1;
    }
    if (is) {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char buffer[length];
        // read data as a block:
        is.read(buffer, length);

        if (!is) {
            cout << "error: only " << is.gcount() << " could be read"  << endl;
        }
        is.close();

        // parse file contents with lookup table

        cout << setw(4) << "I";
        cout << setw(4) << "OPC";
        cout << setw(4) << "ASM" << endl;
        for (int i = 0; i < length; i++) {
            cout << setw(4) << hex << i << " ";
            cout << setw(4) << hex << (int)(unsigned char)buffer[i] << " ";
            switch ((unsigned char)buffer[i]) {
                case 0x00: cout << "NOP" << endl; break;
                case 0x01: cout << hex << "LXI B, " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x02: cout << "STAX B" << endl; break;
                case 0x03: cout << "INX B" << endl; break;
                case 0x04: cout << "INR B" << endl; break;
                case 0x05: cout << "DCR B" << endl; break;
                case 0x06: cout << hex << "MVI B, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x07: cout << "RLC" << endl; break;
                case 0x08: cout << "-" << endl; break;
                case 0x09: cout << "DAD B" << endl; break;
                case 0x0a: cout << "LDAX B" << endl; break;
                case 0x0b: cout << "DCX B" << endl; break;
                case 0x0c: cout << "INR C" << endl; break;
                case 0x0d: cout << "DCR C" << endl; break;
                case 0x0e: cout << hex << "MVI C, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x0f: cout << "RRC" << endl; break;
                case 0x10: cout << "-" << endl; break;
                case 0x11: cout << hex << "LXI D, " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x12: cout << "STAX D" << endl; break;
                case 0x13: cout << "INX D" << endl; break;
                case 0x14: cout << "INR D" << endl; break;
                case 0x15: cout << "DCR D" << endl; break;
                case 0x16: cout << hex << "MVI D, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x17: cout << "RAL" << endl; break;
                case 0x18: cout << "-" << endl; break;
                case 0x19: cout << "DAD D" << endl; break;
                case 0x1a: cout << "LDAX D" << endl; break;
                case 0x1b: cout << "DCX D" << endl; break;
                case 0x1c: cout << "INR E" << endl; break;
                case 0x1d: cout << "DCR E" << endl; break;
                case 0x1e: cout << hex << "MVI E, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x1f: cout << "RAR" << endl; break;
                case 0x20: cout << "-" << endl; break;
                case 0x21: cout << hex << "LXI H, " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x22: cout << hex << "SHLD " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x23: cout << "INX H" << endl; break;
                case 0x24: cout << "INR H" << endl; break;
                case 0x25: cout << "DCR H" << endl; break;
                case 0x26: cout << hex << "MVI H, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x27: cout << "DAA" << endl; break;
                case 0x28: cout << "-" << endl; break;
                case 0x29: cout << "DAD H" << endl; break;
                case 0x2a: cout << hex << "LHLD " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x2b: cout << "DCX H" << endl; break;
                case 0x2c: cout << "INR L" << endl; break;
                case 0x2d: cout << "DCR L" << endl; break;
                case 0x2e: cout << hex << "MVI L, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x2f: cout << "CMA" << endl; break;
                case 0x30: cout << "-" << endl; break;
                case 0x31: cout << hex << "LXI SP, " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x32: cout << hex << "STA " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x33: cout << "INX SP" << endl; break;
                case 0x34: cout << "INR M" << endl; break;
                case 0x35: cout << "DCR M" << endl; break;
                case 0x36: cout << hex << "MVI M, " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x37: cout << "STC" << endl; break;
                case 0x38: cout << "-" << endl; break;
                case 0x39: cout << "DAD SP" << endl; break;
                case 0x3a: cout << hex << "LDA " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0x3b: cout << "DCX SP" << endl; break;
                case 0x3c: cout << "INR A" << endl; break;
                case 0x3d: cout << "DCR A" << endl; break;
                case 0x3e: cout << hex << "MVI A " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0x3f: cout << "CMC" << endl; break;
                case 0x40: cout << "MOV B, B" << endl; break;
                case 0x41: cout << "MOV B, C" << endl; break;
                case 0x42: cout << "MOV B, D" << endl; break;
                case 0x43: cout << "MOV B, E" << endl; break;
                case 0x44: cout << "MOV B, H" << endl; break;
                case 0x45: cout << "MOV B, L" << endl; break;
                case 0x46: cout << "MOV B, M" << endl; break;
                case 0x47: cout << "MOV B, A" << endl; break;
                case 0x48: cout << "MOV C, B" << endl; break;
                case 0x49: cout << "MOV C, C" << endl; break;
                case 0x4a: cout << "MOV C, D" << endl; break;
                case 0x4b: cout << "MOV C, E" << endl; break;
                case 0x4c: cout << "MOV C, H" << endl; break;
                case 0x4d: cout << "MOV C, L" << endl; break;
                case 0x4e: cout << "MOV C, M" << endl; break;
                case 0x4f: cout << "MOV C, A" << endl; break;
                case 0x50: cout << "MOV D, B" << endl; break;
                case 0x51: cout << "MOV D, C" << endl; break;
                case 0x52: cout << "MOV D, D" << endl; break;
                case 0x53: cout << "MOV D, E" << endl; break;
                case 0x54: cout << "MOV D, H" << endl; break;
                case 0x55: cout << "MOV D, L" << endl; break;
                case 0x56: cout << "MOV D, M" << endl; break;
                case 0x57: cout << "MOV D, A" << endl; break;
                case 0x58: cout << "MOV E, B" << endl; break;
                case 0x59: cout << "MOV E, C" << endl; break;
                case 0x5a: cout << "MOV E, B" << endl; break;
                case 0x5b: cout << "MOV E, E" << endl; break;
                case 0x5c: cout << "MOV E, H" << endl; break;
                case 0x5d: cout << "MOV E, L" << endl; break;
                case 0x5e: cout << "MOV E, M" << endl; break;
                case 0x5f: cout << "MOV E, A" << endl; break;
                case 0x60: cout << "MOV H, B" << endl; break;
                case 0x61: cout << "MOV H, C" << endl; break;
                case 0x62: cout << "MOV H, D" << endl; break;
                case 0x63: cout << "MOV H, E" << endl; break;
                case 0x64: cout << "MOV H, H" << endl; break;
                case 0x65: cout << "MOV H, L" << endl; break;
                case 0x66: cout << "MOV H, M" << endl; break;
                case 0x67: cout << "MOV H, A" << endl; break;
                case 0x68: cout << "MOV L, B" << endl; break;
                case 0x69: cout << "MOV L, C" << endl; break;
                case 0x6a: cout << "MOV L, D" << endl; break;
                case 0x6b: cout << "MOV L, E" << endl; break;
                case 0x6c: cout << "MOV L, H" << endl; break;
                case 0x6d: cout << "MOV L, L" << endl; break;
                case 0x6e: cout << "MOV L, M" << endl; break;
                case 0x6f: cout << "MOV L, A" << endl; break;
                case 0x70: cout << "MOV M, B" << endl; break;
                case 0x71: cout << "MOV M, C" << endl; break;
                case 0x72: cout << "MOV M, D" << endl; break;
                case 0x73: cout << "MOV M, E" << endl; break;
                case 0x74: cout << "MOV M, H" << endl; break;
                case 0x75: cout << "MOV M, L" << endl; break;
                case 0x76: cout << "HLT" << endl; break;
                case 0x77: cout << "MOV M, A" << endl; break;
                case 0x78: cout << "MOV A, B" << endl; break;
                case 0x79: cout << "MOV A, C" << endl; break;
                case 0x7a: cout << "MOV A, D" << endl; break;
                case 0x7b: cout << "MOV A, E" << endl; break;
                case 0x7c: cout << "MOV A, H" << endl; break;
                case 0x7d: cout << "MOV A, L" << endl; break;
                case 0x7e: cout << "MOV A, M" << endl; break;
                case 0x7f: cout << "MOV A, A" << endl; break;
                case 0x80: cout << "ADD B" << endl; break;
                case 0x81: cout << "ADD C" << endl; break;
                case 0x82: cout << "ADD D" << endl; break;
                case 0x83: cout << "ADD E" << endl; break;
                case 0x84: cout << "ADD H" << endl; break;
                case 0x85: cout << "ADD L" << endl; break;
                case 0x86: cout << "ADD M" << endl; break;
                case 0x87: cout << "ADD A" << endl; break;
                case 0x88: cout << "ADC B" << endl; break;
                case 0x89: cout << "ADC C" << endl; break;
                case 0x8a: cout << "ADC D" << endl; break;
                case 0x8b: cout << "ADC E" << endl; break;
                case 0x8c: cout << "ADC H" << endl; break;
                case 0x8d: cout << "ADC L" << endl; break;
                case 0x8e: cout << "ADC M" << endl; break;
                case 0x8f: cout << "ADC A" << endl; break;
                case 0x90: cout << "SUB B" << endl; break;
                case 0x91: cout << "SUB C" << endl; break;
                case 0x92: cout << "SUB D" << endl; break;
                case 0x93: cout << "SUB E" << endl; break;
                case 0x94: cout << "SUB H" << endl; break;
                case 0x95: cout << "SUB L" << endl; break;
                case 0x96: cout << "SUB M" << endl; break;
                case 0x97: cout << "SUB A" << endl; break;
                case 0x98: cout << "SSB B" << endl; break;
                case 0x99: cout << "SSB C" << endl; break;
                case 0x9a: cout << "SSB D" << endl; break;
                case 0x9b: cout << "SSB E" << endl; break;
                case 0x9c: cout << "SSB H" << endl; break;
                case 0x9d: cout << "SSB L" << endl; break;
                case 0x9e: cout << "SSB M" << endl; break;
                case 0x9f: cout << "SSB A" << endl; break;
                case 0xa0: cout << "ANA B" << endl; break;
                case 0xa1: cout << "ANA C" << endl; break;
                case 0xa2: cout << "ANA D" << endl; break;
                case 0xa3: cout << "ANA E" << endl; break;
                case 0xa4: cout << "ANA H" << endl; break;
                case 0xa5: cout << "ANA L" << endl; break;
                case 0xa6: cout << "ANA M" << endl; break;
                case 0xa7: cout << "ANA A" << endl; break;
                case 0xa8: cout << "XRA B" << endl; break;
                case 0xa9: cout << "XRA C" << endl; break;
                case 0xaa: cout << "XRA D" << endl; break;
                case 0xab: cout << "XRA E" << endl; break;
                case 0xac: cout << "XRA H" << endl; break;
                case 0xad: cout << "XRA L" << endl; break;
                case 0xae: cout << "XRA M" << endl; break;
                case 0xaf: cout << "XRA A" << endl; break;
                case 0xb0: cout << "ORA B" << endl; break;
                case 0xb1: cout << "ORA C" << endl; break;
                case 0xb2: cout << "ORA D" << endl; break;
                case 0xb3: cout << "ORA E" << endl; break;
                case 0xb4: cout << "ORA H" << endl; break;
                case 0xb5: cout << "ORA L" << endl; break;
                case 0xb6: cout << "ORA M" << endl; break;
                case 0xb7: cout << "ORA A" << endl; break;
                case 0xb8: cout << "CMP B" << endl; break;
                case 0xb9: cout << "CMP C" << endl; break;
                case 0xba: cout << "CMP D" << endl; break;
                case 0xbb: cout << "CMP E" << endl; break;
                case 0xbc: cout << "CMP H" << endl; break;
                case 0xbd: cout << "CMP L" << endl; break;
                case 0xbe: cout << "CMP M" << endl; break;
                case 0xbf: cout << "CMP A" << endl; break;
                case 0xc0: cout << "RNZ" << endl; break;
                case 0xc1: cout << "POP B" << endl; break;
                case 0xc2: cout << hex << "JNZ " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xc3: cout << hex << "JMP " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xc4: cout << hex << "CNZ " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xc5: cout << "PUSH B" << endl; break;
                case 0xc6: cout << hex << "ADI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xc7: cout << "RST 0" << endl; break;
                case 0xc8: cout << "RZ" << endl; break;
                case 0xc9: cout << "RET" << endl; break;
                case 0xca: cout << hex << "JZ " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xcb: cout << "-" << endl; break;
                case 0xcc: cout << hex << "CZ " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xcd: cout << hex << "CALL " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xce: cout << hex << "ACI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xcf: cout << "RST 1" << endl; break;
                case 0xd0: cout << "RNC" << endl; break;
                case 0xd1: cout << "POP D" << endl; break;
                case 0xd2: cout << hex << "JNC " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xd3: cout << hex << "OUT " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xd4: cout << hex << "CNC " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xd5: cout << "PUSH D" << endl; break;
                case 0xd6: cout << hex << "SUI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xd7: cout << "RST 2" << endl; break;
                case 0xd8: cout << "RC" << endl; break;
                case 0xd9: cout << "-" << endl; break;
                case 0xda: cout << hex << "JC " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xdb: cout << hex << "IN " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xdc: cout << hex << "CC " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xdd: cout << "-" << endl; break;
                case 0xde: cout << hex << "SBI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xdf: cout << "RST 3" << endl; break;
                case 0xe0: cout << "RPO" << endl; break;
                case 0xe1: cout << "POP H" << endl; break;
                case 0xe2: cout << hex << "JPO " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xe3: cout << "XTHL" << endl; break;
                case 0xe4: cout << hex << "CPO " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xe5: cout << "PUSH H" << endl; break;
                case 0xe6: cout << hex << "ANI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xe7: cout << "RST 4" << endl; break;
                case 0xe8: cout << "RPE" << endl; break;
                case 0xe9: cout << "PCHL" << endl; break;
                case 0xea: cout << hex << "JPE " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xeb: cout << "XCHG" << endl; break;
                case 0xec: cout << hex << "CPE " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xed: cout << "-" << endl; break;
                case 0xee: cout << hex << "XRI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xef: cout << "RST 5" << endl; break;
                case 0xf0: cout << "RP" << endl; break;
                case 0xf1: cout << "POP PSW" << endl; break;
                case 0xf2: cout << hex << "JP " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xf3: cout << "DI" << endl; break;
                case 0xf4: cout << hex << "CP " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xf5: cout << "PUSH PSW" << endl; break;
                case 0xf6: cout << hex << "ORI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xf7: cout << "RST 6" << endl; break;
                case 0xf8: cout << "RM" << endl; break;
                case 0xf9: cout << "SPHL" << endl; break;
                case 0xfa: cout << hex << "JM " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xfb: cout << "EI" << endl; break;
                case 0xfc: cout << hex << "CM " << (int)(unsigned char)buffer[i+2] << " " << (int)(unsigned char)buffer[i+1] << endl; i = i + 2; break;
                case 0xfd: cout << "-" << endl; break;
                case 0xfe: cout << hex << "CPI " << (int)(unsigned char)buffer[i+1] << endl; i++; break;
                case 0xff: cout << "RST 7" << endl; break;
                default: cout << hex << "NOINSTRUCTION: " << (int)(unsigned char)buffer[i] << endl;

            }
        }

    }
    return 0;
}