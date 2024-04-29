
#include "minishell.h"

/*
** Function handle_pwd :
*/

void	handle_pwd(void)
{
	char	*path;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	g_status = 0;
}
