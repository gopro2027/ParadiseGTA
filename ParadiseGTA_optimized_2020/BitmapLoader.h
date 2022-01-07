#ifdef bitmaploaderfileused

#define LITTLEENDIAN 0
#define PC 0

unsigned int swapEndian(unsigned int ret) {
	unsigned int v0 = ret&0x000000FF;
	unsigned int v1 = ret&0x0000FF00;
	unsigned int v2 = ret&0x00FF0000;
	unsigned int v3 = ret&0xFF000000;
	unsigned int final = (v0<<24)+(v1<<8)+(v2>>8)+(v3>>24);
	return final;
}
class BitmapImage;
struct RGB {
	unsigned char b,g,r;//will need to be flipped on the ps3 of course
};

struct Bitmap {
	unsigned int data;
	unsigned int getFilesize() {
		//in the bitmap file format, the filesize is saved in a little endian type format.
		unsigned int ret = *(volatile unsigned int*)(data+0x2);
		#if LITTLEENDIAN == 1
		return ret;
		#else
		return swapEndian(ret);
		#endif
	}
	unsigned int getWidth() {
		//in the bitmap file format, the width is saved in a little endian type format.
		unsigned int ret = *(volatile unsigned int*)(data+18);
		#if LITTLEENDIAN == 1
		return ret;
		#else
		return swapEndian(ret);
		#endif
		
	}
	unsigned int getHeight() {
		//in the bitmap file format, the height is saved in a little endian type format.
		unsigned int ret = *(volatile unsigned int*)(data+22);
		#if LITTLEENDIAN == 1
		return ret;
		#else
		return swapEndian(ret);
		#endif
	}
	unsigned int getPixelAddress() {
		unsigned int number = *(volatile unsigned int*)(data+10);
		#if LITTLEENDIAN == 0
		number = swapEndian(number);
		#endif
		return number;
	}
	RGB getPixel(int px, int py, char *fileName) {
		//convert y to the opposite so it starts at top left
		py = getHeight()-1-py;
		int row_padded = (getWidth()*3+3) & (~3);
		int y = row_padded*py;
		int spot = y+px*3;
		//printf("pixel spot: 0x%X\n",spot);
		//printf("pixel address: 0x%X\n",getPixelAddress());
		//in the bitmap file, colors are in the form of B G R
		char tmpdata[4];
		readFile(fileName,tmpdata,4,getPixelAddress()+spot);
		//printf("x: %i y: %i tmpdata: 0x%X\n\n",px,py,*(volatile unsigned int*)&tmpdata);
		return *(RGB*)(&tmpdata);
		
	}
	int spotToIndex(int x, int y) {
		return x+getWidth()*y;
	}
};

unsigned int currentOpenPixelAddress = 0x10030000;
class BitmapImage {
public:
	RGB *pixels;
	int width,height;
	bool imageLoaded;
	int spotToIndex(int x, int y) {
		return x+width*y;
	}
	void loadImage(char *filename) {
		imageLoaded = false;
		printf("loading image %s...\n",filename);
		//these will be deleted eventually
		Bitmap bmp;

		//first, load just a little bit so I can decide to size of the bitmap file
		unsigned char buf[100];
		//FILE *f = fopen(filename,"r");
		//fread(buf,sizeof(char),100,f);
		printf("reading file... ");
		readFile(filename,(char*)buf,100);
		printf("read\n");
		bmp.data = (unsigned int)buf;

		//get some info from the headers
		printf("getting filesize... ");
		int fileSize = bmp.getFilesize();
		printf("%iB\n",fileSize);
		width = bmp.getWidth();
		height = bmp.getHeight();
		int totalPixels = width*height;
		printf("Width %i height %i\n",width,height);
		if (totalPixels*4 > 0x100b0000-currentOpenPixelAddress) {
			printf("Picture size too big! Not loading picture.\n");
			return;
		}

		//close file
		//fclose(f);

		//allocate memory for pixels and the file
		printf("allocationg memory... ");
		pixels = (RGB*)currentOpenPixelAddress;//malloc(totalPixels*sizeof(RGB));
		//bmp.data = (unsigned int)neww(fileSize);
		printf("done\n");
		printf("bmp.data address: 0x%X\n",bmp.data);

		//read whole bitmap image to buffer
		//f = fopen(filename,"r");
		//fread((void*)bmp.data,sizeof(char),fileSize,f);
		//sleep(1000);//give time to allocate or something
		//readFile(filename,(char*)bmp.data,fileSize);
		//for (int i = 0; i < fileSize; i++) {
			//printf("%X",((unsigned char*)(0x10020200))[i]);
		//}
		//printf("\n");
		printf("read file into allocated memory\n");
		//copy the pixels into the pixel array
		printf("width: %i, height: %i\n",bmp.getWidth(),bmp.getHeight());
		for (int y = 0; y < bmp.getHeight(); y++) {
			for (int x = 0; x < bmp.getWidth(); x++){
				//printf("x: %i y: %i\n",x,y);
				RGB pixel = bmp.getPixel(x,y,filename);
				//printf("got pixel\n");
				//convert to index
				int i = bmp.spotToIndex(x,y);
				//printf("converted spot to index\n");
				pixels[i].r = pixel.r;
				pixels[i].g = pixel.g;
				pixels[i].b = pixel.b;
				//printf("index: %i x: %i y: %i r: %i g: %i b: %i\n",i,x,y,(int)pixel.r,(int)pixel.g,(int)pixel.b);
				//printf("going to next pixel...\n");
			}
		}
		printf("done loading\n",filename);
		//fclose(f);
		//RGB *tmppixels = pixels;
		//memcpy((void*)currentOpenPixelAddress,pixels,totalPixels*sizeof(RGB));
		//pixels = (RGB*)currentOpenPixelAddress;
		currentOpenPixelAddress+=totalPixels*sizeof(RGB);
		free((void*)bmp.data);
		//free((void*)tmppixels);
		//delete (void*)bmp.data;//not sure what this would be on ps3
		imageLoaded = true;
		
	}
};





