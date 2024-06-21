#include "minishell.h"

 /*
    Minishell needs to display a prompt when waiting for a new command.

        We need to:

        read_command
        parse_command
        execute_command

        And also:
        verify_command
    */

// Variável global para controlar a interrupção ou não do prompt
unsigned int	prompt_status = 0;

void    sigint_handle(int sig)
{
    (void)sig;
    prompt_status = 1;
    printf("\n");
    rl_on_new_line();
    //replace_line("", 0);
    rl_redisplay();
}

int main(void)
{
    //struct s_node   minishell_data;
    char    *input;

    signal(SIGINT, sigint_handle);
    while (42)
    {
        if (prompt_status)
            prompt_status = 0;
        input = readline("$ ");
        if (input == NULL)
        {
            printf("\n");
            break;
        }
        add_history(input);
        printf("You entered: %s\n", input);
        if (ft_strcmp(input, "exit") == 0)
            break;
        free(input);
    }
    clear_history();
    free(input);
}