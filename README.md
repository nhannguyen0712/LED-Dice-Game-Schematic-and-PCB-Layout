# **ATmega328 LED Dice Game**

## **Project Overview**
This project designs an **LED dice game** using an **ATmega328** microcontroller. It generates random numbers to simulate a dice roll and controls **7 LEDs** to represent the rolled number visually. The system ensures smooth LED operation and accurate number generation. The final design includes a **PCB layout** to integrate all components while maintaining signal integrity.

## **Project Diagram**
![image](https://github.com/user-attachments/assets/65b1ee79-5b0a-4f62-82c4-f9031fa104a9)


## **Features**
- **Dice Simulation**: Simulates a 6-faced dice roll using pseudo-random number generation.
- **LED Display**: Lights up LEDs corresponding to the number rolled (1 to 6).
- **Button Interface**: A push button is used to trigger each roll.
- **Debouncing**: Ensures stable button input without glitches.
- **PCB Design**: Includes schematic and PCB layout following design and electrical rules.

## **Technology**
- **Microcontroller**: **ATmega328**
- **Programming Language**: **C**
- **Components**:
  - **6 LEDs** connected to digital output pins
  - **Push Button** connected with pull-down resistor
  - **PCB** designed in **Altium**

## **How It Works**
1. User presses the button to simulate rolling the dice.
2. A random number between 1 and 6 is generated using a seed (e.g., from a timer).
3. Corresponding LEDs light up in a dice-like pattern.
4. After a short delay, the system waits for the next button press.
5. The PCB ensures clean layout, proper decoupling, and minimal signal noise.

## **Files in the Project**
- **main.c**: Contains game logic, RNG, LED control, and button handling.
- **dice.h / dice.c**: Encapsulates dice patterns and LED control functions.
- **schematic.png**: Circuit schematic for reference.
- **pcb_layout.pcb**: PCB design file for fabrication or simulation.

## **Setup & Usage**
1. **Hardware**:
   - Connect **7 LEDs** to output pins of **ATmega328**.
   - Wire a **push button** to a digital input pin with appropriate debounce handling.
   - Upload the code using **Microchip Studio** or Arduino-compatible programmer.
2. **Software**:
   - Compile and flash the code to the microcontroller.
   - Press the button to roll the dice and observe the LED output.

## **How to Run the Code**
1. Set up the circuit on a breadboard or fabricated PCB.
2. Power the ATmega328 and press the button.
3. LEDs will light up representing a number between 1 and 6.

## **Responsibilities**  
- Developed embedded C code for random number generation and LED control.  
- Designed and validated circuit schematic and PCB layout.  
- Ensured reliable user input handling with button debouncing.  
- Optimized LED output for clear and intuitive dice pattern display.

## **Conclusion**
This project showcases an engaging embedded system game using **ATmega328**, focusing on **digital control**, **user interaction**, and **PCB design**. It highlights practical skills in embedded programming, hardware integration, and clean circuit design.
