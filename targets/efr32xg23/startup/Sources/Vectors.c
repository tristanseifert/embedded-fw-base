/**
 * @file
 *
 * @brief Interrupt vector table
 */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "em_device.h"

#include "em_chip.h"
#include "em_cmu.h"

#include "sl_device_init_nvic.h"
#include "sl_device_init_dcdc.h"
#include "sl_device_init_hfxo.h"
#include "sl_device_init_dpll.h"
#include "sl_device_init_emu.h"

// ending address (top) of sstack
extern char _estack;

#define TOTAL_INTERRUPTS    (16 + EXT_IRQ_COUNT)

void Reset_Handler();
void Default_Handler();

/* Cortex-M Processor Exceptions */
void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
#ifndef SL_APP_PROPERTIES
/* Provide a dummy value for the sl_app_properties symbol. */
void sl_app_properties(void);    /* Prototype to please MISRA checkers. */
void sl_app_properties(void) __attribute__ ((weak, alias("Default_Handler")));
#endif

/* Part Specific Interrupts */
void SMU_SECURE_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SMU_S_PRIVILEGED_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SMU_NS_PRIVILEGED_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EMU_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void TIMER4_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void USART0_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void USART0_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART0_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART0_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART1_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART1_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART2_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EUSART2_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void ICACHE0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void BURTC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LETIMER0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SYSCFG_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void MPAHBRAM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LDMA_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LFXO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LFRCO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void ULFRCO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void GPIO_ODD_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void GPIO_EVEN_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EMUDG_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void AGC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void BUFC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void FRC_PRI_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void FRC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void MODEM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void PROTIMER_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void RAC_RSM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void RAC_SEQ_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void HOSTMAILBOX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SYNTH_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void ACMP0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void ACMP1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WDOG0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void WDOG1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void HFXO0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void HFRCO0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void HFRCOEM23_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void CMU_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void AES_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void IADC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void MSC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void DPLL0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void EMUEFP_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void DCDC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void VDAC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void PCNT0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SW0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SW1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SW2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SW3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void KERNEL0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void KERNEL1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void M33CTI0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void M33CTI1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void FPUEXH_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SETAMPERHOST_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SEMBRX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SEMBTX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LESENSE_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SYSRTC_APP_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void SYSRTC_SEQ_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void LCD_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void KEYSCAN_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void RFECA0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));
void RFECA1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler")));

extern void SystemInit();
__attribute__((weak)) void PlatformInit();
__attribute__((weak)) void InitSystemClock();

extern void __libc_heap_init();
extern void __libc_init_constructors();
extern int main(int argc, char **argv);

// load address of .data
extern char _sidata;
// RAM addresses of .data
extern char _sdata, _edata;
// RAM addresses of .bss
extern char _sbss, _ebss;

/**
 * @brief Application entry point
 *
 * This routine runs on startup and is responsible for setting up the C runtime.
 *
 * @remark This expects that .data and .bss are always 4 byte aligned.
 */
__attribute__((section(".startup"))) void Reset_Handler() {
    // initialize system
    SystemInit();

    // copy .data
    const size_t dataLen = ((uintptr_t) &_edata) - ((uintptr_t) &_sdata);
    if(dataLen) {
        uint32_t *readPtr  = (uint32_t *) &_sidata;
        uint32_t *writePtr = (uint32_t *) &_sdata;

        for(size_t i = 0; i < dataLen / 4; i++) {
            *writePtr++ = *readPtr++;
        }
    }

    // init .bss
    const size_t bssLen = ((uintptr_t) &_ebss) - ((uintptr_t) &_sbss);
    if(bssLen) {
        uint32_t *writePtr = (uint32_t *) &_sbss;

        for(size_t i = 0; i < bssLen / 4; i++) {
            *writePtr++ = 0;
        }
    }

    // invoke initializers
    __libc_heap_init();
    __libc_init_constructors();

    // platform init
    PlatformInit();

    // run program
    main(0, NULL);

    // should not get here…
    while(1) {
        asm volatile("bkpt #0");
    }
}

/**
 * @brief Default platform initialization handler
 *
 * This performs some basic initialization to work around chip hardware bugs, then sets up some
 * peropherals (NVIC, DC/DC converter, clocks, and EMU)
 *
 * @remark This is analagous to the sl_platform_init() function that's autogenerated when creating
 *         a project in Simplicity Studio.
 */
__attribute__((weak)) void PlatformInit() {
    // errata workarounds
    CHIP_Init();

    // configure interrupt controller
    sl_device_init_nvic();
    sl_device_init_dcdc();
    sl_device_init_hfxo();
    sl_device_init_dpll();

    InitSystemClock();

    sl_device_init_emu();
}

/**
 * @brief Initialize the system core clock.
 *
 * This is typically autogenerated by Simplicity Studio as `sl_device_init_clocks.c`. In this
 * case, we're going to use a default setting that uses the PLL as the core and peripheral clock,
 * driven by the high frequency external oscillator. All low speed clocks get the internal 32kHz
 * clock.
 */
