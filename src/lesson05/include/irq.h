#ifndef	_IRQ_H
#define	_IRQ_H

void enable_interrupt_controller( void );

void irq_vector_init( void );
void enable_irq( void );
// void show_data_abort_message(unsigned long esr, unsigned long address);
void disable_irq( void );

#endif  /*_IRQ_H */
