# Questions

## What's `stdint.h`?

stdint.h is a header file in the C standard library to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To be more clear to use the data.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE is 1 byte; DWORD is 4 bytes; LONG is 4 bytes; WORD is 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the bitmap file.
biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

It means the origin of bitmap is the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file doesn't exist so it can't be open or the file can't be created.

## Why is the third argument to `fread` always `1` in our code?

The program reads 1 RGB triple at the time.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

According to the formula, the value is 3.

## What does `fseek` do?

Allows us rewind or fast-forward within a file.

## What is `SEEK_CUR`?

Look for current position in file.
