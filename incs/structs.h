#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>

typedef struct termios	t_termios;

typedef enum e_token_type
{
	T_NULL = 0,
	T_WORD = 1,
	T_PIPE = 2,
	T_REDIRECT = 3,
	T_SINGLE_QUOTE = 4,
	T_DOUBLE_QUOTE = 5,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct	s_var
{
	t_termios	old_term;
	t_termios	new_term;
}	t_var;

#endif