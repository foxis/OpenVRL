/*
 * $Source: /cvsroot-fuse/openvrl/ovrl/include/tools/imageprocessing.h,v $
 * $Implementation: $
 * $Revision: 1.1 $
 * $Author: foxis $
 * $Date: 2005/03/04 13:21:16 $
 * $Description:  $
 *
 * $Log: imageprocessing.h,v $
 * Revision 1.1  2005/03/04 13:21:16  foxis
 * no message
 *
 *
 */

#if !defined(__ovrl_IMAGEPROCESSING_H)
#define __ovrl_IMAGEPROCESSING_H

#include "common/all.h"


namespace openvrl {

class CImageProcessing  
{
public:
	class img
	{
		ulong 
			m_Width,
			m_Height,
			m_ScanWidth;
		ulong m_DataSize;

		ushort m_BytesPerPixel;
		ushort m_Planes;
		void* m_Data;

		bool m_Allocated;

	public:
		img(const img& i) { m_Allocated =false; m_DataSize = 0;m_Data=0; m_Width=m_Height=0; *this=i; }
		img() { m_Allocated =false; m_DataSize = 0; m_Data=0; m_Width=m_Height=0; }
		virtual ~img() { if (m_Allocated) delete[] m_Data; m_Data=0; }

		virtual img& operator=(const img& i)
		{
			Allocate(i.m_Width, i.m_Height, i.m_BytesPerPixel, i.m_Data);
			return *this;
		}

		// allocates neccessary space for image data
		int Allocate(ulong w, ulong h, ushort bpp, const void *data=0)
		{
			ulong datasize;
			m_Width = w;
			m_Height = h;
			m_BytesPerPixel = bpp;
			m_ScanWidth = w*bpp;

			datasize = m_ScanWidth*m_Height;
			if ( datasize==0 ) return 1;
			if ( m_Allocated )
			{
				if ( m_DataSize <datasize )
				{
					if ( m_Data )	delete[] m_Data;
					m_DataSize = datasize;
					m_Data = new BYTE[datasize];
				}
			}
			else
			{
				m_DataSize = datasize;
				m_Data = new BYTE[m_DataSize];
			}

			m_Allocated = true;

			if ( data )
				OVRL_memcpy(m_Data, data, datasize);

			return 0;
		}

		// swaps image data
		void swap(img& i)
		{
			const ulong w = m_Width;
			const ulong h = m_Height;
			const ushort bpp = m_BytesPerPixel;
			const ulong sw = m_ScanWidth;
			const ulong DataSize = m_DataSize;
			const bool Allocated = m_Allocated;
			const ushort Planes = m_Planes;
			void* Data = m_Data;

			m_Width = i.m_Width;
			m_Height = i.m_Height;
			m_BytesPerPixel = i.m_BytesPerPixel;
			m_ScanWidth = i.m_ScanWidth;
			m_DataSize = i.m_DataSize;
			m_Data = i.m_Data;
			m_Planes = i.m_Planes;
			m_Allocated = i.m_Allocated;

			i.m_Width = w;
			i.m_Height = h;
			i.m_BytesPerPixel = bpp;
			i.m_ScanWidth = sw;
			i.m_DataSize = DataSize;
			i.m_Data = Data;
			i.m_Planes = Planes;
			i.m_Allocated = Allocated;
		}

		ulong Width() const { return m_Width; }
		ulong Height() const { return m_Height; }
		ulong ScanWidth() const { return m_ScanWidth; }
		ushort BytesPerPixel() const { return m_BytesPerPixel; }
		ushort Planes() const { return m_Planes; }
		void* Data() { return m_Data; }
		void const * Data() const { return m_Data; }
		void* ScanLine(ulong y) { return ((char*)m_Data)+y*m_ScanWidth; }
		void const * ScanLine(ulong y) const { return ((char*)m_Data)+y*m_ScanWidth; }

		ulong& Width() { return m_Width; }
		ulong& Height() { return m_Height; }
		ulong& ScanWidth() { return m_ScanWidth; }
		ushort& BytesPerPixel() { return m_BytesPerPixel; }
		ushort& Planes() { return m_Planes; }

		//
		void SetPixel(ulong x, ulong y, const void*p);
		void GetPixel(ulong x, ulong y, void *p)const;

		///
		void CopyBytes(void *src, ulong sz)
		{
			if ( sz<=m_DataSize ) 
				OVRL_memcpy(m_Data, src, sz);
		}

		// @todo: never hanged
		// copy rectangular portion of image into new image
		void CopyPortion(img* d, ulong x, ulong y, ulong w, ulong h) const;

		// @todo: not tested
		// copy non rectangular portion of image into new rectangular image
		// @todo: bilinear interpolation
		//  !!!!!!!!!!!!!!! no boundary checkings
		void CopyPortionPrimitive(img* d, real x1, real y1, real x2, real y2,
									real x3, real y3, real x4, real y4, real width, real height) const;

		//
		real calc_average() const;
		void   calc_range(int *min, int *max) const;

		//
		real MatchTemplate(const img& i, real th=16) const ;

		// counts pixels greater than th
		ulong count_gt(char th) const;
		// counts pixels lower than th
		ulong count_lt(char th) const;

		void histogram(int *h) const;

		// fills cb bytes of the image with b
		void fill(unsigned char b, ulong cb=0);

		// saves image into a custom format file 
		//   skip - how many bytes to skip from the beginning of the file
		//   width,height,bps - dimention of a RAW image to load
		int LoadFromFile(const char *fname, const char *format, ulong skip=0, ulong width=0, ulong height=0, unsigned char bps=0);

