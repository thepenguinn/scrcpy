#include<stdio.h>
#include "shizuku/shizuku.h"

#include <stdlib.h>

#include "util/file.h"
#include "util/log.h"
#include "util/process_intr.h"
#include "util/str.h" // probably don't need this.

void
shizuku_testing(void) {
	printf("it worked!\n");
}

sc_pid
sc_shizuku_execute(const char *const argv[]) {

    // unsigned process_flags = 0;
    // if (flags & SC_ADB_NO_STDOUT) {
    //     process_flags |= SC_PROCESS_NO_STDOUT;
    // }
    // if (flags & SC_ADB_NO_STDERR) {
    //     process_flags |= SC_PROCESS_NO_STDERR;
    // }

    const char *const *args = argv;

    printf("---------------\n");
    while (*args) {
        printf("%s\n", *args);
        args++;
    }
    printf("---------------\n");

    sc_pid pid;
    enum sc_process_result r =
        sc_process_execute_p(argv, &pid, 0, NULL, NULL, NULL);
    if (r != SC_PROCESS_SUCCESS) {
        // If the execution itself failed (not the command exit code), log the
        // error in all cases
        // show_adb_err_msg(r, argv);
        pid = SC_PROCESS_NONE;
    }

    printf("pid --> %d\n", pid);
    return pid;
}

static bool
process_check_success_internal(sc_pid pid, const char *name, bool close) {

    if (pid == SC_PROCESS_NONE) {
        LOGE("Could not execute \"%s\"", name);
        return false;
    }
    sc_exit_code exit_code = sc_process_wait(pid, close);
    if (exit_code) {
        if (exit_code != SC_EXIT_CODE_NONE) {
            LOGE("\"%s\" returned with value %" SC_PRIexitcode, name,
                 exit_code);
        } else {
            LOGE("\"%s\" exited unexpectedly", name);
        }
        return false;
    }
    return true;
}


static bool
process_check_success_intr(struct sc_intr *intr, sc_pid pid, const char *name) {
    if (intr && !sc_intr_set_process(intr, pid)) {
        // Already interrupted
        return false;
    }

    // Always pass close=false, interrupting would be racy otherwise
    bool ret = process_check_success_internal(pid, name, false);

    if (intr) {
        sc_intr_set_process(intr, SC_PROCESS_NONE);
    }

    // Close separately
    sc_process_close(pid);

    return ret;
}

sc_pid
// sc_shizuku_execute_server(struct sc_server *server, const struct sc_server_params *params) {
sc_shizuku_execute_server(struct sc_intr *intr) {

    const char *const argv[] =
        { "okrish", "/data/local/tmp/scrcpy_start", "app_process", "/", "com.genymobile.scrcpy.Server", "2.1.1", "scid=0000000c", "log_level=info", NULL };
        // { "rish", "/data/local/tmp/scrcpy_start", "echo", "HAI", NULL };

    sc_pid pid = sc_shizuku_execute(argv);

    // sc_process_wait(pid, false); // ignore exit code
    // process_check_success_intr(intr, pid, "okrish");
    return pid;
}

bool
sc_shizuku_push(struct sc_intr *intr, const char *local, const char *remote) {

    printf("local --> %s\n", local);
    printf("remote --> %s\n", remote);

    const char *const argv[] =
        { "rish", "cp", local, remote, NULL };

    sc_pid pid = sc_shizuku_execute(argv);

    return process_check_success_intr(intr, pid, "rish cp");

}
