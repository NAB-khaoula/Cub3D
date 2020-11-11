# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 12:20:20 by knabouss          #+#    #+#              #
#    Updated: 2020/11/11 13:47:14 by knabouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS =	./srcs/raycasting/movement.c \
		./srcs/raycasting/calculate_ray.c	\
		./srcs/raycasting/ft_init.c	\
		./srcs/raycasting/texture.c	\
		./srcs/raycasting/sprite.c	\
		./srcs/raycasting/cub3d.c\
		./srcs/libft_cub/ft_atoi.c	\
		./srcs/libft_cub/ft_isdigit.c	\
		./srcs/libft_cub/ft_split.c	\
		./srcs/libft_cub/ft_strjoin.c	\
		./srcs/libft_cub/ft_strlen.c	\
		./srcs/libft_cub/ft_strncmp.c	\
		./srcs/libft_cub/ft_strtrim.c	\
		./srcs/libft_cub/ft_substr.c	\
		./srcs/libft_cub/ft_putchar_fd.c\
		./srcs/libft_cub/ft_putstr_fd.c	\
		./srcs/libft_cub/ft_strchr.c	\
		./srcs/parsing/check_ceil.c	\
		./srcs/parsing/check_flour.c \
		./srcs/parsing/check_map.c	\
		./srcs/parsing/check_path.c	\
		./srcs/parsing/check_resol.c	\
		./srcs/parsing/get_next_line_utils.c	\
		./srcs/parsing/get_next_line.c	\
		./srcs/parsing/parsing.c	\
		./srcs/parsing/valid_map.c	

OBJ =  $(SRCS:.c=.o)

# CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
		@gcc  $(OBJ)  -lmlx -framework OpenGL -framework AppKit  -o $(NAME)
	 	#  gcc $(CFLAGS) $(OBJ)  -lmlx -framework OpenGL -framework AppKit  -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean:	clean 
	@rm -f $(NAME)

re: fclean all

.PHONY : clean, re, fclean, all