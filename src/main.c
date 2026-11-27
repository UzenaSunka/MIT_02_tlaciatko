#include "main.h"
#include "daughterboard.h"
#include "milis.h"
#include <stdbool.h>
#include <stm8s.h>


void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    init_milis();
    GPIO_Init(DB_LED1_PORT,DB_LED1_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(DB_S1_PORT,DB_S1_PIN,GPIO_MODE_IN_PU_NO_IT);
}

int main(void)
{
    init();
    uint32_t t0 = milis();
    bool s0 = false;

    while (1) {
        if (milis() - t0 > 20) {
            t0 = milis();
            if (PUSH(DB_S1) && !s0) {
                REVERSE(DB_LED1);
            }
//proc mi nefunguje comit
            s0 = PUSH(DB_S1);
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
