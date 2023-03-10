#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  assert(c != NULL);
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case -1: ev.event = EVENT_YIELD; break;
      case SYS_yield:
      case SYS_exit:
      case SYS_brk:
      case SYS_open:
      case SYS_close:
      case SYS_read:
      case SYS_write:
      case SYS_lseek:
      case SYS_gettimeofday:
        ev.event = EVENT_SYSCALL; break;

      default: printf("cause:%d\n", c->mcause); ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    if(ev.event == EVENT_YIELD || ev.event == EVENT_SYSCALL)
      c->mepc += 4;
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
