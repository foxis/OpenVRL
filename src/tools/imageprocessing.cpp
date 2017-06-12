// ImageProcessing.cpp: implementation of the CImageProcessing class.
//
//////////////////////////////////////////////////////////////////////

#include "tools/ImageProcessing.h"
#include <math.h>
#include <windows.h>
#include <wingdi.h>

namespace openvrl {

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif


#define CHECKCLR(r,g,b, r1,g1,b1, t) \
	(r>r1-t&&r<r1+t)&&(g>g1-t&&g<g1+t)&&(b>b1-t&&b<b1+t)?1:0

#if !defined(M_PI)
#define M_PI 3.14159265
#endif

/////////////////////////////////////////////////////////////////////
//
//

void CImageProcessing::img::SetPixel(ulong x, ulong y, const void* p)
{
	if ( x>=m_Width||y>=m_Height ||p==0 ) return;
	ulong offs = (y*m_Width+x)*m_BytesPerPixel;
	memcpy(((BYTE*)m_Data+offs), p, m_BytesPerPixel);
}

void CImageProcessing::img::GetPixel(ulong x, ulong y, void* p) const
{
	if ( x>=m_Width||y>=m_Height ||p==0 ) return;
	ulong offs = (y*m_Width+x)*m_BytesPerPixel;
	memcpy(p, (BYTE*)m_Data+offs, m_BytesPerPixel);
}

void CImageProcessing::img::CopyPortion(CImageProcessing::img* d, ulong x, ulong y, ulong w, ulong h) const
{
	char* src;
	char* dest;
	const ulong hr = (y+h)>m_Height ? m_Height-y : h;
	const ulong wr = (x+w)>m_Width ? m_Width-x : w;
	const ulong sw = wr*m_BytesPerPixel;
	ulong i;

	if ( d==0 || x>=m_Width || y>=m_Height || wr==0 || hr==0 ) return ;   
	d->Allocate(wr,hr,m_BytesPerPixel,0);

	dest = (char*)d->Data();
	src = (char*)Data() + (x + y*m_Width)*m_BytesPerPixel;

	for ( i=0;i<hr;i++ )
	{
		memcpy(dest, src, sw);
		dest+= sw;
		src += m_ScanWidth;
	}
}

void CImageProcessing::img::CopyPortionPrimitive(CImageProcessing::img* d, real x1, real y1, real x2, real y2,
							real x3, real y3, real x4, real y4, real width, real height) const
{
	real i,j, x,y, dx, dy;
	real t, t1, slw;
	real dx1, dy1, dx2, dy2;
	real _x1, _x2, _y1, _y2;

	BYTE *dest, *src;
	if ( d==0 ) return ;

//	width = 256;
//	height = floor(width*1.8);

	dx1 = -(x1-x4);
	dx2 = -(x2-x3);
	dy1 = -(y1-y4);
	dy2 = -(y2-y3);

	d->Allocate((ulong)width, (ulong)height, m_BytesPerPixel);
	src = (BYTE*)m_Data;
	slw = floor(m_BytesPerPixel*width);
	for ( j=0;j<height;j++ )
	{
		dest = (BYTE*)d->Data() + (ulong)(j*slw);
		t = j/(height-1);
		_x1 = x1+t*dx1;
		_x2 = x2+t*dx2;
		_y1 = y1+t*dy1;
		_y2 = y2+t*dy2;
		dx = -(_x1-_x2);
		dy = -(_y1-_y2);
		for ( i=0;i<width;i++ )
		{
			t1 = i/(width-1);
			
			x = floor(_x1 + t1*dx);
			y = floor(_y1 + t1*dy);

//			*dest = src[(ulong)(_x1+_y1*m_Width)];
			memcpy(dest, src+ (ulong)(floor(y*m_ScanWidth)+floor(x*m_BytesPerPixel)), m_BytesPerPixel);

			dest+=m_BytesPerPixel;
		}
	}
}

//
real CImageProcessing::img::MatchTemplate(const CImageProcessing::img& i, real th) const 
{
	BYTE* s1;
	BYTE* s2;
	const ulong n = m_Width*m_Height;
	ulong j, m;
	real r;

	if ( m_BytesPerPixel!=1 ) return 1;
	if ( n!=i.Width()*i.Height() ) return 1;

	s1 = (BYTE*)Data();
	s2 = (BYTE*)i.Data();


	for ( j=0,m=1,r=0;j<n;j++ )
	{
		const real t = abs(*s1-*s2);

		if ( t<th )
			m++;

		r += t;

		s1++;
		s2++;
	}

	return r/(255.0*(real)n);
//	return (n-m-1)/(real)m;
}

//
real CImageProcessing::img::calc_average() const
{
	BYTE* src;
	const ulong n = m_Width*m_Height;
	ulong i;
	real av;

	src = (BYTE*)Data();

	if ( m_BytesPerPixel!=1 ) return 0;

	for ( i=0,av=0;i<n;i++ )
	{
		av += *src;
		src++;
	}
	return av/(real)n;
}

void   CImageProcessing::img::calc_range(int *min, int *max) const
{
	BYTE* src;
	const ulong n = m_Width*m_Height;
	ulong i;
	int mn=(int)1e5, mx=(int)-1e5;

	src = (BYTE*)Data();

	if ( m_BytesPerPixel!=1 ||min==0||max==0) return;

	for ( i=0;i<n;i++ )
	{
		if ( *src>mx )
			mx = *src;
		if ( *src<mn )
			mn = *src;
		src++;
	}
	*min = mn;
	*max = mx;
}

// counts pixels greater than th
ulong CImageProcessing::img::count_gt(char th) const
{
	BYTE* src;
	const ulong n = m_Width*m_Height;
	ulong i;
	unsigned num=0;

	src = (BYTE*)Data();

	if ( m_BytesPerPixel!=1) return 0;

	for ( i=0;i<n;i++ )
	{
		if ( *src>=th )
			num++;
		src++;
	}
	return num;
}

// counts pixels lower than th
ulong CImageProcessing::img::count_lt(char th) const
{
	BYTE* src;
	const ulong n = m_Width*m_Height;
	ulong i;
	unsigned num=0;

	src = (BYTE*)Data();

	if ( m_BytesPerPixel!=1) return 0;

	for ( i=0;i<n;i++ )
	{
		if ( *src<th )
			num++;
		src++;
	}
	return num;
}

// fills cb bytes of the image with b
void CImageProcessing::img::fill(BYTE b, ulong cb)
{
	BYTE* src;
	const ulong _cb = m_Width*m_Height*m_BytesPerPixel;
	src = (BYTE*)Data();
	if ( _cb==0 || src==0 ) 
		return ;

	if ( cb==0 || cb>_cb ) 
		cb = _cb;

	memset(src, b, cb);
}

//	loads a custom format file into image
int CImageProcessing::img::LoadFromFile(const char *fname, const char *format, ulong skip, ulong width, ulong height, BYTE bps)
{
	if ( fname==0 || format==0 ) return 1;

	FILE *f;
	BYTE *buffer;
	size_t cb, n;
	
	f = fopen(fname, "rb");
	if ( f==0 ) return 2;
	n = width*height*bps;
	if ( fseek(f, skip, SEEK_SET)!=0 ) {	fclose(f); return 3; }

	if ( strnicmp(format, "RAW", 3)==0 )		//////// RAW file format loader
	{
		buffer = new BYTE[width*height];	
		cb = fread(buffer, 1, n, f);
		if ( cb!=n ) { delete[] buffer; fclose(f); return 4; }
		Allocate(width, height, bps, buffer);
		delete[] buffer;
		if ( m_Data==0 ) { fclose(f); return 5; }
	} 
	else if ( strnicmp(format, "RAS", 3)==0 )	///////// Sun RAS file format loader
	{
		const ulong  RAS_MAGIC = 0x59a66a95; //0x956aa659
		struct rasterfile {
           ulong  ras_magic;
           ulong  ras_width;
           ulong  ras_height;
           ulong  ras_depth;
           ulong  ras_length;
           ulong  ras_type;
           ulong  ras_maptype;
           ulong  ras_maplength;
		}  head;
#define _CONVERT(a) ( (0x000000FF&((a)>>24)) | (0xFF000000&((a)<<24)) | (0x0000FF00&((a)>>8)) | (0x00FF0000&((a)<<8)) )
		cb = fread(&head, 1, sizeof(head), f);

		head.ras_magic = _CONVERT(head.ras_magic);
		head.ras_width = _CONVERT(head.ras_width);
		head.ras_height = _CONVERT(head.ras_height);
		head.ras_depth = _CONVERT(head.ras_depth);
		head.ras_maplength = _CONVERT(head.ras_maplength);
#undef _CONVERT
		head.ras_length=(head.ras_width*head.ras_height*head.ras_depth>>3);
		if ( cb!=sizeof(head) || head.ras_magic!=RAS_MAGIC || head.ras_type> 1 ) { fclose(f); return 4; }
		cb = fseek(f, head.ras_maplength, SEEK_CUR);
		if ( cb!=0 ) { fclose(f); return 4; }
		buffer = new BYTE [head.ras_length];
		cb = fread(buffer, 1, head.ras_length, f);
		if ( cb!=head.ras_length ) { fclose(f); delete[] buffer; return 4; }
		Allocate(head.ras_width, head.ras_height, (ushort)(head.ras_depth>>3), buffer);
		delete[] buffer;
		if ( m_Data==0 ) { fclose(f); return 5; }
	}
	else if ( strnicmp(format, "BMP", 3)==0 )	///////// 
	{
		BITMAPFILEHEADER    bmfh;
		BITMAPINFOHEADER    bmih;
		RGBQUAD             aColors[256];
//		BYTE                aBitmapBits[];	

		memset(&bmfh, 0, sizeof(bmfh));
		memset(&bmih, 0, sizeof(bmih));
		memset(aColors, 0, sizeof(aColors));

		cb = fread(&bmfh, sizeof(bmfh),1,f);
		if ( cb!=1 || bmfh.bfType!=19778 )  { fclose(f); return 1; }
		cb = fread(&bmih, sizeof(bmih),1,f);
		if ( cb!=1 )  { fclose(f); return 2; }

		cb = fseek(f, bmfh.bfOffBits, SEEK_SET);
		n = abs((bmih.biWidth*bmih.biHeight*bmih.biBitCount)>>3);
		buffer = new BYTE [n];
		cb = fread(buffer, 1, n, f);
		if ( cb!=n ) { fclose(f); delete[] buffer; return 3; }
		Allocate(abs(bmih.biWidth), abs(bmih.biHeight), bmih.biBitCount>>3, 0);
		if ( m_Data==0 ) { fclose(f); delete[] buffer; return 4; }

		const long wdth = m_Width*m_BytesPerPixel;
		if ( bmih.biHeight>0 )	for ( ulong i=1;i<=m_Height;i++ )
		{
			const long off = (m_Height-i)*wdth;
			memcpy((BYTE*)m_Data+(i-1)*wdth, buffer+off, wdth);
		}
		else for ( ulong i=0;i<m_Height;i++ )
		{
			const long off = i*wdth;
			memcpy((BYTE*)m_Data+off, buffer+off, wdth);
		}
		delete[] buffer;
	}
	else
	{
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}

int CImageProcessing::img::SaveToFile(const char *fname, const char *format, ulong skip)
{
	if ( fname==0 || format==0 ) return 1;

	FILE *f;
//	BYTE *buffer;
	size_t cb, n;
	
	f = fopen(fname, "wb");
	if ( f==0 ) return 2;
	n = m_Width*m_Height*m_BytesPerPixel;
	if ( fseek(f, skip, SEEK_SET)!=0 ) {	fclose(f); return 3; }

	if ( strnicmp(format, "RAW", 3)==0 )		//////// RAW file format loader
	{
		fwrite(m_Data, 1, n, f);
	} 
	else if ( strnicmp(format, "RAS", 3)==0 )	///////// Sun RAS file format loader
	{
		const ulong  RAS_MAGIC = 0x59a66a95; //0x956aa659
		BYTE map[3*256];
		struct rasterfile {
           ulong  ras_magic;
           ulong  ras_width;
           ulong  ras_height;
           ulong  ras_depth;
           ulong  ras_length;
           ulong  ras_type;
           ulong  ras_maptype;
           ulong  ras_maplength;
		}  head;
		for ( int i=0;i<256;i++ )
			map[i*3] = map[i*3+1] = map[i*3+2] = i;

#define _CONVERT(a) ( (0x000000FF&((a)>>24)) | (0xFF000000&((a)<<24)) | (0x0000FF00&((a)>>8)) | (0x00FF0000&((a)<<8)) )
		memset(&head, 0, sizeof(head));
		head.ras_magic = _CONVERT(RAS_MAGIC);
		head.ras_width = _CONVERT(m_Width);
		head.ras_height = _CONVERT(m_Height);
		head.ras_depth = _CONVERT(m_BytesPerPixel<<3);
		head.ras_maplength = _CONVERT(3*256);
		head.ras_length = (ulong)_CONVERT(n);

		cb = fwrite(&head, 1, sizeof(head), f);
		if ( cb!=sizeof(head) ) { fclose(f); return 2; }
		cb = fwrite(map, 3, 256, f);
		if ( cb!=256 ) { fclose(f); return 3; }
		cb = fwrite(m_Data, 1, n, f);
		if ( cb!=n ) { fclose(f); return 4; }

#undef _CONVERT
	}
	else if ( strnicmp(format, "BMP", 3)==0 )	///////// 
	{
		BITMAPFILEHEADER    bmfh;
		BITMAPINFOHEADER    bmih;
		RGBQUAD             aColors[256];

		memset(&bmfh, 0, sizeof(bmfh));
		memset(&bmih, 0, sizeof(bmih));
		memset(aColors, 0, sizeof(aColors));
		bmfh.bfSize = sizeof(bmfh)+sizeof(bmih)+sizeof(aColors)+n;
		bmih.biSize = sizeof(bmih);
		for ( int i=0;i<256;i++ )
			aColors[i].rgbBlue = aColors[i].rgbRed = aColors[i].rgbGreen = aColors[i].rgbReserved = i;

		bmfh.bfType = 19778;
		bmih.biBitCount = m_BytesPerPixel<<3;
		bmih.biClrUsed = 256;
		bmih.biPlanes = 1;
		bmih.biHeight = -(LONG)m_Height;
		bmih.biWidth = m_Width;
		bmfh.bfOffBits = sizeof(bmfh)+sizeof(bmih)+sizeof(aColors);

		cb = fwrite(&bmfh, sizeof(bmfh),1,f);
		if ( cb!=1 ) { fclose(f); return 2; }
		cb = fwrite(&bmih, sizeof(bmih),1,f);
		if ( cb!=1 ) { fclose(f); return 3; }
		cb = fwrite(&aColors, sizeof(aColors),1,f);
		if ( cb!=1 ) { fclose(f); return 3; }
		cb = fwrite(m_Data, 1, n, f);
		if ( cb!=n ) { fclose(f); return 4; }
	}
	else
	{
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}

void CImageProcessing::img::histogram(int *h) const
{
	BYTE* src;
	ulong i;
	const ulong _cb = m_Width*m_Height;

	if ( m_BytesPerPixel!=1 || h==0 ) return ;


	memset(h, 0, sizeof(h[0])*256);
	src = (BYTE*)Data();
	for ( i=0;i<_cb;i++ )
	{
		h[*src++]++;
	}
}

/////////////////////////////////////////////////////////////////////
//
//

//
real CImageProcessing::img_window::calc_average() const
{
	BYTE* src;
	ulong i,j;
	real av;

	if ( bytes!=1 ) return 0;

	for ( i=0,av=0;i<H;i++ )
	{
		src = (BYTE*)data+X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			av += *src;
			src++;
		}
	}
	return av/(real)(W*H);
}

void   CImageProcessing::img_window::calc_range(int *min, int *max) const
{
	BYTE* src;
	ulong i,j;
	int mn=(int)1e5, mx=(int)-1e5;

	if ( bytes!=1 ||min==0||max==0) return ;

	for ( i=0;i<H;i++ )
	{
		src = (BYTE*)data+X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			if ( *src>mx )
				mx = *src;
			if ( *src<mn )
				mn = *src;
			src++;
		}
	}

	*min = mn;
	*max = mx;
}

// counts pixels greater than th
ulong CImageProcessing::img_window::count_gt(char th) const
{
	BYTE* src;
	ulong i,j;
	unsigned num=0;

	if ( bytes!=1 ) return 0;

	for ( i=0;i<H;i++ )
	{
		src = (BYTE*)data+X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			if ( *src>=th )
				num++;
			src++;
		}
	}

