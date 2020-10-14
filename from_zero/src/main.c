#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "gnl/get_next_line.h"

int		put_err_msg(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	return (1);
}

#include <string.h>
int	main(int argc, char **argv)
{
	const char	*extension = ".cub";
	const char	*option = "--save";

	if (argc < 2)
		return (put_err_msg("At least one argument needed.\n"));
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], extension, 4) != 0)
		return (put_err_msg(".cub file must be specified.\n"));
	if (argc > 2)
	{
		if (ft_strlen(argv[2]) != ft_strlen(option) || ft_strncmp(argv[2], option, ft_strlen(option)) != 0)
			return (put_err_msg("Invalid option. Option: --save\n"));
		// TODO: save_picture(argv[1]);
	}
	else
		init_everthing(argv[1]);
}