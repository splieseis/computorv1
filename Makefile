# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 15:35:50 by spliesei          #+#    #+#              #
#    Updated: 2019/06/20 15:55:53 by spliesei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME			:= computorV1

# Sources, objects and headers
SRCS			:= computorV1.cpp

OBJS			:= $(SRCS:.cpp=.o)


# Flags and compiler
CXXFLAGS	:= -Wall -Wextra -Werror
CXX				:= clang++

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@$(CXX) $(OBJS) -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@echo "Objects removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re
