##
## Makefile for wolf3d in /home/brout_m/rendu/projet/Infographie/gfx_wolf3d
##
## Made by marc brout
## Login   <brout_m@epitech.net>
##
## Started on  Thu Dec 17 13:59:43 2015 marc brout
## Last update Sat Mar 12 18:58:46 2016 marc brout
##

SRCP	= ./src/

SRCP2	= ./tcore/

SRC     = $(SRCP2)tekpixel.c \
	$(SRCP2)tekray.c \
	$(SRCP)rtload.c \
	$(SRCP)error.c \
	$(SRCP)keyboard.c \
	$(SRCP)rtdisplay.c \
	$(SRCP)raytracer.c \
	$(SRCP)misc.c \
	$(SRCP)my_strdup.c \
	$(SRCP)my_getnbr.c \
	$(SRCP)display_formes.c \
	$(SRCP)sphere.c \
	$(SRCP)plan.c \
	$(SRCP)math.c \
	$(SRCP)ombres.c \
	$(SRCP)check_formes.c \
	$(SRCP)calculs.c \
	$(SRCP)functabs.c \
	$(SRCP)free.c

OBJS    = $(SRC:.c=.o)

NAME    = raytracer1

CC      = gcc

CFLAGS  = -W -Wall -Werror

CFLAGS	+= -I/home/${USER}/.froot/include -I./include

LDFLAGS = -L/home/${USER}/.froot/lib \
	-llapin \
	-lsfml-audio \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	-lstdc++ -ldl \
	-lm \

RM      = rm -f

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
