#include "mtwg_gsettings.h"

int map_key(int mapping, unsigned long xid) {
    setlocale(LC_ALL, "en_US.utf8");
    gchar * freeme = NULL;
    static GSettings * global_settings;
    const gchar * path = NULL;

    if (mapping == 0) {
         path = PATH_REMOTE;
    }
    else {
        path = PATH_CODE;
   }

    /* Check that custom keybinding exists */
    check_keybinding(path);

    /* construct command that actives this window ID */
    char command[COMMAND_SZ];
    construct_command(command, xid);
    debug ("command = %s\n", command);

    /* Create GSettings object */
    global_settings = g_settings_new_with_path (SCHEMA, path);

    /* Check key <command> is writable */
    if (!g_settings_is_writable(global_settings, COMMAND_KEY)) {
        g_printerr ("Key <%s> is not writeable\n", COMMAND_KEY);
        exit(EXIT_FAILURE);
    }

    /* Create key <command> value of type <string> */
    GVariant * g_command = g_variant_new_string (command);

    /* Check new value within range */
    check_key_range(g_command);

    /* Write to schema */
    if (!g_settings_set_value (global_settings, COMMAND_KEY, g_command)) {
        g_printerr ("The key is not writable\n");
        exit (EXIT_FAILURE);
    }
    g_print ("INFO: Schema write done\n");

    g_settings_sync ();
    g_free (freeme);
    return EXIT_SUCCESS;
}

void construct_command(char * command, unsigned long xid) {
    const char * cmd = "mtwg -a ";

    /* Concat command w/option and xid. Exit on failure. */
    int ret = snprintf(command, COMMAND_SZ, "%s%ld", cmd, xid);
    if (ret < 0) {
        fprintf (stderr, "ERROR: constructing <command>: %d\n", ret);
        exit(EXIT_FAILURE);
    }
}

void check_keybinding(const gchar * path) {
    static GSettings * global_settings;
    bool path_keybinding = false;

    global_settings = g_settings_new (SCHEMA_PARENT);
    gchar ** custom_keyb  =  g_settings_get_strv(global_settings, "custom-keybindings");

    /* Check that custom keybindings are registered. */
    gchar ** val;
    for (val = custom_keyb; *val != NULL; val++) {
        if (strcmp(*val, path) == 0) {
            path_keybinding = true;
            break;
        }
    }

    if (!path_keybinding) {
         g_printerr("ERROR: Did not find keybinding. "
                    "Create a custom shortcut: gnome-control-center keyboard\n");
        exit(EXIT_FAILURE);
    }

    g_strfreev(custom_keyb);
}

void check_key_range(GVariant * value) {
    static GSettingsSchemaSource   *global_schema_source;
    static GSettingsSchema * global_schema;
    static GSettingsSchemaKey * global_schema_key;

    global_schema_source = g_settings_schema_source_ref (g_settings_schema_source_get_default ());
    global_schema = g_settings_schema_source_lookup (global_schema_source, SCHEMA, TRUE);
    global_schema_key = g_settings_schema_get_key (global_schema, COMMAND_KEY);

    if (!g_settings_schema_key_range_check (global_schema_key, value)) {
        g_printerr ("The <command> value is outside of the valid range\n");
        g_variant_unref (value);
        exit (EXIT_FAILURE);
    }
}
