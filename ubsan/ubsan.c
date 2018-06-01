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
#include <sys/vfs_syscalls.h>
#include <sys/lwp.h>
#include <sys/ctype_bits.h>
#include <sys/ctype_inline.h>

/* Export symbols for UBSan
 * !Currently dummy functions!
 */

/* Declaration */
void __ubsan_handle_add_overflow(struct overflow_data *data, unsigned long lhs, unsigned long rhs);
/* Definition */
void __ubsan_handle_add_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_sub_overflow(struct overflow_data *data, unsigned long lhs, unsigned long rhs);
/* Definition */
void __ubsan_handle_sub_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_mul_overflow(struct overflow_data *data, unsigned long lhs, unsigned long rhs);
/* Definition */
void __ubsan_handle_mul_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_negate_overflow(struct overflow_data *data, unsigned long old_val);
/* Definition */
void __ubsan_handle_negate_overflow(struct overflow_data *data,
				unsigned long old_val)
{}

/* Declaration */
void __ubsan_handle_divrem_overflow(struct overflow_data *data, unsigned long lhs, unsigned long rhs);
/* Definition */
void __ubsan_handle_divrem_overflow(struct overflow_data *data,
				unsigned long lhs,
				unsigned long rhs)
{}

/* Declaration */
void __ubsan_handle_type_mismatch(struct type_mismatch_data *data, unsigned long ptr);
/* Definition */
void __ubsan_handle_type_mismatch(struct type_mismatch_data *data,
				unsigned long ptr)
{}

/* Declaration */
void __ubsan_handle_type_mismatch_v1(struct type_mismatch_data_v1 *data, unsigned long ptr);
/* Definition */
void __ubsan_handle_type_mismatch_v1(struct type_mismatch_data_v1 *data,
				unsigned long ptr)
{}

/* Declaration */
void __ubsan_handle_vla_bound_not_positive(struct vla_bound_data *data, unsigned long bound);
/* Definition */
void __ubsan_handle_vla_bound_not_positive(struct vla_bound_data *data,
					unsigned long bound)
{}

/* Declaration */
void __ubsan_handle_out_of_bounds(struct out_of_bounds_data *data, unsigned long index);
/* Definition */
void __ubsan_handle_out_of_bounds(struct out_of_bounds_data *data,
				unsigned long index)
{}

/* Declaration */
void __ubsan_handle_shift_out_of_bounds(struct shift_out_of_bounds_data *data, unsigned long lhs, unsigned long rhs);
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
void __ubsan_handle_load_invalid_value(struct invalid_value_data *data, unsigned long val);
/* Definition */
void __ubsan_handle_load_invalid_value(struct invalid_value_data *data,
				unsigned long val)
{}

