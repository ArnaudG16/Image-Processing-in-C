#ifndef __LUT_H
#define __LUT_H
#include "pictures.h"

typedef struct {
    int n;   
    int *values;
} lut;

/*
@requires   size > 0 .
@assigns    Allocates memory for the LUT.
@ensures    Returns a LUT initialised with default values.
*/
lut create_lut(int size);

/*
@requires   l is a valid address to a non-empty LUT.
@assigns    l.
@ensures    The fields in the LUT are reset to an empty value.
*/
void clean_lut(lut *l);

/*
@requires   The picture and LUT must be valid. The LUT size has to be 256.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a new picture in which each pixel has been transformed according to the LUT.
*/
picture apply_lut(picture p, lut l);

/*
@requires   l is a valid address to a non-empty LUT of size 256.
@assigns    l.
@ensures    The LUT contains inverted values (255 - i).
*/
void lut_inverse(lut *l);

/*
@requires   l is a valid address to a non-empty LUT of size 256. 
The min and max values must be between 0 and 255, and min < max.
@assigns    l.
@ensures    The LUT set the [min, max] range to [0, 255].
*/
void lut_normalize_dynamic(lut *l, int min, int max);


/*
@requires   l is a valid address to a non-empty LUT of size 256. nb_levels >= 2 .
@assigns    l.
@ensures    The LUT groups the pixels according to the nb_levels.
*/
void lut_set_levels(lut *l, byte nb_levels);


/*
@requires   nothing.
@assigns    Allocates memory for the LUT.
@ensures    Returns a LUT that makes the picture brighter.
*/
lut create_bright_lut(double factor);

#endif