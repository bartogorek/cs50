# Questions

## What's `stdint.h`?

stdint.h header defines integer types, limits of specified width integer types, limits of other integer types
and macros for integer constant expressions.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

In the bitmap file example we know exactly how our file is built and how many bits/bytes we require for each part of a file, for example :
BITMAPFILEHEADER - 14 bytes long
each RGBTRIPLE - 3 bytes long
Knowing the above, we can allocate memory in a very exact and efficient way, much better than using standard integer data type 'just in case'.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

'BYTE' is 1 byte
'DWORD' is 4 bytes
'LONG' is 4 bytes
'WORD' is 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 and 0x4d representing respectively 'B' and 'M' which allow the file to be recognised as bitmap.

## What's the difference between `bfSize` and `biSize`?

'bfSize' - size of the file including image and header
'biSize' - size of the header info

## What does it mean if `biHeight` is negative?

If 'biHeight' is negative, the bit-map is top-down DIB with the origin at the upper left corner

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

'biBitCount' specifies the number of bits per pixel (bpp)

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

If the file pointer is trying to access file that doesn't exist is has got limited access
(for example trying to access file in 'write' mode while the user hasr read-only access)

## Why is the third argument to `fread` always `1` in our code?

The second argument is requesting one 'triple' to be accessed, that is one pixel (three values: one byte for red,
one byte for green, one byte for blue)

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

The value assigned to padding is 0.

## What does `fseek` do?

'fseek' offsets position in the file by the value of 'padding' (in our example).

## What is `SEEK_CUR`?

SEEK_CUR moves file pointer to given location.
