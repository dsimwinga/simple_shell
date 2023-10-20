#include "shell.h"

/**
 * _strncpy - Copies a string with a maximum length.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t a;
	char *dest_start = dest;

	for (a = 0; a < n && src[a] != '\0'; a++)
		dest[a] = src[a];
	while (a < n)
	{
		dest[a] = '\0';
		a++;
	}
	return dest_start;
}

/**
 * _strncat - Concatenates two strings with a maximum length.
 * @dest: The destination string.
 * @src: The source string to be appended.
 * @n: The maximum number of characters to use.
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t a;
	char *dest_start = dest;

	for (a = 0; a < n && src[a] != '\0'; a++)
		dest[dest_len + a] = src[a];
	dest[dest_len + a] = '\0';

	return dest_start;
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the character or NULL.
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (char *)s;
		s++;
	}
	if (c == '\0')
		return (char *)s;
	return NULL;
}

