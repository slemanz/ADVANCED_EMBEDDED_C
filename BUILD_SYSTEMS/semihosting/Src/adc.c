#include "stm32f401xx.h"
#include "adc.h"

void pa1_adc_init(void)
{
    /***Configure the ADC GPIO pin ***/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set the mode of PA1 to analog*/
	GPIOA->MODER |=(1U<<2);
	GPIOA->MODER |=(1U<<3);
	/***Configure the ADC module***/
	/*Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN;

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/*Enable ADC module*/
	ADC1->CR2 |= ADC_CR2_AD0N;
}

uint32_t adc_read(void)
{
    /*Wait for conversion to be complete*/
	while(!(ADC1->SR & ADC_SR_EOC)){}

	/*Read converted result*/
	return (ADC1->DR);
}

void start_converstion(void)
{
    /*Enable continuous conversion*/
	ADC1->CR2 |= ADC_CR2_CONT;
	/*Start adc conversion*/
	ADC1->CR2 |= ADC_CR2_SWSTART;
}