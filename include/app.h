#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdbool.h>
#include <netdb.h> //hostent
#include <arpa/inet.h>
#include <stdlib.h> //for exit(0);
#include <string.h>
#include <libssh/libssh.h>

#define IP_BUF_LEN 16
#define VERBOSE_DEBUG false

bool find_raspberry_ip(char *hostname, char *ip);

void free_channel(ssh_channel channel);

void free_session(ssh_session session);

void run_nfc_test_platform(char *u_name, char *h_name, char *psk, char *key, char *ret_string);

#endif 