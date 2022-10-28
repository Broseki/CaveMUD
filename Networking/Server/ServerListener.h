//
// Created by Travis Canning on 10/16/22.
//

#ifndef CAVEMUD_SERVERLISTENER_H
#define CAVEMUD_SERVERLISTENER_H


#include "../../Utils/Logger/Logger.h"
#include "../../Session/Sessions.h"
#include "ServerSocket.h"

class ServerListener {
public:
    ServerListener(Logger *logger,
                   ServerSocket *server_socket,
                   Configuration *config,
                   Sessions *sessions);
    ~ServerListener();
    void start();
    void stop();

private:
    struct TCPKeepAliveConfig {
        /** The time (in seconds) the connection needs to remain
         * idle before TCP starts sending keepalive probes (TCP_KEEPIDLE socket option)
         */
        int keepidle;
        /** The maximum number of keepalive probes TCP should
         * send before dropping the connection. (TCP_KEEPCNT socket option)
         */
        int keepcnt;

        /** The time (in seconds) between individual keepalive probes.
         *  (TCP_KEEPINTVL socket option)
         */
        int keepintvl;
    };

    const TCPKeepAliveConfig tcpKeepAliveConfig = { 60, 5, 5 };

    Logger *logger;
    ServerSocket *server_socket;
    Configuration *config;
    Sessions *sessions;
    bool stopped;

    bool setSocketNonBlocking(int socket);
    bool setSocketKeepAlive(int socket);

};


#endif //CAVEMUD_SERVERLISTENER_H
