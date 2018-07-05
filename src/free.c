#include "include.h"

/* From ROM - copyrighted by Russ Taylor */

void free_affect(AFFECT_DATA *af)
{
    if (!IS_VALID(af))
        return;

    INVALIDATE(af);
    af->next = affect_free;
    affect_free = af;
}

EXTRA_DESCR_DATA *extra_descr_free;
EXTRA_DESCR_DATA *new_extra_descr(void)
{
    EXTRA_DESCR_DATA *ed;

    if (extra_descr_free == NULL)
        ed = alloc_perm(sizeof(*ed));
    else
    {
        ed = extra_descr_free;
        extra_descr_free = extra_descr_free->next;
    }

    ed->keyword = &str_empty[0];
    ed->description = &str_empty[0];
    VALIDATE(ed);
    return ed;
}

void free_extra_descr(EXTRA_DESCR_DATA *ed)
{
    if (!IS_VALID(ed))
        return;

    free_string(ed->keyword);
    free_string(ed->description);
    INVALIDATE(ed);

    ed->next = extra_descr_free;
    extra_descr_free = ed;
}

/* stuff for recycling affects */
AFFECT_DATA *affect_free;

AFFECT_DATA *new_affect(void)
{
    static AFFECT_DATA af_zero;
    AFFECT_DATA *af;

    if (affect_free == NULL)
        af = alloc_perm(sizeof(*af));
    else
    {
        af = affect_free;
        affect_free = affect_free->next;
    }

    *af = af_zero;


    VALIDATE(af);
    return af;
}

