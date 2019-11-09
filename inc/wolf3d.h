/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 14:45:35 by tbratsla          #+#    #+#             */
/*   Updated: 2019/10/01 14:45:37 by tbratsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../Libft/libft.h"
# include <math.h>

# define WIDTH		1024
# define HEIGHT		712
# define GREEN		0x00ad20
# define BLUE		0x0058db
# define RED		0xdb0000
# define YELLOW		0xffe600
# define PURPURE	0x960069
# define DARK_RED	0x800000
# define ORANGE		0xffc800
# define ARGENT		0xf5f8ff
# define TEXTW		64
# define TEXTH		64
# define TEXTNUM	34

typedef struct		s_mou
{
	int				x;
	int				y;
}					t_mou;

typedef struct		s_texture
{
	SDL_Surface		**wall_text;
	SDL_Surface		**floor_text;
	int				text_num;
	double			wall_x;
	int				text_x;
	int				text_y;
	int				magic_d;
}					t_text;

typedef struct		s_floor
{
	double			floorX_wall;
	double			floorY_wall;
	double			distWall;
	double			distPlayer;
	double			currentDist;
	int				floorTexX;
	int				floorTexY;
	double			weight;
	double			curFloorX;
	double			curFloorY;
}					t_floor;

typedef struct		s_ev
{
	int				up;
	int				down;
	int				r_rot;
	int				l_rot;
	int				r_move;
	int				l_move;
}					t_ev;

typedef struct		s_wolf
{
	int				**map;
	int				count_str;
	int				count_num;
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		event;
	SDL_Texture		*tex;
	SDL_Renderer	*rend;
	TTF_Font		*font;
	t_text			*texture;
	t_floor			floor;
	double			posX;
	double			posY;  //x and y start position
	double			dirX;
	double			dirY; //initial direction vector
	double			planeX;
	double			planeY; //the 2d raycaster version of camera plane
	double			time; //time of current frame
	double			oldTime; //time of previous frame
	int				mapX;
	int				mapY;
	double			cameraX; //x-coordinate in camera space
	double			rayDirX;
    double			rayDirY;
    double			sideDistX;
    double			sideDistY;
    double			deltaDistX;
    double			deltaDistY;
    double			perpWallDist;
    int				stepX;
    int				stepY;
    int				hit; //was there a wall hit?
    int				side;
    int				lineHeight;
    int				drawStart;
    int				drawEnd;
    Uint32			color;
    double			move_speed;
    double			rot_speed;
    t_ev			*events;
    t_mou			mouse;
    int				text_flag;
    double			angle_x;
}					t_wolf;

/*
** read functions
*/

t_wolf				*ft_read_map(char **av);
void				ft_start_read(t_wolf *wolf, int fd);
void				get_int_map(t_wolf *wolf, char **double_map);
void				ft_check_count_num(t_wolf *wolf, char **map);
void				ft_count_num(t_wolf *wolf, char **map);
void				ft_count_str(t_wolf *wolf, char **double_map);
void				ft_check_map_format(t_wolf *wolf, char **map);

/*
** Raycasting functions
*/

void				game(t_wolf *wolf);
void				init_raycast(t_wolf *wolf, int x);
void				init_sidedist(t_wolf *wolf);
void				init_var(t_wolf *wolf);
void				search_wall(t_wolf *wolf);

/*
** texture functions
*/

void				load_textures(t_wolf *wolf);
void				load_textures2(t_wolf *wolf);
SDL_Surface			*load_texture(char *path);

/*
** event functions
*/

void				event(t_wolf *wolf);
void				rotation(t_wolf *wolf, int side, double angle);
void				movement(t_wolf *wolf, double side);
void				side_step(t_wolf *wolf, int side);

/*
** draw functions
*/

void				set_color(t_wolf *wolf);
void				ft_set_pixel(t_wolf *wolf, int x, int y);
void				draw_vert_line(t_wolf *wolf, int x);
void				ft_clear_screen(t_wolf *wolf);
Uint32				get_pix_from_text(SDL_Surface *text, int x, int y);
void				calc_y(t_wolf *wolf, int x);


/*
** free function
*/

void				free_map(t_wolf *wolf, char **map);

#endif