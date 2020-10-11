NAME = philo_three
CFLAGS = -Wall -Wextra -Werror -g3 -Iinc/

TOTAL = $(shell find src -iname  "*.c" | wc -l | bc)
O_COUNT = 0
COUNT = 0

#Colors
RESET = \033[0m
GREEN_BOLD = \033[32;1m
LIGHT_BLUE = \033[94m


define update
	$(eval O_COUNT := $(shell find obj -iname "*.o" 2> /dev/null | wc -l | bc))
	printf "\r["
	printf "=%.0s" $(shell seq 0 ${O_COUNT})
	printf ">"
	$(eval COUNT := $(shell echo ${TOTAL} - ${O_COUNT} | bc))
	printf "%${COUNT}s" "]"
endef

ifeq ($(D), 1)
		CFLAGS += -fsanitize=thread
endif
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	TICK = \342\234\224
	CC = clang
else
	TICK = \xE2\x9C\x94
	CC = gcc
endif

SRC_DIR = ./src/
SRC = ${wildcard src/*.c}
OBJ = ${patsubst src/%.c, obj/%.o, ${SRC}}

all: $(NAME)

$(NAME): ${OBJ}
	@${CC} ${OBJ} ${CFLAGS} -o ${NAME}
	@echo "${GREEN_BOLD}\r${NAME} by Violetta Goldman is done ${TICK}          ${RESET}"
	@echo "${LIGHT_BLUE}To run the ${NAME} type './${NAME} [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_time_each_philosopher_must_eat]'${RESET}"

./obj/%.o: ./src/%.c
	@mkdir -p ./obj
	@${CC} ${CFLAGS} -c $< -o $@
	@$(call update)

norme:
	@norminette ${SRC_DIR}

clean:
	@rm -rf obj
	@echo "\033[32;1mCleaned ${NAME} ${TICK}\033[0m"

fclean:	clean
	@rm -rf ${NAME} ${NAME}.dySM
	@echo "\033[32;1mForced cleaned ${NAME} ${TICK}\033[0m"

re:	fclean all

.PHONY: clean fclean all re

