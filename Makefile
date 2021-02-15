# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 12:20:20 by knabouss          #+#    #+#              #
#    Updated: 2021/02/15 15:13:03 by knabouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror 

SRCS =	./srcs/raycasting/movement.c \
		./srcs/raycasting/func_bis.c \
		./srcs/raycasting/calculate_ray.c	\
		./srcs/raycasting/ft_init.c	\
		./srcs/raycasting/texture.c	\
		./srcs/raycasting/sprite.c	\
		./srcs/raycasting/cub3d.c	\
		./srcs/raycasting/keys.c	\
		./srcs/raycasting/bmp.c		\
		./srcs/libft_cub/ft_atoi.c	\
		./srcs/libft_cub/ft_strdup.c	\
		./srcs/libft_cub/ft_isdigit.c	\
		./srcs/libft_cub/ft_split.c	\
		./srcs/libft_cub/ft_strjoin.c	\
		./srcs/libft_cub/ft_memset.c	\
		./srcs/libft_cub/ft_strlen.c	\
		./srcs/libft_cub/ft_strncmp.c	\
		./srcs/libft_cub/ft_strtrim.c	\
		./srcs/libft_cub/ft_substr.c	\
		./srcs/parsing/check_path.c	\
		./srcs/libft_cub/ft_putchar_fd.c\
		./srcs/libft_cub/ft_putstr_fd.c	\
		./srcs/libft_cub/ft_strchr.c	\
		./srcs/parsing/check_ceil.c	\
		./srcs/parsing/check_flour.c \
		./srcs/parsing/check_map.c	\
		./srcs/parsing/check_resol.c	\
		./srcs/parsing/get_next_line_utils.c	\
		./srcs/parsing/get_next_line.c	\
		./srcs/parsing/parsing.c	\
		./srcs/parsing/valid_map.c	\
		./srcs/parsing/free.c		\
		./srcs/parsing/normi.c

OBJ =  $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	 	@gcc $(CFLAGS) $(OBJ)  -lmlx -framework OpenGL -framework AppKit  -o $(NAME)
		@echo '\033[1;32m' "________________________________"
		@echo  '\033[1;32m' "COMPILATION DONE, ENJOY THE GAME!"
		@echo '\033[1;32m' "________________________________"   

clean:
	@rm -f $(OBJ)

fclean:	clean 
	@rm -f $(NAME)

re: fclean all

.PHONY : clean, re, fclean, all