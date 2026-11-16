#!/usr/bin/env python3
"""Replay a captured byte stream to a server exe and record the replies.

Use it when the 381 peer set does not speak the 2019 protocol of the exe.
Give the same stream to the original exe and to the lifted exe, then diff the two reply files.

Usage:
  replay.py connect HOST:PORT STREAM OUT [--gap MS] [--wait S] [--hdr N]
      Act as a client (for example a game server that connects to CacheGate public-port).
  replay.py listen  PORT      STREAM OUT [--gap MS] [--wait S] [--hdr N]
      Act as a peer server (for example CacheDaemon). Wait for the exe to connect, then send.

STREAM: raw bytes of one direction of one socket (peer -> exe), for example a capture that
        pkldump.py --bytes -1 shows, saved as binary. "-" = send nothing, only record.
OUT:    text file. One line per received packet: "<ms> <len> <id> <hex>".
--hdr N: packet header for the cut: u16 len + u16 id (N=4, default). The len value counts the
         header too (❓ check with pkldump.py "pkt" kind). N=0: no cut, send and record raw chunks.
--gap MS: delay between sent packets (default 50).
--wait S: time to record after the last send (default 5).
"""
import argparse, socket, struct, sys, time


def cut(data, hdr):
    """Split a stream into packets with a u16 length at offset 0."""
    if hdr == 0:
        return [data] if data else []
    out, i = [], 0
    while i + hdr <= len(data):
        n = struct.unpack_from("<H", data, i)[0]
        if n < hdr or i + n > len(data):
            out.append(data[i:])          # bad length: send the rest raw
            break
        out.append(data[i:i + n])
        i += n
    else:
        if i < len(data):
            out.append(data[i:])
    return out


class Recorder:
    def __init__(self, path, hdr):
        self.f = open(path, "w")
        self.hdr = hdr
        self.buf = b""
        self.t0 = time.monotonic()

    def feed(self, data):
        ms = int((time.monotonic() - self.t0) * 1000)
        if self.hdr == 0:
            self.f.write(f"{ms} {len(data)} - {data.hex()}\n")
            return
        self.buf += data
        while len(self.buf) >= self.hdr:
            n, pid = struct.unpack_from("<HH", self.buf, 0)
            if n < self.hdr:
                self.f.write(f"{ms} {len(self.buf)} bad {self.buf.hex()}\n")
                self.buf = b""
                return
            if len(self.buf) < n:
                return
            self.f.write(f"{ms} {n} {pid} {self.buf[:n].hex()}\n")
            self.buf = self.buf[n:]

    def close(self):
        if self.buf:
            self.f.write(f"- {len(self.buf)} rest {self.buf.hex()}\n")
        self.f.close()


def pump(sock, packets, rec, gap, wait):
    sock.settimeout(0.05)

    def drain(until):
        while time.monotonic() < until:
            try:
                d = sock.recv(65536)
            except socket.timeout:
                continue
            if not d:
                return False
            rec.feed(d)
        return True

    for p in packets:
        sock.sendall(p)
        if not drain(time.monotonic() + gap / 1000.0):
            return
    drain(time.monotonic() + wait)


def main():
    a = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    a.add_argument("mode", choices=["connect", "listen"])
    a.add_argument("addr")
    a.add_argument("stream")
    a.add_argument("out")
    a.add_argument("--gap", type=int, default=50)
    a.add_argument("--wait", type=float, default=5.0)
    a.add_argument("--hdr", type=int, default=4, choices=[0, 4])
    a.add_argument("--accept-timeout", type=float, default=60.0)
    o = a.parse_args()

    data = b"" if o.stream == "-" else open(o.stream, "rb").read()
    packets = cut(data, o.hdr)

    if o.mode == "connect":
        host, port = o.addr.rsplit(":", 1)
        s = socket.create_connection((host, int(port)), timeout=10)
    else:
        ls = socket.socket()
        ls.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        ls.bind(("0.0.0.0", int(o.addr)))
        ls.listen(1)
        ls.settimeout(o.accept_timeout)
        s, peer = ls.accept()
        ls.close()
        print(f"accepted {peer[0]}:{peer[1]}", file=sys.stderr)

    rec = Recorder(o.out, o.hdr)
    try:
        pump(s, packets, rec, o.gap, o.wait)
    finally:
        rec.close()
        s.close()
    print(f"sent {len(packets)} packets, replies in {o.out}", file=sys.stderr)


if __name__ == "__main__":
    main()
