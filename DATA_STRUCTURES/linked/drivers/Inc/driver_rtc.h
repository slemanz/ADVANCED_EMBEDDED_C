#ifndef INC_DRIVER_RTC_H_
#define INC_DRIVER_RTC_H_
#include <stdint.h>
#include "stm32f411xx.h"


#define CR_ALRAIE					(1U<<12)
#define ISR_ALRAF					(1U<<8)
#define ISR_INIT					(1U<<7)

#define CR_TSIE						(1U<<15)
#define CR_TSE						(1U<<11)
#define ISR_TSF						(1U<<11)

#define RTC_TAFCR_TAMPIE            (1U << 2U)
#define RTC_TAFCR_TAMP1TRG          (1U << 1U)
#define RTC_TAFCR_TAMP1E            (1U << 0U)

#define RTC_ISR_TAMP1F              (1U << 13U)

#define RTC_ALRMAR_MSK4             (1U << 31U)

#define RTC_DR_DU_Pos               (0U)
#define RTC_DR_DT                   (0x3UL << 4U)
#define RTC_DR_DU                   (0xFUL << 0)


#define EXTI_IMR_MR21               (1U << 21U)
#define EXTI_IMR_IM21               EXTI_IMR_MR21

void rtc_init(void);
void rtc_alarm_init(void);
void rtc_timestamp_init(void);

uint8_t rtc_convert_bcd2bin(uint8_t value);
uint32_t rtc_date_get_day(void);
uint32_t rtc_date_get_year(void);
uint32_t rtc_date_get_month(void);
uint32_t rtc_time_get_second(void);
uint32_t rtc_time_get_minute(void);
uint32_t rtc_time_get_hour(void);
void rtc_timestamp_init(void);
void rtc_tamper_detect_init(void);

#endif