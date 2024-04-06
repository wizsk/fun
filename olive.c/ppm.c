#include "olive.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define BACLGROUD_COLOR 0xFF202020
#define FOREGROUD_COLOR 0xFF0000FF

u_int32_t pixels[HEIGHT * WIDTH];

// for the cheker board
#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH / COLS)
#define CELL_HEIGHT (HEIGHT / ROWS)
// checkerboard(0xFFAAFAFF, 0xFF0A0A0B);
void checkerboard(u_int32_t color1, u_int32_t color2) {
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      u_int32_t color;
      if ((x + y) % 2 == 0) {
        color = color1;
      } else {
        color = color2;
      }
      fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT,
                CELL_WIDTH, CELL_HEIGHT, color);
    }
  }
}

int main() {
  const char *ouput = "out.ppm";
  fill(pixels, WIDTH, HEIGHT, BACLGROUD_COLOR);
  // checkerboard(0xFFAAFAFF, BACLGROUD_COLOR);f
  file_cir(pixels, WIDTH, HEIGHT, WIDTH / 2, HEIGHT / 2, 60, FOREGROUD_COLOR);
  if (save_to_file(pixels, WIDTH, HEIGHT, ouput) < 0) {
    printf("err: while saveing file\n");
  }
}
