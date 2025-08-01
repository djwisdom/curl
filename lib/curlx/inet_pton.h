#ifndef HEADER_CURL_INET_PTON_H
#define HEADER_CURL_INET_PTON_H
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

#include "../curl_setup.h"

#ifdef HAVE_INET_PTON
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifndef _WIN32
#include <sys/socket.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef __AMIGA__
#define curlx_inet_pton(x,y,z) inet_pton(x,(unsigned char *)CURL_UNCONST(y),z)
#else
#define curlx_inet_pton(x,y,z) inet_pton(x,y,z)
#endif
#else
int curlx_inet_pton(int, const char *, void *);
#endif /* HAVE_INET_PTON */

#endif /* HEADER_CURL_INET_PTON_H */
