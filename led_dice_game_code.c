#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <stdlib.h>

#define DISPLAY_TIME   1500 
#define ROLL_DURATION   600
#define BLINK_DELAY     200 
#define DEBOUNCE_TIME    50

#define GROUP_1 PB0
#define GROUP_2 PB1
#define LED_4   PB2
#define GROUP_3 PB3
#define BUTTON  PB5
#define BUZZER  PC5

// === Dice Faces ===
const uint8_t DICE_FACES[6] = {
    (1 << LED_4),
    (1 << GROUP_1),
    (1 << GROUP_1) | (1 << LED_4),
    (1 << GROUP_1) | (1 << GROUP_3),
    (1 << GROUP_1) | (1 << GROUP_3) | (1 << LED_4),
    (1 << GROUP_1) | (1 << GROUP_2) | (1 << GROUP_3)
};

volatile uint8_t dice_requested = 0;

void init_io() {
    DDRB |= (1 << GROUP_1) | (1 << GROUP_2) | (1 << GROUP_3) | (1 << LED_4);
    DDRC |= (1 << BUZZER);

    DDRB &= ~(1 << BUTTON);
    PORTB |= (1 << BUTTON);

    // Off initially
    PORTB &= ~((1 << GROUP_1) | (1 << GROUP_2) | (1 << GROUP_3) | (1 << LED_4));
    PORTC &= ~(1 << BUZZER);
}

void init_interrupts() {
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT5);
    sei();
}

void init_random() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    srand(ADC);
    ADCSRA &= ~(1 << ADEN);
}

ISR(PCINT0_vect) {
    if (!(PINB & (1 << BUTTON))) {
        _delay_ms(DEBOUNCE_TIME);
        if (!(PINB & (1 << BUTTON))) {
            dice_requested = 1;
        }
    }
}

// === Sleep ===
void enter_sleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable(); // wake here
}

void clear_leds() {
    PORTB &= ~((1 << GROUP_1) | (1 << GROUP_2) | (1 << GROUP_3) | (1 << LED_4));
}

void beep(uint16_t duration_ms) {
    PORTC |= (1 << BUZZER);
    while (duration_ms--) _delay_ms(1);
    PORTC &= ~(1 << BUZZER);
}

void funny_beep_pattern() {
    for (uint8_t i = 0; i < 3; i++) {
        PORTC |= (1 << BUZZER);
        for (uint8_t j = 0; j < (3 + i * 2); j++) _delay_ms(10);
        PORTC &= ~(1 << BUZZER);
        _delay_ms(50);
    }
}

void rolling_effect() {
    uint16_t steps = ROLL_DURATION / BLINK_DELAY;
    for (uint16_t i = 0; i < steps; i++) {
        uint8_t temp_face = rand() % 6;
        PORTB = (PORTB & 0xF0) | DICE_FACES[temp_face];
        funny_beep_pattern();
        _delay_ms(BLINK_DELAY);
        clear_leds();
    }
}

void show_face(uint8_t face) {
    if (face < 1 || face > 6) return;
    PORTB = (PORTB & 0xF0) | DICE_FACES[face - 1];
    beep(200);
    _delay_ms(DISPLAY_TIME);
    clear_leds();
}

int main(void) {
    init_io();
    init_random();
    init_interrupts();

    while (1) {
        enter_sleep();

        if (dice_requested) {
            dice_requested = 0;
            rolling_effect();
            show_face((rand() % 6) + 1);
        }
    }
}

