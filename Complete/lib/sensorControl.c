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
  
  if(iSensorRead >= 1000)
  {
   iSensorRead = 0;
	}
	else
  {
		if(iSensorRead <= 573 )
		{
			iSensorRead = 5;
		}
		else
		{
      iSensorRead = 122f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 1.28f);
      printf("iSensorRead: %Lu \t in volt: %f \t\t", iSensorRead, (iSensorRead * 2.5f) / 1024f );
    }
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