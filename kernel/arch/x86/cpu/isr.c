#include <core/system.h>
#include <core/string.h>
#include <cpu/cpu.h>
#include <core/arch.h>
#include <sys/sched.h>

extern void isr0 (void);
extern void isr1 (void);
extern void isr2 (void);
extern void isr3 (void);
extern void isr4 (void);
extern void isr5 (void);
extern void isr6 (void);
extern void isr7 (void);
extern void isr8 (void);
extern void isr9 (void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
extern void isr128(void);

static const char *int_msg[32] = {
	"Division by zero",				/* 0 */
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",				/* 5 */
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",						/* 10 */
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",			/* 15 */
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void interrupt(regs_t *regs)
{
	extern uint32_t int_num;
	extern uint32_t err_num;
	
	if(int_num == 0x80)	/* syscall */
	{
		arch_syscall(regs);
		/*x86_proc_t *arch = cur_proc->arch;
		memcpy(regs, &arch->stat, sizeof(regs_t));
		return;*/
		kernel_idle();
	}

	const char *msg = int_msg[int_num];
	printk("Recieved interrupt [%d] [err:%d] : %s\n", int_num, err_num, msg);
	printk("eip %x\n", regs->eip);
	printk("Kernel exception\n"); /* That's bad */
	for(;;);
}

void x86_isr_setup(void) {	
	x86_idt_set_gate(0x00, (uint32_t) isr0);
	x86_idt_set_gate(0x01, (uint32_t) isr1);
	x86_idt_set_gate(0x02, (uint32_t) isr2);
	x86_idt_set_gate(0x03, (uint32_t) isr3);
	x86_idt_set_gate(0x04, (uint32_t) isr4);
	x86_idt_set_gate(0x05, (uint32_t) isr5);
	x86_idt_set_gate(0x06, (uint32_t) isr6);
	x86_idt_set_gate(0x07, (uint32_t) isr7);
	x86_idt_set_gate(0x08, (uint32_t) isr8);
	x86_idt_set_gate(0x09, (uint32_t) isr9);
	x86_idt_set_gate(0x0A, (uint32_t) isr10);
	x86_idt_set_gate(0x0B, (uint32_t) isr11);
	x86_idt_set_gate(0x0C, (uint32_t) isr12);
	x86_idt_set_gate(0x0D, (uint32_t) isr13);
	x86_idt_set_gate(0x0E, (uint32_t) isr14);
	x86_idt_set_gate(0x0F, (uint32_t) isr15);
	x86_idt_set_gate(0x10, (uint32_t) isr16);
	x86_idt_set_gate(0x11, (uint32_t) isr17);
	x86_idt_set_gate(0x12, (uint32_t) isr18);
	x86_idt_set_gate(0x13, (uint32_t) isr19);
	x86_idt_set_gate(0x14, (uint32_t) isr20);
	x86_idt_set_gate(0x15, (uint32_t) isr21);
	x86_idt_set_gate(0x16, (uint32_t) isr22);
	x86_idt_set_gate(0x17, (uint32_t) isr23);
	x86_idt_set_gate(0x18, (uint32_t) isr24);
	x86_idt_set_gate(0x19, (uint32_t) isr25);
	x86_idt_set_gate(0x1A, (uint32_t) isr26);
	x86_idt_set_gate(0x1B, (uint32_t) isr27);
	x86_idt_set_gate(0x1C, (uint32_t) isr28);
	x86_idt_set_gate(0x1D, (uint32_t) isr29);
	x86_idt_set_gate(0x1E, (uint32_t) isr30);
	x86_idt_set_gate(0x1F, (uint32_t) isr31);
	x86_idt_set_gate_user(0x80, (uint32_t) isr128);
}