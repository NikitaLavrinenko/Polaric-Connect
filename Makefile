#******************************************************************************#
#                                                                              #
#                                                                              #
#    Makefile                                                                  #
#                                                                              #
#    By: Nikita Lavrinenko <nl@polaricsemi.com>                                #
#                                                                              #
#                                                                              #
#******************************************************************************#

NAME = polaric-connect

SRC = gtk_test.c app.c
ROOT = $(shell pwd)
DESTDIR = $(ROOT)

CC = gcc
FLAGS = `pkg-config --cflags gtk+-3.0`
SRC_DIR = src
H_DIR = include -I$(ROOT)/libs/inlcudes
OBJ_DIR = obj
BIN_DIR = bin
LIBGTK = `pkg-config --libs gtk+-3.0`
LIBSSH = -lssh

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(OBJS) $(LIBGTK) $(LIBSSH) -o $(NAME)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(H_DIR)

install:
	@echo "Installing $(NAME)"
	mkdir -p $(DESTDIR)/usr/bin
	cp $(NAME) $(DESTDIR)/usr/bin/.
	mkdir -p $(DESTDIR)/usr/share/applications
	cp $(NAME).desktop $(DESTDIR)/usr/share/applications/.
	mkdir -p $(DESTDIR)/usr/share/pixmaps/
	cp $(NAME).png $(DESTDIR)/usr/share/pixmaps
	mkdir -p $(DESTDIR)/usr/share/licenses/$(NAME)
	cp LICENSE $(DESTDIR)/usr/share/licenses/.

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
fclean: clean
	@rm $(NAME)
