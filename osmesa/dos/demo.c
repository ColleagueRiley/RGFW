/* #define DO_SVGA */

#include <stdio.h>
#include <i86.h>
#include <stdlib.h>
#include <conio.h>
#include <GL/osmesa.h>
#include <GL/gl.h>
#include <string.h>
#include <dos.h>

OSMesaContext ctx;

#ifdef DO_SVGA
#define WIDTH 640
#define HEIGHT 480
#else
#define WIDTH 320
#define HEIGHT 200
#endif

void(__interrupt *old)();

int quit = 0;
int press = 0;

void __interrupt key(){
	unsigned char sc = inp(0x60);
	press = 1;
	if(sc == 1) quit = 1;
	outp(0x20, 0x20);
}

/* Where you draw stuff */
double deg = 0;
void draw(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(deg++, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
		glVertex2f(0, 50);
	glColor3f(0, 1, 0);
		glVertex2f(-50, -50);
	glColor3f(0, 0, 1);
		glVertex2f(50, -50);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

int main(){
	unsigned char* buf;
	int i;
	int mode;
	union REGS regs;
	long buffer_size;
	unsigned char* base = (unsigned char*)0xa0000;
	long depth;
#ifdef DO_SVGA
	unsigned char svga[256];
	unsigned short wgr;
	unsigned short wseg;
#endif

	printf("OSMesa DOS Demo\n");

#ifdef DO_SVGA
	buffer_size = WIDTH * HEIGHT * 4;
	depth = 4;
	buf = malloc(buffer_size);
	ctx = OSMesaCreateContext(OSMESA_BGRA, NULL);
	OSMesaMakeCurrent(ctx, (unsigned char*)buf, GL_UNSIGNED_BYTE, WIDTH, HEIGHT);
#else
	buffer_size = WIDTH * HEIGHT;
	depth = 1;
	buf = malloc(buffer_size);
	ctx = OSMesaCreateContext(OSMESA_RGB_332, NULL);
	OSMesaMakeCurrent(ctx, (unsigned char*)buf, GL_UNSIGNED_BYTE, WIDTH, HEIGHT);
#endif
	OSMesaPixelStore(OSMESA_Y_UP, 0);

	old = _dos_getvect(0x09);
	_dos_setvect(0x09, key);

	printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
	printf("Press any key to continue... ");
	fflush(stdout);
	while(!press);
	quit = 0;
	press = 0;

	regs.h.ah = 0x0f;
	int386(0x10, &regs, &regs);
	mode = regs.h.al;

#ifdef DO_SVGA
	regs.w.ax = 0x4f01;
	regs.w.cx = 0x112;
	regs.x.edi = (unsigned int)&svga[0];
	int386(0x10, &regs, &regs);

	if(svga[0] & (1 << 1)){
		if(svga[0x19] == 15){
			depth = 2;
		}else{
			depth = svga[0x19] / 8;
		}
	}

	memcpy(&wgr, &svga[4], 2);
	memcpy(&wseg, &svga[8], 2);

	base = (unsigned char*)(wseg * 0x10);

	regs.w.ax = 0x4f02;
	regs.w.bx = 0x112;
	int386(0x10, &regs, &regs);
#else
	regs.h.ah = 0;
	regs.h.al = 0x13;
	int386(0x10, &regs, &regs);

	for(i = 0; i < 256; i++){
		/* RRRGGGBB */
		int r = (double)((i >> 5) & 7) / 7 * 255;
		int g = (double)((i >> 2) & 7) / 7 * 255;
		int b = (double)((i >> 0) & 3) / 3 * 255;
		
		regs.h.ah = 0x10;
		regs.h.al = 0x10;

		regs.w.bx = i;
		regs.h.ch = (double)g / 255 * 0x3f;
		regs.h.cl = (double)b / 255 * 0x3f;
		regs.h.dh = (double)r / 255 * 0x3f;
		int386(0x10, &regs, &regs);
	}
#endif

	while(!quit){
#ifdef DO_SVGA
		long bsz = buffer_size / 4 * depth;
		unsigned char* nbuf = malloc(bsz);
		if(depth == 2){
			unsigned short* b = (unsigned short*)nbuf;
			for(i = 0; i < WIDTH * HEIGHT; i++){
				unsigned char c[4];
				memcpy(c, buf + i * 4, 4);
				b[i] = 0;

				b[i] += (c[2] * 32 / 255);
				b[i] = b[i] << 5;

				b[i] += (c[1] * 32 / 255);
				b[i] = b[i] << 5;

				b[i] += (c[0] * 32 / 255);
			}
		}else if(depth == 4){
			memcpy(nbuf, buf, bsz);
		}
#endif
		draw();
#ifdef DO_SVGA
		i = 0;
		while(bsz > 0){
			long sz = bsz < (wgr * 1024) ? bsz : (wgr * 1024);

			regs.w.ax = 0x4f05;
			regs.h.bh = 0;
			regs.h.bl = 0;
			regs.w.dx = i;
			int386(0x10, &regs, &regs);

			memcpy(base, nbuf + i * wgr * 1024, sz);

			i++;
			bsz -= sz;
		}
		free(nbuf);
#else
		memcpy(base, buf, WIDTH * HEIGHT);
#endif
	}
	OSMesaDestroyContext(ctx);

	regs.h.ah = 0;
	regs.h.al = mode;
	int386(0x10, &regs, &regs);

	_dos_setvect(0x09, old);

	free(buf);

	return 0;
}
