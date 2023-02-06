#include <stdbool.h>
#include <stdint.h>
#include <msp430.h>
#pragma once


void GPIO(uint8_t PORT, uint16_t BIT, bool input);
