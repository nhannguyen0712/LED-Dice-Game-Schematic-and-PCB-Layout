#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// LED pins (PORTB)
#define LED1_7   PB0
#define LED2_6   PB1
#define LED4     PB2
#define LED3_5   PB3

// Buzzer control pin (PC5)
#define BUZZER   PC5

// Button input pin
#define BUTTON   PB5 // Assuming button is connected to PB5

#define DISPLAY_TIME 2000

// Die face patterns: [PB3, PB2, PB1, PB0]
const uint8_t die_patterns[6][4] = {
	{0, 0, 0, 1}, // 1
	{0, 0, 1, 0}, // 2
	{0, 0, 0, 1}, // 3
	{1, 1, 1, 0}, // 4
	{1, 0, 1, 1}, // 5
	{1, 1, 1, 0}  // 6
};

void init_io() {
	// Set PB0–PB3 as output (LEDs)
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);

	// Set PC5 as output for buzzer control
	DDRC |= (1 << BUZZER);
	PORTC &= ~(1 << BUZZER); // Ensure buzzer is OFF by default

	// Set PB5 as input for button
	DDRB &= ~(1 << BUTTON);
	PORTB |= (1 << BUTTON); // Enable pull-up
}

uint8_t button_pressed() {
	if (!(PINB & (1 << BUTTON))) {
		_delay_ms(20); // debounce
		if (!(PINB & (1 << BUTTON))) {
			while (!(PINB & (1 << BUTTON))); // wait for release
			return 1;
		}
	}
	return 0;
}

void clear_leds() {
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3));
}

void beep() {
	// Trigger the 555 timer to start buzzing by setting PC5 LOW
	PORTC &= ~(1 << BUZZER); // Set PC5 LOW to trigger 555 timer
	_delay_ms(300); // Buzz for 300ms
	PORTC |= (1 << BUZZER); // Set PC5 HIGH to stop the buzzer
	_delay_ms(100); // Pause between beeps
}

void show_roll(uint8_t roll) {
	clear_leds();

	// Get pattern for the rolled value
	uint8_t *p = (uint8_t *)die_patterns[roll - 1];
	if (p[0]) PORTB |= (1 << PB3);
	if (p[1]) PORTB |= (1 << PB2);
	if (p[2]) PORTB |= (1 << PB1);
	if (p[3]) PORTB |= (1 << PB0);

	_delay_ms(DISPLAY_TIME);
	clear_leds();
}

int main(void) {
	init_io();

	// Seed random with a fixed value (e.g., 1234)
	srand(1234);  // Using a constant seed (can be any number)

	while (1) {
		if (button_pressed()) {
			beep(); // Trigger the buzzer
			uint8_t roll = (rand() % 6) + 1;
			show_roll(roll);
		}
	}
}
