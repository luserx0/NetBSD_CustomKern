.include "../Makefile.inc"

#S?=	/root/lx0_fork/sys

KMOD=	panic_string
SRCS=	panic_string.c

.include <bsd.kmodule.mk>
