NAME = parser
CPP_FILE = *.cpp
CFLAGS =  -std=c++98
INC_FILE = ../../include/parser/*.hpp

all: $(NAME)

$(NAME): $(CPP_FILE) 
	c++ $(CFLAGS) -o $(NAME) $(CPP_FILE)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re