/*ͼ����ʾģ��*/

/*�ļ�ͷ�ṹ*/
typedef struct tagBITMAPFILEHEADER
{
  int     bfType;
  long    bfSize;
  int     bfReserved1;
  int     bfReserved2;
  long    bfOffBits;
} BITMAPFILEHEADER;


/*��Ϣͷ�ṹ*/
typedef struct tagBITMAPINFOHEADER

{
  long    biSize;             /* ��Ϣͷ��С */
  long    biWidth;            /* ͼ����� */
  long    biHeight;           /* ͼ��߶� */
  int     biPlanes;           /* ����Ϊ1 */
  int     biBitCount;         /* ÿ����λ����������1, 4, 8��24 */
  long    biCompression;      /* ѹ������ */
  long    biSizeImage;        /* ʵ��ͼ���С��������4�ı��� */
  long    biXPelsPerMeter;    /* ˮƽ����ÿ�������� */
  long    biYPelsPerMeter;    /* ��ֱ����ÿ��������*/
  long    biClrUsed;          /* ������ɫ��*/
  long    biClrImportant;     /* ��Ҫ����ɫ�� */
} BITMAPINFOHEADER;


/*��ɫ��*/
typedef struct tagRGBQUAD
{
  char    rgbBlue;   /*��ɫ����*/
  char    rgbGreen;  /*��ɫ����*/
  char    rgbRed;    /*��ɫ����*/
  char    rgbReserved;
} RGBQUAD;




int COLS=640, ROWS=480;     /* ȱʡΪ256ɫ640*480ģʽ */

/*��ҳ����*/
void selectpage(register char page)
{
  union REGS r;

  r.x.ax=0x4f05;
  r.x.bx=0;
  r.x.dx=page;            /*ѡ��ҳ��*/
  int86(0x10,&r,&r);
}

/*����SVGA��Ļģʽ*/
/*101H----256ɫ640��480ģʽ*/
/*103H----256ɫ800��600ģʽ*/
/*105H----256ɫ1024��768ģʽ*/
unsigned char set_SVGA_mode(int vmode)
{
  union REGS r;
  r.x.ax=0x4f02;
  r.x.bx=vmode;
  int86(0x10,&r,&r);     
  return(r.h.ah);
}

/*��ȡ��ǰSVGA��Ļģʽ*/
unsigned int get_SVGA_mode()
{    union REGS r;
  r.x.ax=0x4f03;
  int86(0x10,&r,&r);
  return(r.x.bx);
}


/*���õ�ɫ��*/
void set_SVGA_palette(unsigned char r[],  unsigned char g[], unsigned char b[])
{
  int  k;
  for (k = 0; k < 257; k++) {
     outportb(0x03C8,k);
     outportb(0x03C9,r[k]>>2);
     outportb(0x03C9,g[k]>>2);
     outportb(0x03C9,b[k]>>2);
  }
}


