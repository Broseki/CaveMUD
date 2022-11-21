//
// Created by Travis Canning on 11/20/22.
//

#include "InterruptProcess.h"
#include "../../../../Session/KV_Keys.h"

void InterruptProcess::handleCommand(Logger *logger, Configuration *config, std::shared_ptr<Session> session) {
    logger->log(Logger::DEBUG, "InterruptProcess::handleCommand");
    session->set_kv(SESSION_KV_INTERRUPT_FLAG, true);
}