#if PC == 0
#define WIDTH (*(volatile unsigned int*)0x22147C8)
#define HEIGHT (*(volatile unsigned int*)0x22147CC)
#else
#define WIDTH (1080)
#define HEIGHT (720)
#endif

//namespace GRAPHICS {void DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a) {printf("x: %f\ty: %f\tw: %f\th %f\tr: %i\tg: %i\tb: %i\ta %i\n",x,y,width,height,r,g,b,a);}}

void onePixelSize(float *x, float *y,float scalarx, float scalary) {
	int resx,resy;
	resx = WIDTH;
	resy = HEIGHT;
	*x = scalarx/resx;
	*y = scalary/resy;
}
void renderPixel(int x, int y, int r,int g, int b, int a,float scalarx, float scalary) {
	if (r == 0 && g == 255 && b == 0) {//green screen color
		return;//don't draw a pixel, black means no pixel for this
	}
	float sx,sy;
	onePixelSize(&sx,&sy,scalarx, scalary);
	float px = sx*x;
	float py = sy*y;
	#if PC == 0
	px+=sx/2;
	py+=sy/2;
	#endif
	GRAPHICS::DRAW_RECT(px,py,sx,sy,r,g,b,a);
}
//pixelsizex and pixelsizey are just onePixelSize(&sx,&sy,scalarx, scalary);     sx is pixelsizex and sy is pixelsizey
void renderPixelLess(int x, int y, int r,int g, int b, int a,float sx, float sy) {
	if (r == 0 && g == 255 && b == 0) {//green screen color
		return;//don't draw a pixel, black means no pixel for this
	}
	float px = x;
	float py = y;
	#if PC == 0
	px+=sx/2;
	py+=sy/2;
	#endif
	char buf[50];
	snprintf$(buf,50,"x: %f, y: %f\n",px,py);
	//printf(buf);
	GRAPHICS::DRAW_RECT(px,py,sx,sy,r,g,b,a);
}
void renderPicture(BitmapImage img, int posx, int posy, int alpha, float scalex, float scaley){
	float pixelsizex,pixelsizey;
	onePixelSize(&pixelsizex,&pixelsizey,scalex, scaley);//pre-calculate to save hundreds of lwz and float multiplication every render
	posy = posy/HEIGHT;
	posx = posx/WIDTH;
	char buf[50];
	snprintf$(buf,50,"posx: %f, posy: %f\n",posx,posy);
	//printf(buf);
	//printf("Got one pixel size\n");
	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++) {
			int n = img.spotToIndex(x,y);
			//printf("got spot to index\n");
			RGB c = img.pixels[n];
			//printf("r: %i g: %i b: %i\n",c.r,c.g,c.b);
			//renderPixel(x+posx,y+posy,c.r,c.g,c.b,alpha,scalex,scaley);//without the pre-calculate
			renderPixelLess(x*pixelsizex+posx,y*pixelsizey+posy,c.r,c.g,c.b,alpha,pixelsizex,pixelsizey);
		}
	}
}
void renderPicture(BitmapImage img, int posx, int posy, int alpha, int width, int height) {
	float imageWidth = img.width;
	float imageHeight = img.height;
	float scalex = width/imageWidth;
	float scaley = height/imageHeight;
	float pixelsizex,pixelsizey;
	onePixelSize(&pixelsizex,&pixelsizey,scalex, scaley);//pre-calculate to save hundreds of lwz and float multiplication every render
	posy = posy/HEIGHT;
	posx = posx/WIDTH;
	//printf("Got one pixel size\n");
	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++) {
			int n = img.spotToIndex(x,y);
			//printf("got spot to index\n");
			RGB c = img.pixels[n];
			//printf("r: %i g: %i b: %i\n",c.r,c.g,c.b);
			//renderPixel(x+posx,y+posy,c.r,c.g,c.b,alpha,scalex,scaley);//without the pre-calculate
			//renderPixelLess(x*pixelsizex+posx,y*pixelsizey+posy,c.r,c.g,c.b,alpha,pixelsizex,pixelsizey);
			renderPixelLess(x*pixelsizex+posx,y*pixelsizey+posy,c.r,c.g,c.b,alpha,pixelsizex,pixelsizey);
		}
	}
}

class GTAImage {
public:
	BitmapImage bmp;
	char *file;
	void load(char *fileLocation) {
		bmp.loadImage(fileLocation);
		file = fileLocation;
	}
	//render by pixels
	void render(int posx, int posy, int widthpixels, int heightpixels, int alpha) {
		//printf("Render Using Custom Pixel Width And Height:\n");
		if (bmp.imageLoaded)
			renderPicture(bmp,posx,posy,alpha,widthpixels,heightpixels);
	}
	//render by multiplier
	void render(int posx, int posy, float widthmultiplier, float heightmultiplier, int alpha) {
		//printf("Render Using Scalar Of Original Photo Size:\n");
		if (bmp.imageLoaded)
			renderPicture(bmp,posx,posy,alpha,widthmultiplier,heightmultiplier);
	}
	
};








/*

int _tmain(int argc, _TCHAR* argv[])
{
	GTAImage img;
	img.load("C:\\Users\\NewUser\\Desktop\\pngFormatInfo\\testimage3.bmp");
	img.render(0,0,2.0f,2.0f,255);
	printf("\n");
	img.render(0,0,4,6,255);
	while(true){}//pause program
	return 0;
}
*/

#endif