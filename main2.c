#include "minishell.h"
 
int main(int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    t_minishell mshell;
    char  **str;
    t_redr  *p;
    int i;

    mshell.line.head = NULL;
    while(1)
    {
        mshell.line.rl = readline("MINISHELL : ");
        if (*mshell.line.rl)
        {
            check_syntax(&mshell, &mshell.line, &mshell.list,env);
            //add_history(mshell.line.rl);
        }
        while (mshell.list)
        {
            str = mshell.list->options ;
            p = mshell.list->r_list;
            i = 0;
            while (str[i])
            {
                printf("%s\n",str[i]);
                i++;
            }
            if (p)
            {
                    printf("%s",p->str);
                    p = p->next ;
            }
            mshell.list = mshell.list->next;
            i = 0;
        }
        
    // free_gc(&line.head);
    }
    return(0);
}
