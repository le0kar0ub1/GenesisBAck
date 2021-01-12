# Debug module

The debug module host a GDB-like debugger which is the scheduler of the DEBUG routine (the RELEASE one being the core module).

All the arguments must be given in the described ordrer.

Command name  | Alias | Usage (order respects)     | Description     
--------------|-------|----------------------------|------------------------------------
quit          | q     | `quit`                     | Quit the program
help          | h     | `help [CMD]`               | Display help for all commands or the CMD
continue      | c     | `continue`                 | Execute until next breakpoint (only one breakpoint allowed)
next          | n     | `next [N]`                 | Execute the next next N instruction, defaulting to 1
dump          |       | `dump SIZE ADDR`           | Hexdump SIZE bytes starting at the given ADDR (the address will not be 0x10-aligned)
regs          | r     | `regs [REG]`               | Display all the registers or the REG
burst         | b     | `burst [{(N)\|(N ADDR)}]`  | Disassemble N instructions at the given ADDR, defaulting to PC
breakpoint    | br    | `breakpoint ADDR`          | Put a breakpoint at the given ADDR
wreg          |       | `wreg REG EXPR`            | Write the EXPR in the REG
load          |       | `load [SIZE] ADDR`         | Print SIZE of the given ADDR, defaulting to 4
store         |       | `store [SIZE] EXPR ADDR`   | Store EXPR sizeof SIZE at the given ADDR, defaulting to 4
module        | mod   | `module {NAME\|list}`      | Display information about the given module or list them

Legend:
  * `UPPERCASE` => dynamic expression (variable)
  * `lowercase` => static expression
  * `[]` => optionnal
  * `{}` => multiple option (required or not)
  * `|` => or