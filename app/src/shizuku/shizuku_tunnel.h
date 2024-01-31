#include <stdbool.h>
#include <stdint.h>

#include "options.h"
#include "util/intr.h"
#include "util/net.h"
#include "adb/adb_tunnel.h"

bool
sc_shizuku_tunnel_open(struct sc_adb_tunnel *tunnel,
                       struct sc_intr *intr,
                       const char *device_socket_name);
