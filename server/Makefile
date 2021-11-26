# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 14:49:02 by sbelondr          #+#    #+#              #
#    Updated: 2021/11/26 10:35:43 by sbelondr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- #
# Debug mode #
# ---------- #

DEBUG = yes

# --------- #
# Directory #
# --------- #

SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
LIBDIR=libft/
LIBS_NAMES=libft.a

VPATH = objs:\
	srcs:

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = gcc
ifeq ($(DEBUG), yes)
	CFLAGS = -D_GNU_SOURCE=1 -Wall -Wextra -fsanitize=address -g3
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I libft/ #COUCOU samuel ça c'est un peu moche non ???
#Sam: Oui en effet

# --------------- #
# Different names #
# --------------- #

NAME = server
SRCS_NAMES = server.c\
	color.c\
	termcaps.c\
	act_client.c\
	init_srv.c\
	act_server.c\
	parser.c\
	init_world.c\
	world_map_helper.c\
	gameplay.c\
	client.c\
	client_commands_movement.c\
	client_commands_vision.c\
	client_commands_items.c\
	client_commands_social.c\
	listen.c\
	command_helper.c\
	command_dispatcher.c\
	game_tick.c\
	team_helper.c\
	helpers.c \
	moniteur_commands.c

HEADERS_NAMES = server.h

OBJS_NAMES = $(SRCS_NAMES:.c=.o)

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIB = $(addprefix $(LIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"
MAKE = make

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(LIBS) $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(CFLAGS) $(CPPFLAGS) libft/libft.a #TU te démerdes moi ça me casse les couilles
	@$(PRINT) $(REMOVE)"Executable built\n"

%.o : %.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

libs :
	@$(MAKE) -j3 -C $(LIBDIR)

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed\n"

lldb :
	@lldb ./$(NAME)

norm :
	@norminette ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, lldb, norm and help\n"

.PHONY : $(PHONY)