__attribute__((weak)) void InitSystemClock() {
    CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
#if defined(_CMU_EM01GRPACLKCTRL_MASK)
    CMU_ClockSelectSet(cmuClock_EM01GRPACLK, cmuSelect_HFRCODPLL);
#endif
#if defined(_CMU_EM01GRPBCLKCTRL_MASK)
    CMU_ClockSelectSet(cmuClock_EM01GRPBCLK, cmuSelect_HFRCODPLL);
#endif
    CMU_ClockSelectSet(cmuClock_EM23GRPACLK, cmuSelect_LFRCO);
    CMU_ClockSelectSet(cmuClock_EM4GRPACLK, cmuSelect_LFRCO);

    // enable RTCC and SYSRTC clocks
#if defined(RTCC_PRESENT)
    CMU_ClockSelectSet(cmuClock_RTCC, cmuSelect_LFRCO);
#endif
#if defined(SYSRTC_PRESENT)
    CMU_ClockSelectSet(cmuClock_SYSRTC, cmuSelect_LFRCO);
#endif

    // enable WDOG0 (optionally WDOG1)
    CMU_ClockSelectSet(cmuClock_WDOG0, cmuSelect_LFRCO);
#if WDOG_COUNT > 1
    CMU_ClockSelectSet(cmuClock_WDOG1, cmuSelect_LFRCO);
#endif

    SystemCoreClockUpdate();
}

/**
 * @brief Default exception handler
 *
 * This puts the processor into an infinite loop. If a debugger is attached, it will be broken
 * into at this time.
 */
__attribute__((section(".startup"))) void Default_Handler() {
    __asm volatile("bkpt #0");

    while(true) {
    }
}

#if defined (__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif /* __GNUC__ */

