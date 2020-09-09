

#ifndef bmp_header
#define bmp_header

extern FILE *file_i;
extern long int width,height;
extern int pixel_start,bits_per_pixel,i,i1,padding_removal,pixel_size;
//extern unsigned char pixel[3];
void  input_img(const char *img);
int getpixel(int pix_x,int pix_y,int pix_color);
int* rgb2gray(const char *img1);
void bmp_write(int width,int height,int img_type);

#endif