	return num;
}

// counts pixels lower than th
ulong CImageProcessing::img_window::count_lt(char th) const
{
	BYTE* src;
	ulong i,j;
	unsigned num=0;

	if ( bytes!=1 ) return 0;

	for ( i=0;i<H;i++ )
	{
		src = (BYTE*)data+X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			if ( *src<th )
				num++;
			src++;
		}
	}

	return num;
}

real CImageProcessing::img_window::correlation(const img& im) const
{
	real sum=0;
	BYTE* src;
	BYTE* src1;
	ulong i,j,k;
	ulong cb=im.Width()*im.Height()*im.BytesPerPixel();

//	if ( bytes!=1 ) return 0;

	for ( i=0;i<H;i++ )
	{
		src = (BYTE*)data+X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			const real s = *src;
			src1 = (BYTE*)im.Data();
			for ( k=0;k<cb;k++ )
			{
				sum+= (s-128) *(*src1-128);
				src1++;
			}
			src++;
		}

		src = (BYTE*)data+2*X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			const real s = *src;
			src1 = (BYTE*)im.Data();
			for ( k=0;k<cb;k++ )
			{
				sum+= (s-128) *(*src1-128);
				src1++;
			}
			src++;
		}

		src = (BYTE*)data+3*X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			const real s = *src;
			src1 = (BYTE*)im.Data();
			for ( k=0;k<cb;k++ )
			{
				sum+= (s-128) *(*src1-128);
				src1++;
			}
			src++;
		}

		src = (BYTE*)data+4*X+(i+Y)*scanwidth;;
		for ( j=0;j<W;j++ )
		{
			const real s = *src;
			src1 = (BYTE*)im.Data();
			for ( k=0;k<cb;k++ )
			{
				sum+= (s-128) *(*src1-128);
				src1++;
			}
			src++;
		}
	}

	return sum/(255.0*255.0);
}

