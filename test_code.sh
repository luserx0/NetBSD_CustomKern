#! /bin/sh
cp /home/pleb/kubsan_fix_and_create.c ./sys/arch/amd64/amd64/kubsan.c
./build.sh -m amd64 -V MKCTF=no -u -U -j4 kernel=GENERIC_KUBSAN

