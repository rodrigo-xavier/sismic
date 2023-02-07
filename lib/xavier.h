#include <stdbool.h>
#include <stdint.h>
#include <msp430.h>
#include "xavier.c"
#pragma once


void GPIO(uint8_t PORT, uint16_t BIT, bool ENABLE);
