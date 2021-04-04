static void shiftview(const Arg *arg);

static void shiftview(const Arg *arg) {

  /* TODO: more elegant way to do this? */
  Arg shift;
  int i = 0, len = LENGTH(tags) - 1;
  unsigned int curtag = selmon->tagset[selmon->seltags], temp = (1 << len),
               seltag = 0, activetagmask = curtag;

  for (Client *c = selmon->clients; c; c = c->next)
    activetagmask |= c->tags;

  /* no other tags active so return */
  if (activetagmask == selmon->tagset[selmon->seltags])
    return;

  if (arg->i > 0) {
    /* moving to next tag */
    for (i = 1; !((curtag << i) & temp); i++) {
      if (activetagmask & (curtag << i))
        break;
    }
    if ((curtag << i) & temp) {
      /* no tags infront of curtag so find the last tag behind it */
      for (i = 0; i <= len; i++) {
        if (activetagmask & (1 << i))
          break;
      }
      seltag = (1 << i);
    } else
      seltag = (curtag << i);
  } else {
    /* moving to prev tag */
    for (i = 1; curtag >> i; i++) {
      if (activetagmask & (curtag >> i))
        break;
    }
    if ((curtag >> i) == 0) {
      /* no tags behind curtag so find the last tag infront of it */
      for (i = len; i >= 0; i--) {
        if (activetagmask & (1 << i))
          break;
      }
      seltag = (1 << i);
    } else
      seltag = (curtag >> i);
  }

  shift.ui = seltag;
  view(&shift);
}