ulong CImageProcessing::img_window::compare(const img& im, ulong t) const
{
	BYTE* src;
	BYTE* src1;
	ulong i,j,matched=0;
	ulong cb=im.BytesPerPixel();
	ulong sw =cb*im.Width();

//	if ( bytes!=1 ) return 0;

	for ( i=0;i<H;i++ )
	{
		src = (BYTE*)data+(X<<2)+(i+Y)*scanwidth;
		src1 = (BYTE*)im.Data() + (i)*sw;
		for ( j=0;j<W;j++ )
		{
			if ( CHECKCLR(src[2],src[1],src[0], src1[2],src1[1],src1[0], t) )
				matched ++ ;
			src1+=cb;
			src+=cb;
		}
	}

	return matched;
}

void CImageProcessing::img_window::histogram(int *h) const
{
	BYTE* src;
	ulong i,j;

	if ( bytes!=1 || h==0 ) return;


	memset(h, 0, sizeof(h[0])*256);
	for ( i=0;i<H;i++ )
	{
		if ( Y+i>=0 && Y+i<m_Img->Height() )
		{
			src = (BYTE*)data+X+(i+Y)*scanwidth;
			for ( j=0;j<W;j++ )
				if  ( X+j>=0 && X+j<m_Img->Width() )
					h[*src++]++;
		}
	}

//	if ( X>=0 && Y>=0 && X+W<m_Img->Width() && Y+H<m_Img->Height() )
//	{
//		for ( i=0;i<H;i++ )
//		{
//			src = (BYTE*)data+X+(i+Y)*scanwidth;
//			for ( j=0;j<W;j++ )
//				h[*src++]++;
//		}
//	}
//	else if ( (X<0 || X+W>=m_Img->Width()) &&Y>0 &&Y+H<m_Img->Height() )
//	{
//		for ( i=0;i<H;i++ )
//		{
//			src = (BYTE*)data+(i+Y)*scanwidth+X;
//			for ( j=0;j<W;j++ )
//				if ( X+j>=0 && X+j<m_Img->Width() ) h[*src++]++;
//		}
//	} 
//	else if ( X>=0 && X+W<m_Img->Width() && (Y<0 || Y+H>=m_Img->Height()) )
//	{
//		for ( i=0;i<H;i++ )
//		{
//			if ( Y+i>0 && Y+i<m_Img->Height() )
//			{
//				src = (BYTE*)data+(i+Y)*scanwidth+X;
//				for ( j=0;j<W;j++ )
//					h[*src++]++;
//			}
//		}
//	}

}

