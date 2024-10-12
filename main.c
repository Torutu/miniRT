#include "includes/main.h"

int main(void)
{
    mlx_set_setting(MLX_MAXIMIZED, true);
    // Initialize MLX and create a window
    mlx_t *mlx = mlx_init(800, 600, "miniRT", true);
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return (1);
    }

    // Create an image buffer to draw onto
    mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        fprintf(stderr, "Failed to create an image\n");
        mlx_terminate(mlx);
        return (1);
    }

    // Attach the image to the window
    mlx_image_to_window(mlx, img, 0, 0);

    // Render a sample scene (you can adjust this part)
    t_sphere sphere = {{0, 0, -5}, 1.0, 0x0000FF}; // Example sphere setup
    t_vector camera = {0, 0, 0};
    t_scene scene = {&sphere, 1};

    render_scene(&scene, camera, WIDTH, HEIGHT, img);

    // Enter the MLX loop to keep the window open
    mlx_loop(mlx);

    // Clean up when finished
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    return (0);
}
