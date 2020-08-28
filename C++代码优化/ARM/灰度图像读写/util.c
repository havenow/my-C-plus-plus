#include "png.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

void readImageData(const char *filename, png_bytep *data,
                   size_t *w, size_t *h) {
  FILE *png_input  = fopen(filename, "rb");
  assert(png_input != NULL);

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                               NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, png_input);
  png_read_info(png_ptr, info_ptr);
  *w = png_get_image_width(png_ptr, info_ptr);
  *h = png_get_image_height(png_ptr, info_ptr);

  *data = malloc(*h * png_get_rowbytes(png_ptr, info_ptr) + sizeof(png_bytep) * 16);
  for(unsigned int ii=0; ii<*h; ii++) {
    png_read_row(png_ptr,
                 *data + ii * png_get_rowbytes(png_ptr, info_ptr),
                 NULL);
  }

  png_read_end(png_ptr, info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  fclose(png_input);
}


void writeImageData(const char* filename, png_bytep data,
                    size_t w, size_t h, size_t bitdepth ) {
  FILE *png_output = fopen(filename, "wb");
  assert(png_output != NULL);

  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                                NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, png_output);
  png_set_IHDR(png_ptr, info_ptr, w, h, bitdepth,
               PNG_COLOR_TYPE_GRAY,
               //PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
  png_write_info(png_ptr, info_ptr);
  /* png_set_swap(png_ptr); //correct byte order*/
  for(unsigned int ii=0; ii<h; ii+=1) {
    png_write_row(png_ptr, data + ii*png_get_rowbytes(png_ptr, info_ptr));
  }

  png_write_end(png_ptr, NULL);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_output);
}
