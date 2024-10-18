NAME = fractol

CC = gcc

SRC = *.c

MLX_FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all : $(NAME)

$(NAME) :	$(SRC)
			$(CC) $(SRC) -o $(NAME) libmlx_Linux.a $(MLX_FLAGS)

clean :

fclean :	clean
			rm $(NAME)
