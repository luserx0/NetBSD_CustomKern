#!/bin/sh

version=7.1.2

cd /root/lx0_fork/tests
#PATH=/public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/:$PATH /public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/nbmake-amd64 $@ clean
PATH=/public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/:$PATH /public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/nbmake-amd64 $@ dependall
PATH=/public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/:$PATH /public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/nbmake-amd64 $@
#PATH=/public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/:$PATH /public/netbsd-root/tooldir.NetBSD-$version-amd64/bin/nbmake-amd64 $@ install
