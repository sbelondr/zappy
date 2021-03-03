# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 14:49:02 by sbelondr          #+#    #+#              #
#    Updated: 2021/03/03 15:18:59 by sbelondr         ###   ########.fr        #
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

VPATH = objs:\
	srcs:

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = cc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR)

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
	listen.c
HEADERS_NAMES = server.h

OBJS_NAMES = $(SRCS_NAMES:.c=.o)

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"

# ----- #
# Rules #
# ----- #

all : $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) $(REMOVE)"Executable built\n"

%.o : %.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

clean : 
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans 
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
