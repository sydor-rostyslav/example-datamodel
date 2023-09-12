#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <amxc/amxc.h>
#include <amxp/amxp_signal.h>
#include <amxd/amxd_action.h>
#include <amxm/amxm.h>
#include <amxd/amxd_dm.h>
#include <debug/sahtrace.h>
#include <debug/sahtrace_macros.h>

#include "my_manager_priv.h"

#define ODL_DEFAULTS "?include '${odl.directory}/${name}.odl':'${odl.dm-defaults}';"

typedef struct _my_manager {
    amxd_dm_t* dm;
    amxo_parser_t* parser;
    amxb_bus_ctx_t* ctx;                            // bus context
    bool nm_init;
} my_manager_t;

my_manager_t my_manager;

amxd_dm_t* my_manager_get_dm(void) {
    return my_manager.dm;
}

amxo_parser_t* my_manager_get_parser(void) {
    return my_manager.parser;
}

amxb_bus_ctx_t* my_manager_get_ctx(void) {
    return my_manager.ctx;
}

static int my_manager_init_bus_ctx(void) {
    int status = -1;
    my_manager.ctx = amxb_be_who_has("Obj");
    if(my_manager.ctx != NULL)
        status = 0;

    return status;
}

int my_manager_init(amxd_dm_t* dm, amxo_parser_t* parser) {
    int rv = -1;

    my_manager.dm = dm;
    my_manager.parser = parser;

    rv = my_manager_init_bus_ctx(); // sets my_manager.ctx
    when_failed_trace(rv, exit, ERROR, "Unable to initialise bus context, retval = %d", rv);

    // load the defaults after the configuration module is loaded so the
    // default/saved configuration can be applied at start-up.
    rv = amxo_parser_parse_string(parser, ODL_DEFAULTS, amxd_dm_get_root(dm));
    when_failed_trace(rv, exit, ERROR, "Failed to load the defaults/saves returned error, %d", rv);

exit:
    return rv;
}

void _add_stat(const char* const sig_name,
               const amxc_var_t* const data,
               UNUSED void* const priv) {
//    printf("Signal received - %s\n", sig_name);
    if (strcmp(sig_name, "dm:instance-added") != 0)
        return;

    amxd_object_t *obj = amxd_dm_get_object(my_manager.dm, "Obj.");
    uint32_t stat = amxd_object_get_value(uint32_t, obj, "stat", NULL);
    amxd_object_set_value(uint32_t, obj, "stat", ++stat);
}

void _print_event(const char* const sig_name,
                  const amxc_var_t* const data,
                  UNUSED void* const priv) {
    printf("Signal received - %s\n", sig_name);
    printf("Signal data = \n");
    fflush(stdout);
    if(!amxc_var_is_null(data)) {
        amxc_var_dump(data, STDOUT_FILENO);
    }
}

int _my_manager_main(int reason, amxd_dm_t* dm, amxo_parser_t* parser) {
    int retval = 0;
    switch (reason) {
    case AMXO_START:
        retval = my_manager_init(dm, parser);
        break;
    case AMXO_STOP:
        amxm_close_all();
        break;
    }

    return retval;
}

