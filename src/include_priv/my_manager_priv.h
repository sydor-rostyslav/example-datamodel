#if !defined(__TR_MY_PRIV_H__)
#define __TR_MY_PRIV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <amxc/amxc_macros.h>
#include <amxc/amxc.h>
#include <amxp/amxp_signal.h>
#include <amxd/amxd_types.h>
#include <amxd/amxd_transaction.h>
#include "amxd/amxd_dm.h"
#include "amxd/amxd_object.h"
#include <amxo/amxo.h>
#include <amxp/amxp_slot.h>
#include <amxb/amxb.h>
#include <debug/sahtrace.h>
#include <debug/sahtrace_macros.h>

#define ME my_manager

int _my_manager_main(int reason, amxd_dm_t* dm, amxo_parser_t* parser);

int my_manager_init(amxd_dm_t* dm, amxo_parser_t* parser);
amxd_dm_t* my_manager_get_dm(void);
amxo_parser_t* my_manager_get_parser(void);
amxb_bus_ctx_t* my_manager_get_ctx(void);

/* Debugging Event Printer */
void _print_event(const char* const sig_name,
                  const amxc_var_t* const data,
                  void* const priv);

void _add_stat(const char* const sig_name,
                  const amxc_var_t* const data,
                  void* const priv);

#ifdef __cplusplus
}
#endif

#endif // __TR_MY_PRIV_H__
