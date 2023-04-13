#/usr/bin/env bash

set -euo pipefail

[ -f Makedile ] && make maintainer-clean

autoreconf -i

[ -z "${NOCONFIGURE:-}" ] && CFLAGS="-O0 -fdebug-macro -g3" ./configure -q "$@" && make -j
