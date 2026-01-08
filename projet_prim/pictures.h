#ifndef __PICTURES_H
#define __PICTURES_H

typedef unsigned char byte;


#define MAX_BYTE 255



/*On définit le type picture*/
typedef struct {
    int height; /*hauteur*/
    int width;  /*largeur*/
    int can;    /*nombre de canaux de l'image*/ 
    byte* data; /*pointeur vers les données pixels de l'image */
} picture;


/*
@requires   filename is a valid existing file.
@assigns    nothing.
@ensures    read the pgm file and return the corresponding picture
*/
picture read_file_picture(char * filename);


/*
@requires   p is a valid picture and filename is an existing file.
@assigns    nothing.
@ensures    write the picture p in the file named name. It returns 0 if 
the writing was successful, -1 otherwise.
*/
int write_file_picture( char * filename,picture p);


/*
@requires   The width, height and number of channels must be positive.
@assigns    Allocates memory to stock pixels.
@ensures    Returns a valid picture initialized with null values.
*/
picture create_picture(unsigned int width,unsigned int height,unsigned int channels);


/*
@requires   p is a valid address and *p is a non-empty valid picture.
@assigns    Free memory allocated for pixels and reset the picture.
@ensures    The picture is emptied.
*/
void clean_picture(picture * p);


/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the new picture.
@ensures    Returns a copy of the input picture.
*/
picture copy_picture(picture p);


/*
@requires   p is a valid picture.
@assigns    nothing.
@ensures    Returns 1 if p is empy, 0 otherwise.
*/
int is_empty_picture(picture p);


/*
@requires   p is a non-empty valid picture.
@assigns    nothing.
@ensures    Returns 1 if the picture has one channel, 0 otherwise.
*/  
int is_gray_picture(picture p);


/*
@requires   p is a non-empty valid picture.
@assigns    nothing.
@ensures    Returns 1 if the picture has 3 channels, 0 otherwise.
*/
int is_color_picture(picture p);


/*
@requires   p is a non-empty valid picture.
@assigns    nothing.
@ensures    Displays information on the standard output.
*/
void info_picture(picture p);




/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the new picture.
@ensures    If p was already in colour, it returns a copy. If p was a grayscale image, we repeat the
grayscale component in each of the components (red, green, blue) of the resulting picture.
*/
picture convert_to_color_picture(picture p);



/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the new picture.
@ensures    If p was a colour picture, we convert it to grayscale using the following rule:
G = (0.299 x R) + (0.587 x V) + (0.114 x B).
If p was already a grayscale picture, it returns a copy.
*/
picture convert_to_gray_picture(picture p);



/*
@requires   p is a non-empty valid colour picture.
@assigns    Allocates memory for the three pictures.
@ensures    Returns an array containing three grayscale pictures if p is a color picture,
a pointer to a copy of p if p is a gray scale picture, NULL otherwise.
*/
picture * split_picture(picture p);




/*
@requires   Three valid grayscale non-empty pictures.
@assigns    Allocates memory for the resulting colour picture.
@ensures    Returns the corresponding colour picture. If the result picture cannot be created,
it returns an empty picture.
*/
picture merge_picture(picture red, picture green, picture blue);




/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture where each pixel is multiplied by the factor.
*/
picture brighten_picture(picture p, double factor);




/*
@requires   p is a non-empty valid picture and number > 0.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture edited with the melt effect.
*/
picture melt_picture(picture p, int number);



/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns an inverted picture.
*/
picture inverse_picture(picture p);



/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture with grey levels between 0 and 255.
*/
picture normalize_dynamic_picture(picture p);


/*
@requires   p is a non-empty valid picture and nb_levels >=2.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture with a reduced number of levels.
*/
picture set_levels_picture(picture p, byte nb_levels);




/*
@requires   p1 and p2 are non-empty valid pictures.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture containing the difference (in absolute value) between the
two input pictures.
*/
picture diff_picture(picture p1, picture p2);




/*
@requires   p1 and p2 are non-empty valid pictures.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture containing the product of the two input pictures. 
*/
picture mult_picture(picture p1, picture p2);





/*
@requires   p1, p2 and p3 are non-empty valid pictures.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture obtained by mixing two pictures according to a 3rd one,
by applying the given formula.
*/
picture mix_picture(picture p1, picture p2, picture p3);


/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture of size with x height by applying the nearest neighbour policy.
*/
picture resample_picture_nearest(picture p, unsigned int width, unsigned int height);




/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture of size with x height by applying the bi-linear interpolation policy.
*/
picture resample_picture_bilinear(picture p, unsigned int width, unsigned int height);




//BONUS


/*
@requires   p is a non-empty valid picture.
@assigns    Allocates memory for the resulting picture.
@ensures    Returns a picture where each pixel is multiplied by the factor, thanks to a lut.
*/
picture brighten_picture_lut(picture p, double factor);




typedef struct {
    int n;          /*taille de la matrice*/ 
    float* coeffs;   /*Coefficients du noyau*/
    float factor;       
    float offset;      
} noyau;

noyau create_noyau_flou();

picture apply_noyau(picture p, noyau k);

#endif