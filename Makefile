# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 19:46:19 by oztozdem          #+#    #+#              #
#    Updated: 2025/07/11 12:41:40 by oztozdem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3D
CC =		@cc
CFLAGS =	-Wall -Wextra -Werror -g3
LDFLAGS =	-lXext -lX11 -L./minilibx-linux -lmlx -L./libft -lft
OBJS =		$(patsubst srcs%, objs%, $(SRCS:.c=.o))
SRCS =		srcs/cub3d.c \
			srcs/utils.c \
			srcs/free.c \
			srcs/parsing/parsing.c \
			srcs/parsing/free.c \
			srcs/parsing/utils.c \
			srcs/parsing/duplicate.c \
			srcs/parsing/check.c \
			srcs/parsing/color.c \
			srcs/parsing/print.c \
			srcs/parsing/fill_map.c \
			srcs/parsing/check_close.c \
			srcs/parsing/v_or_x.c \

GREEN =		\033[1;32m
YELLOW =	\033[1;33m
BLUE =		\033[1;34m
RED =		\033[1;31m
RESET =		\033[0m
BOLD =		\033[1m

all:		objs ${NAME}

${NAME}:	${OBJS}
			@printf "\n"
			@printf "\033[31;1m ██████╗ \033[33;1m██╗   ██╗\033[32;1m██████╗ "
			@printf "\033[36;1m██████╗ \033[34;1m██████╗ \n"
			@printf "\033[31;1m██╔════╝ \033[33;1m██║   ██║\033[32;1m██╔══██╗"
			@printf "\033[36;1m╚════██╗\033[34;1m██╔══██╗\n"
			@printf "\033[31;1m██║      \033[33;1m██║   ██║\033[32;1m██████╔╝"
			@printf "\033[36;1m █████╔╝\033[34;1m██║  ██║\n"
			@printf "\033[31;1m██║      \033[33;1m██║   ██║\033[32;1m██╔══██╗"
			@printf "\033[36;1m ╚═══██╗\033[34;1m██║  ██║\n"
			@printf "\033[31;1m╚██████╗ \033[33;1m╚██████╔╝\033[32;1m██████╔╝"
			@printf "\033[36;1m██████╔╝\033[34;1m██████╔╝\n"
			@printf "\033[31;1m ╚═════╝ \033[33;1m ╚═════╝ \033[32;1m╚═════╝ "
			@printf "\033[36;1m╚═════╝ \033[34;1m╚═════╝ \n"
			@printf "\033[0m\n"
			@echo "$(BLUE)$(BOLD)Compiling libft.a... 🛠️$(RESET)"
			@make -sC libft/
			@echo "$(GREEN)$(BOLD)libft.a compiled 🚀$(RESET)"
			@echo "$(BLUE)$(BOLD)Compiling MiniLibX... 🛠️$(RESET)"
			@make -sC minilibx-linux/ > /dev/null 2>&1
			@echo "$(GREEN)$(BOLD)MiniLibX compiled 🚀$(RESET)"
			@echo "$(BLUE)$(BOLD)Compiling ${NAME}... 🛠️$(RESET)"
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "$(GREEN)$(BOLD)${NAME} compiled 🚀$(RESET)"

objs:
			@mkdir -p $(dir $(OBJS))

objs/%.o:	srcs/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@echo "$(RED)$(BOLD)Cleaning up MiniLibX object files 🧹$(RESET)"
			@make clean -sC minilibx-linux/ > /dev/null 2>&1
			@echo "$(GREEN)$(BOLD)MiniLibX object files removed! ✅$(RESET)"
			@echo "$(RED)$(BOLD)Cleaning up libft object files 🧹$(RESET)"
			@make clean -sC libft/
			@echo "$(GREEN)$(BOLD)libft object files removed! ✅$(RESET)"
			@echo "$(RED)$(BOLD)Cleaning up ${NAME} object files 🧹$(RESET)"
			@rm -rf ${OBJS} objs
			@echo "$(GREEN)$(BOLD)${NAME} object files removed! ✅$(RESET)"

fclean:		clean
			@echo "$(RED)$(BOLD)Deleting libft.a 🗑️$(RESET)"
			@make fclean -sC libft/
			@echo "$(GREEN)$(BOLD)libft.a deleted! ❌$(RESET)"
			@echo "$(RED)$(BOLD)Deleting ${NAME} 🗑️$(RESET)"
			@rm -rf ${NAME}
			@echo "$(GREEN)$(BOLD)${NAME} deleted! ❌$(RESET)"

re:			
			@echo "$(YELLOW)$(BOLD)Recompiling ${NAME} 🔄$(RESET)"
			@$(MAKE) -s fclean all
			@echo "$(YELLOW)$(BOLD)Done recompiling! ✅$(RESET)"

.PHONY:		all clean fclean re