#ifndef OLIVE_C
#define OLIVE_C

#include <stdio.h>
#include <sys/types.h>

int save_to_file(u_int32_t *pixels, size_t pixels_width, size_t pixels_height,
                 const char *file_name) {
  FILE *f = fopen(file_name, "w");
  if (f == NULL) {
    return -1;
  }

  fprintf(f, "P6\n%zu %zu\n255\n", pixels_width, pixels_height);

  for (int i = 0; i < (int)(pixels_width * pixels_height); ++i) {
    u_int32_t color = pixels[i];

    u_int8_t bytes[3] = {
        (u_int8_t)((color >> (8 * 0)) & 0xFF),
        (u_int8_t)((color >> (8 * 1)) & 0xFF),
        (u_int8_t)((color >> (8 * 2)) & 0xFF),
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

void fill(u_int32_t *pixels, size_t pixels_width, size_t pixels_height,
          u_int32_t color) {
  for (int i = 0; i < (int)(pixels_width * pixels_height); ++i) {
    pixels[i] = color;
  }
}

void fill_rect(u_int32_t *pixels, size_t pixels_width, size_t pixels_height,
               int x0, int y0, u_int32_t w, u_int32_t h, u_int32_t color) {
  for (int dy = 0; dy < (int)h; dy++) {
    int y = y0 + dy;
    if (0 <= y && y < (int)pixels_height) {
      for (int dx = 0; dx < (int)w; dx++) {
        int x = x0 + dx;
        if (0 <= x && x < (int)pixels_width) {
          pixels[y * pixels_width + x] = color;
        }
      }
    }
  }
}

void fill_cir(u_int32_t *pixels, size_t pixels_width, size_t pixels_height,
              int cx, int cy, int r, u_int32_t color) {
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

void swap_int(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void draw_line(u_int32_t *pixels, size_t pixels_width, size_t pixels_height,
               int x1, int y1, int x2, int y2, u_int32_t color) {
  // y1 = K*x1 + c
  // y2 = K*x2 + c
  //
  // c = y1 - K*x1
  //
  // y2 = K*x2 + y1 - K*x1
  // y2 - y1 = K(x2 - x1)
  // K = (y2 - y1)/(x2-x1)
  //
  int dx = x1 - x2;
  int dy = y1 - y2;
  if (dx != 0) {
    int c = y1 - (dy * x1) / dx; // - k

    if (x1 > x2) {
      swap_int(&x1, &x2);
    }

    for (int x = x1; x <= x2; x++) {
      if (0 <= x && x < (int)pixels_width) {
        int sy1 = (dy * x) / dx + c;       // current y
        int sy2 = (dy * (x + 1)) / dx + c; // next y
        if (sy1 > sy2)
          swap_int(&sy1, &sy2);
        for (int y = sy1; y <= sy2; ++y) {
          if (0 <= y && y < (int)pixels_height) {
            pixels[y * pixels_width + x] = color;
          }
        }
      }
    }

  } else {
    // perpentigular to --------x--------
    int x = x1;
    if (0 <= x && x < (int)pixels_width) {
      if (y1 > y2)
        swap_int(&y1, &y2);
      for (int y = y1; y <= y2; y++) {
        if (0 <= y && y < (int)pixels_height) {
          pixels[y * pixels_width + x] = color;
        }
      }
    }
  }
}

#endif // OLIVE_INPLIMENTATRION
