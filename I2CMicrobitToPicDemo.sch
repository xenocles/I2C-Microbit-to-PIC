EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "I2C Microbit to PIC"
Date "2023-12-30"
Rev "1"
Comp "Jonathan Carr"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L JC_SMD:PIC12LF1552 U1
U 1 1 658F92A1
P 6850 2900
F 0 "U1" H 7450 2000 50  0000 C CNN
F 1 "PIC12LF1552" H 7450 3074 50  0000 C CNN
F 2 "Microchip-PIC12LF1552" H 6850 3300 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/40001723A.pdf" H 6850 3400 50  0001 L CNN
	1    6850 2900
	1    0    0    -1  
$EndComp
Text GLabel 6950 3600 0    50   Input ~ 0
VDD
Text GLabel 7950 3600 2    50   Input ~ 0
VSS
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 658FB2D0
P 4700 3000
F 0 "J1" H 4800 2700 50  0000 C CNN
F 1 "PIC ICSP Connector" H 4900 3400 50  0000 C CNN
F 2 "" H 4700 3000 50  0001 C CNN
F 3 "~" H 4700 3000 50  0001 C CNN
	1    4700 3000
	1    0    0    -1  
$EndComp
Text Notes 4650 2800 2    50   ~ 0
MCLR
Text Notes 4650 2900 2    50   ~ 0
VDD
Text Notes 4650 3000 2    50   ~ 0
GND
Text Notes 4650 3100 2    50   ~ 0
PGD
Text Notes 4650 3200 2    50   ~ 0
PGC
Text GLabel 4900 2900 2    50   Input ~ 0
VDD
Text GLabel 4900 3000 2    50   Input ~ 0
VSS
Text GLabel 4900 2800 2    50   Input ~ 0
MCLR
Text GLabel 4900 3100 2    50   Input ~ 0
ICSPDAT
Text GLabel 4900 3200 2    50   Input ~ 0
ICSPCLK
Text GLabel 6750 2900 0    50   Input ~ 0
ICSPCLK
Text GLabel 6750 3200 0    50   Input ~ 0
MCLR
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 659046BE
P 4700 4000
F 0 "J2" H 4800 3700 50  0000 C CNN
F 1 "Microbit breakout" H 4800 4300 50  0000 C CNN
F 2 "" H 4700 4000 50  0001 C CNN
F 3 "~" H 4700 4000 50  0001 C CNN
	1    4700 4000
	1    0    0    -1  
$EndComp
Text Notes 4650 3900 2    50   ~ 0
I2C_EXT_SDA/P20
Text Notes 4650 4000 2    50   ~ 0
I2C_EXT_SCL/P19
Text Notes 4650 4100 2    50   ~ 0
3V
Text Notes 4650 4200 2    50   ~ 0
GND
Text GLabel 4900 4200 2    50   Input ~ 0
VSS
Text GLabel 4900 4100 2    50   Input ~ 0
VDD
Text Notes 4200 3250 2    50   Italic 0
Note: Disconnect Microbit\nSCL before ICSP programming\n\nEnsure the programmer is not\npowering the target circuit,\notherwise completely disconnect\nthe Microbit before programming
Text GLabel 4900 3900 2    50   Input ~ 0
SDA
Text GLabel 4900 4000 2    50   Input ~ 0
SCL
$Comp
L Device:R R2
U 1 1 6590AB05
P 6350 3550
F 0 "R2" H 6420 3596 50  0000 L CNN
F 1 "1K" H 6420 3505 50  0000 L CNN
F 2 "" V 6280 3550 50  0001 C CNN
F 3 "~" H 6350 3550 50  0001 C CNN
	1    6350 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 6590B3BE
P 6350 3850
F 0 "D1" V 6389 3732 50  0000 R CNN
F 1 "LED" V 6298 3732 50  0000 R CNN
F 2 "" H 6350 3850 50  0001 C CNN
F 3 "~" H 6350 3850 50  0001 C CNN
	1    6350 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 3400 6350 3400
$Comp
L Device:R R1
U 1 1 6590E658
P 5850 3550
F 0 "R1" H 5920 3596 50  0000 L CNN
F 1 "22K" H 5920 3505 50  0000 L CNN
F 2 "" V 5780 3550 50  0001 C CNN
F 3 "~" H 5850 3550 50  0001 C CNN
	1    5850 3550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 65910358
P 5850 3000
F 0 "SW1" V 5896 2952 50  0000 R CNN
F 1 "SW_Push" V 5805 2952 50  0000 R CNN
F 2 "" H 5850 3200 50  0001 C CNN
F 3 "~" H 5850 3200 50  0001 C CNN
	1    5850 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 3300 6950 3300
Wire Wire Line
	5850 3300 5850 3400
Wire Wire Line
	5850 3700 5850 4100
Wire Wire Line
	5850 4100 6350 4100
Wire Wire Line
	6350 4000 6350 4100
Text GLabel 6750 3100 0    50   Input ~ 0
SDA
Text GLabel 6750 3000 0    50   Input ~ 0
SCL
Text GLabel 6750 2800 0    50   Input ~ 0
ICSPDAT
Wire Wire Line
	6950 3200 6750 3200
Wire Wire Line
	6750 3100 6950 3100
Wire Wire Line
	6950 3000 6800 3000
Wire Wire Line
	6750 2900 6800 2900
Wire Wire Line
	6800 2900 6800 3000
Connection ~ 6800 3000
Wire Wire Line
	6800 3000 6750 3000
Wire Wire Line
	6950 2900 6850 2900
Wire Wire Line
	6850 2900 6850 2800
Wire Wire Line
	6850 2800 6750 2800
Wire Wire Line
	5850 2800 5850 2700
Wire Wire Line
	5850 4100 5850 4200
Connection ~ 5850 4100
Text GLabel 5850 4200 3    50   Input ~ 0
VSS
Text GLabel 5850 2700 1    50   Input ~ 0
VDD
Wire Wire Line
	5850 3200 5850 3300
Connection ~ 5850 3300
$Comp
L power:VDD #PWR?
U 1 1 6592FE9F
P 6650 4700
F 0 "#PWR?" H 6650 4550 50  0001 C CNN
F 1 "VDD" V 6665 4827 50  0000 L CNN
F 2 "" H 6650 4700 50  0001 C CNN
F 3 "" H 6650 4700 50  0001 C CNN
	1    6650 4700
	0    -1   -1   0   
$EndComp
$Comp
L power:VSS #PWR?
U 1 1 65930B60
P 6650 4850
F 0 "#PWR?" H 6650 4700 50  0001 C CNN
F 1 "VSS" V 6665 4978 50  0000 L CNN
F 2 "" H 6650 4850 50  0001 C CNN
F 3 "" H 6650 4850 50  0001 C CNN
	1    6650 4850
	0    -1   -1   0   
$EndComp
Text GLabel 6650 4700 2    50   Input ~ 0
VDD
Text GLabel 6650 4850 2    50   Input ~ 0
VSS
Text Notes 6950 4850 0    50   ~ 0
Current draw is low enough to \ndrive this circuit from the Microbit
$EndSCHEMATC