/////////////////////////////////////////////////////////////////////
//
//

CImageProcessing::CImageProcessing()
{
	m_bR= m_bG= m_bB= m_bA = false;
}

CImageProcessing::~CImageProcessing()
{

}


void CImageProcessing::SetChannel(const CImageProcessing::img&i, char channel)
{
	switch ( channel )
	{
	case 'r':
		m_rImage = i;
		break;
	case 'g':
		m_gImage = i;
		break;
	case 'b':
		m_bImage = i;
		break;
	case 'a':
		m_aImage = i;
		break;
	case 'R':
		m_rPImage = i;
		break;
	case 'G':
		m_gPImage = i;
		break;
	case 'B':
		m_bPImage = i;
		break;
	case 'A':
		m_aPImage = i;
		break;
	}
}

void CImageProcessing::GetChannel(CImageProcessing::img* i, char channel)
{
	if ( i ) switch ( channel )
	{
	case 'r':
		*i = m_rPImage;
		break;
	case 'g':
		*i = m_gPImage;
		break;
	case 'b':
		*i = m_bPImage;
		break;
	case 'a':
		*i = m_aPImage;
		break;
	case 'R':
		*i = m_rImage;
		break;
	case 'G':
		*i = m_gImage;
		break;
	case 'B':
		*i = m_bImage;
		break;
	case 'A':
		*i = m_aImage;
		break;
	}
}

// puts processed image to primary image
void CImageProcessing::RotateImage()
{
	m_PrimaryImage.swap(m_ProcessedImage);
}

// 
void CImageProcessing::RotateChannels()
{
	m_rImage.swap(m_rPImage);
	m_gImage.swap(m_gPImage);
	m_bImage.swap(m_bPImage);
	m_aImage.swap(m_aPImage);
}

// 
void CImageProcessing::RotateChannel(char channel)
{
	switch ( channel )
	{
	case 'r': m_rImage.swap(m_rPImage); break;
	case 'g': m_gImage.swap(m_gPImage);  break;
	case 'b': m_bImage.swap(m_bPImage); break;
	case 'a': m_aImage.swap(m_aPImage); break;
	default:
		return;
	}
}

// loads raw image into primary image buffer
void CImageProcessing::LoadImage_RAW(const char* fname, ulong width, ulong height, ulong bpp, ulong header)
{
	FILE* f;
	void *dtmp;
	CImageProcessing::img tmp;

	f = fopen(fname, "rb");
	if ( f==0 ) return;

	dtmp = new char[width*height*bpp];
	if ( dtmp==0 )
	{
		fclose(f);
		return;
	}

	fseek(f, header, SEEK_SET);
	fread(dtmp, 1,width*height*bpp, f);

	m_PrimaryImage.Allocate(width, height, (ushort)bpp, dtmp);

	delete[] dtmp;
	fclose(f);
}

typedef struct ByteImage 
	{
		ulong width;
		ulong height;
		BYTE * img;
} ByteImage;

// loads rw image into primary image buffer
void CImageProcessing::LoadImage_RW(const char* fname)
{
	ByteImage tmp;
	FILE* f = fopen(fname, "rb");
	if ( f )
	{
		fread(&tmp, sizeof(tmp),1,f);
		tmp.img = new BYTE[tmp.height*tmp.width*4];
		fread(tmp.img,1, tmp.height*tmp.width*4, f);

		m_PrimaryImage.Allocate(tmp.width, tmp.height, 4, tmp.img);

		delete[] tmp.img;
		fclose(f);
	}
}


////////////////
//
//
//

// splits image into rgba channels
void CImageProcessing::SplitChannels()
{
	char *data;
	ulong i, w, h, bpp, cb;

	if ( m_PrimaryImage.BytesPerPixel()<3 )
		return ;

	w = m_PrimaryImage.Width();
	h = m_PrimaryImage.Height();
	bpp = m_PrimaryImage.BytesPerPixel();
	data = (char*)m_PrimaryImage.Data();
	cb = w*h;

	m_rImage.Allocate(w,h,1);
	m_gImage.Allocate(w,h,1);
	m_bImage.Allocate(w,h,1);
	m_aImage.Allocate(w,h,1);

	if ( m_PrimaryImage.BytesPerPixel()==4 ) for ( i=0;i<cb;i++ )
	{
		((BYTE*)m_rImage.Data())[i] = data[i*4+2];
		((BYTE*)m_gImage.Data())[i] = data[i*4+1];
		((BYTE*)m_bImage.Data())[i] = data[i*4+0];
		((BYTE*)m_aImage.Data())[i] = data[i*4+3];
	}
	else for ( i=0;i<cb;i++ )
	{
		BYTE
			r = data[i*3+2],
			g = data[i*3+1],
			b = data[i*3+0];
		((BYTE*)m_rImage.Data())[i] = r;
		((BYTE*)m_gImage.Data())[i] = g;
		((BYTE*)m_bImage.Data())[i] = b;
		((BYTE*)m_aImage.Data())[i] = (BYTE)(0.212671 * r + 0.715160 * g + 0.072169 * b);
	}
}

// merge color channels into an image
void CImageProcessing::MergeChannels()
{
	char *data;
	ulong i, w, h, bpp, cb;

	
	w = m_rPImage.Width();
	h = m_rPImage.Height();
	bpp = m_rPImage.BytesPerPixel();

	m_ProcessedImage.Allocate(w,h,4);

	data = (char*)m_ProcessedImage.Data();
	cb = w*h;

	for ( i=0;i<cb;i++ )
	{
		data[i*4+2] = ((char*)m_rPImage.Data())[i];
		data[i*4+1] = ((char*)m_gPImage.Data())[i];
		data[i*4+0] = ((char*)m_bPImage.Data())[i];
		data[i*4+3] = ((char*)m_aPImage.Data())[i];
	}
}

char** CImageProcessing::AllocRowList(const CImageProcessing::img& i)
{
	char** tmp;
	ulong j;

	tmp = new char*[i.Height()];
	if ( tmp==0 ) return 0;
	for ( j=0;j<i.Height();j++ )
	{
		tmp[j] = (char*)i.ScanLine(j);
	}
	return tmp;
}



////////////////////////////////////////////////////////////////////////////////////
//	algorithms
////////////////////////////////////////////////////////////////////////////////////

void CImageProcessing::CalculateGrayscale(char channel)
{
	BYTE* src, *dest;
	ulong width, height;
	ulong i;

	width = m_PrimaryImage.Width();
	height = m_PrimaryImage.Height();
	src = (BYTE*)m_PrimaryImage.Data();

	switch ( channel )
	{
	case 'r':
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	case 'R':
		src = (BYTE*)m_rImage.Data();
		m_rImage.Allocate(width,height,1);
		dest = (BYTE*)m_rImage.Data();
		break;

	case 'G':
		m_gImage.Allocate(width,height,1);
		dest = (BYTE*)m_gImage.Data();
		break;

	case 'B':
		m_bImage.Allocate(width,height,1);
		dest = (BYTE*)m_bImage.Data();
		break;

	case 'A':
		m_aImage.Allocate(width,height,1);
		dest = (BYTE*)m_aImage.Data();
		break;

	default:
		return;
	}

	const ulong cb1 = width*height;
	for ( i=0;i<cb1;i++ )
	{
		const BYTE
			r = src[0],
			g = src[1],
			b = src[2];
		dest[i] = (BYTE) (0.212671 * r + 0.715160 * g + 0.072169 * b);
		src += m_PrimaryImage.BytesPerPixel();
	}
}

