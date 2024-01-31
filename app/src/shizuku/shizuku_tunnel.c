#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include "util/log.h"
#include "util/net_intr.h"
#include "util/process_intr.h"
#include "shizuku_tunnel.h"

// bool
// sc_shizuku_tunnel_init();

bool
sc_shizuku_tunnel_open(struct sc_adb_tunnel *tunnel,
                       struct sc_intr *intr,
                       const char *device_socket_name) {

    sc_socket server_socket = net_socket_un();
    int ok;

    ok = net_shizuku_listen_intr(intr, server_socket, device_socket_name, 1);

    if (ok) {
        tunnel->server_socket = server_socket;
        return true;
    }

    // probably don't need this.
    if (sc_intr_is_interrupted(intr)) {
        // Stop immediately
        return false;
    }

    return false;
}

// bool
// sc_shizuku_tunnel_close();
