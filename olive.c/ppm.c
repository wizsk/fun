#include <err.h>
#include <stdio.h>
#include <sys/types.h>

#define WIDTH 400
#define HEIGHT 600

u_int32_t pixels[HEIGHT * WIDTH];

void fill(u_int32_t *pixels, int height, int width, u_int32_t color) {
  for (int i = 0; i < height * width; ++i) {
    pixels[i] = color;
  }
}

void fill_rect(u_int32_t *pixels, u_int32_t pixels_height,
               u_int32_t pixels_width, int x0, int y0, u_int32_t w, u_int32_t h,
               u_int32_t color) {

  for (int dy = 0; dy < h; dy++) {
    int y = y0 + dy;
    if (0 <= y && y < (int)pixels_height) {
      for (int dx = 0; dx < h; dx++) {
        int x = x0 + dx;
        if (0 <= x && x < (int)pixels_width) {
          pixels[y * pixels_width + x] = color;
        }
      }
    }
  }
}

int save_to_file(const u_int32_t *pixels, int height, int width,
                 const char *file_name) {
  FILE *f = fopen(file_name, "w");
  if (f == NULL) {
    return -1;
  }

  fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

  for (int i = 0; i < height * width; ++i) {
    u_int32_t color = pixels[i]; // red

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
  fill(pixels, HEIGHT, WIDTH, 0xFF100101);
  fill_rect(pixels, HEIGHT, WIDTH, 100, 10, 50, 70, 0xFFAABAFF);
  fill_rect(pixels, HEIGHT, WIDTH, 200, 20, 50, 70, 0xFFb0a0FF);

  if (save_to_file(pixels, HEIGHT, WIDTH, ouput) < 0) {
    printf("err: while saveing file\n");
  }
  //
}
