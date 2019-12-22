# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yait-el- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 02:58:50 by yait-el-          #+#    #+#              #
#    Updated: 2019/12/22 08:45:28 by yait-el-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = mlx/libmlx.a 
INC = inc/fractol.h  
SRC = src/main.c src/zoom.c src/mouse.c src/keys.c  src/mainv2.c src/ft_itoa.c
FLAGCL = -lmlx -framework OpenGL -framework AppKit -framework OpenCL -lz
OBJ = $(SRC:.c=.o)

all: $(NAME) 
$(NAME):$(INC) $(OBJ)  
		@echo "\033[95m**********make libft and minilibx_macos [OK]"
	    @Make -C ./mlx
		@echo "\033[92m**********done!\033[0m [OK]"
		@ $(CC) $(CFLAGS) $(OBJ) $(LIB) $(FLAGCL) -o $(NAME)
clean:
		@echo "\033[94mcleaning..."
		@Make clean -C ./mlx
		@rm -rf $(OBJ) 
		@echo "\033[91m**********object files removed!\033[0m [OK]"
		@echo "\033[91mdone!\033[0m"
fclean: clean 
		@rm -f $(NAME)
		@echo "\033[93m**********fdf executable removed!\033[0m [OK]"
		#@Make fclean -C ./mlx
		@echo "\033[92m**********executable removed!\033[0m [OK]"
		
re: fclean all
norme:
		@echo "\033[96m**********norminette..."
		norminette $(SRC)
		norminette $(INC)
