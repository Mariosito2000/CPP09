# COLOR DEFINITION #
RED     := \033[0;31m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
GREEN   := \033[1;32m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m
WHITE   := \033[0;37m
RESET   := \033[0m

SOURCES	=	main.cpp\
			Span.cpp

OBJS	=	$(SOURCES:.cpp=.o)

DEPS	=	$(OBJS:.o=.d)

NAME	=	mutantstack_test

CC		=	c++

#DEBUG	=	-g3

DEPFLAGS	=	-MMD

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 $(DEBUG)

RM 		=	rm -rf

.cpp.o:
	@$(CC) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@
	@echo "$(RED)Compiling $(RESET) $(CC) $(CPPFLAGS) $<"

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CPPFLAGS) $(DEPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)==========GENERATED $(NAME)==========$(RESET)"

clean:
	@$(RM) $(OBJS) $(DEPS)
	@echo "$(YELLOW)==========OBJS DELETED==========$(RESET)"

fclean: clean
	@$(RM) ${NAME}
	@echo "$(RED)==========$(NAME) DELETED==========$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re