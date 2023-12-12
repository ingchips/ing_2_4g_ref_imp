;/**************************************************************************//**
; * @file     startup_ARMCM3.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM3 Device Series
; * @version  V1.08
; * @date     03. February 2012
; *
; * @note
; * Copyright (C) 2012 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/

Stack_Size      EQU     0x00000004

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
                EXPORT  __initial_sp


                EXPORT  __heap_base
                EXPORT  __heap_limit
                
Heap_Size       EQU     0

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     0                         ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     Override_Handler          ; NMI Handler
                DCD     Override_Handler          ; Hard Fault Handler
                DCD     Override_Handler          ; MPU Fault Handler
                DCD     Override_Handler          ; Bus Fault Handler
                DCD     Override_Handler          ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     Override_Handler          ; SVCall Handler
                DCD     Override_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     Override_Handler          ; PendSV Handler
                DCD     Override_Handler          ; SysTick Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                DCD     Override_Handler
                
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler
                IMPORT  __scatterload

                ; this push is consumed by main
                PUSH    {R1, LR}

                ; save msp
                MRS     R1, MSP
                MSR     PSP, R1

                LDR     R0, =__scatterload
                BX      R0
                
                ENDP

                ALIGN

Override_Handler PROC
                IMPORT UserHandler

                ; int irq = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
                LDR     r0, =0xE000ED04
                LDR     r1, [r0]
                BFC     r1,#9,#23

                ; if (irq > 15) call UserHandler; else call default
                CMP     r1, #0x0F
                BGT     CALL_USER_ISR

                ; TODO: response Exception

                ; continue to call Exception handle function from platform
                ; f_irq_handler isr = (f_irq_handler)io_read(PLATFORM_NVIC_VECT + irq * 4);
                ; take ING916xx for example,start address of interrupt vector table of platfrom is 0x02002000
                LDR     r0, =0x02002000
                LDR     r0, [r0, r1, LSL #2]
                BX      r0

CALL_USER_ISR
                MOV     r0, r1
                LDR     r1, =UserHandler
                BX      r1

				ENDP
                    
main            PROC
                EXPORT  main
                IMPORT  app_main

                LDR     R0, =app_main
                BLX     R0

                ; restore msp
                MRS     R1, PSP
                MSR     MSP, R1

                POP     {R1, PC}

                ENDP
                
                ALIGN

                END
