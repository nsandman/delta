#include <stdint.h>

#ifndef _INTERRUPT_
#define _INTERRUPT_

typedef struct registers {
   uint64_t ds;                  // Data segment selector
   uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax; // Pushed in isr_common_stub
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint64_t rip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

// This IDT struct's sizes are based on the table at:
// wiki.osdev.org/Interrupt_Descriptor_Table#IDT_in_IA-32e_Mode_.2864-bit_IDT.29
struct idt_descriptor {
	uint16_t base_low;
	uint16_t sel;
	uint8_t  zero;
	uint8_t  flags;
	uint16_t base_mid;
	uint32_t base_hi;
	uint32_t also_zero;
} __attribute__((packed));
typedef struct idt_descriptor idt_desc_t;

void idt_init();
void idt_set_gate(uint8_t, uint64_t, uint16_t, uint8_t);
static inline void change_idt_address(idt_desc_t**, uint64_t);

#endif