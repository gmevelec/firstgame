#include "textures/Bitmap.h"
#include <stdexcept>
#include <cstdlib>

// Uses stb_image to try load files
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <SOIL/SOIL.h>

#include <iostream>

using namespace tdogl;

inline unsigned char AverageRGB(unsigned char rgb[3])
{
	return ((unsigned char)(((double)rgb[0] + (double)rgb[1] + (double)rgb[2]) / 3.0));
}

static void	Grayscale2GrayscaleAlpha(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = 255;
}

static void	Grayscale2RGB(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[0];
	dest[2] = src[0];
}

static void	Grayscale2RGBA(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[0];
	dest[2] = src[0];
	dest[3] = 255;	
}

static void	GrayscaleAlpha2Grayscale(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
}

static void	GrayscaleAlpha2RGB(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[0];
	dest[2] = src[0];
}

static void	GrayscaleAlpha2RGBA(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[0];
	dest[2] = src[0];
	dest[3] = src[1];
}

static void	RGB2Grayscale(unsigned char *src, unsigned char *dest)
{
	dest[0] = AverageRGB(src);
}

static void	RGB2GrayscaleAlpha(unsigned char *src, unsigned char *dest)
{
	dest[0] = AverageRGB(src);
	dest[1] = 255;
}

static void	RGB2RGBA(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = 255;
}

static void	RGBA2Grayscale(unsigned char *src, unsigned char *dest)
{
	dest[0] = AverageRGB(src);
}

static void	RGBA2GrayscaleAlpha(unsigned char *src, unsigned char *dest)
{
	dest[0] = AverageRGB(src);
	dest[3] = src[3];
}

static void	RGBA2RGB(unsigned char *src, unsigned char *dest)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

typedef void(*FormatConverterFunc)(unsigned char *, unsigned char *);

static FormatConverterFunc ConverterFuncForFormats(Bitmap::Format srcFormat, Bitmap::Format destFormat)
{
	if (srcFormat == destFormat)
		throw std::runtime_error("Just use memcpy if pixel formats are the same");

	switch (srcFormat)
	{
		case Bitmap::Format_Grayscale:
			switch (destFormat)
			{
				case Bitmap::Format_GrayscaleAlpha:	return (Grayscale2GrayscaleAlpha);
				case Bitmap::Format_RGB:			return (Grayscale2RGB);
				case Bitmap::Format_RGBA:			return (Grayscale2RGBA);
				default:
					throw std::runtime_error("Unhandled bitmap format");
			}
			break;
		case Bitmap::Format_GrayscaleAlpha:
			switch (destFormat)
			{
				case Bitmap::Format_Grayscale:		return (GrayscaleAlpha2Grayscale);
				case Bitmap::Format_RGB:			return (GrayscaleAlpha2RGB);
				case Bitmap::Format_RGBA:			return (GrayscaleAlpha2RGBA);
				default:
					throw std::runtime_error("Unhandled bitmap format");
			}
			break;
		case Bitmap::Format_RGB:
			switch (destFormat)
			{
				case Bitmap::Format_Grayscale:		return (RGB2Grayscale);
				case Bitmap::Format_GrayscaleAlpha:	return (RGB2GrayscaleAlpha);
				case Bitmap::Format_RGBA:			return (RGB2RGBA);
				default:
					throw std::runtime_error("Unhandled bitmap format");
			}
			break;
		case Bitmap::Format_RGBA:
			switch (destFormat)
			{
				case Bitmap::Format_Grayscale:		return (RGBA2Grayscale);
				case Bitmap::Format_GrayscaleAlpha:	return (RGBA2GrayscaleAlpha);
				case Bitmap::Format_RGB:			return (RGBA2RGB);
				default:
					throw std::runtime_error("Unhandled bitmap format");
			}
			break;
	}
}

/*
** Misc functions.
*/

inline unsigned	GetPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Bitmap::Format format)
{
	(void)height;
	return ((row * width + col) * format);
}

inline bool		RectsOverlap(unsigned srcCol, unsigned srcRow, unsigned destCol, unsigned destRow, unsigned width, unsigned height)
{
	unsigned colDiff = srcCol > destCol ? srcCol - destCol : destCol - srcCol;
	if (colDiff < width)
		return (true);

	unsigned rowDiff = srcRow > destRow ? srcRow - destRow : destRow - srcRow;
	if (rowDiff < height)
		return (true);
	return (false);
}

/*
** Bitmap class
*/

Bitmap::Bitmap(unsigned width,
				unsigned height,
				Format format,
				const unsigned char *pixels) :
	_pixels(NULL)
{
	_set(width, height, format, pixels);
}

Bitmap::~Bitmap()
{
	if (_pixels)
		free(_pixels);
}

Bitmap		Bitmap::bitmapFromFile(std::string filePath)
{
	int				width;
	int				height;
	int				channels;
	unsigned char	*pixels = SOIL_load_image(filePath.c_str(), &width, &height, &channels, 0);
	if (!pixels)
		throw std::runtime_error("soil_failure_reason");
	Bitmap bmp(width, height, (Format)channels, pixels);
	SOIL_free_image_data(pixels);
	return (bmp);
}

