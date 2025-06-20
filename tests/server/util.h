#ifndef HEADER_CURL_SERVER_UTIL_H
#define HEADER_CURL_SERVER_UTIL_H
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
#include "curl_setup.h"

/* adjust for old MSVC */
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#  define snprintf _snprintf
#endif

#ifdef _WIN32
#  define CURL_STRNICMP(p1, p2, n) _strnicmp(p1, p2, n)
#elif defined(HAVE_STRCASECMP)
#  ifdef HAVE_STRINGS_H
#    include <strings.h>
#  endif
#  define CURL_STRNICMP(p1, p2, n) strncasecmp(p1, p2, n)
#elif defined(HAVE_STRCMPI)
#  define CURL_STRNICMP(p1, p2, n) strncmpi(p1, p2, n)
#elif defined(HAVE_STRICMP)
#  define CURL_STRNICMP(p1, p2, n) strnicmp(p1, p2, n)
#else
#  error "missing case insensitive comparison function"
#endif

enum {
  DOCNUMBER_NOTHING    = -7,
  DOCNUMBER_QUIT       = -6,
  DOCNUMBER_BADCONNECT = -5,
  DOCNUMBER_INTERNAL   = -4,
  DOCNUMBER_CONNECT    = -3,
  DOCNUMBER_WERULEZ    = -2,
  DOCNUMBER_404        = -1
};

char *data_to_hex(char *data, size_t len);
void logmsg(const char *msg, ...) CURL_PRINTF(1, 2);
void loghex(unsigned char *buffer, ssize_t len);
unsigned char byteval(char *value);

#define SERVERLOGS_LOCKDIR "lock"  /* within logdir */

/* global variables */
extern const char *srcpath;  /* where to find the 'data' dir */
extern const char *pidname;
extern const char *portname;
extern const char *serverlogfile;  /* log file name */
extern int serverlogslocked;
extern const char *configfile;
extern const char *logdir;
extern char loglockfile[256];
#ifdef USE_IPV6
extern bool use_ipv6;
#endif
extern const char *ipv_inuse;
extern unsigned short server_port;
extern const char *socket_type;
extern int socket_domain;

#ifdef _WIN32
int win32_init(void);
const char *sstrerror(int err);
#else
#define sstrerror(e) strerror(e)
#endif

/* fopens the test case file */
FILE *test2fopen(long testno, const char *logdir);

#include "timeval.h"

int wait_ms(timediff_t timeout_ms);
curl_off_t our_getpid(void);
int write_pidfile(const char *filename);
int write_portfile(const char *filename, int port);
void set_advisor_read_lock(const char *filename);
void clear_advisor_read_lock(const char *filename);

/* global variable which if set indicates that the program should finish */
extern volatile int got_exit_signal;

/* global variable which if set indicates the first signal handled */
extern volatile int exit_signal;

#ifdef _WIN32
/* global event which if set indicates that the program should finish */
extern HANDLE exit_event;
#endif

void install_signal_handlers(bool keep_sigalrm);
void restore_signal_handlers(bool keep_sigalrm);

#include <curl/curl.h> /* for curl_socket_t */

#ifdef USE_UNIX_SOCKETS
#ifdef HAVE_SYS_UN_H
#include <sys/un.h> /* for sockaddr_un */
#endif
int bind_unix_socket(curl_socket_t sock, const char *unix_socket,
                     struct sockaddr_un *sau);
#endif /* USE_UNIX_SOCKETS */

typedef union {
  struct sockaddr      sa;
  struct sockaddr_in   sa4;
#ifdef USE_IPV6
  struct sockaddr_in6  sa6;
#endif
#ifdef USE_UNIX_SOCKETS
  struct sockaddr_un   sau;
#endif
} srvr_sockaddr_union_t;

unsigned short util_ultous(unsigned long ulnum);

#endif  /* HEADER_CURL_SERVER_UTIL_H */
