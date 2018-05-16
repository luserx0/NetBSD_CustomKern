/*-
 * Copyright (c) 2018 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <sys/cdefs.h>
//__KERNEL_RCSID(0, "dunno what to put here");

#include <sys/param.h>
#include <sys/device.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/cprng.h>
#include <sys/kmem.h>
#include <sys/systm.h>
#include <sys/types.h>


/*
 * Create a device /dev/panic from which you can read sequential
 * user input.
 *
 * To use this device you need to do:
 *      mknod /dev/panic c 210 0
 *
 * TODO: Add description of what the module does
 *
 *
 */

// TODO: * Remove comments made for you,
//       * read coding_style for kernel and fix indentation etc.


dev_type_open(panic_string_open);
dev_type_close(panic_string_close);
dev_type_read(panic_string_read);
dev_type_write(panic_string_write);

static struct cdevsw panic_string_cdevsw = {
    .d_open = panic_string_open,
    .d_close = panic_string_close,
    .d_read = panic_string_read,
    .d_write = panic_string_write,
    .d_ioctl = noioctl,
    .d_stop = nostop,
    .d_tty = notty,
    .d_poll = nopoll,
    .d_mmap = nommap,
    .d_kqfilter = nokqfilter,
    .d_discard = nodiscard,
    .d_flag = D_OTHER
};

static struct panic_string_softc {
    char *buf;
    size_t buf_len;
} sc;

int
panic_string_open(dev_t self __unused, int flag __unused, int mod __unused, struct lwp *l __unused)
{
    return 0;
}

int
panic_string_close(dev_t self __unused, int flag __unused, int mod __unused, struct lwp *l __unused)
{
    return 0;
}

int
panic_string_read(dev_t self __unused, struct uio *uio, int flag __unused)
{
    if (sc.buf == NULL || uio->uio_resid < sc.buf_len)
        return EINVAL;

    uiomove(sc.buf, sc.buf_len, uio);
    //panic("panic string: %s\n", sc.buf);
    printf("panic string: %s\n", sc.buf);
    return 0;
}
/*int
panic_string_write(dev_t self __unused, struct uio *uio, int flag __unused)
{
    if(sc.buf)
        kmem_free(sc.buf, sc.buf_len);
    sc.buf_len = uio->uio_iov->iov_len;
    sc.buf = (char *)kmem_alloc(sc.buf_len, KM_SLEEP);
    uiomove(sc.buf, sc.buf_len, uio);
    printf("panic string: %s\n", sc.buf);
    return 0;
}*/
// BASE MODULE STRUCTURE
// MODULE(class, name, required), defines module's metadata
MODULE(MODULE_CLASS_MISC, panic_string, NULL);


// MODULE_NAME_modcmd: is the function that the kernel calls to report important module-related events, like when the module loads or unloads
static int
panic_string_modcmd(modcmd_t cmd, void *arg __unused)
{
    /* TODO: Add description */
    int cmajor = 210, bmajor = -1;

    switch (cmd) {
    case MODULE_CMD_INIT:
        printf("Example module loaded.\n");
        if (devsw_attach("panic", NULL, &bmajor, &panic_string_cdevsw,
                         &cmajor))
            return ENXIO;
        return 0;

    case MODULE_CMD_FINI:
        printf("Example module unloaded.\n");
        devsw_detach(NULL, &panic_string_cdevsw);
        return 0;
    default:
        return ENOTTY;
    }
}
