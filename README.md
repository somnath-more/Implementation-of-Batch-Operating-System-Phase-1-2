# Implementation-of-Batch-Operating-System-Phase-1-2
Implementation of Batch-Operating System Phase 1 &amp; 2
I will Explain all about Input and Output File
Phase 1:
input_Phase_1.txt
$AMJ000200160003
GD30GD40GD50LR50SR60LR52SR61PD30PD40LR30CR40BT14PD50HPD60H
$DTA 
IIT
NIT
IS  NOT SAME
$END0002

OUTPUT:output_Phase1.txt
code in memory 
Memory :       
0: G D 3 0     
1: G D 4 0     
2: G D 5 0     
3: L R 5 0     
4: S R 6 0     
5: L R 5 2     
6: S R 6 1     
7: P D 3 0     
8: P D 4 0     
9: L R 3 0     
10: C R 4 0    
11: B T 1 4    
12: P D 5 0    

Execution0: GD30
Data is IIT
Row No is 30

Execution1: GD40
Data is NIT
Row No is 40

Execution2: GD50
Data is IS  NOT SAME
Row No is 50

Execution3: LR50

Execution4: SR60

Execution5: LR52

Execution6: SR61

Execution7: PD30

Execution8: PD40

Execution9: LR30

Execution10: CR40
C: F

Execution11: BT14
C is F
Instruction counter is now 11

Execution12: PD50
Memory After Execution :
0: G D 3 0
1: G D 4 0
2: G D 5 0 
3: L R 5 0
4: S R 6 0
5: L R 5 2
6: S R 6 1
7: P D 3 0
8: P D 4 0
9: L R 3 0 
10: C R 4 0
11: B T 1 4
12: P D 5 0
13: * * * *
14: * * * * 
15: * * * *
16: * * * *
17: * * * *
18: * * * *
19: * * * *
20: * * * *
21: * * * *
22: * * * *
23: * * * * 
24: * * * *
25: * * * *
26: * * * *
27: * * * *
28: * * * *
29: * * * * 
30: I I T *
31: * * * *
32: * * * *
33: * * * *
34: * * * * 
35: * * * *
36: * * * *
37: * * * *
38: * * * *
39: * * * * 
40: N I T *
41: * * * *
42: * * * *
43: * * * *
44: * * * *
45: * * * *
46: * * * * 
47: * * * *
48: * * * *
49: * * * *
50: I S
51: N O T
52: S A M E
53: * * * * 
54: * * * *
55: * * * *
56: * * * *
57: * * * *
58: * * * *
59: * * * *
60: I S     
61: S A M E
62: * * * *
63: * * * *
64: * * * *
65: * * * *
66: * * * *
67: * * * * 
68: * * * *
69: * * * *
70: * * * *
71: * * * *
72: * * * *
73: * * * *
74: * * * *
75: * * * * 
76: * * * *
77: * * * *
78: * * * *
79: * * * *
80: * * * *
81: * * * *
82: * * * *
83: * * * *
84: * * * *
85: * * * *
86: * * * *
87: * * * *
88: * * * *
89: * * * *
90: * * * *
91: * * * *
92: * * * *
93: * * * *
94: * * * *
95: * * * *
96: * * * *
97: * * * *
98: * * * *
99: * * * *
 
 
 
 
 
////////////////////////////////////////////////////////OSPHASE 2////////////////////////////////////////////////////////////////////////////////
input_Phase_2.txt
$AMJ000100050002
GD10PD10GD20PD20H
$DTA
HELLO WORLD
No Error Job
$END0001

$AMJ000200050002
GD10PD10GD20PD20H
$DTA
$END0002

$AMJ000300050002
GD10PD10GD20PD20H
$DTA
HELLO WORLD
$END0003

$AMJ000400030002
GD10PD10GD20PD20H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0004

$AMJ000500050002
LD10PD10GD20PD20H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0005

$AMJ000600050002
GDLOPD10GD20PD20H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0006

$AMJ000700060002
GD10PD10GD20PD20SR30H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0007

$AMJ000800050001
GD10PD10GD20PD20H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0008

$AMJ000900030001
GD10PD10GD20LS20H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0009

$AMJ001000030001
GD10PD10GD20PDL1H
$DTA
HELLO WORLD
STAY HOME STAY SAFE
$END0010

$AMJ001100030001
GD10PD20H
$DTA
INVALID PAGE
$END0011

///////////////////////output_Phase_2.txt//////
OUTPUT:
Execution log for JobID : 1
TTL: 5
TLL: 2

Valid page fault at IC: 1
Get data from RA: 40
Data printed to output file at RA: 40
Valid page fault at IC: 3
Get data from RA: 100
Data printed to output file at RA: 100
End of Execution of JobID: 1


Execution log for JobID : 2
TTL: 5
TLL: 2

Valid page fault at IC: 1
Get data from RA: 180
End of Execution of JobID: 2


Execution log for JobID : 3
TTL: 5
TLL: 2

Valid page fault at IC: 1
Get data from RA: 140
Data printed to output file at RA: 140
Valid page fault at IC: 3
Get data from RA: 50
End of Execution of JobID: 3


Execution log for JobID : 4
TTL: 3
TLL: 2

Valid page fault at IC: 1
Get data from RA: 270
Data printed to output file at RA: 270
Valid page fault at IC: 3
Get data from RA: 110
End of Execution of JobID: 4


Execution log for JobID : 5
TTL: 5
TLL: 2

End of Execution of JobID: 5


Invalid page fault at IC: 0
Execution log for JobID : 6
TTL: 5
TLL: 2

End of Execution of JobID: 6


Execution log for JobID : 7
TTL: 6
TLL: 2

Valid page fault at IC: 1
Get data from RA: 20
Data printed to output file at RA: 20
Valid page fault at IC: 3
Get data from RA: 30
Data printed to output file at RA: 30
Valid page fault at IC: 5
Content of general register stored at RA : 220
End of Execution of JobID: 7


Execution log for JobID : 8
TTL: 5
TLL: 1

Valid page fault at IC: 1
Get data from RA: 260
Data printed to output file at RA: 260
Valid page fault at IC: 3
Get data from RA: 80
Data printed to output file at RA: 80
End of Execution of JobID: 8


Execution log for JobID : 9
TTL: 3
TLL: 1

Valid page fault at IC: 1
Get data from RA: 60
Data printed to output file at RA: 60
Valid page fault at IC: 3
Get data from RA: 110
End of Execution of JobID: 9


Execution log for JobID : 10
TTL: 3
TLL: 1

Valid page fault at IC: 1
Get data from RA: 220
Data printed to output file at RA: 220
Valid page fault at IC: 3
Get data from RA: 170
End of Execution of JobID: 10


Execution log for JobID : 11
TTL: 3
TLL: 1

Valid page fault at IC: 1
Get data from RA: 240
End of Execution of JobID: 11


Invalid page fault at IC: 0
Data printed to output file at RA: -1

Thank you!!!!!

