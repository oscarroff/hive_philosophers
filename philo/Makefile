# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 14:57:58 by thblack-          #+#    #+#              #
#    Updated: 2026/01/24 12:36:52 by thblack-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJECT NAME
PROJECT		= philo
NAME		= philo

# COMPILING
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# PROJECT DIRECTORIES
SRC_D		= src
OBJ_D		= obj
INC_D		= inc

# SOURCE DIRECTORIES
UTILS_D		= src/utils

# SOURCE FILES
UTILS_F		= ft_atoui.c ft_error.c ft_isdigit.c ft_issign.c ft_isspace.c \
			  ft_naun.c ft_strlen.c
MAIN_F		= cutlery.c exit.c fed_philos_do_things.c init.c main.c monitor.c \
			  routine_even.c routine_init.c routine_lonely.c routine_odd.c \
			  threads.c time.c

# PROJECT SOURCES
MAIN		= $(addprefix $(SRC_D)/, $(MAIN_F))
UTILS		= $(addprefix $(UTILS_D)/, $(UTILS_F))
SOURCES		= $(MAIN) $(UTILS)

# HEADER FILES
HEADER_F	= philo.h
HEADER		= $(addprefix $(INC_D)/, $(HEADER_F))

# PROJECT OBJECTS
OBJ			= $(patsubst $(SRC_D)/%.c, $(OBJ_D)/%.o, $(SOURCES))
OBJ_DIRS	= $(sort $(dir $(OBJ)))
DEPS		= $(OBJ:.o=.d)

# MAC INCLUDE PATHS AND LIBRARIES
INC			= -I. -I$(INC_D)

# <<<<<<< MAIN TARGETS >>>>>>>

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIRS):
	mkdir -p $@

$(OBJ_D)/%.o: $(SRC_D)/%.c $(HEADER) | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEPS)

.SECONDARY: $(OBJ) 

# <<<<<<< PHONY TARGETS >>>>>>>

.PHONY: all clean fclean re

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all
