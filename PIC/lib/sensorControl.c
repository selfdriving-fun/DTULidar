#include "sensorControl.h"

void initSensors()
{
  /* Setup the  ADC to 2.5V */
  //setup_vref(VREF_LOW | 0x0C);
  setup_vref(0xEC);
  setup_adc(ADC_CLOCK_DIV_32);
  setup_adc_ports (sAN4 | sAN6 | VSS_VREF);
   
  /* Initially start with channel 6 */
  set_adc_channel(6);
}

int16 readRangeSensor()
{
   float fShortMeasRange = readShortRangeSensor();
   float fLongMeasRange = readLongRangeSensor();
   
   //DEBUG
   return ((int16)fShortMeasRange);
   //DEBUG
   
   if(fShortMeasRange == 150)
   {
      return ((int16)fLongMeasRange);
   }
   else
   {
      return ((int16)fShortMeasRange);
   }
}

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

float readLongRangeSensor()
{
  unsigned int16 iSensorRead;
  float fSensorRead;
  float fCumulativeMeasurement = 0.0f;
  
  for(int i = 0; i <10; i++)
  {
     iSensorRead = readInternalAdc(CHANNEL_LONG_RANGE);
  
     if(iSensorRead >= 940)
     {
      fSensorRead = 0;
      }
      else
     {
         if(iSensorRead <= 630 )
         {
            fSensorRead = 500;
         }
         else
         {
         fSensorRead = 122f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 1.28f);
   //      printf("iSensorRead: %Lu \t in volt: %f \t\t", iSensorRead, (iSensorRead * 2.5f) / 1024f );
       }
     }
     
     fCumulativeMeasurement += fSensorRead; 
   }
  
   return (fCumulativeMeasurement/10.0f);
}

float readShortRangeSensor()
{
  unsigned int16 iSensorRead;
  float fSensorRead;
  float fCumulativeMeasurement = 0;
  
  for(int i = 0; i<10; i++)
  {
   iSensorRead = readInternalAdc(CHANNEL_SHORT_RANGE);
   // measurement below 30cm
   if(iSensorRead >= 724 )
   {
      fSensorRead = 30;
   }
   else 
   {
      // measurement above 150
      if( iSensorRead <= 204 )
         fSensorRead = 150;
      else
         fSensorRead = 50f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 0.1f); 
   }
   fCumulativeMeasurement += fSensorRead;
  }
  
  return (fCumulativeMeasurement/10.0);
}
