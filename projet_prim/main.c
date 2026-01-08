#include <stdio.h>
#include <stdlib.h>
#include "pictures.h"
#include "filename.h"

int main(int argc,char ** argv) {
    if(argc<2){
        perror("Usage");
        exit(8);
    }
    char *colour = argv[1]; 
    char *gray = argv[2];
     

    picture lenna_gray = read_file_picture(gray);
    picture lenna_color = read_file_picture(colour);

    if (is_empty_picture(lenna_gray) || is_empty_picture(lenna_color)) {
            perror("Image vide");
            exit(7);
        }

    // Extraction des parties des chemins
    char *dir_gray = dir_from_path(gray);
    char *name_gray = name_from_path(gray);
    char *ext_gray = ext_from_path(gray);

    char *dir_color = dir_from_path(gray);
    char *name_color = name_from_path(colour);
    char *ext_color = ext_from_path(colour);

    /*Lenna_gray_convert_color.ppm*/
    picture lenna_gray_color = convert_to_color_picture(lenna_gray);
    char *gray_color = concat_parts(dir_gray, name_gray, "convert_color", ext_color);
    write_file_picture(gray_color, lenna_gray_color);

    /*Lenna_gray_convert_gray.pgm*/
    picture lenna_color_gray = convert_to_gray_picture(lenna_color);
    char *color_gray = concat_parts(dir_color, name_color, "convert_gray", ext_gray);
    write_file_picture(color_gray, lenna_color_gray);

    /*Lenna_color_red.pgm Lenna_color_green.pgm Lenna_color_blue.pgm*/
    picture *lenna_color_tab = split_picture(lenna_color);
    char *rouge = concat_parts(dir_color, name_color, "red", ext_gray);
    write_file_picture(rouge, lenna_color_tab[0]);
    char *vert = concat_parts(dir_color, name_color, "green", ext_gray);
    write_file_picture(vert, lenna_color_tab[1]);
    char *bleu = concat_parts(dir_color, name_color, "blue", ext_gray);
    write_file_picture(bleu, lenna_color_tab[2]);

    /*Lenna_gray_brighten.pgm*/
    picture lenna_bright=brighten_picture(lenna_gray,1.5);
    char* bright=concat_parts(dir_gray,name_gray,"brighten",ext_gray);
    write_file_picture(bright,lenna_bright);


    /*Lenna_color_melted.ppm*/
    picture melt=melt_picture(lenna_color,lenna_color.height*lenna_color.width*lenna_color.can*5);
    char* fond=concat_parts(dir_color,name_color,"melted",ext_color);
    write_file_picture(fond,melt);
    
    /*Lenna_color_inverse.pgm*/
    picture inv=inverse_picture(lenna_color);
    char* inverse=concat_parts(dir_color,name_color,"inverse",ext_color);
    write_file_picture(inverse,inv);


    /*Lenna_gray_dynamic.pgm*/
    picture dyn = normalize_dynamic_picture(lenna_gray);
    char* dyna=concat_parts(dir_gray,name_gray,"dynamic",ext_gray);
    write_file_picture(dyna,dyn);

    /*Lenna_color_dynamic.ppm*/
    picture merge = merge_picture(lenna_color_tab[0],lenna_color_tab[1],lenna_color_tab[2]);
    picture dynamic=normalize_dynamic_picture(merge);
    char* color_dyn=concat_parts(dir_color,name_color,"dynamic",ext_color);
    write_file_picture(color_dyn,dynamic);

    /*Lenna_color_levels.ppm*/
    picture lev= set_levels_picture(lenna_color,8);
    char* levels=concat_parts(dir_color,name_color,"levels",ext_color);
    write_file_picture(levels,lev);

    /*Lenna_color_smaller_nearest.ppm*/
    picture smalln=resample_picture_nearest(lenna_color,(1-0.36)*lenna_color.width,(1-0.36)*lenna_color.height);
    char* small=concat_parts(dir_color,name_color,"smaller_nearest",ext_color);
    write_file_picture(small,smalln);

    /*Lenna_color_smaller_bilinear.ppm*/
    picture smallb=resample_picture_bilinear(lenna_color,(1-0.36)*lenna_color.width,(1-0.36)*lenna_color.height);
    char* smallbili=concat_parts(dir_color,name_color,"smaller_bilinear",ext_color);
    write_file_picture(smallbili,smallb);


    /*Lenna_color_larger_nearest.ppm*/
    picture largen=resample_picture_nearest(lenna_color,1.36*lenna_color.width,1.36*lenna_color.height);
    char* large=concat_parts(dir_color,name_color,"larger_nearest",ext_color);
    write_file_picture(large,largen);

    /*Lenna_color_larger_bilinear.ppm*/
    picture largeb=resample_picture_bilinear(lenna_color,1.36*lenna_color.width,1.36*lenna_color.height);
    char* largebili=concat_parts(dir_color,name_color,"larger_bilinear",ext_color);
    write_file_picture(largebili,largeb);

    /*Lenna_color_difference.ppm*/
    picture diff=diff_picture(largen,largeb);
    picture normalized_diff=normalize_dynamic_picture(diff);
    char* dif=concat_parts(dir_color,name_color,"difference",ext_color);
    write_file_picture(dif,normalized_diff);

    /*Lenna_gray_product.pgm*/
    char* bw=argv[3];
    picture lenna_bw=read_file_picture(bw);
    resample_picture_bilinear(lenna_bw,lenna_color.width,lenna_color.height);
    
    picture prod=mult_picture(lenna_gray,lenna_bw);
    char* produit=concat_parts(dir_gray,name_gray,"product",ext_gray);
    write_file_picture(produit,prod);


    /*Lenna_color_mixture.ppm*/
    picture mix =mix_picture(inv,lenna_color,lenna_bw);
    char* mixt=concat_parts(dir_color,name_color,"mixture",ext_color);
    write_file_picture(mixt,mix);


    //BONUS

    /*Lenna_gray_brighten_lut.pgm*/
    picture lenna_bright_lut=brighten_picture_lut(lenna_gray,2.5);
    char* bright_lut=concat_parts(dir_gray,name_gray,"brighten_lut",ext_gray);
    write_file_picture(bright_lut,lenna_bright_lut);


    /*Lenna_gray_noyau.ppm*/
    picture lenna_noyau=apply_noyau(lenna_gray,create_noyau_flou());
    char* noy=concat_parts(dir_gray,name_gray,"noyau",ext_gray);
    write_file_picture(noy,lenna_noyau);




    clean_picture(&lenna_gray);
    clean_picture(&lenna_color);
    clean_picture(&lenna_gray_color);
    clean_picture(&lenna_color_gray);
    clean_picture(&lenna_color_tab[0]);
    clean_picture(&lenna_color_tab[1]);
    clean_picture(&lenna_color_tab[2]);
    free(lenna_color_tab);
    clean_picture(&lenna_bright);
    clean_picture(&melt);
    clean_picture(&inv);
    clean_picture(&dyn);
    clean_picture(&merge);
    clean_picture(&dynamic);
    clean_picture(&lev);
    clean_picture(&smalln);
    clean_picture(&smallb);
    clean_picture(&largeb);
    clean_picture(&largen);
    clean_picture(&diff);
    clean_picture(&normalized_diff);
    clean_picture(&mix);
    clean_picture(&prod);
    clean_picture(&lenna_bw);
    clean_picture(&lenna_bright_lut);
    clean_picture(&lenna_noyau);

    return 0;
}