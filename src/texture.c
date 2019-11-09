/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:35:30 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/31 12:35:31 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void			load_textures(t_wolf *wolf)
{
	if (!(wolf->texture->wall_text = ft_memalloc(sizeof(SDL_Surface) * TEXTNUM)) ||
		!(wolf->texture->floor_text = ft_memalloc(sizeof(SDL_Surface) * 2)))
	{
		ft_putendl("ERROR: cannot load texture (");
		exit(1);
	}
	wolf->texture->wall_text[0] = load_texture("./texture/glass_light_blue.png");
	wolf->texture->wall_text[1] = load_texture("./texture/brick.png");
	wolf->texture->wall_text[2] = load_texture("./texture/redstone_lamp_on.png");
	wolf->texture->wall_text[3] = load_texture("./texture/crafting_table_front.png");
	wolf->texture->wall_text[4] = load_texture("./texture/diamond_block.png");
	wolf->texture->wall_text[5] = load_texture("./texture/diamond_ore.png");
	wolf->texture->wall_text[6] = load_texture("./texture/glass_lime.png");
	wolf->texture->wall_text[7] = load_texture("./texture/gravel.png");
	wolf->texture->wall_text[8] = load_texture("./texture/redstone_block.png");
	wolf->texture->wall_text[9] = load_texture("./texture/hay_block_side.png");
	wolf->texture->wall_text[10] = load_texture("./texture/iron_ore.png");
	wolf->texture->wall_text[11] = load_texture("./texture/leaves_acacia_opaque.png");
	wolf->texture->wall_text[12] = load_texture("./texture/log_oak.png");
	wolf->texture->wall_text[13] = load_texture("./texture/glass_blue.png");
	wolf->texture->wall_text[14] = load_texture("./texture/piston_bottom.png");
	wolf->texture->wall_text[15] = load_texture("./texture/planks_acacia.png");
	wolf->texture->wall_text[16] = load_texture("./texture/planks_big_oak.png");
	wolf->texture->wall_text[17] = load_texture("./texture/planks_birch.png");
	wolf->texture->wall_text[18] = load_texture("./texture/planks_jungle.png");
	wolf->texture->wall_text[19] = load_texture("./texture/planks_oak.png");
	wolf->texture->wall_text[20] = load_texture("./texture/planks_spruce.png");
	wolf->texture->wall_text[21] = load_texture("./texture/pumpkin_face_on.png");
	load_textures2(wolf);
}

void			load_textures2(t_wolf *wolf)
{
	wolf->texture->wall_text[22] = load_texture("./texture/pumpkin_side.png");
	wolf->texture->wall_text[23] = load_texture("./texture/emerald_block.png");
	wolf->texture->wall_text[24] = load_texture("./texture/ice.png");
	wolf->texture->wall_text[25] = load_texture("./texture/emerald_ore.png");
	wolf->texture->wall_text[26] = load_texture("./texture/redstone_block.png");
	wolf->texture->wall_text[27] = load_texture("./texture/stonebrick_mossy.png");
	wolf->texture->wall_text[28] = load_texture("./texture/tnt_side.png");
	wolf->texture->wall_text[29] = load_texture("./texture/bookshelf.png");
	wolf->texture->wall_text[30] = load_texture("./texture/wool_colored_blue.png");
	wolf->texture->wall_text[31] = load_texture("./texture/wool_colored_lime.png");
	wolf->texture->wall_text[32] = load_texture("./texture/wool_colored_purple.png");
	wolf->texture->wall_text[33] = load_texture("./texture/wool_colored_yellow.png");
	wolf->texture->floor_text[0] = load_texture("./texture/wool_colored_blue.png");
	wolf->texture->floor_text[1] = load_texture("./texture/glowstone.png");
}

SDL_Surface		*load_texture(char *path)
{
	SDL_Surface		*tmp;

	tmp = IMG_Load(path);
	if (tmp == NULL)
	{
		SDL_FreeSurface(tmp);
		ft_putstr("ERROR: cannot load texture (");
		ft_putstr(path);
		ft_putendl(")");
		exit(1);
	}
	return (tmp);
}

