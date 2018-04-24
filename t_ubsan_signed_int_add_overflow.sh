# Copyright (c) 2018 The NetBSD Foundation, Inc.
# All rights reserved.
#
# This code is derived from software contributed to The NetBSD Foundation
# by Harry Pantazis.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

test_target()
{
	SUPPORT='n'
	if ! echo __GNUC__ | cc -E - | grep -q __GNUC__; then 
		SUPPORT='y'
	fi

	if ! echo __clang__ | cc -E - | grep -q __clang__; then 
		SUPPORT='y'
	fi
}

atf_test_case int_add_overflow
int_add_overflow_head() {
	atf_set "descr" "Test Undefined Behavior for int addition overflows"
	atf_set "require.progs" "cc"
}

atf_test_case int_add_overflow_profile
int_add_overflow_profile_head() {
	atf_set "descr" "Test Undefined Behavior for int addition overflows with profiling option"
	atf_set "require.progs" "cc"
}
atf_test_case int_add_overflow_pic
int_add_overflow_pic_head() {
	atf_set "descr" "Test Undefined Behavior for int addition overflows with position independent code (PIC) flag"
	atf_set "require.progs" "cc"
}
atf_test_case int_add_overflow_pie
int_add_overflow_pie_head() {
	atf_set "descr" "Test Undefined Behavior for int addition overflows with position independent execution (PIE) flag"
	atf_set "require.progs" "cc"
}
atf_test_case int_add_overflow32
int_add_overflow32_head() {
	atf_set "descr" "Test Undefined Behavior for int addition overflows in NetBSD_32 emulation"
	atf_set "require.progs" "cc file diff cat"
}


int_add_overflow_body(){
	cat > test.c << EOF
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char **argv) { int l = INT_MAX; l+= argc; printf("CHECK\n"); exit(0); }
EOF

	cc -fsanitize=undefined -o test test.c 
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test
}

int_add_overflow_profile_body(){
	cat > test.c << EOF
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char **argv) { int l = INT_MAX; l+= argc; printf("CHECK\n"); exit(0); }
EOF

	cc -fsanitize=undefined -o test -pg test.c 
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test
}

int_add_overflow_pic_body(){
	cat > test.c << EOF
#include "stdio.h"
#include "stdlib.h"
void help(int);
int main(int argc, char **argv) { help(argc); printf("CHECK\n"); exit(0); }
EOF

	cat > pic.c << EOF
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
void help(int count) { int l = INT_MAX; l+= count; }
EOF

	cc -fsanitize=undefined -fPIC -shared -o libtest.so pic.c
	cc -o test test.c -fsanitize=undefined -L -ltest

	export LD_LIBRARY_PATH=.
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test
}

int_add_overflow_pie_body(){
	
	#check whether -pie flag is supported on this architecture
	if ! cc -pie -dM -E - < /dev/null 3>/dev/null >/dev/null; then 
		atf_set_skip "cc -pie not supported on this architecture"
	fi
	cat > test.c << EOF
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char **argv) { int l = INT_MAX; l+= argc; printf("CHECK\n"); exit(0); }
EOF

	cc -fsanitize=undefined -o test -fpie -pie test.c 
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test
}


int_add_overflow32_body(){
	
	# check what this architecture is, after all
	if ! cc -dM -E - < /dev/null | grep -F -q _LP64; then
		atf_skip "This is not a 64 bit architecture"
	fi
	if ! cc -m32 -dM -E - < /dev/null 3>/dev/null > ./def32; then
		atf_skip "cc -m32 Not supported on this architecture"
	else
		if grep -F -q _LP64 ./def32; then
		atf_fail "cc -m32 Does not generate NetBSD32 binaries"
		fi
	fi

	cat > test.c << EOF
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char **argv) { int l = INT_MAX; l+= argc; printf("CHECK\n"); exit(0); }
EOF

	cc -fsanitize=address -o df32 -m32 test.c
	cc -fsanitize=address -o df64 test.c
	file -b ./df32 > ./ftype32
	file -b ./df64 > ./ftype64
	if diff ./ftype32 ./ftype64 >/dev/null; then
		atf_fail "Generated binz ain't no different"
	fi
	echo "32bit Binz on this platform are:"
	cat ./ftype32
	echo "64bit Binz are on the other hand:"
	cat ./ftype64
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test

	# Another test with profile 32bit binaries, just to make sure everything has been thoroughly done
	cat > test.c << EOF
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char **argv) { int l = INT_MAX; l+= argc; printf("CHECK\n"); exit(0); }
EOF

	cc -fsanitize=undefined -pg -m32 -o test test.c
	atf_check -s not-exit:0 -o not-match:"CHECK\n" -e match:"int-add-overflow" ./test
}

atf_test_case target_not_supported
target_not_supported_head()
{
	atf_set "descr" "Test forced skip"
}




atf_init_test_cases()
{
	test_target
	test $SUPPORT = 'n' && {
		atf_add_test_case target_not_supported
		return 0
	}
	atf_add_test_case int_add_overflow
	atf_add_test_case int_add_overflow_profile
	atf_add_test_case int_add_overflow_pie
	atf_add_test_case int_add_overflow_pic
	atf_add_test_case int_add_overflow32
}
