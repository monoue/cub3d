#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int	main() // endline = 313
{
////////////////////////////////
//         ft_memset          //
////////////////////////////////

	// char	b1[20];
	// char	b2[20];

	// memset(b1, 'B', 10);
	// ft_memset(b2, 'B', 10);

	// memset(b1, 'A', 5);
	// ft_memset(b2, 'A', 5);
	// printf("%s\n", b1);
	// printf("%s\n", b2);
	// // memset end


////////////////////////////////
//         ft_bzero           //
////////////////////////////////

	// char	str[20];
	// char	str2[20];

	// memset(str, 'a', 20);
	// memset(str2, 'a', 20);

	// bzero(str, 20);
	// ft_bzero(str2, 20);
	// printf("%s\n", str);
	// printf("%s\n", str2);
	// printf("%d\n", strncmp(str, str2, 20));


////////////////////////////////
//         ft_memcpy          //
////////////////////////////////

	// char	src[] = "memcpy test";
	// char	buff1[20];
	// char	buff2[20];

	// memcpy(buff1, src, 20);
	// ft_memcpy(buff2, src, 20);
	// printf("%s\n", buff1);
	// printf("%s\n", buff2);
	// printf("%d\n", strncmp(buff1, buff2, 20));


////////////////////////////////
//         ft_memccpy         //
////////////////////////////////

	// char	src[] = "memccpy test";
	// char	buff1[20];
	// char	buff2[20];

	// bzero(buff1, 20);
	// bzero(buff2, 20);

	// memccpy(buff1, src, 'c', 6);
	// ft_memccpy(buff2, src, 'c', 6);
	// printf("%s\n", buff1);
	// printf("%s\n", buff2);
	// printf("%d\n", memcmp(buff1, buff2, 6));


////////////////////////////////
//         ft_memmove         //
////////////////////////////////

	// char	*src = "memmove test \r\n";
	// char	dst1[0xF0];
	// char	dst2[0xF0];
	// int		size = strlen(src);

	// memmove(dst1, src, size);
	// ft_memmove(dst2, src, size);
	// printf("%s\n", dst1);
	// printf("%s\n", dst2);
	// printf("%d\n", memcmp(dst1, dst2, size));


////////////////////////////////
//         ft_memchr          //
////////////////////////////////

	// char			*src = "/|\x12\xff\x09\x42\042\42|\\";
	// int				size = 10;

	// char	*str1 = memchr(src, '\x42', size);
	// char	*str2 = ft_memchr(src, '\x42', size);
	// printf("%s\n", str1);
	// printf("%s\n", str2);
	// printf("%d\n", str1 == str2);


////////////////////////////////
//         ft_memcmp          //
////////////////////////////////

	// char	*s1 = "\xff\xaa\xde\x12MACOSX";
	// char	*s2 = "\xff\xaa\xde\x12MACOSX";
	// size_t	size = 10;

	// int		i1 = memcmp(s1, s2, size);
	// int		i2 = ft_memcmp(s1, s2, size);
	// printf("%d\n", i1);
	// printf("%d\n", i2);


////////////////////////////////
//         ft_strlen          //
////////////////////////////////

	// int		r1;
	// int		r2;
	// char	*str = "strlen test";

	// r1 = strlen(str);
	// r2 = ft_strlen(str);
	// printf("%d\n", r1);
	// printf("%d\n", r2);


////////////////////////////////
//         ft_strdup          //
////////////////////////////////

	// char 	*str;
	// char	*tmp = "strdup \0 test";

	// str = ft_strdup(tmp);
	// printf("%s\n", str);
	// printf("%s\n", tmp);
	// printf("%d\n", strncmp(str, tmp, strlen(str)));


////////////////////////////////
//         ft_calloc          //
////////////////////////////////

	// char	*ptr;

	// ptr = ft_calloc(4, 20);
	// printf("%d\n", ptr == NULL);


////////////////////////////////
//         ft_strlcat         //
////////////////////////////////

	// char	buff1[13] = "strlcat ";
	// char	buff2[13] = "strlcat ";
	// char	*src = "test";
	// size_t	max = strlen(src) + strlen(buff1);
	// printf("dest: %zu\n", ft_strlen(buff1));
	// printf("src: %zu\n", ft_strlen(src));
	// printf("dest + src: %zu\n", max);
	// printf("%zu\n", ft_strlcat(buff1, src, 13));
	// printf("%zu\n", ft_strlcat(buff2, src, 13));
	// printf("%s\n", buff1);
	// printf("%s\n", buff2);


////////////////////////////////
//         ft_strchr          //
////////////////////////////////

	// char	*src = "strchr test";

	// char	*d1 = strchr(src, ' ');
	// char	*d2 = ft_strchr(src, ' ');
	// printf("%s\n", d1);
	// printf("%s\n", d2);


////////////////////////////////
//         ft_strrchr         //
////////////////////////////////

	// char	*src = "strchr test";

	// char	*d1 = strrchr(src, ' ');
	// char	*d2 = ft_strrchr(src, ' ');
	// printf("%s\n", d1);
	// printf("%s\n", d2);


////////////////////////////////
//         ft_strnstr         //
////////////////////////////////

	// char	*s1 = "strnstr test";
	// char	*s2 = "nstr";
	// size_t	max = strlen(s1);

	// char	*i1 = strnstr(s1, s2, max);
	// char	*i2 = ft_strnstr(s1, s2, max);
	// printf("%s\n", i1);
	// printf("%s\n", i2);


////////////////////////////////
//         ft_strncmp         //
////////////////////////////////

	// char	*s1 = "abcdefg";
	// char	*s2 = "abcDefg";
	// size_t	size = strlen(s1);

	// int		i1 = strncmp(s1, s2, size);
	// int		i2 = ft_strncmp(s1, s2, size);
	// printf("%d\n", i1);
	// printf("%d\n", i2);


////////////////////////////////
//         ft_atoi            //
////////////////////////////////


	// char	*n = "945";

	// int		i1 = atoi(n);
	// int		i2 = ft_atoi(n);
	// printf("%d\n", i1);
	// printf("%d\n", i2);


////////////////////////////////
//         ft_isalpha         //
////////////////////////////////

	// char c;

	// c = 'Z';
	// printf("%d\n", isalpha(c));
	// printf("%d\n", ft_isalpha(c));


////////////////////////////////
//         ft_isdigit         //
////////////////////////////////

	// char c;

	// c = '5';
	// printf("%d\n", isalpha(c));
	// printf("%d\n", ft_isalpha(c));


////////////////////////////////
//         ft_isalnum         //
////////////////////////////////

	// char c;

	// c = ' ';
	// printf("%d\n", isalnum(c));
	// printf("%d\n", ft_isalnum(c));


////////////////////////////////
//         ft_isascii         //
////////////////////////////////

	// char c;

	// c = ' ';
	// printf("%d\n", isascii(c));
	// printf("%d\n", ft_isascii(c));


////////////////////////////////
//         ft_isprint         //
////////////////////////////////

	// char c;

	// c = ' ';
	// printf("%d\n", isprint(c));
	// printf("%d\n", ft_isprint(c));


////////////////////////////////
//        ft_touupper         //
////////////////////////////////

	// char c;

	// c = 'a';
	// printf("%c\n", toupper(c));
	// printf("%c\n", ft_toupper(c));


////////////////////////////////
//        ft_tolower         //
////////////////////////////////

	// char c;

	// c = 'Z';
	// printf("%c\n", tolower(c));
	// printf("%c\n", ft_tolower(c));
}

