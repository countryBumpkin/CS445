* *************************************
* C- Compiler version 1.0
* Author: Garrett Wells
* *************************************
* 
* FUNCTION input
1:	ST	3, -1(1) Store return address
2:	IN	2, 2, 2 Grab int input
3:	LD	3, -1(1) Load return address
4:	LD	1, 0(1) Adjust
5:	JMP	7, 0(3) Return
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* END FUNCTION inputb
6:	ST	3, -1(1) Store return address
7:	INB	2, 2, 2 Grab bool input
8:	LD	3, -1(1) Load return address
9:	LD	1, 0(1) Adjust fp
10:	JMP	7, 0(3) Return
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
11:	ST	3, -1(1) Store return address
12:	INC	2, 2, 2 Grab char input
13:	LD	3, -1(1) Load return address
14:	LD	1, 0(1) Adjust
15:	JMP	7, 0(3) Return
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
16:	ST	3, -1(1) Store return address
17:	LD	3, -2(1) Load parameter
18:	OUT	3, 3, 3 Output integer
19:	LD	3, -1(1) Load return address
20:	LD	1, 0(1) Adjust
21:	JMP	7, 0(3) Return
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
22:	ST	3, -1(1) Store return address
23:	LD	3, -2(1) Load parameter
24:	OUTB	3, 3, 3 Output bool
25:	LD	3, -1(1) Load return address
26:	LD	1, 0(1) Adjust
27:	JMP	7, 0(3) Return
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
28:	ST	3, -1(1) Store return address
29:	LD	3, -2(1) Load parameter
30:	OUTC	3, 3, 3 Output char
31:	LD	3, -1(1) Load return address
32:	LD	1, 0(1) Adjust
33:	JMP	7, 0(3) Return
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
34:	ST	3, -1(1) Store return address
35:	OUTNL	3, 3, 3 Output a newline
36:	LD	3, -1(1) Load return address
37:	LD	1, 0(1) Adjust
38:	JMP	7, 0(3) Return
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF dec: -2
39:	ST	3, -1(1) Store return address
* Compound
* CALLING outputb
* TOFF dec: -2
40:	ST	1, -2(1) store frame pointer in dmem
* PARAM
41:	LDC	3, 1(0) Load Boolean constant
42:	ST	3, -4(1) Push parameter
* END PARAM
43:	LDA	1, -1(1) Ghost frame becomes new active frame
44:	LDA	3, 1(7) Return address in ac
45:	JMP	7, -27(7) Call outputb
46:	LDA	3, 0(2) Save result in ac
* END CALL outputb
* END COMPOUND
47:	LDA	2, 0(6) load function return with a value in register xxx
48:	LD	3, -1(1) recover old pc
49:	LD	1, 0(1) pop the frame
50:	JMP	7, 0(3) jump to old pc
* END FUNCTION main
* 
0:	JMP	7, 0(7) JMP to init
* INIT
51:	LDA	3, 1(7) return address in ac
52:	ST	1, 0(1) store old 
53:	LDA	3, 1(7) return address in ac
54:	JMP	7, -15(7) jump to main
55:	HALT	0, 0, 0 END EXECUTION
* END INIT
