#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pictures.h"
#include "lut.h"


picture read_file_picture(char* name){
    FILE* f = fopen(name,"r");
    if (f==NULL) {
        perror("Erreur lors de la lecture du fichier");
        exit(0);
    }

    char buffer[128];
    int width;
    int height;
    picture image;
    byte *btm;
    fgets(buffer,128,f);
    /*on ignore les commentaires.*/
    while(buffer[0]=='#'){fgets(buffer,128,f);
    }

    if(strcmp(buffer, "P5\n")==0){
        fgets(buffer, 128, f);
        /*on ignore les commentaires.*/
        while(buffer[0]=='#'){fgets(buffer,128,f);
        }
        sscanf(buffer, "%d %d", &width, &height);
        /*on ignore les commentaires.*/
        while(buffer[0]=='#'){fgets(buffer,128,f);
        }
        fgets(buffer,128,f);
        btm = malloc(width*height*sizeof(byte));
        if (btm == NULL) {
            perror("Erreur allocation de mémoire");
            exit(5);
        }
        size_t size = width*height;
        if(fread(btm, sizeof(byte), width*height, f)!=size){
        perror("Erreur lecture du contenu de l'image");
        exit(1);
        }
        image.can=1;        
    }

    else if(strcmp(buffer,"P6\n")==0){
        fgets(buffer, 128, f);
         /*on ignore les commentaires.*/
        while(buffer[0]=='#'){fgets(buffer,128,f);
        }
        sscanf(buffer, "%d %d", &width, &height);
        /*on ignore les commentaires.*/
        while(buffer[0]=='#'){fgets(buffer,128,f);
        }
        fgets(buffer,128,f);
        btm = malloc(3*width*height*sizeof(byte));
        if (btm == NULL) {
            perror("Erreur allocation de mémoire");
            exit(5);
        }
        size_t size = width*height*3;
        if(fread(btm, sizeof(byte), 3*width*height, f)!=size){
        perror("Erreur lecture du contenu de l'image");
        exit(1);
        }
        image.can=3;    
    }


   else{ 
    perror("Le fichier n'est pas un fichier PPM/PGM");
    fclose(f);
    exit(3);
   }

    image.width = width;
    image.height = height;
    image.data = btm;

    if(width==0 || height==0 ){
        perror("Image de taille nulle");
        free(btm);
        exit(4);
    }

    fclose(f);
    return image;
}

int write_file_picture(char* name, picture p){
    FILE* f = fopen(name, "wb");
        if (f == NULL) {
        perror("Impossible de créer le fichier");
        return -1;
    }

    /*On récupère le chiffre après le  " P "(5 ou 6)*/
    int x;
    if (p.can==1){
        x=5;
    }
    else if(p.can==3){
        x=6;
    }
    else{
        perror("fichier non pris en charge");
        fclose(f);
        return -1;
    }
    fprintf(f, "P%d\n%d %d\n%d\n", x, p.width, p.height,MAX_BYTE);
    size_t data_size = p.width * p.height * p.can;
    if (fwrite(p.data, sizeof(byte), data_size, f) != data_size) {
        perror("Données incomplètes");
        fclose(f);
        return -1;
    }
    fclose(f);
    return 0;
}

picture create_picture(unsigned int width,unsigned int height,unsigned int channels){
    picture image;
    image.can=channels;
    image.height=height;
    image.width=width;
    byte*dat=malloc(sizeof(byte)*width*height*channels);
    if (dat == NULL) {
    perror("Erreur allocation de mémoire");
    exit(5);
}
    image.data=dat;
    return image;
}

void clean_picture(picture * p){
    p->can=0;
    p->height=0;
    p->width=0;
    p->data=NULL;
}

picture copy_picture(picture p){
    picture image;
    image.width=p.width;
    image.height=p.height;
    image.can=p.can;
    size_t data_size = p.width * p.height * p.can;
    image.data = malloc(data_size);
    if (image.data == NULL) {
        perror("Erreur allocation de mémoire");
        exit(5);    
    }
    for (size_t i = 0; i < data_size; i++) {
        image.data[i] = p.data[i];
    }
    return image;
}


int is_empty_picture(picture p){
    if(p.can==0 || p.width==0 || p.height==0 || p.data==NULL){
        return 1;
    }
return 0;
}

int is_gray_picture(picture p){
    if(p.can==1){
        return 1;
    }
    else if(p.can==3){
        return 0;
    }
    else{
        perror("format non pris en charge");
        exit(6);
    }
}

int is_color_picture(picture p){

 if(p.can==3){
        return 1;
    }
    else if(p.can==1){
        return 0;
    }
    else{
        perror("format non pris en charge");
        exit(6);
    }

}

void info_picture(picture p){
    printf("(%d X %d X %d)",p.width,p.height,p.can);
}


