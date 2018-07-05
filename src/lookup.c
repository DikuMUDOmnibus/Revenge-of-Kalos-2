#include "include.h"

int liq_lookup (const char *name)
{
    int liq;

    for ( liq = 0; liq_table[liq].liq_name != NULL; liq++)
    {
        if (LOWER(name[0]) == LOWER(liq_table[liq].liq_name[0])
        && !str_prefix(name,liq_table[liq].liq_name))
            return liq;
    }

    return -1;
}
