#ifndef define MINISHELL_H
# define MINISHELL_H

//Readline 
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_SIZE_TOKEN ?
# define TOKEN_SIZE ?

typedef     struct s_node
{
    char    *content;
    char    *symbol;
    void    *next;
}       t_node;

typedef     struct s_token
{
    char    token_type;
    char    token_value[MAX_SIZE_TOKEN];

}       t_token;

enum    e_token
{
    CMD,
    PIPE,
    HEREDOC,
};

#endif