void CImageProcessing::filter_Sobel(char channel)
{
	int rows;
	int cols;
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		rows = m_rImage.Height();
		cols = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		rows = m_gImage.Height();
		cols = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		rows = m_bImage.Height();
		cols = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		rows = m_aImage.Height();
		cols = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

	int X, Y, I, J;
	int sumX, sumY, SUM;

   int			GX[3][3];
   int			GY[3][3];

   /* 3x3 GX Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
   GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
   GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
   GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

   /* 3x3 GY Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
   GY[0][0] =  1; GY[0][1] =  2; GY[0][2] =  1;
   GY[1][0] =  0; GY[1][1] =  0; GY[1][2] =  0;
   GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;

   /*---------------------------------------------------
		SOBEL ALGORITHM STARTS HERE
   ---------------------------------------------------*/
   for(Y=0; Y<=(rows-1); Y++)  {
	for(X=0; X<=(cols-1); X++)  {
	     sumX = 0;
	     sumY = 0;

             /* image boundaries */
	     if(Y==0 || Y==rows-1)
		  SUM = 0;
	     else if(X==0 || X==cols-1)
		  SUM = 0;

	     /* Convolution starts here */
	     else   {

	       /*-------X GRADIENT APPROXIMATION------*/
	       for(I=-1; I<=1; I++)  {
		   for(J=-1; J<=1; J++)  {
		      sumX = sumX + (int)( (*(src + X + I + (Y + J)*cols)) * GX[I+1][J+1]);
		   }
	       }
	       if(sumX>255)  sumX=255;
	       if(sumX<0)    sumX=0;

	       /*-------Y GRADIENT APPROXIMATION-------*/
	       for(I=-1; I<=1; I++)  {
		   for(J=-1; J<=1; J++)  {
		       sumY = sumY + (int)( (*(src + X + I + (Y + J)*cols)) * GY[I+1][J+1]);
		   }
	       }
	       if(sumY>255)   sumY=255;
	       if(sumY<0)     sumY=0;

	       SUM = abs(sumX) + abs(sumY); /*---GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)----*/
             }

	     *(dest + X + Y*cols) = 255-(BYTE)(SUM);  /* make edges black and background white */
//	     fwrite( (dest + X + Y*cols), sizeof(char), 1, bmpOutput);
	}
   }
}

