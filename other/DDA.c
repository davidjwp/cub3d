#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    void    *mlx;
    void    *mlx_win;
}               t_data;

// Function to put pixel on the image
void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// DDA Algorithm for line drawing
void draw_line_dda(t_data *data, int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = fmax(abs(dx), abs(dy));

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(data, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

int main() {
    t_data  img;
    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "DDA Line Drawing");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Draw line using DDA
    draw_line_dda(&img, 100, 100, 700, 500, 0x00FF0000); // Red line

    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
    mlx_loop(img.mlx);
    return (0);
}
