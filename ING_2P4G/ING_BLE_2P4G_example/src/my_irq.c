#include "my_irq.h"
#include "ing_2p4g.h"




#if 1
#define IRQ_OFFSET      16

#define IRQ_TIM2        (5 + IRQ_OFFSET)
#define IRQ_TIM1        (6 + IRQ_OFFSET)
#define IRQ_DMA         (22 + IRQ_OFFSET)
#define IRQ_KEYSCAN     (23 + IRQ_OFFSET)
#define IRQ_USB         (31 + IRQ_OFFSET)
#define IRQ_PTE1        (40 + IRQ_OFFSET)

#define PLATFORM_NVIC_VECT  (FLASH_BASE + 0x2000)
typedef void (*f_irq_handler)(void);
extern uint32_t _2P4G_IrqHandler(int irq);
ADDITIONAL_ATTRIBUTE void UserHandler(void)
{
    int irq = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
    f_irq_handler isr = (f_irq_handler)io_read(PLATFORM_NVIC_VECT + irq * 4);

    if(_2P4G_IrqHandler(irq))
        return;
    
//    printf("%d\n",irq);
//    switch (irq)
//    {
//        case IRQ_TIM2:
//            return;
//    }
    
    isr();
}
#endif

