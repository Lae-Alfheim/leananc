# Welcome to new beginings

This is my relearn of c, hopfully the proper way.

This will be apart of a multitude of books that I am reading. I hope this could
help all of you may need help in learning c, or for your computer science, or
something of the like. :)

# Compiling with gcc 

- -O <filename> Saves the compiled binary with this name. The
            default is to ssave the output as a.out
- -S Produces a file containing assembly instructions; saved with an .S
            extension.
- -ggdb Produces extra debuggin infromatino; useful when using the GNU
            debugger (gdb).
- -c Compiles without linkking; produces object files with an
            .o extension
- -mprefferred--stack-boundary=2  Compiles the program using DWORD size stack
            simplifying the debugging process while you learn.
- -fno-stack-protector    Disables the stack protection; introduced with GCC
            4.1. This option iss useful when you're learning about buffer
            overflows.
- -z execstack    Enables an executable stack. This option is useful when
            you're learning about buffer overflows.


# Computer Memory Size

|What Makes It Up        |Name of size          |
|------------------------|----------------------|
|1 or 0                  |bit                   |
|4 bits                  |nibble                |
|2 nibbles or 8 bits     |byte                  |
|1024 bytes              |KiloByte(KB)          |
|1024 KiloBytes          |GigaByte(GB)          |
|1024 GigaBytes          |TeraByte(TB)          |
|1024 TeraBytes          |PetaByte(PB)          |
|1024 PetaBytes          |HexaByte/exaByte(EB)  |
|1024 ExaBytes           |ZettaByte(ZB)         |
|1024 ZettaBytes         |YottaByte(YB)         |
|1024 YottaBytes         |BrontoByte            |
|1024 BrontoBytes        |GeopByte              |


# Segmentation of Memory

Each process (oversimplifie) needs to have access to its own area in memory.
After all you would not want process overwriting another programs data. So the
solution is to break down the momory into segments and hand it out to the
processes as they are needed. The Register are used to store and keep track of
the current segments. Offset registers are used to keep track of where in the
segment critical pieces of data are kept. It also describes the memory layout
within a virtual address space. Some segments are intentionally allocated to
different regions of the address, within a process to prevent a collision.

Withing some of these sections there are many reginons, for now will stick with
the main 6.

## .text section

this section, also know as the code segment, corrisponds the text portion of the
binary executable file. This section is marked as readable and ececutable,
without any write permissions, generating a violation if attempt made. The size
if fixed at runtime.

## .data section

The data section is used to store global initialized variables, such as
        int i = 12;

The size is again fixed at runtime.

## .bss secetion

The bellow stack section is used to store certain types of global non
initialized variables such as
        int i;

The size is Fixed at runtime. needt to be readable and writeable but not
executable.


## Heap Section

Used to store dynamically allocated variables and grows from the lower-addressed
memory to the higher-addressed memory, Controled through malloc, realloc, and
free. For example
        int i = malloc(sizeof(int));

This section should be readable and writeable but should not be executable, an
attacker could easily perform shellcode execution other ways.


## Stack Section

Used to keep track of function calls, and grows from higher addressed memory to
lower. if multithreaded, each thread will have a unique stack. The way the
memory is addressed allows for buffer overflows to exist.

## MORE SOON...



<!-- vim: tw=80
-->
