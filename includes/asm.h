/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:05:56 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/10 20:43:50 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/libft/inc/libft.h"
# include "get_next_line.h"
# include <limits.h>
# include <fcntl.h>

# define NUMBERMAX_ERROR 5
# define BUFFER_TOKENS CHAMP_MAX_SIZE
# define BUFFER_LABELS CHAMP_MAX_SIZE
# define SIZEMAX_STRING 2048

typedef struct		s_op
{
	char			*operation;
	int				number_param;
	int				tab[3];
	int				id;
	int				cycle;
	char			*comment;
	int				val1;
	int				val2;
}					t_op;

typedef struct		s_fichier
{
	int				fd_in;
	int				fd_out;
	char			*file_name;
	char			*line;
	int				line_nb;
}					t_fichier;

typedef enum		e_type
{
	EMPTY,
	NAME,
	COMMENT,
	STRING,
	LABEL,
	INSTRUCTION,
	SEPARATOR,
	REGISTER,
	DIRECT_LABEL,
	DIRECT_LABEL_STR,
	DIRECT,
	INDIRECT,
	INDIRECT_LABEL,
	INDIRECT_LABEL_STR,
	UNKNOWN,
}					t_type;

typedef union		u_value
{
	t_op			*operation;
	int				number;
	char			*data;
}					t_value;

typedef struct		s_token
{
	t_type			type;
	t_value			value;
	int				line;
	int				pos;
	struct s_token	*param[3];
}					t_token;

typedef struct		s_champion
{
	t_header		*header;
	t_token			**tokens;
	int				number_token;

	int				*labels;
	int				number_labels;

	int				instructions[CHAMP_MAX_SIZE];
	int				number_instructions;

	int				size;
	int				hasname;
	int				hascomment;
	int				number_error;
	int				number_warning;

	unsigned char	prog[CHAMP_MAX_SIZE * 2];
}					t_champion;

extern t_op			g_tab[17];

/*
**=======================PROTO========================
*/

/*
** add_token.c
*/

t_token				*add_token_operation(t_token *token, char *str);
t_token				*add_token_string(t_token *token, char *str);
t_token				*add_token_integer(t_token *token, int value);

/*
** analyse_string.c
*/

t_token				*analyse_string(char **line, t_fichier *file);

/*
** check_instruction.c
*/

int					check_instruction(t_champion *c, t_token *token, int pos,
											int tok_line);

/*
** check_token.c
*/

int					error_name_comment(t_champion *c, t_token *t, t_token
						*next, int nb_tok);
void				check_name_comment(t_champion *c, t_token *t, t_token *next,
						int nb_tok);

/*
** desas_instruction.c
*/

int					get_instruction(t_champion *champion, unsigned char *prog);
int					get_instruction_argcode(unsigned char *prog,
						t_token *token);
t_token				*get_param(char param, unsigned char *prog, int *pos);

/*
** desassembler.c
*/

int					read_header(t_champion *champion, int fd);
int					read_champion(t_champion *champion, int fd);

/*
** error.c
*/

int					malloc_error(char *str);
int					warning_champion(t_champion *champion, char *s, int line);
int					error_champion(t_champion *champion, char *s, int line);

/*
** free.c
*/

void				free_token(t_token **token);
void				free_file(t_fichier **file);
void				free_champion(t_champion **champion);
void				delete_token(t_token *token);

/*
** get_token.c
*/

t_token				*get_token(t_champion *c, char *s, int end, int line_nb);
int					move_token(t_token **token, t_token **t);
int					ft_isnumber(char *s);

/*
** hexa.c
*/

long long			convert_bigendian(long long val, unsigned int size);
int					convert_token_hexa(t_champion *c, int start,
						t_token *token);
int					convert_param_hexa(t_champion *c, t_token *token,
						int start, int id);

/*
** init.c
*/

t_fichier			*init_file();
t_champion			*init_champion();
t_champion			*clear_champion(t_champion *champion);
t_fichier			*clear_file(t_fichier *file);

/*
** label.c
*/

int					manage_label_param(t_champion *champion, char *str);
void				check_label(t_champion *c, t_token *t, int deb,
											int tok_line);
int					already_label(t_champion *c, char *str, int s);

/*
** parsing.c
*/

int					parsing(t_fichier *file, t_champion *champion);

/*
** recognize.c
*/

int					islabel(char *s);
int					isintruction(char *s);
int					isindirect_label(char *s);
int					isregister(char *s);
int					compose_withthese_letters(char *word, char *letters);

/*
** token.c
*/

t_token				*create_token(int line_nb, int type);
int					size_token(int t, int id);
int					add_token(t_token *token, t_champion *champion);

/*
** verify.c
*/

int					verify_champion(t_champion *c);

/*
** write_champion.c
*/

int					write_header(t_header *header, int fd);
int					create_champion(t_fichier *file, t_champion *champion);
unsigned char		opcode(t_token *token);
int					manage_prog(t_champion *champion);

/*
** write_champion.c
*/

int					write_champion_prog(t_champion *champion, char *str);
void				write_line_token(t_token *token, int fd);
long long			cast_element(long long value, unsigned char size);

/*
** test.c
*/

# define MODETOKEN 1
# define MODEREEL 2

int					affichetype(int type);
int					test_champion(t_champion *champion, int mode);
int					affichelabels(t_champion *champion);

#endif
