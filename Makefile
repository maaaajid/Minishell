# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 15:35:55 by lahamoun          #+#    #+#              #
#    Updated: 2023/06/26 04:30:11 by lahamoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBFT = libft.a
LIBFT_DIR = ./libft

INCLUDES = -I$(LIBFT_DIR) 
SRC_DIR = ./src/
SRC_DIR2 = ./builtins/
OBJ_DIR = ./obj/

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

SRCS = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR2)*.c)
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(patsubst $(SRC_DIR2)%.c,$(OBJ_DIR)%.o,$(SRCS)))

DEPS = $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME) -L ~/Desktop/readline-8.2 -I ~/Desktop/readline-8.2 -lreadline -lcurses
	@echo "$(GREEN)Done!$(NC)"
	@echo "$(GREEN)"
	
	@echo "     	 __  __ _       _  _____ _          _ _ "
	@echo "     	|  \/  (_)     (_)/ ____| |        | | |"
	@echo "     	| \  / |_ _ __  _| (___ | |__   ___| | |"
	@echo "     	| |\/| | | '_ \| |\___ \| '_ \ / _ \ | |"
	@echo "     	| |  | | | | | | |____) | | | |  __/ | |"
	@echo "     	|_|  |_|_|_| |_|_|_____/|_| |_|\___|_|_|"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR2)%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	rm -f $(OBJS) $(DEPS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


