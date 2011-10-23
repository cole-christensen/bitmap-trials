#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
   float    x;
   float    y;
} point;

int main(){
	struct tri_2d {
		point A;
		point B;
		point C;
	} hello;

	hello.A.x = 0.0;
	hello.A.y = 1.0;
	hello.B.x = 0.0;
	hello.B.y = 0.0;
	hello.C.x = 1.0;
	hello.C.y = 0.0;
	
	int i=0;
	int j=0;
	int w = 800;
	int h = 600;
	int x = 0;
	int y = 0;
	unsigned char r,g,b;

	float xmin = -10.0;
	float xmax =  10.0;
	float dx   = (xmax - xmin) / w;
	float fx   = 0.0;
	
	float ymin = -10.0;
	float ymax =  10.0;
	float dy   = (ymax - ymin) / h;
	float fy   = 0.0;

	float d; //distance

	point A;
	point B;

	unsigned char *img = (unsigned char *)malloc(3*w*h);	

	for(i=0; i<w; i++){
		for(j=0; j<h; j++){
			x=i; y=(h-1)-j;
			fx = xmin + (float)(x)*dx;
			fy = ymin + (float)(y)*dy;

			r = 255*(sin(fx)+1)/2;
			g = 255*(cos(fy)+1)/2;
			b = 255*(sin(fx*fy)+1)/2;
			
			img[(x+y*w)*3+2] = (unsigned char)(r); //red
			img[(x+y*w)*3+1] = (unsigned char)(g); //green
			img[(x+y*w)*3+0] = (unsigned char)(b); //blue

			//render A to B
			A = hello.A;
			B = hello.B;
			d = 0.5 - abs((A.x - B.x)*(A.y - fy) - (A.x - fx)*(B.y-A.y))/sqrt(pow(A.x-B.x,2) + pow(A.y - B.y,2));
			if(d<0.5){
				r = (d/0.5 * 255);
				g = (d/0.5 * 255);
				b = (d/0.5 * 255);
				img[(x+y*w)*3+2] = (unsigned char)(r); //red
				img[(x+y*w)*3+1] = (unsigned char)(g); //green
				img[(x+y*w)*3+0] = (unsigned char)(b); //blue
			}
			
			//render B to C
			A = hello.B;
			B = hello.C;
			d = 0.5 - abs((A.x - B.x)*(A.y - fy) - (A.x - fx)*(B.y-A.y))/sqrt(pow(A.x-B.x,2) + pow(A.y - B.y,2));
			if(d<0.5){
				r = (d/0.5 * 255);
				g = (d/0.5 * 255);
				b = (d/0.5 * 255);
				img[(x+y*w)*3+2] = (unsigned char)(r); //red
				img[(x+y*w)*3+1] = (unsigned char)(g); //green
				img[(x+y*w)*3+0] = (unsigned char)(b); //blue
			}
			
			//render C to A
			A = hello.C;
			B = hello.A;
			d = 0.5 - abs((A.x - B.x)*(A.y - fy) - (A.x - fx)*(B.y-A.y))/sqrt(pow(A.x-B.x,2) + pow(A.y - B.y,2));
			if(d<0.5){
				r = (d/0.5 * 255);
				g = (d/0.5 * 255);
				b = (d/0.5 * 255);
				img[(x+y*w)*3+2] = (unsigned char)(r); //red
				img[(x+y*w)*3+1] = (unsigned char)(g); //green
				img[(x+y*w)*3+0] = (unsigned char)(b); //blue
			}
			
		}
	}

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
    
    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

	FILE *f = fopen("img2.bmp","wb");

    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }

	fclose(f);
	return 0;
}