void CImageProcessing::Resize(real ratio, char channel)
{
	ulong w0,w1;
	ulong h0,h1;
	const BYTE* src;
	BYTE* dest;

	switch ( channel )
	{
	case 'r':
		h0 = m_rImage.Height();
		w0 = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
	w1= (ulong)floor(ratio*w0);
	h1 = (ulong)floor(ratio*h0);
		m_rPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		h0 = m_gImage.Height();
		w0 = m_gImage.Width();
	w1= (ulong)floor(ratio*w0);
	h1 = (ulong)floor(ratio*h0);
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		h0 = m_bImage.Height();
		w0 = m_bImage.Width();
	w1= (ulong)floor(ratio*w0);
	h1 = (ulong)floor(ratio*h0);
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		h0 = m_aImage.Height();
		w0 = m_aImage.Width();
	w1= (ulong)floor(ratio*w0);
	h1 = (ulong)floor(ratio*h0);
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

	real x, y; // coordinates in the output bitmap
	real dx, dy; // coordinate derivatives in the output bitmap
	int x1,y1;
	BYTE *counts;
	ushort *dtmp;

	counts = new BYTE[w1*h1];
	dtmp = new ushort [w1*h1];
	memset(counts, 0, w1*h1*sizeof(counts[0]));
	memset(dtmp, 0, w1*h1*sizeof(dtmp[0]));

	dx = w1/(real)w0;
	dy = h1/(real)h0;
	y=y1=0;


	while ( y1<(signed int)h0 )
	{
		const int offs0 = (y1*w0);
		const int offs1 = (((int)floor(y))*w1);
		x=x1=0;
		while ( x1<(signed)w0 )
		{
			const int xoffs0 = x1;
			const int xoffs1 = ((int)floor(x));
			dtmp[offs1+xoffs1+0] += src[offs0+xoffs0+0];
			counts[(offs1+xoffs1)] ++;
			x+=dx;
			x1++;
		}
		y+=dy;
		y1++;
	}

	for ( unsigned long i=0;i<w1*h1;i++ )
	{
		const int tmp = dest[i] = (int)floor(dtmp[i] / (real)counts[i]);

	}


	delete[] dtmp;
	delete[] counts;
}

void CImageProcessing::Resize(ulong w1, ulong h1, char channel)
{
	ulong w0;
	ulong h0;
	const BYTE* src;
	BYTE* dest;

	switch ( channel )
	{
	case 'r':
		h0 = m_rImage.Height();
		w0 = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		h0 = m_gImage.Height();
		w0 = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		h0 = m_bImage.Height();
		w0 = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		h0 = m_aImage.Height();
		w0 = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(w1,h1,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}


	real x, y; // coordinates in the output bitmap
	real dx, dy; // coordinate derivatives in the output bitmap
	int x1,y1;
	BYTE *counts;
	ushort *dtmp;

	counts = new BYTE[w1*h1];
	dtmp = new ushort [w1*h1];
	memset(counts, 0, w1*h1*sizeof(counts[0]));
	memset(dtmp, 0, w1*h1*sizeof(dtmp[0]));

	dx = w1/(real)w0;
	dy = h1/(real)h0;
	y=y1=0;


	while ( y1<(signed int)h0 )
	{
		const int offs0 = (y1*w0);
		const int offs1 = (((int)floor(y))*w1);
		x=x1=0;
		while ( x1<(signed int)w0 )
		{
			const int xoffs0 = x1;
			const int xoffs1 = ((int)floor(x));
			dtmp[offs1+xoffs1+0] += src[offs0+xoffs0+0];
			counts[(offs1+xoffs1)] ++;
			x+=dx;
			x1++;
		}
		y+=dy;
		y1++;
	}

	for ( unsigned long i=0;i<w1*h1;i++ )
	{
		const int tmp = dest[i] = (int)floor(dtmp[i] / (real)counts[i]);

	}


	delete[] dtmp;
	delete[] counts;
}


void CImageProcessing::DetectEdges(char channel)
{
	int rows;
	int cols;
	BYTE *dest;
	BYTE *tmp;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		rows = m_rImage.Height();
		cols = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		rows = m_gImage.Height();
		cols = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		rows = m_bImage.Height();
		cols = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		rows = m_aImage.Height();
		cols = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(cols,rows,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

	int I, J;
	int sumX, sumY, SUM;
    int			MASK[5][5];
    int			GX[3][3];
    int			GY[3][3];

   int		r, c;
   int			leftPixel, rightPixel;
   int			P1, P2, P3, P4, P5, P6, P7, P8;
   BYTE 	*pChar, someChar;
   real		ORIENT;
   int			edgeDirection;
   int			highThreshold, lowThreshold;

   someChar = '0'; pChar = &someChar;
	tmp = new BYTE[rows*cols];

   /* 5x5 Gaussian mask.  Ref: http://www.cee.hw.ac.uk/hipr/html/gsmooth.html */
   MASK[0][0] = 2; MASK[0][1] =  4; MASK[0][2] =  5; MASK[0][3] =  4; MASK[0][4] = 2;
   MASK[1][0] = 4; MASK[1][1] =  9; MASK[1][2] = 12; MASK[1][3] =  9; MASK[1][4] = 4;
   MASK[2][0] = 5; MASK[2][1] = 12; MASK[2][2] = 15; MASK[2][3] = 12; MASK[2][4] = 5;
   MASK[3][0] = 4; MASK[3][1] =  9; MASK[3][2] = 12; MASK[3][3] =  9; MASK[3][4] = 4;
   MASK[4][0] = 2; MASK[4][1] =  4; MASK[4][2] =  5; MASK[4][3] =  4; MASK[4][4] = 2;

   /* 3x3 GX Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
   GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
   GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
   GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

   /* 3x3 GY Sobel mask.  Ref: www.cee.hw.ac.uk/hipr/html/sobel.html */
   GY[0][0] =  1; GY[0][1] =  2; GY[0][2] =  1;
   GY[1][0] =  0; GY[1][1] =  0; GY[1][2] =  0;
   GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;


   /**********************************************
   *	GAUSSIAN MASK ALGORITHM STARTS HERE
   ***********************************************/
   for(r=0; r<=(signed int)(rows-1); r++)  {
	for(c=0; c<=(signed int)(cols-1); c++)  {
	     SUM = 0;

	     /* image boundaries */
             if(r==0 || r==1 || r==rows-2 || r==rows-1)
		  SUM = *pChar;
	     else if(c==0 || c==1 || c==cols-2 || c==cols-1)
		  SUM = *pChar;

	     /* Convolution starts here */
	     else   {

	       for(I=-2; I<=2; I++)  {
		   for(J=-2; J<=2; J++)  {
		      SUM = SUM + (int)( (*(src + c + I + (r + J)*cols)) * (MASK[I+2][J+2])/115.0);
		   }
	       }
	     }

	     if(SUM>255)  SUM=255;
	     if(SUM<0)    SUM=0;
	     *(tmp + c + r*cols) = (BYTE)(SUM);
	}
   }


   /***********************************************
   *	SOBEL GRADIENT APPROXIMATION
   ***********************************************/
   for(r=0; r<=(signed int)(rows-1); r++)  {
	for(c=0; c<=(signed int)(cols-1); c++)  {
	     sumX = 0;
	     sumY = 0;

		 const int rcols = r*cols;
             /* image boundaries */
	     if(r==0 || r==rows-1 ||r==rows-2 )
		  SUM = 0;
	     else if(c==0 || c==cols-1 ||c==cols-2)
		  SUM = 0;


	     /* Convolution starts here */
	     else   {

	       /***********************************
	       * X gradient approximation
	       ***********************************/
	       for(I=-1; I<=1; I++)  {
		   for(J=-1; J<=1; J++)  {
		      sumX = sumX + (int)( (*(tmp + c + I + (r + J)*cols)) * GX[I+1][J+1]);
		   }
	       }

	       /**************************
	       * Y gradient approximation
	       **************************/
	       for(I=-1; I<=1; I++)  {
		   for(J=-1; J<=1; J++)  {
		       sumY = sumY + (int)( (*(tmp + c + I + (r + J)*cols)) * GY[I+1][J+1]);
		   }
	       }

	       /***********************************************
	       * GRADIENT MAGNITUDE APPROXIMATION (Myler p.218)
	       ***********************************************/
	       SUM = abs(sumX) + abs(sumY);

	       if(SUM>255)    SUM=255;
	       if(SUM<0)      SUM=0;

	       /***************************
	       * Magnitude orientation
	       ***************************/
	       /* Cannot divide by zero*/
	       if(sumX == 0)   {
		   if(sumY==0) ORIENT = 0.0;
		   else if (sumY<0)   {
		       sumY = -sumY;
		       ORIENT = 90.0;
		   }
		   else ORIENT = 90.0;
	       }
	       /* Can't take invtan of angle in 2nd Quad */
	       else if(sumX<0 && sumY>0)   {
		   sumX = -sumX;
		   ORIENT = 180 - ((atan((real)(sumY)/(real)(sumX))) * (180/M_PI));
	       }

	       /* Can't take invtan of angle in 4th Quad */
	       else if(sumX>0 && sumY<0)   {
		   sumY = -sumY;
		   ORIENT = 180 - ((atan((real)(sumY)/(real)(sumX))) * (180/M_PI));
	       }

	       /* else angle is in 1st or 3rd Quad */
	       else ORIENT = (atan((real)(sumY)/(real)(sumX))) * (180/M_PI);

	       /***************************************************
	       * Find edgeDirection by assigning ORIENT a value of
	       * either 0, 45, 90 or 135 degrees, depending on which
	       * value ORIENT is closest to
	       ****************************************************/
	       if(ORIENT < 22.5) edgeDirection = 0;
	       else if(ORIENT < 67.5) edgeDirection = 45;
	       else if(ORIENT < 112.5) edgeDirection = 90;
	       else if(ORIENT < 157.5) edgeDirection = 135;
	       else edgeDirection = 0;

	       /***************************************************
	       * Obtain values of 2 adjacent pixels in edge
	       * direction.
	       ****************************************************/
	       if(edgeDirection == 0)   {
		   leftPixel = (int)(*(tmp + rcols + c - 1));
		   rightPixel = (int)(*(tmp + rcols + c + 1));
	       }

	       else if(edgeDirection == 45)   {
		   leftPixel = (int)(*(tmp + rcols + c + cols - 1));
		   rightPixel = (int)(*(tmp + rcols + c - cols + 1));
	       }

	       else if(edgeDirection == 90)   {
		   leftPixel = (int)(*(tmp + rcols + c - cols));
		   rightPixel = (int)(*(tmp + rcols + c + cols));
	       }

	       else   {
		   leftPixel = (int)(*(tmp + rcols + c - cols - 1));
		   rightPixel = (int)(*(tmp + rcols + c + cols + 1));
	       }


	       /*********************************************
	       * Compare current magnitude to both adjacent
	       * pixel values.  And if it is less than either
	       * of the 2 adjacent values - suppress it and make
	       * a nonedge.
	       *********************************************/

	       if(SUM < leftPixel || SUM < rightPixel) SUM = 0;

	       else   {

		 /**********************
		 * Hysteresis
		 **********************/
		 highThreshold = 120;
		 lowThreshold = 40;

		 if(SUM >= highThreshold)
		     SUM = 255; /* edge */
		 else if(SUM < lowThreshold)
		     SUM = 0;  /* nonedge */

		 /* SUM is between T1 & T2 */
		 else   {

		     /* Determine values of neighboring pixels */
		     P1 = (int)(*(tmp + rcols + c - cols - 1));
             P2 = (int)(*(tmp + rcols + c - cols));
             P3 = (int)(*(tmp + rcols + c - cols + 1));
             P4 = (int)(*(tmp + rcols + c - 1));
             P5 = (int)(*(tmp + rcols + c + 1));
             P6 = (int)(*(tmp + rcols + c + cols - 1));
             P7 = (int)(*(tmp + rcols + c + cols));
             P8 = (int)(*(tmp + rcols + c + cols + 1));

		     /* Check to see if neighboring pixel values are edges */
		     if(P1 > highThreshold || P2 > highThreshold || P3 > highThreshold || P4 > highThreshold || P5 > highThreshold || P6 > highThreshold || P7 > highThreshold || P8 > highThreshold)
				 SUM = 255; /* make edge */
		     else 
				SUM = 0; /* make nonedge */
		 }

	       }



	     } /* else loop ends here (starts after b.c.) */

	     *(dest + c + r*cols) = 255-(BYTE)(SUM);
	}
   }

   delete[] tmp;
}

/*


  radial symmetry



*/

//////// 
//
void CImageProcessing::Skeletonize(ulong maxIterations, char channel)
{
	int width; 
	int height; 
	BYTE *dest;
	BYTE* src;
	char**	image;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		image = AllocRowList(m_rPImage);
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		image = AllocRowList(m_gPImage);
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		image = AllocRowList(m_bPImage);
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		image = AllocRowList(m_aPImage);
		break;

	default:
		return;
	}

} 


// return radial symmetry map
void CImageProcessing::RadialSimmetryMap(CImageProcessing::img *map, int min_radius, int max_radius, char channel)
{
	ulong width; 
	ulong height; 
	BYTE *src;
	CImageProcessing::img 
		igx,igy;

	if ( map==0 ) return;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		break;

	default:
		return;
	}

}

//
void CImageProcessing::CalcMinMax(int*min, int*max, char channel)
{
	ulong width; 
	ulong height; 
	BYTE* src;

	if ( min==0 || max==0 ) return ;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		break;

	default:
		return;
	}

	int _min=(signed int)1e5, _max=-(signed int)1e5;
	const ulong cb = height*width;
	ulong i;

	for ( i=0;i<cb;i++ )
	{
		const BYTE a = *src;
		if ( a>_max ) _max=a;
		if ( a<_min ) _min=a;
		src++;
	}

	*min = _min;
	*max = _max;
}

