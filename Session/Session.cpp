//
// Created by Travis Canning on 10/16/22.
//

#include "Session.h"

Session::Session(int socketfd) {
    this->socketfd = socketfd;
}

int Session::get_socketfd() {
    return this->socketfd;
}
