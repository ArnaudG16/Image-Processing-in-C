#include <stdlib.h>  
#include <stdio.h>   
#include "lut.h"


lut create_lut(int size) {
    lut lut;
    lut.n = size;
    lut.values = (int *)malloc(size * sizeof(int));
    if (lut.values == NULL) {
        perror("Erreur allocation de mémoire");
        exit(5); 
    }
    return lut;
}


void clean_lut(lut *l) {
    if (l->values) {
        free(l->values);
        l->values = NULL;
        l->n = 0;
    }
}


picture apply_lut(picture p, lut l) {
    for (int i = 0; i < p.width * p.height * p.can; ++i) {
        p.data[i] = l.values[p.data[i]];
    }
    return p;
}


void lut_inverse(lut *l) {
    for (int i = 0; i < l->n; ++i) {
        l->values[i] = 255 - i;
    }
}

void lut_normalize_dynamic(lut *l, int min, int max) {
    for (int i = 0; i < l->n; ++i) {
        if (i < min) {
            l->values[i] = 0;
        } else if (i > max) {
            l->values[i] = 255;
        } else {
            l->values[i] = 255 * (i - min) / (max - min);
        }
    }
}


void lut_set_levels(lut *l, byte nb_levels) {
    int pas = 256 / nb_levels;
    for (int i = 0; i < l->n; ++i) {
        l->values[i] = (i / pas) * pas;
    }
}


lut create_bright_lut(double factor) {
    lut l=create_lut(256);
    for (int i = 0; i < 256; i++) {
        int val = i * factor;
        if(val > 255){
            val=255;
        }
        l.values[i] = val;
    }
    return l;
}