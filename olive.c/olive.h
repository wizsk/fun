#ifndef OLIVE_H
#define OLIVE_H

#include <stdio.h>
#include <sys/types.h>

void fill(u_int32_t *pixels, int width, int height, u_int32_t color) {
  for (int i = 0; i < width * height; ++i) {
    pixels[i] = color;
  }
}

void fill_rect(u_int32_t *pixels, u_int32_t pixels_width,
               u_int32_t pixels_height, int x0, int y0, u_int32_t w,
               u_int32_t h, u_int32_t color) {
  for (int dy = 0; dy < h; dy++) {
    int y = y0 + dy;
    if (0 <= y && y < (int)pixels_height) {
      for (int dx = 0; dx < w; dx++) {
        int x = x0 + dx;
        if (0 <= x && x < (int)pixels_width) {
          pixels[y * pixels_width + x] = color;
        }
      }
    }
  }
}

void fill_cir(u_int32_t *pixels, u_int32_t pixels_width,
              u_int32_t pixels_height, int cx, int cy, int r, u_int32_t color) {
  int x1 = cx - r;
  int y1 = cy - r;
  int x2 = cx + r;
  int y2 = cy + r;

  for (int y = y1; y <= y2; y++) {
    if (0 <= y && y < (int)pixels_height) {
      for (int x = x1; x <= x2; x++) {
        if (0 <= x && x < (int)pixels_width) {
          int dx = x - cx;
          int dy = y - cy;
          if (dx * dx + dy * dy <= r * r) {
            pixels[y * pixels_width + x] = color;
          }
        }
      }
    }
  }
}

int save_to_file(const u_int32_t *pixels, int width, int height,
                 const char *file_name) {
  FILE *f = fopen(file_name, "w");
  if (f == NULL) {
    return -1;
  }

  fprintf(f, "P6\n%d %d\n255\n", width, height);

  for (int i = 0; i < width * height; ++i) {
    u_int32_t color = pixels[i];

    u_int8_t bytes[3] = {
        color & 0xFF,
        (color >> 8) & 0xFF,
        (color >> 16) & 0xFF,
    };

    fwrite(bytes, sizeof(bytes), 1, f);
    if (ferror(f)) {
      fclose(f);
      return -1;
    }
  }

  fclose(f);
  return 0;
}

#endif // OLIVE_INPLIMENTATRION
