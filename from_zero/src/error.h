#ifndef ERROR_H
# define ERROR_H

# include "libft/libft.h"
# include "defs.h"
# include <errno.h>

void	map_exit_failure(char *map_line, char *error_message);
void	exit_with_error_message(t_error_types message_type,  char *error_content);

#endif

