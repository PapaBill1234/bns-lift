#!/usr/bin/env python3
"""Write the Task 4 input streams for compare_postofficedaemon.sh.

Usage: python3 -I tools/verify/pod_streams.py [OUT_DIR]   (default build/verify/pod-streams)
Then:  D=<OUT_DIR>; POD_CACHEGATE_STREAM=$D/cachegate.bin POD_AGENT_STREAM=$D/agent.bin \
       POD_WORLD_STREAM=$D/world.bin POD_MANAGE_STREAM=$D/manage.bin tools/verify/compare_postofficedaemon.sh 25 --pktlog
Packet = u16 size (includes the size field), u16 cmd, body. Text packet = u16 wchar count, UTF-16 text.
"""
import os
import struct
import sys


def pkt(body):
    return struct.pack("<h", len(body) + 2) + body


def main():
    out = sys.argv[1] if len(sys.argv) > 1 else "build/verify/pod-streams"
    os.makedirs(out, exist_ok=True)
    streams = {
        # CacheGate HelloOk (cmd 2), HandleCacheGateHelloOk.
        "cachegate.bin": pkt(struct.pack("<h", 2)),
        # Agent HandlePostOfficeHelloReq "hhhhhQ": cmd 1, version 15, agent version 10, economy 10, wid 1, type 0.
        "agent.bin": pkt(struct.pack("<hhhhHB", 1, 15, 10, 10, 1, 0)),
        # World HandlePostOfficeServiceHelloReq "hhhhih": cmd 1, version 16, economy 10, wid 1, 127.0.0.1, 20100.
        "world.bin": pkt(struct.pack("<hhhHIH", 1, 16, 10, 1, 0x0100007F, 20100)),
        # Management text command.
        "manage.bin": struct.pack("<h", 5) + "Hello".encode("utf-16-le"),
    }
    for name, data in streams.items():
        with open(os.path.join(out, name), "wb") as f:
            f.write(data)
        print(name, data.hex())


if __name__ == "__main__":
    main()
