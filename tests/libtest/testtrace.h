#ifndef HEADER_LIBTEST_TESTTRACE_H
#define HEADER_LIBTEST_TESTTRACE_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include "first.h"

void debug_dump(const char *timebuf, const char *text,
                FILE *stream, const unsigned char *ptr,
                size_t size, int nohex);

struct libtest_trace_cfg {
  int tracetime;  /* 0 represents FALSE, anything else TRUE */
  int nohex;      /* 0 represents FALSE, anything else TRUE */
};

extern struct libtest_trace_cfg debug_config;

int libtest_debug_cb(CURL *handle, curl_infotype type,
                     char *data, size_t size, void *userp);

/* callback for CURLOPT_DEBUGFUNCTION (client tests) */
int cli_debug_cb(CURL *handle, curl_infotype type,
                 char *data, size_t size, void *userp);

#endif /* HEADER_LIBTEST_TESTTRACE_H */
