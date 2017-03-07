Set of instructions to be followed in the input file

2)$zero is to be written as $0

3)$sp(the pointer) is assumed to be zero. So, if an instruction has to do with $sp, then the final value of $sp is based on this assumption

4)After every register, a comma followed by a space is adhered to, i.e, addi $t0,$t0,12 is invalid. It should be addi $t0, $t0, 12

5)Don’t use any instruction other than add, addi, sub, mul, and, andi, or, ori, nor, slt, slti, lw, sw, beq, bne, j, halt

6)Input MIPS file should be of name Untitled with extension .txt and the file should be in the same directory of C file

7)For instruction mul all three should be registers, i.e, mul $t0, $t1, 12 is invalid

9)The instruction la shouldn’t be there in the MIPS file. So in sw/lw, offset is defined only for $sp,As there isn’t la use sub,add for stack pointer increments and decrements.

10)Errors that can be formed are infinite. So identifying ALL the syntax errors in the input MIPS file is highly impossible.

11)

12)In output the values the values of that particular  step are shown in the brackets , i.e, addi $t0,$t0,$t1
In output you could see 

Values before the operation and then the values after the operation at each step
Finally all register values are printed stack values aren’t printed

