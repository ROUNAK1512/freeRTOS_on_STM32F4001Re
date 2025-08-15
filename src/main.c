
#include "main_header.h" 
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

 SemaphoreHandle_t xMutex;
static inline void vTask1(void *pvParameters)
{
   
    while(1)
    { 
			for(unsigned int i=0;i<650000;i++); 
			 xSemaphoreTake( xMutex, portMAX_DELAY );
       if ((*GPIOA_ODR & (1 << 5)) != 0) { // If PA5 is currently HIGH
    *GPIOA_BSRR = (1 << (5 + 16)); // Set reset bit to make it LOW
} else { // If PA5 is currently LOW
    *GPIOA_BSRR = (1 << 5);  
    }
    xSemaphoreGive( xMutex);
}
return;}

static inline void vTask2(void *pvParameters)
{
   
    while(1)
    {  for(unsigned int i=0;i<650000;i++); 
       if ((*GPIOA_ODR & (1 << 5)) == 0) { // If PA5 is currently HIGH
    *GPIOA_BSRR = (1 << (9 + 16)); // Set reset bit to make it LOW
} else { // If PA5 is currently LOW
    *GPIOA_BSRR = (1 << 9);  
    }
    
}return;}

int main()
{  xMutex=xSemaphoreCreateMutex();
	*RCC_AHPENAB = 0x1| (0x1<<2);
	*RCC_APB2ENR |= 0x1<<14; 
		*GPIOA_MODER &= ~((0x3UL << (2 * 5))|0x3UL << (2 * 9)) ;
	*GPIOA_MODER|=(0x1<<10) |(0x1<<18);
	*GPIOA_MODER &= ~(0x3UL << (2 * 7));
	*GPIOC_MODER &= ~(0x3UL << (2 * 13));
	*GPIOA_BSRR=(0x1<<0)|(0x1<<9);
		*GPIOA_BSRR=0x0;
	*SYSCFG_EXTICR4 &=~(0xF<<4);
	*SYSCFG_EXTICR4 |=(0x2<<4);
	*SYSCFG_EXTICR2 &=~(0xF<<12);
	*EXTI_IMR |= (0x1<<13 | 0x1<<7);
	*EXTI_FTSR |= (0x1<<13 );
	*EXTI_FTSR |= 0x1<<7;
	//*EXTI_RTSR |= 0x1<<7;
	__NVIC_EnableIRQ(EXTI15_10_IRQn);
	__NVIC_EnableIRQ(EXTI9_5_IRQn);
	int	ReturnVal=xTaskCreate(vTask1,"T1",configMINIMAL_STACK_SIZE,NULL,1,NULL);
	ReturnVal= xTaskCreate(vTask2,"T2",configMINIMAL_STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();

	while(1)
	{ 
		/*if((*GPIOA_IDR &(1<<7))==0){
			for(unsigned i=0;i<65000;i++);
				if ((*GPIOA_ODR & (1 << 5)) != 0) { // If PA5 is currently HIGH
    *GPIOA_BSRR = (1 << (5 + 16)); // Set reset bit to make it LOW
} else { // If PA5 is currently LOW
    *GPIOA_BSRR = (1 << 5);        // Set set bit to make it HIGH
}
			for(unsigned i=0;i<65000;i++);
		}*/
	}
	
	
	
return 0;
	
}