#ifndef GPIO_INTERRUPTS_H
#define GPIO_INTERRUPTS_H

#include "interrupts.h"

/*
 * Module to configure GPIO interrupts for Raspberry Pi.
 * Because all of the GPIO pins share a small set of GPIO
 * interrupts, you need a level of indirection to be able
 * to handle interrupts for particular pins. This module
 * allows a client to register one handler for each
 * GPIO pin.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 *
 * Last update:   May 2020
 */

/*
 * `gpio_interrupts_init`: Required initialization for module
 *
 * Initialize the GPIO interrupts module. The init function must be
 * called before any calls to other functions in this module.
 * The init function initializes the data structure that stores
 * interrupt handler function pointers and auxiliary data.
 * This function registers a handler for GPIO interrupts with the
 * top-level interrupts module. The top-level handler receives
 * GPIO events for all pins and in turn dispatches to the handler
 * registered with the gpio interrupts module for the specific pin.
 * When this function returns, GPIO interrupts are disabled and
 * must be nabled with `gpio_interrupts_enable`.
 */
void gpio_interrupts_init(void);


/*
 * `gpio_interrupts_enable`
 *
 * Global enable for GPIO interrupts.
 */
void gpio_interrupts_enable(void);

/*
 * `gpio_interrupts_disable`
 *
 * Global disable for GPIO interrupts.
 */
void gpio_interrupts_disable(void);

/*
 * `gpio_interrupts_default_handler`
 *
 * The default handler for GPIO events. Does nothing. Provided
 * as reference point for what the prior handler returned from
 * registering a handler, plus as a convenience for uninstalling
 * a handler (replace it with this).
 */
void gpio_default_handler(unsigned int pc, void *aux_data);


/*
 * `gpio_interrupts_register_handler`
 *
 * Register a handler function to a given GPIO pin. Each GPIO
 * pin can have one handler: further dispatch should be invoked by
 * the handler itself. Use the events system defined in `gpio_extra.h`
 * to configure which GPIO events are detected by the pin.
 *
 * @param pin       GPIO pin to register handler
 * @param fn        handler function to call when interrupt generated on pin
 * @param aux_data  client's data pointer to be passed as second argument
 *                  when calling handler function
 *
 * An assert is raised if `pin` is invalid. `aux_data` can be NULL if
 * handler function has no need for auxiliary data. If `fn` is NULL, removes
 * any handler previously registered for `pin`.
 *
 * This function asserts on an attempt to register handler without first
 * initializing the module (i.e. required to call `gpio_interrupts_init`).
 */
void gpio_interrupts_register_handler(unsigned int pin, handler_fn_t fn, void *aux_data);


#endif
