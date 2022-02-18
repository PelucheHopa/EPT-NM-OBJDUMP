##
## EPITECH PROJECT, 2020
## nothing
## File description:
## nothing
##

CFLAGS		+=	-W -Wall -Wextra -I include/

NM_SRC		=	src/nm/engine_add.c \
			src/nm/engine_do.c \
			src/nm/engine_nm.c \
			src/nm/engine_print.c \
			src/nm/engine_symbol.c \
			src/nm/engine.c \
			src/nm/exception.c \
			src/nm/get.c \
			src/nm/main.c \
			src/nm/sort.c

OBJ_SRC		=	src/objdump/64bit.c	\
			src/objdump/32bit.c	\
			src/objdump/display.c	\
			src/objdump/main.c	\
			src/objdump/flag.c	\
			src/objdump/extract.c

OBJ_NM		=	$(NM_SRC:.c=.o)

OBJ_OBJ		=	$(OBJ_SRC:.c=.o)

NM_NAME		=	my_nm

OBJ_NAME	=	my_objdump

all:		$(NM_NAME) $(OBJ_NAME)

nm:			$(NM_NAME)

objdump:	$(OBJ_NAME)

$(NM_NAME): $(OBJ_NM)
			gcc -o $(NM_NAME) $(OBJ_NM)

$(OBJ_NAME): $(OBJ_OBJ)
			gcc -o $(OBJ_NAME) $(OBJ_OBJ)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f my_objdump
	rm -f my_nm
	rm -f $(NAME_TEST)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.out
	rm -f src/nm/*.o
	rm -f src/objdump/*.o
path:
	LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH

tri-all:
	mv *.h include/
	mv *.c src
tri-c:
	mv *.c src/
auteur:
	echo $(USER) > auteur

re:     fclean all
## n'affiche pas les commandes
.SILENT:

## ne compare pas les fichiers
.PHONY:

##export xLDFLAGS
##	
