NAME = lem-in

SRCPATH = ./src/

ODIR = ./bin/

TESTDIR = ./.test/

SRCFILES =	exit.c \
			free.c \
			get_classify_lines.c \
			get_find_room.c \
			get_nb_of_ants.c \
			get_print_next_line.c \
			get_rooms.c \
			get_sorttree.c \
			get_tunnels.c \
			main.c \
			paths_add_1path.c \
			paths_check_rooms_in_paths.c \
			paths_copy_lop.c \
			paths_fill_top.c \
			paths_find_next_room.c \
			paths_find_paths.c \
			paths_find_rooms.c \
			paths_test_paths.c \
			print.c \
			print_browse.c \
			print_set_values.c
			
LIBS = 		./src/libft.a
			
FLAGS = -Wall -Wextra -Werror -O3

OBJS = $(addprefix $(ODIR), $(SRCFILES:.c=.o))

vpath %.c src/

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(ODIR)%.o: %.c
	gcc $(FLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean all

