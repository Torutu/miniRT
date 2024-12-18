/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/18 18:44:29 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <stdlib.h>
#include <stdio.h>

// Function to render a gradient with a progress indicator


int32_t main(void) {
    // Initialize MLX42
    mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "hmmm yes raytracing", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX42\n");
        return EXIT_FAILURE;
    }

    // Create an image
    mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img) {
        fprintf(stderr, "Failed to create image\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }
    // Render the raytraced image
    render_raytraced_image(img);

    // Display the image in the window
    if (mlx_image_to_window(mlx, img, 0, 0) < 0) {
        fprintf(stderr, "Failed to put image to window\n");
        mlx_delete_image(mlx, img);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Main loop
    mlx_loop(mlx);

    // Clean up
    mlx_terminate(mlx);
    return EXIT_SUCCESS;
}

// int32_t main(void) {
//     // Initialize MLX42
//     mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Raytraced Scene with Lights", true);
//     if (!mlx) {
//         fprintf(stderr, "Failed to initialize MLX42\n");
//         return EXIT_FAILURE;
//     }

//     // Create an image
//     mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
//     if (!img) {
//         fprintf(stderr, "Failed to create image\n");
//         mlx_terminate(mlx);
//         return EXIT_FAILURE;
//     }

//     // Define ambient light (strength: 0.1, color: white)
//     t_ambient_light ambient = {0.1, vec3(1.0, 1.0, 1.0)};

//     // Define point light (position: (0, 5, 0), strength: 1.0)
//     t_point_light point_light = {vec3(0, 5, 0), 1.0};

//     // Render the image with lighting
//     render_raytraced_image(img, ambient, point_light);

//     // Display the image
//     if (mlx_image_to_window(mlx, img, 0, 0) < 0) {
//         fprintf(stderr, "Failed to put image to window\n");
//         mlx_delete_image(mlx, img);
//         mlx_terminate(mlx);
//         return EXIT_FAILURE;
//     }

//     // Main loop
//     mlx_loop(mlx);

//     // Clean up
//     mlx_terminate(mlx);
//     return EXIT_SUCCESS;
// }