void ShowPicture(int canshu,int x,int y)				/* ��һ����������ȡ����ͼ����������������ͼ��λ�� */
{

     BITMAPFILEHEADER    FileHeader;
     BITMAPINFOHEADER    bmiHeader;
     RGBQUAD             bmiColors[256];
     unsigned char       buffer[1024], r[257], g[257], b[257];
     unsigned int    width, height, linebytes;
     long        offset, position;
     char page_new=0,page_old=0;
     int i,j,k,n,savemode;
     FILE *fp;
     char str1[]="f:\tc\1\start.bmp" ;
     char str2[]="f:\tc\1\1.bmp";
     char str3[]="f:\tc\1\2.bmp";
     char str4[]="f:\tc\1\3.bmp" ;
     char str5[]="f:\tc\1\4.bmp";
     char str6[]="f:\tc\1\5.bmp";
     char str7[]="f:\tc\1\6.bmp";
     char str8[]="f:\tc\1\7.bmp";
     char str9[]="f:\tc\1\8.bmp";
     char str10[]="f:\tc\1\9.bmp";
     char str11[]="f:\tc\1\10.bmp";
     char str12[]="f:\tc\1\exit.bmp";

     int x_offset,  y_offset ;
     x_offset=x; y_offset=y;

     /*����Ҫ��ʾ��BMP�ļ�·��*/
     if(canshu==1)	 strcpy(buffer,str1);
     if(canshu==2)	 strcpy(buffer,str2);
     if(canshu==3)	 strcpy(buffer,str3);
     if(canshu==4)	 strcpy(buffer,str4);
     if(canshu==5)	 strcpy(buffer,str5);
     if(canshu==6)	 strcpy(buffer,str6);
     if(canshu==7)	 strcpy(buffer,str7);
     if(canshu==8)	 strcpy(buffer,str8);
     if(canshu==9)	 strcpy(buffer,str9);
     if(canshu==10)	 strcpy(buffer,str10);
     if(canshu==11)	 strcpy(buffer,str11);
     if(canshu==12)	 strcpy(buffer,str12);

     if((fp=fopen(buffer,"rb"))==NULL) /*�жϴ��ļ��Ƿ���ȷ*/
     {
       printf("Can't open file: %s",buffer);
       return;
     }

     if (fread((char *)&FileHeader, sizeof(FileHeader), 1, fp) != 1) {
        printf("Can't read file header !\n"); /* ���ļ�ͷ */
        return;
     }
     if (FileHeader.bfType != 0X4D42) {  /* BM */
        fprintf(stderr, "Not a BMP file !\n");
        return;
     }

     if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1) {
        fprintf(stderr, "Can't read bmiHeader !\n");    /* ����Ϣͷ */
        return;
     }
     if (bmiHeader.biBitCount > 8) {    /* ������ʾ���ɫͼ�� */
        fprintf(stderr, "Can not display ture color image !\n");
        return;
     }
     if (bmiHeader.biCompression != 0) { /* ���ܴ���ѹ��ͼ�� */
        fprintf(stderr, "Not non-compressed image !\n");
        return;
     }

     width = (unsigned int)bmiHeader.biWidth;
     height = (unsigned int)bmiHeader.biHeight;
     linebytes = ((width*(long)bmiHeader.biBitCount+31)/32)*4; /* ÿ���ֽ���--4�������� */

     if (fread((char *)&bmiColors[0], 4, 256, fp) != 256) { /* ����ɫ������ */
        fprintf(stderr, "Can't get palette !\n");
        return;
     }

     savemode=get_SVGA_mode(); /*�ȱ���ԭ������Ļģʽ*/
     set_SVGA_mode(0x101); /*Ӳ���޹��Գ�ʼ����ĻΪ256ɫ640*480ģʽ*/
     COLS=640;ROWS=480;
     r[256]= 0;g[256]=0;b[256]=0;
     for (i = 0; i < 256; i++) {
        r[i] = bmiColors[i].rgbRed;
        g[i] = bmiColors[i].rgbGreen;
        b[i] = bmiColors[i].rgbBlue;
     }
     set_SVGA_palette(r, g, b); /* ���õ�ɫ�� */

     offset = FileHeader.bfOffBits;
     fseek(fp, offset, SEEK_SET);    /* ����λͼ���ݵ���ʼλ�� */
     for(j=height-1;j>=0;j--) {
     fread(buffer,linebytes,1,fp);
     for(i=0,n=0;i<width;i++,n++) {
        position=(j+y_offset)*(long)COLS+i+x_offset; /*����Ҫ��ʾ����Դ�λ��*/
        page_new=position/65536l; /*������ʾҳ*/
        if(page_new!=page_old) /*����ʾҳ��ͬʱ����ҳ�棬���һ��������ٶ�*/
    	{
            selectpage(page_new);
            page_old=page_new;
    	}
        pokeb(0xa000,position%65536l,buffer[n]); /*д���Դ�λ��*/
     }
  }
  fclose(fp);
  bioskey(0);
  set_SVGA_mode(savemode); /*�ָ���Ļ*/
}