NAME = ft_ls

SRCS = main.c options.c arguments.c arguments_files.c arguments_paths.c directory.c directory_read.c file_info.c \
	output.c output_permissions.c output_format.c output_long.c \
	sort.c sort_arguments.c recursive.c errors.c memory.c output_total.c widths.c
SRCS_DIR = ./srcs
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c includes/ft_ls.h $(LIBFT_DIR)/libft.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(wildcard libft/*.c libft/*.h) libft/Makefile
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
