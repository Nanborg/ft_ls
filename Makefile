NAME = ft_ls

SRCS = main.c options.c arguments.c directory.c file_info.c \
	output.c sort.c recursive.c errors.c memory.c
SRCS_DIR = ./srcs
OBJS = $(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c includes/ft_ls.h $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(wildcard libft/*.c libft/*.h) libft/Makefile
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
