#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbratsla <tbratsla@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 14:53:03 by tbratsla          #+#    #+#              #
#    Updated: 2019/10/01 14:53:04 by tbratsla         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS = -Werror -Wall -O3 -Wextra -Ofast -flto -pipe -fsanitize=address -g

NAME = wolf3d

SRC = main.c read_map.c free.c game.c init.c events.c draw.c \

INC = inc/wolf3d.h

SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./inc/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FT = ./Libft/

FT_LIB	= $(addprefix $(FT),libft.a)

LINKS = -L$(FT) -l ft

SDL_PATH = ./framework

INCLUDES = 		-I$(FT) -I$(INC_DIR) \
				-I./frameworks/SDL2.framework/Headers \
				-I./frameworks/SDL2_image.framework/Headers \
				-I./frameworks/SDL2_ttf.framework/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks

FRAMEWORKS = 	-F./frameworks \
				-rpath ./frameworks \
				-framework AppKit -framework OpenGL \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_ttf \

all: obj_dir $(FT_LIB) $(NAME)
	echo 'Compilated!'
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FRAMEWORKS) $(OBJ) $(LINKS) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

obj_dir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all