// maximize image
void CImageProcessing::MaximizeImage()
{

}

// maximize channel
void CImageProcessing::MaximizeChannel(int min, int max, char channel)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

//	int min=1e5, max=-1e5;
	const ulong cb = height*width;
	ulong i;
//	BYTE *p;

//	for ( i=0,p=src;i<cb;i++ )
//	{
//		const BYTE a = *p;
//		if ( a>max ) max=a;
//		if ( a<min ) min=a;
//		p++;
//	}
	const real scale = 255/(real)(max-min);

//#define Double2Fixed8x8(a) (unsigned short)((a)*255)
//#define Fixed8x8Mul(a,b)	(((unsigned short)((a)*(b)))>>8)

	for ( i=0;i<cb;i++ )
	{
		const BYTE a = *src;
		BYTE b = (BYTE)((a-min)*scale);
		if ( b<0 ) b=0;
		if ( b>255 ) b=255;
		*dest = b;
		src++;
		dest++;
	}
}

// blurs image
void CImageProcessing::Blur(ulong radius, char channel)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

}

//
void CImageProcessing::GradientX(char channel)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

}

void CImageProcessing::GradientY(char channel)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

}

void CImageProcessing::GradientXY(char channel)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}


}


// retreaves a Histogram for r/g/b/a or c-rgb, C-rgba
//void CImageProcessing::Histogram(CImageProcessing::histogram* h, char channel)
//{}


void CImageProcessing::Threshold(BYTE min, BYTE max, char channel, bool leave)
{
	ulong width; 
	ulong height; 
	BYTE *dest;
	BYTE* src;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}


}


void CImageProcessing::AutoTreshold(int c, char channel)
{
	ulong width; 
	ulong height; 
	BYTE* src;
	BYTE* dest;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		break;

	default:
		return;
	}

}

void sub_hist(int*a, int*b)
{
	ulong i;
	for (i=0;i<256;i++,a++,b++)
		*a = (*a)-(*b);
}
void add_hist(int*a, int*b)
{
	ulong i;
	for (i=0;i<256;i++,a++,b++)
		*a = (*a)+(*b);
}
void CImageProcessing::AdaptiveOtsuTreshold(int radius, char channel)
{
	ulong width; 
	ulong height; 
	BYTE* src;
	BYTE* dest;
	CImageProcessing::img_window	wnd;

	switch ( channel )
	{
	case 'r':
		height = m_rImage.Height();
		width = m_rImage.Width();
		src = (BYTE*)m_rImage.Data();
		m_rPImage.Allocate(width,height,1);
		dest = (BYTE*)m_rPImage.Data();
		wnd.set(&m_rImage);
		break;

	case 'g':
		height = m_gImage.Height();
		width = m_gImage.Width();
		src = (BYTE*)m_gImage.Data();
		m_gPImage.Allocate(width,height,1);
		dest = (BYTE*)m_gPImage.Data();
		wnd.set(&m_gImage);
		break;

	case 'b':
		height = m_bImage.Height();
		width = m_bImage.Width();
		src = (BYTE*)m_bImage.Data();
		m_bPImage.Allocate(width,height,1);
		dest = (BYTE*)m_bPImage.Data();
		wnd.set(&m_bImage);
		break;

	case 'a':
		height = m_aImage.Height();
		width = m_aImage.Width();
		src = (BYTE*)m_aImage.Data();
		m_aPImage.Allocate(width,height,1);
		dest = (BYTE*)m_aPImage.Data();
		wnd.set(&m_aImage);
		break;

	default:
		return;
	}

}


