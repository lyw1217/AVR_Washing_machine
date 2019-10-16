/*
 * adc.h
 *
 * Created: 2019-07-10 오후 12:42:12
 *  Author: LYW
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "main.h"

void ADC_init(unsigned char channel);
int read_ADC();
void ADC_init_single();
int read_ADC_single(unsigned char channel);


#endif /* ADC_H_ */