////////////////////////////////
//         ft_strmapi         //
////////////////////////////////

// char	f_addi(unsigned i, char c) { return (c + i); }

// int	main()
// {
// 	char	*b = "aaaaaaaaaaa";
// 	char	b2[0xF0];
// 	size_t	size = strlen(b);

// 	for (size_t i = 0; i < size; i++) // 地道に実施した場合
// 		b2[i] = f_addi(i, b[i]);
// 	b2[size] = 0;
// 	char	*ret = ft_strmapi(b, f_addi); // strmapi 使用の場合
// 	printf("%s\n", b2);
// 	printf("%s\n", ret);
// }


////////////////////////////////
//         ft_strjoin         //
////////////////////////////////

// int	main()
// {
// 	char	*s1 = "this is a test case";
// 	char	*s2 = " of ";
// 	char	*s3 = "strjoin";
// 	char	*ans = "this is a test case of strjoin";
// 	char	*res = ft_strjoin(ft_strjoin(s1, s2), s3);
// 	printf("%d\n", strncmp(res, ans, strlen(ans)));
// }


////////////////////////////////
//         ft_strtrim         //
////////////////////////////////

// int	main()
// {
// 	char	*s1 = "   \t  \n\n \t\t  \n\n\nstr \t  trim\n test\n   \n \n \t\t\n  ";
// 	char	*ans = "str \t  trim\n test";
// 	char	*trim_set = " \n\t";
// 	char	*res = ft_strtrim(s1, trim_set);
// 	printf("%s\n", ans);
// 	printf("%s\n", res);
// 	printf("%d\n", ft_strncmp(res, ans, strlen(ans)));
// }


////////////////////////////////
//        ft_split         //
////////////////////////////////

// int main()
// {
// 	char	*str = "xx1xx22xx333xx4444xx";
// 	char	**arrs = ft_split(str, 'x');

// 	for (int i = 0; i < 4; i++)
// 		printf("%s\n", arrs[i]);
// }


////////////////////////////////
//         ft_itoa            //
////////////////////////////////


// int main()
// {
// 	char	*intmax = "2147483647";
// 	char	*intmin = "-2147483648";

// 	if (!(strncmp(intmax, ft_itoa(INT_MAX), strlen(intmax))))
// 		printf("MAX OK\n");
// 	if (!(strncmp(intmin, ft_itoa(INT_MIN), strlen(intmin))))
// 		printf("MIN OK\n");
// }


////////////////////////////////
//       ft_putchar_fd        //
////////////////////////////////