////////////////////
//
// custom algorithms
//
unsigned long CImageProcessing::Compare(const CImageProcessing::img& a, const CImageProcessing::img& b, ulong t)
{
	unsigned long matched = 0;
	unsigned long i,n,bw ;
	BYTE* ba, *bb;

	ba = (BYTE*)a.Data();
	bb = (BYTE*)b.Data();

	if ( a.Width()!=b.Width() || a.Height()!=b.Height() || a.BytesPerPixel()!=b.BytesPerPixel() )
		return 0;

	for ( i=0, n=a.Width()*a.Height(),bw=a.BytesPerPixel();i<n;i++ ) 
	{
//		if ( CHECKCLR(ba[2],ba[1],ba[0], bb[2],bb[1],bb[0], t) )
		if ( (ulong)abs(ba[2]-bb[2])<t )
			matched ++ ;
		ba+= bw;
		bb+= bw;
	}

	return matched;
}
unsigned long CImageProcessing::CompareBytes(const CImageProcessing::img& a, const CImageProcessing::img& b, ulong t)
{
	unsigned long matched = 0;
	unsigned long i,n ;
	BYTE* ba, *bb;

	ba = (BYTE*)a.Data();
	bb = (BYTE*)b.Data();

	if ( a.Width()!=b.Width() || a.Height()!=b.Height() || a.BytesPerPixel()!=b.BytesPerPixel() )
		return 0;

	for ( i=0, n=a.Width()*a.Height()*a.BytesPerPixel();i<n;i++ ) 
	{
		const int _a = *ba;
		const int _b = *bb;
		if ( ba>bb-t && ba<bb+t )
			matched ++ ;
		ba++;
		bb++;
	}

	return matched;
}


void CImageProcessing::AccumulateImage(ulong width, ulong height, void* img, BYTE bytes, float coef)
{
	const ulong fcb = sizeof(float);
	const ulong cb = bytes*width*height;
	ulong i;
	float* dest;
	BYTE* src;

	if ( img==0 ) return;
	if ( m_PrimaryImage.Width()!=width || m_PrimaryImage.Height()!=height || m_PrimaryImage.BytesPerPixel()!=fcb*bytes )
	{
		return;
	}

	src= (BYTE*) img;
	dest = (float*)m_PrimaryImage.Data();

	if ( m_AccumulateMethod==CImageProcessing::FADING )
	{
		for ( i=0;i<cb;i++ )
		{
			const float a = *src;
			const float b = *dest;
			const float ab = a + (b-a)*coef; 
			*dest = ab;
			src++;
			dest++;
		}
	}
	else if ( m_AccumulateMethod==CImageProcessing::AVERAGE )
	{
		for ( i=0;i<cb;i++ )
		{
			const float a = *src;
			const float b = *dest;
			const float ab = a + b; 
			*dest = ab;
			src++;
			dest++;
		}
	}

	m_AccumulateCount++;
}

void CImageProcessing::AccumulateProcessImage()
{
	const ulong cb = m_PrimaryImage.Width()*m_PrimaryImage.Height()*m_PrimaryImage.BytesPerPixel()/sizeof(float);
	ulong i;
	float* src;
	BYTE* dest;

	if ( m_AccumulateCount==0 ) return;

	const real cc= 1/(real)m_AccumulateCount;

	m_ProcessedImage.Allocate(m_PrimaryImage.Width(), m_PrimaryImage.Height(), m_PrimaryImage.BytesPerPixel()/sizeof(float));

	src = (float*)m_PrimaryImage.Data();
	dest = (BYTE*)m_ProcessedImage.Data();

	if ( m_AccumulateMethod==CImageProcessing::FADING )
	{
		for ( i=0;i<cb;i++ )
		{
			const float a = *src;
			*dest = (BYTE)floor(a);
			src++;
			dest++;
		}
	}
	else if ( m_AccumulateMethod==CImageProcessing::AVERAGE )
	{
		for ( i=0;i<cb;i++ )
		{
			const float a = *src;
			*dest = (BYTE)floor(a*cc);
			src++;
			dest++;
		}
	}
}

void CImageProcessing::AccumulateStart(ulong width, ulong height, BYTE bytes, CImageProcessing::Accumulate_METHOD method)
{
	const ulong fcb = sizeof(float);
	const ulong cb = bytes*width*height;
	m_AccumulateCount = 0;
	m_PrimaryImage.Allocate(width, height, fcb*bytes);
	m_PrimaryImage.fill(0);
	m_AccumulateMethod = method;
}


class RGBA
{
public:
	BYTE b,g,r,a;

public:
	RGBA() {}
	RGBA(const RGBA& rgba) {*this=rgba;}
	RGBA(const real rgba) {*this=rgba;}
	~RGBA() {}

	RGBA& operator=(const RGBA& rgba)
	{
		r=rgba.r;
		g=rgba.g;
		b=rgba.b;
		a=rgba.a;
		return *this;
	}
	RGBA& operator=(const real rgba)
	{
		r=(BYTE)rgba;
		g=(BYTE)rgba;
		b=(BYTE)rgba;
		a=(BYTE)rgba;
		return *this;
	}
	RGBA operator*(const real x) const
	{
		RGBA tmp;
		tmp.r = (BYTE)(r*x);
		tmp.g = (BYTE)(g*x);
		tmp.b = (BYTE)(b*x);
		tmp.a = (BYTE)(a*x);
		return tmp;
	}
	RGBA operator+(const RGBA rgba) const
	{
		RGBA tmp;
		tmp.r = r+rgba.r;
		tmp.g = g+rgba.g;
		tmp.b = b+rgba.b;
		tmp.a = a+rgba.a;
		return tmp;
	}
	RGBA operator-(const RGBA rgba) const
	{
		RGBA tmp;
		tmp.r = r-rgba.r;
		tmp.g = g-rgba.g;
		tmp.b = b-rgba.b;
		tmp.a = a-rgba.a;
		return tmp;
	}
};
class dRGBA
{
public:
	real b,g,r,a;

public:
	dRGBA() {}
	dRGBA(const dRGBA& rgba) {*this=rgba;}
	dRGBA(const RGBA& rgba) {*this=rgba;}
	dRGBA(const real rgba) {*this=rgba;}
	~dRGBA() {}

	dRGBA& operator=(const dRGBA& rgba)
	{
		r=rgba.r;
		g=rgba.g;
		b=rgba.b;
		a=rgba.a;
		return *this;
	}
	 operator RGBA() const
	{
		RGBA tmp;
		tmp.r = (BYTE)r;
		tmp.g = (BYTE)g;
		tmp.b = (BYTE)b;
		tmp.a = (BYTE)a;
		return tmp;
	}
	dRGBA& operator=(const RGBA& rgba)
	{
		r=rgba.r;
		g=rgba.g;
		b=rgba.b;
		a=rgba.a;
		return *this;
	}
	dRGBA& operator=(const real rgba)
	{
		r=rgba;
		g=rgba;
		b=rgba;
		a=rgba;
		return *this;
	}
	dRGBA operator*(const real x) const
	{
		dRGBA tmp;
		tmp.r = r*x;
		tmp.g = g*x;
		tmp.b = b*x;
		tmp.a = a*x;
		return tmp;
	}
	dRGBA operator+(const dRGBA rgba) const
	{
		dRGBA tmp;
		tmp.r = r+rgba.r;
		tmp.g = g+rgba.g;
		tmp.b = b+rgba.b;
		tmp.a = a+rgba.a;
		return tmp;
	}
	dRGBA operator-(const dRGBA rgba) const
	{
		dRGBA tmp;
		tmp.r = r-rgba.r;
		tmp.g = g-rgba.g;
		tmp.b = b-rgba.b;
		tmp.a = a-rgba.a;
		return tmp;
	}
};


}