#include "olive.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

#define BACLGROUD_COLOR 0xFF202020
#define FOREGROUD_COLOR 0xFF0000FF

u_int32_t pixels[HEIGHT * WIDTH];

// for the cheker board
#define COLS (8 * 2)
#define ROWS (6 * 2)
#define CELL_WIDTH (WIDTH / COLS)
#define CELL_HEIGHT (HEIGHT / ROWS)
void checkerboard_rec() {
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      u_int32_t color;
      if ((x + y) % 2 == 0) {
        color = FOREGROUD_COLOR;
      } else {
        color = BACLGROUD_COLOR;
      }

      fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT,
                CELL_WIDTH, CELL_HEIGHT, color);
    }
  }
  const char *ouput = "chekerboard_rec.ppm";
  if (save_to_file(pixels, WIDTH, HEIGHT, ouput) < 0) {
    printf("err: while saveing file %s\n", ouput);
  }
}

// soto -> boro
float lerpf(float a, float b, float t) { return a + (b - a) * t; }

void checkerboard_cir() {
  fill(pixels, WIDTH, HEIGHT, BACLGROUD_COLOR);
  for (int y = 0; y < ROWS; ++y) {
    for (int x = 0; x < COLS; ++x) {
      float u = (float)x / COLS;
      float v = (float)y / ROWS;
      float t = (u + v) / 2;

      int r = CELL_WIDTH;
      if (CELL_HEIGHT < r)
        r = CELL_HEIGHT;

      fill_cir(pixels, WIDTH, HEIGHT, x * CELL_WIDTH + CELL_WIDTH / 2,
               y * CELL_HEIGHT + CELL_HEIGHT / 2,
               (int)lerpf((float)r / 8, (float)r / 2, t), FOREGROUD_COLOR);
    }
  }
  const char *ouput = "chekerboard_cir.ppm";
  if (save_to_file(pixels, WIDTH, HEIGHT, ouput) < 0) {
    printf("err: while saveing file %s\n", ouput);
  }
}

int main() {
  checkerboard_rec();
  checkerboard_cir();
}