extern const tVectorEntry __VECTOR_TABLE[TOTAL_INTERRUPTS];
const tVectorEntry __VECTOR_TABLE[TOTAL_INTERRUPTS] __attribute__((aligned(512)))
    __attribute__((section(".isr_vector"))) = {

    { .topOfStack = &_estack },            /*      Initial Stack Pointer     */
    { Reset_Handler },                          /*      Reset Handler             */
    { NMI_Handler },                            /*      -14 NMI Handler           */
    { HardFault_Handler },                      /*      -13 Hard Fault Handler    */
    { MemManage_Handler },                      /*      -12 MPU Fault Handler     */
    { BusFault_Handler },                       /*      -11 Bus Fault Handler     */
    { UsageFault_Handler },                     /*      -10 Usage Fault Handler   */
    { SecureFault_Handler },                    /*      -9 Secure Fault Handler   */
    { Default_Handler },                        /*      Reserved                  */
    { Default_Handler },                        /*      Reserved                  */
#ifdef BOOTLOADER_ENABLE
    { (VECTOR_TABLE_Type) & mainStageTable },
#else
    { Default_Handler },                         /*      Reserved                  */
#endif
    { SVC_Handler },                             /*      -5 SVCall Handler         */
    { DebugMon_Handler },                        /*      -4 Debug Monitor Handler  */
#ifdef SL_APP_PROPERTIES
    { (VECTOR_TABLE_Type) & sl_app_properties }, /*      Application properties    */
#else
    { sl_app_properties },                       /*      Application properties    */
#endif
    { PendSV_Handler },                          /*      -2 PendSV Handler         */
    { SysTick_Handler },                         /*      -1 SysTick Handler        */

    /* External interrupts */
    { SMU_SECURE_IRQHandler },                       /* -16 = SMU_SECURE */
    { SMU_S_PRIVILEGED_IRQHandler },                 /* -15 = SMU_S_PRIVILEGED */
    { SMU_NS_PRIVILEGED_IRQHandler },                /* -14 = SMU_NS_PRIVILEGED */
    { EMU_IRQHandler },                              /* -13 = EMU */
    { TIMER0_IRQHandler },                           /* -12 = TIMER0 */
    { TIMER1_IRQHandler },                           /* -11 = TIMER1 */
    { TIMER2_IRQHandler },                           /* -10 = TIMER2 */
    { TIMER3_IRQHandler },                           /* -9 = TIMER3 */
    { TIMER4_IRQHandler },                           /* -8 = TIMER4 */
    { USART0_RX_IRQHandler },                        /* -7 = USART0_RX */
    { USART0_TX_IRQHandler },                        /* -6 = USART0_TX */
    { EUSART0_RX_IRQHandler },                       /* -5 = EUSART0_RX */
    { EUSART0_TX_IRQHandler },                       /* -4 = EUSART0_TX */
    { EUSART1_RX_IRQHandler },                       /* -3 = EUSART1_RX */
    { EUSART1_TX_IRQHandler },                       /* -2 = EUSART1_TX */
    { EUSART2_RX_IRQHandler },                       /* -1 = EUSART2_RX */
    { EUSART2_TX_IRQHandler },                       /* 00 = EUSART2_TX */
    { ICACHE0_IRQHandler },                          /* 01 = ICACHE0 */
    { BURTC_IRQHandler },                            /* 02 = BURTC */
    { LETIMER0_IRQHandler },                         /* 03 = LETIMER0 */
    { SYSCFG_IRQHandler },                           /* 04 = SYSCFG */
    { MPAHBRAM_IRQHandler },                         /* 05 = MPAHBRAM */
    { LDMA_IRQHandler },                             /* 06 = LDMA */
    { LFXO_IRQHandler },                             /* 07 = LFXO */
    { LFRCO_IRQHandler },                            /* 08 = LFRCO */
    { ULFRCO_IRQHandler },                           /* 09 = ULFRCO */
    { GPIO_ODD_IRQHandler },                         /* 10 = GPIO_ODD */
    { GPIO_EVEN_IRQHandler },                        /* 11 = GPIO_EVEN */
    { I2C0_IRQHandler },                             /* 12 = I2C0 */
    { I2C1_IRQHandler },                             /* 13 = I2C1 */
    { EMUDG_IRQHandler },                            /* 14 = EMUDG */
    { AGC_IRQHandler },                              /* 15 = AGC */
    { BUFC_IRQHandler },                             /* 16 = BUFC */
    { FRC_PRI_IRQHandler },                          /* 17 = FRC_PRI */
    { FRC_IRQHandler },                              /* 18 = FRC */
    { MODEM_IRQHandler },                            /* 19 = MODEM */
    { PROTIMER_IRQHandler },                         /* 20 = PROTIMER */
    { RAC_RSM_IRQHandler },                          /* 21 = RAC_RSM */
    { RAC_SEQ_IRQHandler },                          /* 22 = RAC_SEQ */
    { HOSTMAILBOX_IRQHandler },                      /* 23 = HOSTMAILBOX */
    { SYNTH_IRQHandler },                            /* 24 = SYNTH */
    { ACMP0_IRQHandler },                            /* 25 = ACMP0 */
    { ACMP1_IRQHandler },                            /* 26 = ACMP1 */
    { WDOG0_IRQHandler },                            /* 27 = WDOG0 */
    { WDOG1_IRQHandler },                            /* 28 = WDOG1 */
    { HFXO0_IRQHandler },                            /* 29 = HFXO0 */
    { HFRCO0_IRQHandler },                           /* 30 = HFRCO0 */
    { HFRCOEM23_IRQHandler },                        /* 31 = HFRCOEM23 */
    { CMU_IRQHandler },                              /* 32 = CMU */
    { AES_IRQHandler },                              /* 33 = AES */
    { IADC_IRQHandler },                             /* 34 = IADC */
    { MSC_IRQHandler },                              /* 35 = MSC */
    { DPLL0_IRQHandler },                            /* 36 = DPLL0 */
    { EMUEFP_IRQHandler },                           /* 37 = EMUEFP */
    { DCDC_IRQHandler },                             /* 38 = DCDC */
    { VDAC_IRQHandler },                             /* 39 = VDAC */
    { PCNT0_IRQHandler },                            /* 40 = PCNT0 */
    { SW0_IRQHandler },                              /* 41 = SW0 */
    { SW1_IRQHandler },                              /* 42 = SW1 */
    { SW2_IRQHandler },                              /* 43 = SW2 */
    { SW3_IRQHandler },                              /* 44 = SW3 */
    { KERNEL0_IRQHandler },                          /* 45 = KERNEL0 */
    { KERNEL1_IRQHandler },                          /* 46 = KERNEL1 */
    { M33CTI0_IRQHandler },                          /* 47 = M33CTI0 */
    { M33CTI1_IRQHandler },                          /* 48 = M33CTI1 */
    { FPUEXH_IRQHandler },                           /* 49 = FPUEXH */
    { SETAMPERHOST_IRQHandler },                     /* 50 = SETAMPERHOST */
    { SEMBRX_IRQHandler },                           /* 51 = SEMBRX */
    { SEMBTX_IRQHandler },                           /* 52 = SEMBTX */
    { LESENSE_IRQHandler },                          /* 53 = LESENSE */
    { SYSRTC_APP_IRQHandler },                       /* 54 = SYSRTC_APP */
    { SYSRTC_SEQ_IRQHandler },                       /* 55 = SYSRTC_SEQ */
    { LCD_IRQHandler },                              /* 56 = LCD */
    { KEYSCAN_IRQHandler },                          /* 57 = KEYSCAN */
    { RFECA0_IRQHandler },                           /* 58 = RFECA0 */
    { RFECA1_IRQHandler },                           /* 59 = RFECA1 */
};

#if defined (__GNUC__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
