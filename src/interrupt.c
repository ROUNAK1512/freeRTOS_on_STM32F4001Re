extern volatile int* GPIOA_BSRR;
extern volatile int* GPIOC_IDR;
extern volatile int* EXTI_PR;
extern volatile int *GPIOA_ODR;
 void EXTI15_10_IRQHandler(void ) 
{ unsigned int i;
for(i=0;i<65000;i++);
		
	 if ((*EXTI_PR & (1 << 13)) != 0)
		{ 
			
			if ((*GPIOA_ODR & (1 << 5)) != 0) { // If PA5 is currently HIGH
    *GPIOA_BSRR= (1 << (5 + 16)); // Set reset bit to make it LOW
} else { // If PA5 is currently LOW
    *GPIOA_BSRR = (1 << 5);        // Set set bit to make it HIGH
}
			*EXTI_PR = (1 << 13);
		}
	
	}

	void EXTI9_5_IRQHandler(void ) 
{ unsigned int i;
for(i=0;i<65000;i++);
		
	 if ((*EXTI_PR & (1 << 7)) != 0)
		{ 
			
			if ((*GPIOA_ODR & (1 << 5)) != 0) { // If PA5 is currently HIGH
    *GPIOA_BSRR = (1 << (5 + 16)); // Set reset bit to make it LOW
} else { // If PA5 is currently LOW
    *GPIOA_BSRR = (1 << 5);        // Set set bit to make it HIGH
}
			*EXTI_PR = (1 << 7);
		}
	
	}