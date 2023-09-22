#include <16F887.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=4000000)

#use FIXED_IO( C_outputs=PIN_C7,PIN_C6,PIN_C5,PIN_C4,PIN_C3,PIN_C2,PIN_C1,PIN_C0 )
#use FIXED_IO( D_outputs=PIN_D7,PIN_D6,PIN_D5,PIN_D4,PIN_D3,PIN_D2,PIN_D1,PIN_D0 )

#define state1   PIN_D2
#define state2   PIN_D1
#define state3   PIN_D0
#define state4   PIN_D7
#define state5   PIN_D6
#define state6   PIN_D5
#define state7   PIN_D4
#define state8   PIN_D3

#define out1   PIN_C4
#define out2   PIN_C5
#define out3   PIN_C6
#define out4   PIN_C7
#define out5   PIN_C0
#define out6   PIN_C1
#define out7   PIN_C2
#define out8   PIN_C3

#define btn1   PIN_B7
#define btn2   PIN_B6
#define btn3   PIN_B5
#define btn4   PIN_B4
#define btn5   PIN_B3
#define btn6   PIN_B2
#define btn7   PIN_B1
#define btn8   PIN_B0

