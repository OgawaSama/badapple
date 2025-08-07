#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <png.h>

#define MAX_FILENAME 32 

png_structp pngptr;
png_infop pnginfo;
png_bytepp rows;

int width, height;
int whiteCharacter = ' ';
int blackCharacter = '*';
const int frameTotal = 7777;
int currentFrame = 1;

void setup_png_file(int frame_number) {
    // resolutions:
    // 38x28    // 1/25th of the original resolution
    // 114x88   // best!
    // 960x720  // works, but needs to zoom out the terminal a lot
    char file_name[MAX_FILENAME] = "imgs/frame_";
    char str[10];
    for (size_t a = 0; a < 10; a++)
        str[a] = '\0';
    int i = 0;
    while (frame_number > 0) {
        str[i++] = ('0' + frame_number % 10);
        frame_number /= 10;
    }
    int l = 0;
    int r =  i-1;
    char t;
    while (l < r) {
        t = str[l];
        str[l++] = str[r];
        str[r--] = t;
    }
    strcat(file_name, str);
    strcat(file_name, ".png");
    
    FILE *fp = fopen(file_name, "rb");
    if (!fp) {
        printf("%s couldnt be read\n", file_name);
        return;
    }
    pngptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    pnginfo = png_create_info_struct(pngptr);
    png_set_palette_to_rgb(pngptr);
    png_init_io(pngptr, fp);
    png_read_png(pngptr, pnginfo, PNG_TRANSFORM_IDENTITY, NULL);

    fclose(fp);
}


int main(void){
    // clear screen
    printf("\x1b[2J");
    char* buffer = (char*) malloc(sizeof(char) * 1);

    while(1) {

        // make png pointer for libpng
        setup_png_file(currentFrame % frameTotal);

        // play song and resize buffer with actual image size
        if (currentFrame % frameTotal == 1) {
            system("mpg123 -f \"7500\" -q badapple.mp3 &");
            width = png_get_image_width(pngptr, pnginfo);
            height = png_get_image_height(pngptr, pnginfo);
            buffer = (char*) realloc(buffer, sizeof(int)*height*width);
        }

        // fill buffer with black&white
        rows = png_get_rows(pngptr, pnginfo);
        int pos = 0;
        for (size_t lin = 0; lin < height; lin++) {
            for (size_t col = 0; col < width * 3; col+=3) {
                if (rows[lin][col]==255 && rows[lin][col+1]==255 && rows[lin][col+2]==255)
                    buffer[pos] = whiteCharacter;
                else if (rows[lin][col]==0 && rows[lin][col+1]==0 && rows[lin][col+2]==0)
                    buffer[pos] = blackCharacter;
                pos++;
            }
        }

        // clear screen and print frame
        printf("\x1b[H");
        for (size_t k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }

        usleep(41667);  // for 24fps
        //printf("\n\nFrame: %i\n", currentFrame);
        currentFrame++;
    }

    return 0;
}