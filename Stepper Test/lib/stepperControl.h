#ifndef stepperControl
#define stepperControl

/*Declarations*/
#BYTE portc = 7            // Port used to control motor
#BYTE portd = 8      // PIC16F887 datasheet page 25
#define BOTTOM_MOTOR 0 
#define TOP_MOTOR 1
#define BOTTOM_MOTOR_LIMIT 45
#define TOP_MOTOR_LIMIT 30

/* Globals */
BYTE const POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
unsigned int8 iCurrentState[2] = { 0 }; /* This variable keeps track of the current state */
unsigned int32 iDelay = 5000; // delay default 5ms
signed int8 iGlobalPosition[2] = { 0 };
int1  bSequenceOver = FALSE;
int1  bGlobalGoRight = FALSE;

void initStepper(void);
void stepperRotateSingleRight(int motor);
void stepperRotateSingleLeft(int motor);
int16 moveMeasure(int measureTime_ms, int rotation);
void stepperRotate180right(int timeDelay_us, int motor);
void stepperRotate180left(int timeDelay_us, int motor);
void stepperMotorSequenceTop(void);
void stepperMotorSequence(void);

#endif
