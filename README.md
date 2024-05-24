# CG2271 Source Codes

Keil µVision Source Codes for our RTOS-based robot. Codes for our ESP32 are not provided here.

![CG2271 Final Robot](/cg2271%20final%20bot.jpg)

For National University of Singapore's CG2271 - Real-Time Operating Systems, AY2324S2

# Overview

Our robot uses the Keil RTX5 (based on CMSIS-RTOS2) on a FRDM-KL25Z running on the ARM® Cortex™-M0+ processor.

Its objective is to complete a course as fast as possible, whilst being able to blink LEDs and play music. As shown above, we used a controller to pilot our robot.

In `main.c`, multiple threads corresponding to these various tasks are used. UART was used to receive signals from the controller. Within our code, we used Message Queues and Event flags to communicate and synchronise between threads.

# Contributors

- Willson Han Zhekai [@wallywallywally](https://github.com/wallywallywally)

- Nicholas H Goh Maowen [@nicholas132000](https://github.com/nicholas132000)

- Webster Tan Jia Sheng [@webtjs](https://github.com/webtjs)

- Ong Yi Kai Samuel [@samuelory](https://github.com/samuelory)