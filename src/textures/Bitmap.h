/*
** This class represents an image and allows operations on it.
*/

#pragma once

#include <string>

namespace tdogl
{
	class Bitmap
	{
	public:
		/*
		** Represents the number of channels per pixel, and the order of the channels.
		** Each channel is one byte (unsigned char).
		*/
		enum Format
		{
			Format_Grayscale = 1,
			Format_GrayscaleAlpha = 2,
			Format_RGB = 3,
			Format_RGBA = 4
		};

		/*
		** Creates a new image with the specified width, height and format.
		** Width qnd height are in pixels. Image will contain random garbage if pixels = NULL.
		*/
		Bitmap(unsigned width,
				unsigned height,
				Format format,
				const unsigned char *pixels = NULL);
		virtual ~Bitmap();

		/*
		** Tries to load the fiven file into a tdogl::Bitmap.
		*/
		static Bitmap		bitmapFromFile(std::string filePath);

		/*
		** @result	The width in pixel.
		*/
		unsigned			width() const;
		
		/*
		** @result	The height in pixel.
		*/
		unsigned			height() const;
		
		/*
		** @result	The format or the bitmap.
		*/
		Format 				format() const;
		
		/*
		** @result	Pointer to the raw pixel data of the bitmap.
		**
		** Each channel is 1 byte. The number and meaning of channles per pixel is specified
		** by the `Format` of the image. The pointer points to all the columns of the top row
		** of the image, followed by each remaining row down to the bottom.
		*/
		unsigned char		*pixelBuffer() const;

		/*
		** @return	A pointer to the start of the pixel at the given coordinates.
		**
		** The size of the pixel depends on the `Format` of the image.
		*/
		unsigned char		*getPixel(unsigned int col, unsigned int row) const;
		
		/*
		** Set the raw pixel data at the given coordinates.
		**
		** The size of the pixel depends on the `Format` of the image.
		*/
		void				setPixel(unsigned int col, unsigned int row, const unsigned char *pixel);

		/*
		** Reverses the row order of the pixels, so the bitmap will be upside down.
		*/
		void				flipVertically();

		/*
		** Rotate the image 90 degrees counter clockwise.
		*/
		void				rotate90CounterClockwise();

		/*
		** Copies a rectangular area from the given source bitmap into this bitmap.
		**
		** If srcCol, srcRow, width and height are all zero, the entire source 
		** bitmap will be copied (full width and height)
		**
		** If the source birmap has a different format to the destination bitmap,
		** the pixels will be converted to match the destination format.
		**
		** Will throw an exception if th esource and destination bitmaps are the same,
		** and the source and and destination overlap. If you want to copy a bitmap
		** onto itself, then make a copy of the bitmap first.
		*/
		void				copyRectFromBitmap(const Bitmap& src,
												unsigned srcCol,
												unsigned srcRow,
												unsigned destCol,
												unsigned destRow,
												unsigned width,
												unsigned height);

		Bitmap(const Bitmap& bitmap);
		Bitmap&				operator=(const Bitmap& src);

	private:
		Format 			_format;
		unsigned		_width;
		unsigned		_height;
		unsigned char	*_pixels;

		void		_set(unsigned width, unsigned height, Format format, const unsigned char *pixels);
		static void	_getPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Format format);
	};
}