		// loads a custom format file into image
		//   skip - how many bytes to skip from the beginning of the file
		//   width,height,bps - dimention of a RAW image to load
		int SaveToFile(const char *fname, const char *format, ulong skip=0);
	};

	typedef ulong COLOR;

	class img_window
	{
		img* m_Img;
		ulong 
			W, H;
		int 
			X, Y;
		char	
			*data,
			*line;
		ulong 
			bytes,
			width,
			scanwidth;

	public:
		img_window() : m_Img(0) { }
		img_window(img* i) : m_Img(i) {  }
		~img_window() {}

		void set(img* i) { m_Img = i; }
		void position(int x, int y, ulong w, ulong h)
		{
			X = x;
			Y = y;
			W = w; 
			H = h;
			data= (char*)m_Img->Data();
			bytes = m_Img->BytesPerPixel();
			width = m_Img->Width();
			scanwidth = width*bytes;
		}

		void *getAt(ulong x, ulong y) { return data+(x+X+(y+Y)*width)*bytes; }
		void setScanLine(ulong y) { line= data+(y+Y)*scanwidth; }
		void *getScanLineAt(ulong x) { return line + (x+X)*bytes; }

		int getX() const { return X; }
		int getY() const { return Y; }
		ulong getW() const { return W; }
		ulong getH() const { return H; }
		int& getX() { return X; }
		int& getY() { return Y; }
		ulong& getW() { return W; }
		ulong& getH() { return H; }

		//
		real calc_average() const;
		void   calc_range(int *min, int *max) const;

		// counts pixels greater than th
		ulong count_gt(char th) const;
		// counts pixels lower than th
		ulong count_lt(char th) const;

		//
		real correlation(const img& im) const;
		//
		ulong compare(const img& im, ulong t) const;

		void histogram(int *h) const;
	};


	enum Accumulate_METHOD	
	{
		FADING,
		AVERAGE
	};


	Accumulate_METHOD	m_AccumulateMethod;
	ulong	m_AccumulateCount;
	img		m_igx,m_igy;
	img		m_PrimaryImage;
	img		m_ProcessedImage;
	img		m_rImage;
	img		m_gImage;
	img		m_bImage;
	img		m_aImage;
	img		m_rPImage;
	img		m_gPImage;
	img		m_bPImage;
	img		m_aPImage;

	img		m_Temp0;
	img		m_Temp1;
	img		m_Temp2;
	img		m_Temp3;

	bool m_bR, m_bG, m_bB, m_bA;

public:
	CImageProcessing();
	virtual ~CImageProcessing();

	// copys image into primary image buffer
	void SetPrimaryImage(const img& i) { m_PrimaryImage = i; }
	void GetPrimaryImage(img* i) { if(i)*i=m_PrimaryImage; }
	void GetProcessedImage(img* i) { if(i)*i=m_ProcessedImage; }
	void SetChannel(const img&i, char channel);
	void GetChannel(img* i, char channel);

	// puts processed image to primary image
	void RotateImage();
	// puts processed image to primary image
	void RotateChannels();
	void RotateChannel(char channel);

	// loads raw image into primary image buffer
	void LoadImage_RAW(const char* fname, ulong width, ulong height, ulong bpp, ulong header=0);
	// loads rw image into primary image buffer
	void LoadImage_RW(const char* fname);


	////////////////
	//
	//
	//

	// splits image into rgba channels
	void SplitChannels();

	// merge color channels into an image
	void MergeChannels();


	///////////////
	//
	//	general algorithms
	//

	void CalculateGrayscale(char channel);

	// 
	void filter_Sobel(char channel);
	
	// resizes channel
	void Resize(ulong w1, ulong h1, char channel);
	void Resize(real ratio, char channel);

	// detects edges
	void DetectEdges(char channel);

	// skeletonizes 
	void Skeletonize(ulong maxIterations, char channel);

	// return radial symmetry map
	void RadialSimmetryMap(img *map, int min_radius, int max_radius, char channel);

	// retreaves a Histogram for r/g/b/a or c-rgb, C-rgba
//	void Histogram(histogram* h, char channel);

	// threshold 
	void Threshold(unsigned char min, unsigned char max, char channel, bool leave=false);

	void AutoTreshold(int c, char channel);

	void AdaptiveOtsuTreshold(int radius, char channel);

	//
	void CalcMinMax(int*min, int*max, char channel);
	// maximize image
	void MaximizeImage();
	// maximize image
	void MaximizeChannel(int min, int max, char channel);

	// blurs image
	void Blur(ulong radius, char channel);

	//
	void GradientX(char channel);
	void GradientY(char channel);
	void GradientXY(char channel);



	////////////////////
	//
	// custom algorithms
	//

	// compares two images pixel by pixel and returns the number of pixels that match
	// t is matching threshold
	unsigned long Compare(const img& a, const img& b, ulong t);
	unsigned long CompareBytes(const img& a, const img& b, ulong t);

	// image coupling
	void AccumulateImage(ulong width, ulong height, void* img, unsigned char bytes, float coef);
	void AccumulateProcessImage();
	void AccumulateStart(ulong width, ulong height, unsigned char bytes, Accumulate_METHOD method);
	ulong GetAccumulateCount() const { return m_AccumulateCount; }

private:
	char** AllocRowList(const img& i);
	void FreeRowList(char** rl)
	{
		delete[] rl;
	}
};

};

#endif 
