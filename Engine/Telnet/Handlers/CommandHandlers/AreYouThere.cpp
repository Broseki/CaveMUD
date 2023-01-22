//
// Created by Travis Canning on 11/19/22.
//

#include "AreYouThere.h"
#include "../../../../Session/KV_Keys.h"

void AreYouThere::handleCommand(Logger *logger, Configuration *config, Session* session) {
    logger->log(Logger::DEBUG, "AreYouThere::handleCommand");
    session->set_kv(SESSION_KV_AYT_FLAG, true);
}
