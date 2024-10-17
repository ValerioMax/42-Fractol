NAME = fractol

CC = gcc

SRC = *.c

all : $(NAME)

$(NAME) :	$(SRC)
			$(CC) $(SRC) -o $(NAME) libmlx.a -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

clean :

fclean :	clean
			rm $(NAME)
