NAME = fractol

CC = gcc

SRC = main.c fractol_window.c fractol_mandelbrot.c fractol_actions.c fractol_utils.c

MLX_FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz #-lXrender

MLX_LIB = libmlx_Linux.a

all : $(NAME)

$(NAME) :	$(SRC)
			$(CC) $(SRC) -o $(NAME) $(MLX_LIB) $(MLX_FLAGS)

clean :

fclean :	clean
			rm $(NAME)
