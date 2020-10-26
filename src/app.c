#include <app.h>

bool find_raspberry_ip(char *hostname, char *ip)
{
    struct hostent *host;
    struct in_addr **addr_list;

    host = gethostbyname(hostname);
    if (host)
    {
        addr_list = (struct in_addr **)host->h_addr_list;
        for (uint8_t i = 0; addr_list[i] != NULL; i++)
        {
            //Return the first one;
            strcpy(ip, inet_ntoa(*addr_list[i]));
            return true;
        }
    }
    return false;
}

void free_channel(ssh_channel channel)
{
    if (channel)
    {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }
}

void free_session(ssh_session session)
{
    if (session)
    {
        ssh_disconnect(session);
        ssh_free(session);
    }
}

void run_nfc_test_platform(char *u_name, char *h_name, char *psk, char *key, char *ret_string)
{
    ssh_session session = NULL;
    ssh_channel channel = NULL;
    int rc = 0, port = 22;
    char ip[IP_BUF_LEN];
    char buffer[1024];
    unsigned int nbytes;

    bzero(buffer, 1024);
    if (find_raspberry_ip(h_name, ip))
    {
        if (VERBOSE_DEBUG)
            printf("Session...\n");
        session = ssh_new();
        if (session != NULL)
        {
            ssh_options_set(session, SSH_OPTIONS_HOST, ip);
            ssh_options_set(session, SSH_OPTIONS_PORT, &port);
            ssh_options_set(session, SSH_OPTIONS_USER, u_name);
            if (VERBOSE_DEBUG)
                printf("Connecting...\n");
            rc = ssh_connect(session);
            if (rc == SSH_OK)
            {
                if (VERBOSE_DEBUG)
                    printf("Password Autentication...\n");
                rc = ssh_userauth_password(session, NULL, psk);
                if (rc == SSH_AUTH_SUCCESS)
                {
                    if (VERBOSE_DEBUG)
                        printf("Channel...\n");
                    channel = ssh_channel_new(session);
                    if (channel != NULL)
                    {
                        if (VERBOSE_DEBUG)
                            printf("Opening...\n");
                        rc = ssh_channel_open_session(channel);
                        if (rc == SSH_OK)
                        {
                            if (VERBOSE_DEBUG)
                                printf("Executing remote command...\n");
                            sprintf(buffer, "Polaric/nfc_test_platform %s", key);
                            rc = ssh_channel_request_exec(channel, buffer);
                            if (rc == SSH_OK)
                            {
                                if (VERBOSE_DEBUG)
                                    printf("Executing remote command success\n");
                                bzero(buffer,sizeof(buffer));
                                rc = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
                                strcpy(ret_string, buffer);
                                goto exit_ret;
                            }
                        }
                    }
                }
            }
        }
    }
    strcpy(ret_string, "ssh_error");
exit_ret:
    free_channel(channel);
    free_session(session);
    return;
}