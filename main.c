#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIDTH 9
#define HEIGHT 9
#define DENSITY 0.125

typedef struct f_s {
        int width;
        int height;
        char* fielddata;
        char* fieldmask;
} FIELD;

int compare( const void* a, const void* b) {
  int int_a = * ( (int*) a );
  int int_b = * ( (int*) b );
  return (int_a > int_b) - (int_a < int_b);
}

void gen_field(FIELD* f) {
        int num_mines = DENSITY * f->width * f->height;
        int* minebuf = malloc(sizeof(int) * num_mines);
        for(int i=0;i<num_mines;++i) {
repeat:
                minebuf[i] = rand()%(f->width*f->height);
                for(int j=0;j<i;++j) {
                        if(minebuf[i] == minebuf[j])
                                goto repeat;
                }
        }
        qsort( minebuf, num_mines, sizeof(int), compare );
        int j=0;
        for(int i=0;i<f->width*f->height;++i) {
                f->fielddata[i] = minebuf[j] == i ? '#' : '0';
                if(minebuf[j] == i)
                        j++;
        }
        free(minebuf);
        int attemptedX, attemptedY;
        for(int h=0;h<f->height;++h)
                for(int w=0;w<f->width;++w)
                        if(f->fielddata[h*f->width + w] == '#')
                                for(int i=-1;i<=1;++i)
                                        for(int j=-1;j<=1;++j) {
                                                attemptedX = w+i;
                                                attemptedY = h+j;
                                                if(attemptedX < 0 || attemptedX >= f->width || attemptedY < 0 || attemptedY >= f->height || f->fielddata[attemptedY*f->width+attemptedX] == '#')
                                                        continue;
                                                f->fielddata[attemptedY*f->width+attemptedX]++;
                                        }
}

void print_field(FIELD* f) {
        for(int i=0;i<f->height;++i) {
                for(int j=0;j<f->width;++j)
                        if(f->fieldmask[i*f->width+j] == 1)
                                printf("%c ", f->fielddata[i*f->width+j]);
                        else if(f->fieldmask[i*f->width+j] == 2)
                                printf("P ");
                        else
                                printf(". ");
                printf("\n");
        }
}

void unmask(FIELD* f, int x, int y) {
        if(x < 0 || y < 0 || x >= f->width || y >= f->height || f->fieldmask[y*f->width+x] == 1)
                return;
        f->fieldmask[y*f->width+x] = 1;
        if(f->fielddata[y*f->width+x] == '0')
                for(int i=-1;i<=1;++i)
                        for(int j=-1;j<=1;++j) {
                                if(i==0 && j==0) continue;
                                unmask(f, x+i, y+j);
                        }
}

void flag(FIELD* f, int x, int y) {
        if(x < 0 || y < 0 || x > f->width || y > f->height || f->fieldmask[y*f->width+x] == 1)
                return;
        f->fieldmask[y*f->width+x] ^= 2;
}

int is_win(FIELD* f) {
        for(int i=0;i<f->width*f->height;++i)
                if(f->fieldmask[i] == 0)
                        return 0;
        return 1;
}

int is_mine(FIELD* f, int x, int y) {
        if(x < 0 || y < 0 || x >= f->width || y >= f->height || f->fieldmask[y*f->width+x] == 0)
                return 0;
        return f->fielddata[y*f->width+x] == '#' && f->fieldmask[y*f->width+x] != 2;
}

int main() {
        srand(time(NULL));
        FIELD f;
        f.width = WIDTH;
        f.height = HEIGHT;
        f.fielddata = malloc(WIDTH*HEIGHT*sizeof(char));
        f.fieldmask = malloc(WIDTH*HEIGHT*sizeof(char));
        memset(f.fieldmask, 0, WIDTH*HEIGHT);
        gen_field(&f);
        int x, y;
        char p;
        while(!is_win(&f)) {
                print_field(&f);
                int err = scanf("%d %d %c", &x, &y, &p);
                if(err == 3 && p == 'b')
                        unmask(&f, x, y);
                else if(err == 3 && p == 'f')
                        flag(&f, x, y);
                if(is_mine(&f, x, y)) {
                        for(int i=0;i<f.width*f.height;++i) {
                                if(f.fieldmask[i] == 0)
                                        f.fieldmask[i] = 1;
                        }
                        print_field(&f);
                        break;
                }
        }
        free(f.fielddata);
}