// int main()
// {
// 	ft_putchar_fd('a', 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putchar_fd('Z', 2);
// 	ft_putchar_fd('\n', 2);
// }


////////////////////////////////
//       ft_putstr_fd         //
////////////////////////////////

// int main()
// {
// 	ft_putstr_fd("abcde\n", 1);
// 	ft_putstr_fd("VWXYZ\n", 2);
// }



////////////////////////////////
//       ft_putendl_fd        //
////////////////////////////////

// int main()
// {
// 	ft_putendl_fd("abcde\n", 1);
// 	ft_putendl_fd("VWXYZ\n", 2);
// }


////////////////////////////////
//       ft_putnbr_fd         //
////////////////////////////////

// int main()
// {
// 	ft_putnbr_fd(12345, 1);
// 	ft_putnbr_fd(67890, 2);
// }


////////////////////////////////
//        ft_lstnew           //
////////////////////////////////

// int main()
// {
// 	char	*data = "lstnew test";
// 	t_list	*l = ft_lstnew(data);
// 	printf("%s\n", l->content);
// }



////////////////////////////////
//        ft_lstdelone        //
////////////////////////////////

// int 	flag;

// void	f(void *d)
// {
// 	free(d);
// 	flag = 1;
// }

// t_list	*lstnew(void *d)
// {
// 	t_list *ret = malloc(sizeof(t_list));

// 	if (!ret)
// 		return (NULL);
// 	ret->next = NULL;
// 	ret->content = d;
// 	return (ret);
// }

// int main()
// {
// 	t_list	*l = lstnew(malloc(10));

// 	flag = 0;
// 	ft_lstdelone(l, f);
// 	if (flag)
// 		printf("lstdelone OK\n");
// }


////////////////////////////////
//         ft_lstclear        //
////////////////////////////////

// void	show_list_contents(t_list **top)
// {
// 	t_list	*p = *top;

// 	if (!p)
// 	{
// 		printf("list is null\n");
// 		return ;
// 	}
// 	printf("show list: ");
// 	while (p->next != NULL)
// 	{
// 		printf("%s -> ", (char *)p->content);
// 		p = p->next;
// 	}
// 	printf("%s ", (char *)p->content);
// 	printf("\n");
// }

// int 	flag;

// void	f(void *d)
// {
// 	free(d);
// 	flag = 1;
// }

// int main()
// {
// 	t_list	*l = ft_lstnew(strdup("lstclear"));

// 	l->next = ft_lstnew(strdup("#TEST#"));
// 	ft_lstclear(&l, f);
// 	if (!l)
// 		printf("lstclear OK\n");
// }

////////////////////////////////
//      ft_lstadd_front       //
////////////////////////////////

// int main()
// {
// 	t_list	*l = ft_lstnew(strdup("hogehoge"));
// 	t_list	*n = ft_lstnew(strdup("lstadd_front OK"));

// 	ft_lstadd_front(&l, n);

// 	printf("%d\n", l == n);
// 	printf("%s\n", l->content);
// }


////////////////////////////////
//     ft_lstadd_back        //
////////////////////////////////

// int main()
// {
// 	t_list	*l = ft_lstnew(strdup("fugafuga"));
// 	t_list	*n = ft_lstnew(strdup("lstadd_back OK"));

// 	ft_lstadd_back(&l, n);
// 	printf("%s\n", l->next->content);
// }


////////////////////////////////
//        ft_lstsize          //
////////////////////////////////

// int main()
// {
// 	t_list	*l;

// 	l = ft_lstnew(strdup("a"));
// 	l->next = ft_lstnew(strdup("b"));
// 	l->next->next = ft_lstnew(strdup("c"));
// 	printf("%d\n", ft_lstsize(l));
// }


////////////////////////////////
//        ft_lstlast          //
////////////////////////////////

// int main()
// {
// 	t_list	*l;

// 	l = ft_lstnew(strdup("a"));
// 	l->next = ft_lstnew(strdup("b"));
// 	l->next->next = ft_lstnew(strdup("lstlast OK"));
// 	printf("%s\n", ft_lstlast(l)->content);
// }

// ここからは自分の確認用。レビューでは不要
// // lstdelone start

// void	delete(void *p)
// {
// 	p = NULL;
// }

// int	main()
// {
// 	t_list	*l;

// 	l = ft_lstnew(ft_strdup("abcde"));
// 	printf("%s\n", l->content);
// 	void (* pfunc)(void *);
// 	pfunc = delete;
// 	ft_lstdelone(l, pfunc);
// 	printf("%s\n", l->content);
// }
// // lstdelone end

// // lstclear start
// #include <stdio.h>

// void	delete(void *p)
// {
// 	p = NULL;
// }

// int	main()
// {
// 	t_list	*l;

// 	l = ft_lstnew(ft_strdup("abcde"));
// 	printf("%s\n", l->content);
// 	void (* pfunc)(void *);
// 	pfunc = delete;
// 	ft_lstdelone(l, pfunc);
// 	printf("%s\n", l->content);
// }
// // lstclear end
