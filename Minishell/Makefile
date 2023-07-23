# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME			=	minishell

# ---- Directories ---- #

DIR_OBJS		=	bin/

DIR_SRCS		=	srcs/

DIR_HEADERS		=	includes/

# ---- Libs variables ---- #

LIBFT			=	lib/libft/libft.a

# ---- Files ---- #

HEADERS_LIST	=	builtins.h		exec.h		\
					minishell.h		sig.h		\
					struct.h		parsing.h	\
					error_message.h

SRCS_LIST		=	main.c		prompt.c		\
\
					builtins/cd.c		builtins/echo.c			\
					builtins/env.c		builtins/exit.c			\
					builtins/export.c	builtins/export_utils.c	\
					builtins/pwd.c		builtins/unset.c		\
\
					exec/execution.c		exec/execution_2.c		\
					exec/exec_cmd.c			exec/here_doc.c			\
					exec/translate_cmd.c	exec/io_handling.c		\
					exec/free_exec.c		exec/write_here_doc.c	\
\
					signal/init_sigaction.c		signal/sig_handlers.c		\
\
					parsing/parse_pipe.c		parsing/parse_syntax_check.c	\
					parsing/parse_syntax_utils.c	parsing/parse_syntax.c		\
					parsing/path.c					parsing/check_cmd.c			\
					parsing/env_symbol.c			parsing/quotes_type.c		\
					parsing/quotes_env.c			parsing/quotes_utils.c		\
					parsing/quotes.c				parsing/token_builtins.c	\
					parsing/token_check.c			parsing/token_cmd.c			\
					parsing/token_env_var.c			parsing/token_infile.c		\
					parsing/token_init.c			parsing/token_is_in.c		\
					parsing/token_outfile.c			parsing/token_utils.c		\
					parsing/token.c												\
					parsing/utils_free.c			parsing/utils_str.c			\
					parsing/utils.c					parsing/utils2.c			\
					parsing/utils_exit.c			parsing/utils_trunc.c


HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CC				=	cc

CFLAGS			=	 -Wall -Werror -Wextra -g3



FRAMEWORKS		=	-Llib/libft -lft -lreadline


# ---- Commands ---- #

RM				=	rm -rf

MKDIR			=	mkdir -p

# ********* RULES ******** #


all				:	${OBJS} ${HEADERS}
					make -C lib/libft
					make ${NAME}

fsanitize		:
					make debug -C lib/libft
					make all CFLAGS+="-fsanitize=address -g3"

no_flags		:
					make fclean -C lib/libft
					make fclean
					make -C lib/libft FLAGS="-g3"
					make all CFLAGS="-g3"

# ---- Variables Rules ---- #

${NAME}			:	${OBJS} ${HEADERS} ${LIBFT}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} ${FRAMEWORKS} -o ${NAME}

# ---- Compiled Rules ---- #

${OBJS}			:	| ${DIR_OBJS}

${DIR_OBJS}%.o	:	${DIR_SRCS}%.c ${HEADERS}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}
					${MKDIR} ${DIR_OBJS}builtins
					${MKDIR} ${DIR_OBJS}parsing
					${MKDIR} ${DIR_OBJS}exec
					${MKDIR} ${DIR_OBJS}signal

# ---- Usual Rules ---- #

clean			:
					make -C lib/libft clean
					${RM} ${OBJS}
					${RM} ${DIR_OBJS}

fclean			:
					make clean
					${RM} ${NAME}
					make -C lib/libft fclean

re				:
					make fclean
					make all

.PHONY:	all clean fclean re
