/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbariol- <nassimbariol@student.42.fr>>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:00:00 by nbariol-          #+#    #+#             */
/*   Updated: 2024/11/08 14:00:00 by nbariol-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	init_img(t_cub *data, t_img *img, int width, int height)
{
	img->data = mlx_new_image(data->mlx, width, height);
	if (!img->data)
		return ;
	img->addr = mlx_get_data_addr(img->data, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	set_image_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel_addr;

	if (!img || !img->addr)
		return ;
	pixel_addr = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel_addr = color;
}

void	free_tab(void **tab)
{
	int	index;

	if (!tab)
		return ;
	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

void	err_msg(char *detail, char *str, int code)
{
	(void)detail;
	(void)code;
	if (str)
		printf("%s\n", str);
}

void	debug_display_minimap(t_minimap *minimap)
{
	int	row;

	if (!minimap || !minimap->map)
		return ;
	printf("\n=== MINIMAP DEBUG ===\n");
	row = 0;
	while (row < minimap->size && minimap->map[row])
	{
		printf("%s\n", minimap->map[row]);
		row++;
	}
	printf("====================\n\n");
}
