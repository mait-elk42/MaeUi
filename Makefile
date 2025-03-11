
LIB= -Llib -lraylib -lchipmunk -lGL -lm -lpthread -ldl -lrt -lX11
COMPILER= c++
CFLAGS= -I include
SRCS= src/Application.cpp
SRCS_O= $(SRCS:.cpp=.o)
NAME= app

all: $(NAME)

$(NAME): $(SRCS_O) main.cpp
	$(COMPILER) main.cpp $(SRCS_O) $(CFLAGS) $(LIB) -o $(NAME) -D PHYSAC_IMPLEMENTATION

src/%.o: src/%.cpp include/MaeUI/%.hpp
	$(COMPILER) -c $(CFLAGS) $< $(CFLAGS) -o $@

clean:
	rm -f $(SRCS_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean