NAME = lem-in

SRCPATH = ./src/

ODIR = ./bin/

TESTDIR = ./.test/

PSCRFILES = exit.c \
			free.c \
			get_classify_lines.c \
			get_find_room.c \
			get_nb_of_ants.c \
			get_next_line.c \
			get_print_next_line.c \
			get_rooms.c \
			get_sorttree.c \
			get_tunnels.c \
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

SRCFILES =	$(PSCRFILES) \
			main.c \
			
VSRCFILES =	$(PSCRFILES) \
			visual_create_ant_room_array.c \
			visual_find_rooms.c \
			visual_get_nb_of_ants.c \
			visual_get_rooms.c \
			visual_get_tunnels.c \
			visual_is_move.c \
			visual_make_ants_move.c \
			visual_visu-hex.c \
			visual_window.c
			
LIBS = 		./lib/libft.a
			
FLAGS = -Wall -Wextra -Werror -O3

VNAME = visu-hex

VSRCPATH = ./src/

VODIR = ./bin/

VTESTDIR = ./.test/
			
VLIBS =	./lib/libft.a \
		./lib/libSDL.a
			
VFLAGS = -Wall -Wextra -Werror

OBJS = $(addprefix $(ODIR), $(SRCFILES:.c=.o))

VOBJS = $(addprefix $(VODIR), $(VSRCFILES:.c=.o))

vpath %.c src/

all: $(NAME) $(VNAME)

lem: $(NAME)

visu: $(VNAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)
	
$(VNAME): $(VOBJS)
	gcc $(VFLAGS) -o $(VNAME) $(VOBJS) $(VLIBS)

$(ODIR)%.o: %.c
	gcc $(FLAGS) -c $< -o $@
	
$(VODIR)%.o: %.c
	gcc $(VFLAGS) -c $< -o $@
	
clean_lem:
	rm -f $(OBJS)
	
fclean_lem: clean_lem
	rm -f $(NAME)
	
re_lem: fclean_lem lem

clean_visu:
	rm -f $(VOBJS)
	
fclean_visu: clean_visu
	rm -f $(VNAME)
	
re_visu: fclean_visu visu
	
clean:
	rm -f $(OBJS)
	rm -f $(VOBJS)
	
fclean: clean
	rm -f $(NAME)
	rm -f $(VNAME)
	
re: fclean all