picture convert_to_color_picture(picture p){
    if(p.can==3){
        return copy_picture(p);
    }
    else if(p.can==1){
        picture copy = create_picture(p.width, p.height, 3);
        for (int i = 0; i < p.width * p.height; i++) {
            copy.data[i * 3] = p.data[i];       /*Red*/
            copy.data[i * 3 + 1] = p.data[i];   /*Green*/
            copy.data[i * 3 + 2] = p.data[i];   /*Blue*/
        }
        return copy; 
    }  
    else{
        perror("erreur type de fichier");
        exit(6);
    }
}

picture convert_to_gray_picture(picture p){
    if(p.can==1){
        return copy_picture(p);
    }
    else if(p.can==3){
        picture copy = create_picture(p.width, p.height, 1);
        for(int i=0;i<p.width*p.height;i++){
            float R = p.data[3*i]*0.299;
            float V = p.data[3*i+1]*0.587;
            float B = p.data[3*i+2]*0.114;
            copy.data[i]=R+V+B;
        }
        return copy;
    }
    
    else{
        perror("erreur type de fichier");
        exit(6);
    }
}


picture * split_picture(picture p){
    if(p.can==1){
    picture* copy=malloc(sizeof(picture));
    if (copy==NULL){
        perror("Erreur allocation de mémoire");
        exit(5); 
    }
    (*copy)=copy_picture(p);
    return copy;
    }
    else if (p.can==3){
        picture R=create_picture(p.width,p.height,1);
        picture V=create_picture(p.width,p.height,1);
        picture B=create_picture(p.width,p.height,1);
        for(int i=0;i<p.width*p.height;i++){
            R.data[i]=p.data[3*i];
            V.data[i]=p.data[3*i+1];
            B.data[i]=p.data[3*i+2];
            }
        picture *split=malloc(3*sizeof(picture));
        if(split==NULL){
            perror("Erreur allocation de mémoire");
            exit(5); 
        }
        split[0]=R;
        split[1]=V;
        split[2]=B;
        return split;
    }
else{
        return NULL;
    }
}

picture merge_picture(picture red, picture green, picture blue){
    if (red.width != green.width || red.width != blue.width ||
        red.height != green.height || red.height != blue.height ||
        red.can != 1 || green.can != 1 || blue.can != 1) {
        perror("Erreur les images à fusionner doivent être en niveaux de gris et de même taille.");
        exit(7);
    }
    picture color_pic = create_picture(red.width, red.height, 3);
    for (int i = 0; i < red.width * red.height; i++) {
        color_pic.data[i * 3] = red.data[i];      
        color_pic.data[i * 3 + 1] = green.data[i]; 
        color_pic.data[i * 3 + 2] = blue.data[i];  
    }
    return color_pic;
}

picture brighten_picture(picture p, double factor) {
    picture copy = copy_picture(p);
    for (int i = 0; i < p.can * p.width * p.height; i++) {
        double new_value = p.data[i] * factor;
        if (new_value > MAX_BYTE) {
            new_value = MAX_BYTE;
        } else if (new_value < 0) {
            new_value = 0;
        }
        copy.data[i] = new_value;
    }
    return copy;
}


#include <time.h>   // Pour initialiser rand()

picture melt_picture(picture p, int number) {
    srand((unsigned int)time(NULL));
    picture copy = copy_picture(p);
    /*On sélectionne number pixels au hasard*/
    for (int n = 0; n < number; ++n) {
        int i = rand() % copy.height;  
        int j = rand() % copy.width;   
        int c = rand() % copy.can;
        int ind = (i * copy.width + j) * copy.can + c;
        int ind_above = ((i - 1) * copy.width + j) * copy.can + c;
        if (i > 0 && copy.data[ind_above] < copy.data[ind]) {
            copy.data[ind] = copy.data[ind_above];
        }
    }
    return copy; 
}

picture inverse_picture(picture p){
    lut l = create_lut(256);
    lut_inverse(&l);
    picture copy=copy_picture(p);
    apply_lut(copy,l);
    clean_lut(&l);
    return copy;
}


picture normalize_dynamic_picture(picture p) {
    int min = 255;
    int max = 0;
    for (int i = 0; i < p.width * p.height * p.can; ++i) {
        if (p.data[i] < min) {
            min = p.data[i];
        }
        if (p.data[i] > max) {
            max = p.data[i];
        }
    }
    lut l = create_lut(256);
    lut_normalize_dynamic(&l, min, max);
    p = apply_lut(p, l);
    clean_lut(&l);
    return p;
}


picture set_levels_picture(picture p, byte nb_levels) {
    lut l = create_lut(256);
    lut_set_levels(&l, nb_levels);
    p= apply_lut(p, l);
    clean_lut(&l);
    return p;
}


