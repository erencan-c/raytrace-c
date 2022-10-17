#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ppm_color {
   uint8_t r,g,b;
} PPM_Color;

typedef struct PPM {
   size_t row, col;
   PPM_Color data[];
} PPM;

#define PIXEL(self, x, y) (self)->data[(x) * (self)->col + (y)]

PPM* PPM_new(const size_t row, const size_t col);
PPM* PPM_read(const char* const filename);
PPM* PPM_readfile(const FILE* const file);
void PPM_write(const PPM* const self, const char* const filename);
void PPM_writefile(const PPM* const self, FILE* file);
