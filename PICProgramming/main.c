
/*
#include <main.h>
//#include "lcd16216.c"

#define PWM_PERIOD_VAL 199   //250   // Calculated
#define PWM_DUTY_MIN 0
#define PWM_DUTY_MAX 800 //change

int pwm_count = 0;
int servo_angle = 0;


#int_ccp1
void ccp1_int(){
//   output_toggle(PIN_D0);
   
   if(pwm_count++ == 200){
      pwm_count = 0;
   }
   
   if(pwm_count <= 19){ //servo_angle
      output_high(PIN_D0);      
   }else{
      output_low(PIN_D0);
   } 
}


void main()
{
   

   setup_oscillator(OSC_8MHZ,2);
   CCP_1 = 25;
   setup_ccp1(CCP_COMPARE_RESET_TIMER|CCP_COMPARE_INT);
//   setup_ccp1(CCP_COMPARE_RESET_TIMER); 
//   setup_ccp1(CCP_COMPARE_INT); 
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   
   enable_interrupts(INT_CCP1);
   enable_interrupts(GLOBAL);

   while(TRUE){
      
      while(servo_angle < 19){
         servo_angle++;
         delay_ms(50);
      }
      while(servo_angle > 9){
         servo_angle--;
         delay_ms(50);
      }
   }

   
   
   
   
   while(1){
   
   }
   
   
}
*/




#include <main.h>

#define CHANNEL_LONG_RANGE  4
#define CHANNEL_SHORT_RANGE 6

unsigned int16 readInternalAdc(unsigned int8 channel)
{
  set_adc_channel(channel);
  delay_us(20);

  read_adc(ADC_START_ONLY); // start the ADC for conversion
  
  int1 done = adc_done();   // Poll on ADC result
  while(!done) 
  {
    // wait until measurement is ready
    done = adc_done();
  }
  
  // read conversion result
  return((int16)read_adc(ADC_READ_ONLY));
}

//unsigned int16 readLongRangeSensor()
float readLongRangeSensor()
{
  unsigned int16 iSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_LONG_RANGE);
  
  if(iSensorRead >= 1000 || iSensorRead <= 573 ){
   iSensorRead = 0;
  }
  else
  {
      iSensorRead = 122f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 1.28f);
      /* Add conversion formulas here */
      //  return ((275 * iSensorRead) / 1025);
      //  return ((float) iSensorRead) * 0.268f;
      printf("iSensorRead: %Lu \t in volt: %f \t\t", iSensorRead, (iSensorRead * 2.5f) / 1024f );
   
  }
   return iSensorRead;
}

unsigned int16 readShortRangeSensor()
{
  unsigned int16 iSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_SHORT_RANGE);
  /* Add conversion formulas here */
  return iSensorRead;
}

void init()
{
  setup_oscillator(OSC_8MHZ,2);
 
  /* Setup the  ADC to 2.5V */
  //setup_vref(VREF_LOW | 0x0C);
   setup_vref(0xEC);
  setup_adc(ADC_CLOCK_DIV_32);
  setup_adc_ports (sAN4 | sAN6 | VSS_VREF);
   
  /* Initially start with channel 6 */
  set_adc_channel(6);
}


void main()
{
  init();

  while(1)
  {
//   printf("Long range read: %lu\n", readLongRangeSensor());
   printf("Long range read: %f\n", readLongRangeSensor());    
    
//    printf("Short range read: %lu\n\n", readShortRangeSensor());
    delay_ms(20);
  }
}