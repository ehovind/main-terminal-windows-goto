#include "mtwg.h"

int main (int argc, char **argv) {
    WnckScreen *screen;
    enum mapping my_mapping = 0;
    unsigned long xid = 0;

    /* Initialize gdk */
    gdk_init (&argc, &argv);
    screen = wnck_screen_get_default();
    wnck_screen_force_update(screen);

    /* Parse command line options and arguments */
    int index, c;
    opterr = 0;
    while ((c = getopt (argc, argv, "a:lr:c:vh")) != -1) {
        switch (c) {
            case 'l':
                list_windows(screen);
                break;
            case 'a':
                xid = parse_xid(optarg);
                activate_main_terminal(xid, screen);
                break;
            case 'r':
                my_mapping = remote;
                xid = parse_xid(optarg);
                map_key(my_mapping, xid);
                break;
            case 'c':
                my_mapping = code;
                xid = parse_xid(optarg);
                map_key(my_mapping, xid);
                break;
            case 'v':
                fprintf (stdout, "%s version %s\n", argv[0], VERSION);
                break;
            case 'h':
                fprintf(stdout, "Usage: \t%s [-arc] X_WINDOW_ID \n"
                                "  or:  \t%s [-lvh] \n",argv[0], argv[0]);
                fprintf(stdout, "Map key to main terminal windows.\n\n");
                fprintf(stdout, "-a,\t activate window\n"
                                "-r,\t register key for remote terminal\n"
                                "-c,\t register key for code terminal\n"
                                "-l,\t list X windows\n"
                                "-v,\t output version information and exit\n"
                                "-h,\t display this help and exit\n");
                break;
            case '?':
                if (optopt == 'a')
                    fprintf (stderr, "Option -%c requires an argument\n", optopt);
                else if (optopt == 'r')
                    fprintf (stderr, "Option -%c requires an argument\n", optopt);
                else if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n",optopt);
                return 1;
            default:
                abort ();
        }
    }

    for (index = optind; index < argc; index++)
          fprintf (stderr, "Non-option argument %s\n", argv[index]);
}

void activate_main_terminal(unsigned long xid, WnckScreen * screen) {
    GList *window_l;
    WnckWindow * window;
    GdkWindow * root_window = gdk_get_default_root_window();

    debug("Activate terminal window: %ld\n", xid);

    /* Iterate X windows and activate the matching xid */
    for (window_l = wnck_screen_get_windows(screen); window_l != NULL; window_l = window_l->next) {
        if (window_l == NULL) {
            fprintf (stderr, "ERROR: activate_main_terminal(): window_l is NULL\n");
            exit(EXIT_FAILURE);
        }
        window = WNCK_WINDOW (window_l->data);
        if (xid == wnck_window_get_xid(window)) {
            wnck_window_activate(window, gdk_x11_get_server_time(root_window));
        }
    }
}

void list_windows(WnckScreen * screen) {
    GList *window_l;
    WnckWindow * window;

    fprintf(stdout, "=========  ===========================================\n");
    fprintf(stdout, "%-10s %-80s\n", "WINDOW_ID", "Window title");
    fprintf(stdout, "=========  ===========================================\n");
    for (window_l = wnck_screen_get_windows(screen); window_l != NULL; window_l = window_l->next) {
        if (window_l == NULL) {
            fprintf (stderr, "ERROR: list_window(): window_l is NULL\n");
            exit(EXIT_FAILURE);
        }
        window = WNCK_WINDOW(window_l->data);
        fprintf(stdout, "%-10ld %-80s\n", wnck_window_get_xid(window), wnck_window_get_name (window));
    }
}

unsigned long parse_xid(char * xid_text) {
    unsigned long xid = 0;
    char * illegal_chars = xid_text;
    errno = 0;

    /* Convert char * to unsigned long. Store illegal chars and check if any. */
    xid = strtoul(xid_text, &illegal_chars, 10);
    if (errno == ERANGE || (*illegal_chars)) {
        fprintf(stderr, "ERROR: conversion failed, check X_WINDOW_ID input: %s\n", xid_text);
        exit(EXIT_FAILURE);
    }
    return xid;
}

