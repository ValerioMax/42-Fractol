NAME = fractol

CC = gcc

INCLUDES = -I includes

SRCS_DIR = srcs

SRCS =	srcs/main/main.c \
		srcs/main/fractol_window.c \
		srcs/main/fractol_fractal.c \
		srcs/main/fractol_actions.c \
		srcs/generic_utils/generic_utils.c \
		srcs/image_utils/image_utils.c \
		srcs/event_utils/event_utils.c

MLX_FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz #-lXrender

MLX_LIB = libmlx_Linux.a

all : $(NAME)

$(NAME) :	$(SRCS)
			$(CC) $(SRCS) -o $(NAME) $(MLX_LIB) $(INCLUDES) $(MLX_FLAGS)

clean :

fclean :	clean
			rm $(NAME)
