# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/03 19:46:19 by oztozdem          #+#    #+#              #
#    Updated: 2025/07/11 13:10:24 by vnieto-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		cub3D
CC =		@cc
CFLAGS =	-Wall -Wextra -Werror -g3
LDFLAGS =	-L./minilibx-linux -lmlx -L./libft -lft -lXext -lX11 -lbsd -lm
OBJS =		$(patsubst srcs%, objs%, $(SRCS:.c=.o))
SRCS =		srcs/cub3d.c \
			srcs/utils.c \
			srcs/parsing/parsing.c \
			srcs/parsing/free.c \
			srcs/parsing/utils.c \
			srcs/parsing/duplicate.c \
			srcs/exec/draw.c \
			srcs/exec/exec_1.c \
			srcs/exec/free.c \
			srcs/exec/hook.c \
			srcs/exec/init_mlx.c \
			srcs/exec/move_1.c \
			srcs/exec/move_2.c \
			srcs/exec/raycasting.c \
			srcs/exec/raycasting_init.c \

GREEN =		\033[1;32m
YELLOW =	\033[1;33m
BLUE =		\033[1;34m
RED =		\033[1;31m
RESET =		\033[0m
BOLD =		\033[1m

all:		objs ${NAME}

${NAME}:	${OBJS}
			@echo "$(BLUE)$(BOLD)\n\tCompiling libft.a... 🛠️\n$(RESET)"
			@make -sC libft/
			@echo "$(GREEN)$(BOLD)\n\tlibft.a compiled 🚀\n$(RESET)"
			@echo "$(BLUE)$(BOLD)\n\tCompiling MiniLibX... 🛠️\n$(RESET)"
			@make -sC minilibx-linux/ > /dev/null 2>&1
			@echo "$(GREEN)$(BOLD)\n\tMiniLibX compiled 🚀\n$(RESET)"
			@echo "$(BLUE)$(BOLD)\n\tCompiling ${NAME}... 🛠️\n$(RESET)"
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}
			@echo "$(GREEN)$(BOLD)\n\t${NAME} compiled 🚀\n$(RESET)"

objs:
			@mkdir -p $(dir $(OBJS))

objs/%.o:	srcs/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@echo "$(RED)$(BOLD)\n\tCleaning up MiniLibX object files 🧹\n$(RESET)"
			@make clean -sC minilibx-linux/ > /dev/null 2>&1
			@echo "$(GREEN)$(BOLD)\n\tMiniLibX object files removed! ✅\n$(RESET)"
			@echo "$(RED)$(BOLD)\n\tCleaning up libft object files 🧹\n$(RESET)"
			@make clean -sC libft/
			@echo "$(GREEN)$(BOLD)\n\tlibft object files removed! ✅\n$(RESET)"
			@echo "$(RED)$(BOLD)\n\tCleaning up ${NAME} object files 🧹\n$(RESET)"
			@rm -rf ${OBJS} objs
			@echo "$(GREEN)$(BOLD)\n\t${NAME} object files removed! ✅\n$(RESET)"

fclean:		clean
			@echo "$(RED)$(BOLD)\n\tDeleting libft.a 🗑️\n$(RESET)"
			@make fclean -sC libft/
			@echo "$(GREEN)$(BOLD)\n\tlibft.a deleted! ❌\n$(RESET)"
			@echo "$(RED)$(BOLD)\n\tDeleting ${NAME} 🗑️\n$(RESET)"
			@rm -rf ${NAME}
			@echo "$(GREEN)$(BOLD)\n\t${NAME} deleted! ❌\n$(RESET)"

re:			
			@echo "$(YELLOW)$(BOLD)\n\tRecompiling ${NAME} 🔄\n$(RESET)"
			@$(MAKE) -s fclean all
			@echo "$(YELLOW)$(BOLD)\n\tDone recompiling! ✅\n$(RESET)"

.PHONY:		all clean fclean re