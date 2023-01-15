# stm32f4-embedded
The drivers of STM32F4 for everyone. It includes UART (Tx, Rx), ADC, Timers, Interrupts, DMA, I2C, and SPI. Stay tuned

# UART_TX_RX drivers 
In src folder, there is a code file uart.c which includes the Tx-Rx port configuration, UART TX-RX configuration, receive function, transmit function. 
The driver is developed for STM32F411RE and tested on STM32F411RE board. 

Transmitter Example: In main.c uncomment the transmitter section
I use the REAL TERM software for receiving the data installed on my windows desktop. Open this software, go to port section, set baud rate use in my code which is 115200 and set the port as your COM port. Then open the port, you will see the data is coming from STM32F411RE.

Receiver Example: In main.c uncomment the receiver section
1) Debug this example in STM32 CUBE IDE
2) Go to Live perspective on the right hand side, and write the variable there which receive the data. for example data_rx
3) Press run button
4) I use the REAL TERM software for receiving the data installed on my windows desktop. Open this software, go to port section, set baud rate use in my code which is 115200 and set the port as your COM port. Then open the port, press any key from your PC keyboard. 
5) You will see the data is coming to real window on STM32 CUBE IDE
6) If press 1 it will turn on LED on your PC, else off
