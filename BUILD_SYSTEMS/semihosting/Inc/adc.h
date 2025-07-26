#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>

#define GPIOAEN                 (1U<<0)
#define ADC1EN                  (1U<<8)
#define ADC_CH1	                (1U<<0)
#define ADC_SEQ_LEN_1           (0x00)
//#define ADC_CR2_AD0N            (1U<<0)
//#define ADC_CR2_SWSTART         (1U<<30)
//#define ADC_SR_EOC              (1U<<1)
//#define ADC_CR2_CONT            (1U<<1)


void pa1_adc_init(void);
uint32_t adc_read(void);
void start_converstion(void);

#endif /* INC_ADC_H_ */