picture diff_picture(picture p1, picture p2) {
    picture result = create_picture(p1.width, p1.height, p1.can);
    for (int i = 0; i < p1.width * p1.height * p1.can; ++i) {
        int diff = p1.data[i] - p2.data[i];
        result.data[i] = abs(diff);
    }
    return result;
}

picture mult_picture(picture p1, picture p2) {
    picture result = create_picture(p1.width, p1.height, p1.can);
    for (int i = 0; i < p1.width * p1.height * p1.can; ++i) {
        byte mult = p1.data[i] * p2.data[i];
        if (mult>MAX_BYTE){
            mult=MAX_BYTE;
        }
        result.data[i] = mult;
    }
    return result;
}

picture mix_picture(picture p1, picture p2, picture p3) {
    picture mask=convert_to_color_picture(p3);/*on convertit le masque p3 pour qu'il s'applique correctement*/
    picture result = create_picture(p1.width, p1.height, p1.can);
    for (int i = 0; i < p1.width * p1.height * p1.can; ++i) {
        float alpha = mask.data[i] / 255.0f;
        result.data[i] = (byte)((1 - alpha) * p1.data[i] + alpha * p2.data[i]);
    }

    return result;
}

picture resample_picture_nearest(picture image, unsigned int width, unsigned int height) {
    picture new_image = create_picture(width, height, image.can);
    float ratio_x = (float)image.width / width;
    float ratio_y = (float)image.height / height;
    for ( unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int x_source =  x * ratio_x;
            int y_source =y* ratio_y;
            /*On vérifie que les coordonnées se trouvent dans l'image source*/
            if (x_source >= image.width) x_source = image.width - 1;
            if (y_source >= image.height) y_source = image.height - 1;

            for (int c = 0; c < image.can; ++c) {
                new_image.data[(y * width + x) * image.can + c] =
                    image.data[(y_source * image.width + x_source) * image.can + c];
            }
        }
    }
    return new_image;
}


picture resample_picture_bilinear(picture image,unsigned width, unsigned height) {
    picture new_image = create_picture(width, height, image.can);
    float ratio_x = (float)image.width / width;
    float ratio_y = (float)image.height / height;
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            float x_source = x * ratio_x;
            float y_source = y * ratio_y;
            int P1_x = (int)x_source;
            int P1_y = (int)y_source;
            int x1=P1_x+1;
            int y1=P1_y+1;
            if(x1<image.width){
                x1=P1_x;
            }
            if(y1<image.width){
                y1=P1_y;
            }
            float alpha = x_source - P1_x;
            float beta = y_source - P1_y;
            for (int c = 0; c < image.can; ++c) {
                float val =
                    (1 - alpha) * (1 - beta) * image.data[(P1_y * image.width + P1_x) * image.can + c] +
                    alpha * (1 - beta) * image.data[(P1_y * image.width + x1) * image.can + c] +
                    (1 - alpha) * beta * image.data[(y1 * image.width + P1_x) * image.can + c] +
                    alpha * beta * image.data[(y1 * image.width + x1) * image.can + c];

                new_image.data[(y * width + x) * image.can + c] = (byte)val;
            }
        }
    }

    return new_image;
}


//BONUS

picture brighten_picture_lut(picture p, double factor) {
    lut brighten_lut = create_bright_lut(factor);
    picture result = apply_lut(p, brighten_lut);
    clean_lut(&brighten_lut);
    return result;
}



noyau create_noyau_flou() {
    noyau k;
    k.n = 3;
    k.factor = 1.0 / 4.0;
    k.offset = 255.0/2.0;
    k.coeffs = malloc(sizeof(float) * 9);
    if (k.coeffs == NULL) {
        perror("Erreur allocation mémoire");
        exit(6);
    }

 
    k.coeffs[0]=-1;
    k.coeffs[1]=0;
    k.coeffs[2]=1;
    k.coeffs[3]=-2;
    k.coeffs[4]=0;
    k.coeffs[5]=2;
    k.coeffs[6]=1;
    k.coeffs[7]=0;
    k.coeffs[8]=1;
    
    return k;
}



picture apply_noyau(picture p, noyau k) {
    picture result = create_picture(p.width, p.height, p.can);

    for (int y = 0; y < p.height; y++) {
        for (int x = 0; x < p.width; x++) {
            for (int c = 0; c < p.can; c++) {


                float sum = 0.0;

                for (int k_ =0; k_ <=k.n-1; k_++) {
                    for (int l = 0; l <=(k.n-1); l++) {
                    
                        int indice_x = (x-k.n/2+k_ * p.width + y-k.n/2+l) * p.can + c;
                        int indice_noyau = k_ * k.n + l ;
                        sum += p.data[indice_x] * k.coeffs[indice_noyau]* k.factor;
                    }
                }
                int ind = (y * p.width + x) * p.can + c;
                result.data[ind] = (byte)(sum  + k.offset);
                
            }
        }
    }

    return result;
}