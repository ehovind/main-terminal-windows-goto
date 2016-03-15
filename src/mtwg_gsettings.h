#include <stdlib.h>
#include <gio/gio.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include "debug.h"

int map_key(int mapping, unsigned long xid);
void construct_command(char * command, unsigned long xid);
void check_keybinding(const gchar * path);
void check_key_range(GVariant * value);

#define SCHEMA_PARENT "org.gnome.settings-daemon.plugins.media-keys"
#define SCHEMA "org.gnome.settings-daemon.plugins.media-keys.custom-keybinding"
#define PATH_REMOTE "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/"
#define PATH_CODE "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom1/"
#define COMMAND_SZ 64
#define COMMAND_KEY "command"
