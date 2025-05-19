ifndef VERBOSE
MAKEFLAGS += --no-print-directory --silent
endif

NAME := ft_nm
CC := clang
CFLAGS := -Wextra -Wall -Werror -g

SRCS = src/main.c

SRC_DIR := src
OBJS_DIR := obj
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
LIBFT_DIR := lib/libft/
LIBFT_EXEC := lib/libft/libft.a

all: libft $(NAME)

libft:
	@make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_EXEC)
	echo "Compiling\033[1m\033[32m" $@ "\033[0m"
	echo "\033[42mSuccessfully compiled :)\033[0m"

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)


fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
