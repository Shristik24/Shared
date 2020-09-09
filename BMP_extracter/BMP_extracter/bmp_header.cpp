
#include<stdio.h>
#include<stdlib.h>
#include"bmp_header.h"

using namespace std;


FILE *file_i,*file_o;
long int width,height,t;
int pixel_start,bits_per_pixel,i,i1,padding_removal,pixel_size,pixel_value=0;
unsigned char ch;
int *pixel,*pix_gray; 
char BITMAPFILEHEADER[] ={0x42, 0x4D, 0xAE, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00};
char BITMAPINFOHEADER[] ={0x28, 0x00, 0x00, 0x00, 0x2B, 0x01, 0x00, 0x00, 0xDE, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x16, 0x00, 0x00, 0x34, 0x16, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void  input_img(const char *img)
{
     file_i=fopen(img,"rb+");
     
     fseek(file_i,10,SEEK_SET);
     fread(&pixel_start,4,1,file_i);
     //printf("%d   ",pixel_start);
          
     fseek(file_i,18,SEEK_SET);
     fread(&width,4,1,file_i);
     //printf("%ld  ",width);    //width = no. of pixel points in a row( i.e width=3 means 3 RGB(=3*3bytes))
     
     fseek(file_i,22,SEEK_SET);
     fread(&height,4,1,file_i);
     //printf("%ld   ",height);
     
     fseek(file_i,28,SEEK_SET);
     fread(&bits_per_pixel,2,1,file_i);
     //printf("%d  ",bits_per_pixel);
     pixel_size=bits_per_pixel/8;
     
     pixel=new int[width*height*pixel_size];
     fseek(file_i,pixel_start,SEEK_SET);
     							                  //Total bytes in a row=width*no of bytes per RGB --should be multiple of 4
     padding_removal=4-((width*(bits_per_pixel/8)) % 4);  //Else 4-remainder bytes are padded;
     //printf("%d  ",padding_removal);
     int origin=0;  //right now works for 8,24 bit images
     for(i=0;i<height;i++)
     {
          for(i1=0;i1<width;i1++)
          {
               for(int i2=0;i2<pixel_size;i2++)
               {
               fread(&ch,1,1,file_i);
               pixel[origin]=int(ch);
               origin++;
               //fprintf(file_w,"%d ",pixel);
               }
           }
           fseek(file_i,padding_removal,SEEK_CUR);
           //file=file+padding_removal;
           //fprintf(file_w,"\n");
     }
     
     fclose(file_i);
     //return 0;
}
int getpixel(int x,int y,int pix_color)
{    
    pixel_value=0; 
    if(pixel_size==2)
          {
               switch (pix_color)
               {
                    case 0:
                    pixel_value=pixel[pixel_size*width*y + pixel_size*x + 0]%32; // to fetch BGR swapped 16bit image value
                    break;

                    case 1:
                    pixel_value=(pixel[pixel_size*width*y + pixel_size*x + 1]%8)*2^3 + pixel[pixel_size*width*y + pixel_size*x + 0]/32;
                    break;

                    case 2:
                    pixel_value=pixel[pixel_size*width*y + pixel_size*x + 0]/32;
                    break;

                    default:
                    printf("Put the correct pixel color (value less than 3)\n");
                    break;
               }
          }

     else if(pix_color < pixel_size)
          {              
          pixel_value=pixel[pixel_size*width*y + pixel_size*x + pix_color]; //pixel_value=width*height*y+width*x+pix_col
          }

     else
     printf("Put the correct pixel color value\n" );
               
     return pixel_value;
};

int* rgb2gray(const char *img1) //RGB to Gray Conversion using Averaging Method
{
     int w=width/3;
    pix_gray=new int[w*height*pixel_size]; 
    int k=0;
    for(i=0;i<height;i++)
     {
          for(i1=0;i1<width/3;i1++)
          {
               pix_gray[k]= (pixel[k]+pixel[k+1]+pixel[k+2])/3;
               k++;
          }
     }

return pix_gray;
}

void bmp_write(int width,int height,int img_type)
{
     int *pos=0,bfSIZE=0,biSIZE=40,biBITCOUNT=img_type,pad_value=0;
     char f=255,f1=0;
     file_o=fopen("Output_img.bmp","wb+");
     fwrite(&BITMAPFILEHEADER,sizeof(BITMAPFILEHEADER),1,file_o);
     fwrite(&BITMAPINFOHEADER,sizeof(BITMAPINFOHEADER),1,file_o);
     if((width*(img_type/8)%4)!=0)
     {
          pad_value=(width*(img_type/8))%4;
     }
     bfSIZE=54+(((width*(img_type/8))+pad_value)*height);
     fseek(file_o,2,SEEK_SET);
     fwrite(&bfSIZE,sizeof(bfSIZE),1,file_o);
     fseek(file_o,14,SEEK_SET);
     fwrite(&biSIZE,sizeof(biSIZE),1,file_o);
     fseek(file_o,18,SEEK_SET);
     fwrite(&width,sizeof(width),1,file_o);
     fseek(file_o,22,SEEK_SET);
     fwrite(&height,sizeof(height),1,file_o);
     fseek(file_o,28,SEEK_SET);
     fwrite(&biBITCOUNT,sizeof(img_type),1,file_o);

     // for(i=0;i<h;i++)
     // {
     //      for(i1=0;i1<w;i1++)
     //      {
     //           fwrite(&arr[i][i1],sizeof(arr[i][i1]),1,file_o);
     //      }
     //      if(pad_value!=0)
     //      fwrite(&f,1,pad_value,file_o);
     // }
     f1=0;
     f=255;
     printf("%d\n", pad_value);
     fseek(file_o,54,SEEK_SET);
     for(i=0;i<height;i++)
     {
          for(i1=0;i1<width;i1++)
          {
               f=255;
            fwrite(&f,1,1,file_o);
            fwrite(&f,1,1,file_o); 
            fwrite(&f,1,1,file_o);    
            
          }
          f=0;
           fwrite(&f,1,1,file_o);
           fwrite(&f,1,1,file_o);
           fwrite(&f,1,1,file_o);
          
     }
     fclose(file_o);

}