Bitmap::Bitmap(const Bitmap& bitmap) : _pixels(NULL)
{
	_set(bitmap._width, bitmap._height, bitmap._format, bitmap._pixels);
}

Bitmap&		Bitmap::operator=(const Bitmap& src)
{
	_set(src._width, src._height, src._format, src._pixels);
	return (*this);
}

unsigned int	Bitmap::width() const
{
	return (_width);
}

unsigned int 	Bitmap::height() const
{
	return (_height);
}

Bitmap::Format 	Bitmap::format() const
{
	return (_format);
}

unsigned char	*Bitmap::pixelBuffer() const
{
	return (_pixels);
}

unsigned char	*Bitmap::getPixel(unsigned int col, unsigned int row) const
{
	if (col >= _width || row >= _height)
		throw std::runtime_error("Pixel coordinates out of bounds.");
	return (_pixels + GetPixelOffset(col, row, _width, _height, _format));
}

void			Bitmap::setPixel(unsigned int col, unsigned int row, const unsigned char *pixel)
{
	unsigned char *myPixel = getPixel(col, row);
	memcpy(myPixel, pixel, _format);
}

void			Bitmap::flipVertically()
{
	unsigned long	rowSize = _format * _width;
	unsigned char	*rowBuffer = new unsigned char[rowSize];
	unsigned		halfRows = _height / 2;

	for (unsigned rowIdx = 0; rowIdx < halfRows; ++rowIdx)
	{
		unsigned char *row = _pixels + GetPixelOffset(0, rowIdx, _width, _height, _format);
		unsigned char *oppositeRow = _pixels + GetPixelOffset(0, _height - rowIdx - 1, _width, _height, _format);

		// std::cout << "	SUCCESS GetPixelOffset" << std::endl;
		// std::cout << "		rowSize = " << rowSize << std::endl;
		// std::cout << "		_format = " << _format << std::endl;
		// std::cout << "		_width = " << _width << std::endl;
		memcpy(rowBuffer, row, rowSize);
		memcpy(row, oppositeRow, rowSize);
		memcpy(oppositeRow, rowBuffer, rowSize);
	}
	// std::cout << ">>>>>>>>> 2" << std::endl;
	delete [] rowBuffer;
}

void			Bitmap::rotate90CounterClockwise()
{
	unsigned char *newPixels = (unsigned char*) malloc(_format * _width * _height);

	for (unsigned row = 0; row < _height; ++row)
	{
		for (unsigned col = 0; col < _width; ++col)
		{
			unsigned srcOffset = GetPixelOffset(col, row, _width, _height, _format);
			unsigned destOffset = GetPixelOffset(row, _width - col - 1, _height, _width, _format);
			// Copy one pixel
			memcpy(newPixels + destOffset, _pixels + srcOffset, _format);
		}
	}
	free(_pixels);
	_pixels = newPixels;

	unsigned tmp = _height;
	_height = _width;
	_width = tmp;
}

void			Bitmap::copyRectFromBitmap(const Bitmap& src,
											unsigned srcCol,
											unsigned srcRow,
											unsigned destCol,
											unsigned destRow,
											unsigned width,
											unsigned height)
{
	if (srcCol == 0 && srcRow == 0 && width == 0 && height == 0)
	{
		width = src.width();
		height = src.height();
	}
	if (width == 0 || height == 0)
		throw std::runtime_error("Can't copy zero height/width rectangle.");
	if (srcCol + width >= src.width() || srcRow + height >= src.height())
		throw std::runtime_error("Rectangle doesn't fit within source bitmap.");
	if (destCol + width >= src.width() || destRow + height >= src.height())
		throw std::runtime_error("Rectangle doesn't fit within destination bitmap.");
	if (_pixels == src._pixels && RectsOverlap(srcCol, srcRow, destCol, destRow, width, height))
		throw std::runtime_error("Source and destination are the same bitmap, and rects overlap. Not allowed.");

	FormatConverterFunc converter = NULL;
	if (_format != src._format)
		converter = ConverterFuncForFormats(_format, src._format);
	for (unsigned row = 0; row < height; ++row)
	{
		for (unsigned col = 0; col < width; ++col)
		{
			unsigned char *srcPixel = src._pixels + GetPixelOffset(srcCol + col, srcRow + row, src._width, src._height, src._format);
			unsigned char *destPixel = src._pixels + GetPixelOffset(destCol + col, destRow + row, _width, _height, _format);
			if (converter)
				converter(srcPixel, destPixel);
			else
				memcpy(destPixel, srcPixel, _format);
		}

	}
}

void			Bitmap::_set(unsigned width,
							unsigned height,
							Format format,
							const unsigned char *pixels)
{
	if (width == 0)
		throw std::runtime_error("Zero width bitmap.");
	if (height == 0)
		throw std::runtime_error("Zero height bitmap.");
	if (format <= 0 || format > 4)
		throw std::runtime_error("Invalid bitmap format.");

    _width = width;
    _height = height;
    _format = format;

	size_t newSize = _width * _height * _format;
	if (_pixels)
		_pixels = (unsigned char*)realloc(_pixels, newSize);
	else
		_pixels = (unsigned char*)malloc(newSize);
	if (pixels)
		memcpy(_pixels, pixels, newSize);
}

