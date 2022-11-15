/*
 * To new beginings - This is a combined to get me back up to speed
 *  When it comes to c, and a few new methods as well.
 *
 */

#include <stdio.h>
#include <string.h>


/* meet.c - to greet using inputs from function
 * to use greeting(firstname, secondname);
 */
void greeting(char *temp1, char *temp2) {
    char name[512];
    strcpy(name, temp2);
    printf("Hello %s %s\n", temp1, name);
    printf("BYE\n");
    /* greeting(argv[1], argv[2]); */
}

int main(int argc, char * argv[]) {
    greeting(argv[1], argv[2]);
}


/* Compiling with gcc {{{
 *  -O <filename> Saves the compiled binary with this name. The
 *              default is to ssave the output as a.out
 *  -S Produces a file containing assembly instructions; saved with an .S
 *              extension.
 *  -ggdb Produces extra debuggin infromatino; useful when using the GNU
 *              debugger (gdb).
 *  -c Compiles without linkking; produces object files with an
 *              .o extension
 *  -mprefferred--stack-boundary=2  Compiles the program using DWORD size stack
 *              simplifying the debugging process while you learn.
 *  -fno-stack-protector    Disables the stack protection; introduced with GCC
 *              4.1. This option iss useful when you're learning about buffer
 *              overflows.
 *  -z execstack    Enables an executable stack. This option is useful when
 *              you're learning about buffer overflows.
 * }}} */

/* Computer Memmory Size {{{Type
 * 1 or 0                   bit
 * 4 bits                   nibble
 * 2 nibbles or 8 bits      byte
 * 1024 bytes               KiloByte(KB)
 * 1024 KiloBytes           GigaByte(GB)
 * 1024 GigaBytes           TeraByte(TB)
 * 1024 TeraBytes           PetaByte(PB)
 * 1024 PetaBytes           HexaByte/exaByte(EB)
 * 1024 ExaBytes            ZettaByte(ZB)
 * 1024 ZettaBytes          YottaByte(YB)
 * 1024 YottaBytes          BrontoByte
 * 1024 BrontoBytes         GeopByte
 * }}} */

// vim: tw=80