/* The MIT License (MIT)
 *
 * Copyright (c) 2014 Josef Gajdusek
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

const struct option longopts[] = {
	{ "quiet",		no_argument, NULL, 'q' },
	{ "effective",	no_argument, NULL, 'f' },
	{ "read",		no_argument, NULL, 'r' },
	{ "write",		no_argument, NULL, 'w' },
	{ "execute",	no_argument, NULL, 'x' },
	{ "help",		no_argument, NULL, 'h' },
	{ 0, 0, 0, 0 },
};

void print_usage()
{
	printf(	"Usage: access [OPTIONS].. [FILE]...\n"
			"Lists whether the current user does have specified permissions to the files.\n"
			"The exit code is 0 if all the listed files match the mask.\n"
			"See man 2 access for more details.\n"
			"\n"
			"  -q, --quiet\t\t\tNo output, just the exit code\n"
			"  -e, --effective\t\t\tUse the eacess syscall instead\n"
			"  -r, --read\t\t\tCheck whether the user can read\n"
			"  -w, --write\t\t\tCheck whether the user can write\n"
			"  -x, --execute\t\t\tCheck whether the user can execute\n"
			"  -h, --help\t\t\tDisplay this message\n");
}

int main(int argc, char **argv)
{
	bool quiet_flag = false;
	int opt = 0;
	int mode = 0;
	int i;
	int exit = EXIT_SUCCESS;
	int (*fn)(const char *, int) = access;

	while ((opt = getopt_long(argc, argv, "qfrwxh", longopts, NULL)) != -1) {
		switch (opt) {
			case 'q':
				quiet_flag = true;
				break;
			case 'f':
				fn = eaccess;
				break;
			case 'r':
				mode |= R_OK;
				break;
			case 'w':
				mode |= W_OK;
				break;
			case 'x':
				mode |= X_OK;
				break;
			case '?':
				exit = EXIT_FAILURE;
			case 'h':
				print_usage();
				return exit;
		}
	}

	if (optind == argc) {
		printf("%s: no files specified\n", argv[0]);
		print_usage();
		return EXIT_FAILURE;
	}

	/* If no flags were specified, default to read */
	if (mode == 0) {
		mode = R_OK;
	}

	for (i = optind; i < argc; i++) {
		if (fn(argv[i], mode)) {
			if (!quiet_flag)
				printf("%s no\n", argv[i]);
			exit = EXIT_FAILURE;
		} else {
			if (!quiet_flag)
				printf("%s yes\n", argv[i]);
		}
	}

	return exit;
}
