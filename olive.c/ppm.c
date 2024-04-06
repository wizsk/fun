#include <err.h>
#include <stdio.h>
#include <sys/types.h>

#define WIDTH 400
#define HEIGHT 600

u_int32_t pixels[HEIGHT * WIDTH];

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

int main() {
  const char *ouput = "out.ppm";
  fill(pixels, WIDTH, HEIGHT, 0xFF100101);
  fill(pixels, WIDTH, HEIGHT, 0xFFFFFFFF);

  int rw = 50;
  int rh = 30;
  fill_rect(pixels, WIDTH, HEIGHT, WIDTH / 2 - (rw / 2), HEIGHT / 2 - (rh / 2),
            rw, rh, 0xFFb0a0FF);

  fill_rect(pixels, WIDTH, HEIGHT, WIDTH / 2, 0, 1, HEIGHT, 0xFF000000);
  fill_rect(pixels, WIDTH, HEIGHT, 0, HEIGHT / 2, WIDTH, 1, 0xFF000000);

  if (save_to_file(pixels, WIDTH, HEIGHT, ouput) < 0) {
    printf("err: while saveing file\n");
  }
  //
}
