/* code that i borrowed from a guy on reddit. this is way more elegant than what i actually did */
/* https://www.reddit.com/r/suckless/comments/mjuvgc/dwm_a_patch_to_move_to_only_active_tags_nonvacant/gtchw2v */
static void shiftview(const Arg *arg);

static void shiftview(const Arg *arg) {
    Arg shifted;
    Client *c;
    unsigned int tagmask = 0;
    int NUMTAGS = LENGTH(tags);

    for (c = selmon->clients; c; c = c->next) {
        if (strcmp(c->name, scratchpadname))
            tagmask |= c->tags;
    }

    shifted.ui = selmon->tagset[selmon->seltags];
    if (arg->i > 0) // left circular shift
        do {
            shifted.ui =
                (shifted.ui << arg->i) | (shifted.ui >> (NUMTAGS - arg->i));
        } while (tagmask && !(shifted.ui & tagmask));
    else // right circular shift
        do {
            shifted.ui =
                (shifted.ui >> -arg->i) | (shifted.ui << (NUMTAGS + arg->i));
        } while (tagmask && !(shifted.ui & tagmask));

    view(&shifted);
}
