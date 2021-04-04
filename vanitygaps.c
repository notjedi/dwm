/* Keybind Functions */
static void incrgaps(const Arg *arg);
static void incrogaps(const Arg *arg);
static void incrohgaps(const Arg *arg);
static void incrovgaps(const Arg *arg);
static void togglegaps(const Arg *arg);
static void defaultgaps(const Arg *arg);

/* Layouts */
static void tile(Monitor *);
static void fibonacci(Monitor *m);
static void dwindle(Monitor *m);

/* Internal Functions */
static void getgaps(Monitor *m, int *oh, int *ov, int *in, int *iv, unsigned int *nc);
static void setgaps(int oh, int ov, int ih, int iv);

/* Settings */
static int enablegaps = 1;                    /* enables gaps, used by togglegaps */
static const int smartgaps        = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int gappih  = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv  = 10;       /* vert inner gap between windows */
static const unsigned int gappoh  = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov  = 10;       /* vert outer gap between windows and screen edge */


static void togglegaps(const Arg *arg) {
  enablegaps = !enablegaps;
  arrange(selmon);
}

static void defaultgaps(const Arg *arg) {
  setgaps(gappoh, gappov, gappih, gappiv);
}

static void incrgaps(const Arg *arg) {
  setgaps(selmon->gappoh + arg->i, selmon->gappov + arg->i,
          selmon->gappih + arg->i, selmon->gappiv + arg->i);
}

static void incrogaps(const Arg *arg) {
  setgaps(selmon->gappoh + arg->i, selmon->gappov + arg->i, selmon->gappih,
          selmon->gappiv);
}

static void incrohgaps(const Arg *arg) {
  setgaps(selmon->gappoh + arg->i, selmon->gappov, selmon->gappih,
          selmon->gappiv);
}

static void incrovgaps(const Arg *arg) {
  setgaps(selmon->gappoh, selmon->gappov + arg->i, selmon->gappih,
          selmon->gappiv);
}


static void getgaps(Monitor *m, int *oh, int *ov, int *ih, int *iv,
                    unsigned int *nc) {
  unsigned int n, oe, ie;
#if PERTAG_PATCH
  oe = ie = selmon->pertag->enablegaps[selmon->pertag->curtag];
#else
  oe = ie = enablegaps;
#endif // PERTAG_PATCH
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (smartgaps && n == 1) {
    oe = 0; // outer gaps disabled when only one client
  }

  *oh = m->gappoh * oe; // outer horizontal gap
  *ov = m->gappov * oe; // outer vertical gap
  *ih = m->gappih * ie; // inner horizontal gap
  *iv = m->gappiv * ie; // inner vertical gap
  *nc = n;              // number of clients
}

static void setgaps(int oh, int ov, int ih, int iv) {
  if (oh < 0)
    oh = 0;
  if (ov < 0)
    ov = 0;
  if (ih < 0)
    ih = 0;
  if (iv < 0)
    iv = 0;

  selmon->gappoh = oh;
  selmon->gappov = ov;
  selmon->gappih = ih;
  selmon->gappiv = iv;
  arrange(selmon);
}

/* Layouts */

static void tile(Monitor *m) {
  unsigned int i, n, h, r, oe = enablegaps, ie = enablegaps, mw, my, ty;
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (n == 0)
    return;

  if (smartgaps == n) {
    oe = 0; // outer gaps disabled
  }

  if (n > m->nmaster)
    mw = m->nmaster ? (m->ww + m->gappiv * ie) * m->mfact : 0;
  else
    mw = m->ww - 2 * m->gappov * oe + m->gappiv * ie;
  for (i = 0, my = ty = m->gappoh * oe, c = nexttiled(m->clients); c;
       c = nexttiled(c->next), i++)
    if (i < m->nmaster) {
      r = MIN(n, m->nmaster) - i;
      h = (m->wh - my - m->gappoh * oe - m->gappih * ie * (r - 1)) / r;
      resize(c, m->wx + m->gappov * oe, m->wy + my,
             mw - (2 * c->bw) - m->gappiv * ie, h - (2 * c->bw), 0);
      my += HEIGHT(c) + m->gappih * ie;
    } else {
      r = n - i;
      h = (m->wh - ty - m->gappoh * oe - m->gappih * ie * (r - 1)) / r;
      resize(c, m->wx + mw + m->gappov * oe, m->wy + ty,
             m->ww - mw - (2 * c->bw) - 2 * m->gappov * oe, h - (2 * c->bw), 0);
      ty += HEIGHT(c) + m->gappih * ie;
    }
}

static void fibonacci(Monitor *m) {
  unsigned int i, n;
  int nx, ny, nw, nh;
  int oh, ov, ih, iv;
  int nv, hrest = 0, wrest = 0, r = 1;
  Client *c;

  getgaps(m, &oh, &ov, &ih, &iv, &n);
  if (n == 0)
    return;

  nx = m->wx + ov;
  ny = m->wy + oh;
  nw = m->ww - 2 * ov;
  nh = m->wh - 2 * oh;

  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
    if (r) {
      if ((i % 2 && (nh - ih) / 2 <= (bh + 2 * c->bw)) ||
          (!(i % 2) && (nw - iv) / 2 <= (bh + 2 * c->bw))) {
        r = 0;
      }
      if (r && i < n - 1) {
        if (i % 2) {
          nv = (nh - ih) / 2;
          hrest = nh - 2 * nv - ih;
          nh = nv;
        } else {
          nv = (nw - iv) / 2;
          wrest = nw - 2 * nv - iv;
          nw = nv;
        }
      }

      if ((i % 4) == 0) {
        ny += nh + ih;
        nh += hrest;
      } else if ((i % 4) == 1) {
        nx += nw + iv;
        nw += wrest;
      } else if ((i % 4) == 2) {
        ny += nh + ih;
        nh += hrest;
        if (i < n - 1)
          nw += wrest;
      } else if ((i % 4) == 3) {
        nx += nw + iv;
        nw -= wrest;
      }
      if (i == 0) {
        if (n != 1) {
          nw = (m->ww - iv - 2 * ov) - (m->ww - iv - 2 * ov) * (1 - m->mfact);
          wrest = 0;
        }
        ny = m->wy + oh;
      } else if (i == 1)
        nw = m->ww - nw - iv - 2 * ov;
      i++;
    }

    resize(c, nx, ny, nw - (2 * c->bw), nh - (2 * c->bw), False);
  }
}

static void dwindle(Monitor *m) { fibonacci(m); }
