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
//__KERNEL_RCSID(0, "");

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
#include <sys/filedesc.h>

/* Export symbols for UBSan
 * !Currently dummy functions!
 */


#ifndef _LIB_UBSAN_H
#define _LIB_UBSAN_H

enum {
	type_kind_int = 0,
	type_kind_float = 1,
	type_unknown = 0xffff
};

struct type_descriptor {
	uint16_t type_kind;
	uint16_t type_info;
	char type_name[1];
};

struct source_location {
	const char *file_name;
	union {
		unsigned long reported;
		struct {
			uint32_t line;
			uint32_t column;
		};
	};
};

struct overflow_data {
	struct source_location location;
	struct type_descriptor *type;
};

struct type_mismatch_data {
	struct source_location location;
	struct type_descriptor *type;
	unsigned long alignment;
	unsigned char type_check_kind;
};

struct type_mismatch_data_v1 {
	struct source_location location;
	struct type_descriptor *type;
	unsigned char log_alignment;
	unsigned char type_check_kind;
};

struct type_mismatch_data_common {
	struct source_location *location;
	struct type_descriptor *type;
	unsigned long alignment;
	unsigned char type_check_kind;
};

struct nonnull_arg_data {
	struct source_location location;
	struct source_location attr_location;
	int arg_index;
};

struct vla_bound_data {
	struct source_location location;
	struct type_descriptor *type;
};

struct out_of_bounds_data {
	struct source_location location;
	struct type_descriptor *array_type;
	struct type_descriptor *index_type;
};

struct shift_out_of_bounds_data {
	struct source_location location;
	struct type_descriptor *lhs_type;
	struct type_descriptor *rhs_type;
};

struct unreachable_data {
	struct source_location location;
};

struct invalid_value_data {
	struct source_location location;
	struct type_descriptor *type;
};

#if defined(CONFIG_ARCH_SUPPORTS_INT128) && defined(__SIZEOF_INT128__)
typedef __int128 s_max;
typedef unsigned __int128 u_max;
#else
typedef int64_t s_max;
typedef uint64_t u_max;
#endif

#endif

/* Declaration */
void __ubsan_handle_add_overflow(struct overflow_data *, unsigned long, unsigned long);
/* Definition */
void __ubsan_handle_add_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_sub_overflow(struct overflow_data *, unsigned long, unsigned long);
/* Definition */
void __ubsan_handle_sub_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_mul_overflow(struct overflow_data *, unsigned long, unsigned long);
/* Definition */
void __ubsan_handle_mul_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_negate_overflow(struct overflow_data *, unsigned long);
/* Definition */
void __ubsan_handle_negate_overflow(struct overflow_data *data,
				unsigned long old_val)
{}

/* Declaration */
void __ubsan_handle_divrem_overflow(struct overflow_data *, unsigned long, unsigned long);
/* Definition */
void __ubsan_handle_divrem_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_type_mismatch(struct type_mismatch_data *, unsigned long);
/* Definition */
void __ubsan_handle_type_mismatch(struct type_mismatch_data *data,
				unsigned long ptr)
{}

/* Declaration */
void __ubsan_handle_type_mismatch_v1(struct type_mismatch_data_v1 *, unsigned long);
/* Definition */
void __ubsan_handle_type_mismatch_v1(struct type_mismatch_data_v1 *data,
				unsigned long ptr)
{}

/* Declaration */
void __ubsan_handle_vla_bound_not_positive(struct vla_bound_data *, unsigned long);
/* Definition */
void __ubsan_handle_vla_bound_not_positive(struct vla_bound_data *data,
					unsigned long bound)
{}

/* Declaration */
void __ubsan_handle_out_of_bounds(struct out_of_bounds_data *, unsigned long);
/* Definition */
void __ubsan_handle_out_of_bounds(struct out_of_bounds_data *data,
				unsigned long index)
{}

/* Declaration */
void __ubsan_handle_shift_out_of_bounds(struct shift_out_of_bounds_data *, unsigned long, unsigned long);
/* Definition */
void __ubsan_handle_shift_out_of_bounds(struct shift_out_of_bounds_data *data,
					unsigned long lhs, unsigned long rhs)
{}

/*
void __noreturn
__ubsan_handle_builtin_unreachable(struct unreachable_data *data);
void __noreturn
__ubsan_handle_builtin_unreachable(struct unreachable_data *data)
{}
*/

/* Declaration */
void __ubsan_handle_load_invalid_value(struct invalid_value_data *, unsigned long);
/* Definition */
void __ubsan_handle_load_invalid_value(struct invalid_value_data *data,
				unsigned long val)
{}

MODULE(MODULE_CLASS_MISC, ubsan, NULL);

static int
ubsan_modcmd(modcmd_t cmd, void *arg)
{
        switch(cmd) {
        case MODULE_CMD_INIT:
                printf("UBSan symbols declared!\n");
                break;
        case MODULE_CMD_FINI:
                printf("UBSan symbols unloaded!\n");
                break;
        case MODULE_CMD_STAT:
                printf("Example module status queried.\n");
                break;
        default:
                return ENOTTY;
        }
        return 0;
}
