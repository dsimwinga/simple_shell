#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptf: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptf)
{
    if (ptf && *ptf)
    {
        free(*ptf);
        *ptf = NULL;
        return 1;
    }
    return 0;
}

