// sc_shizuku_get_executable(void)

// sc_pid
// sc_shizuku_execute(const char *const argv[], unsigned flags) {
//     return sc_adb_execute_p(argv, flags, NULL);
// }
//
//
// bool
// sc_shizuku_start_server(struct sc_intr *intr, unsigned flags) {
//     const char *const argv[] = SC_ADB_COMMAND("start-server");
//
//     sc_pid pid = sc__execute(argv, flags);
//     return process_check_success_intr(intr, pid, "adb start-server", flags);
// }
#include<stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#include "util/intr.h"

void shizuku_testing(void);

bool
sc_shizuku_push(struct sc_intr *intr, const char *local, const char *remote);

sc_pid
sc_shizuku_execute(const char *const argv[]);

sc_pid
sc_shizuku_execute_server(struct sc_intr *intr);
