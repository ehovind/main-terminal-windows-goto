#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libwnck/libwnck.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>
#include "mtwg_gsettings.h"
#include "debug.h"

enum mapping { remote = 0, code = 1 };

void activate_main_terminal(unsigned long xid, WnckScreen * screen);
void list_windows(WnckScreen * screen);
unsigned long parse_xid(char * xid);

#define VERSION "0.8.0"
