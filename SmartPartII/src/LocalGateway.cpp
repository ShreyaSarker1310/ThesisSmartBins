#include "LocalGateway.h"

Define_Module(LocalGateway);

void LocalGateway::initialize() {
    // Initialization code here
}

void LocalGateway::handleMessage(cMessage *msg) {
    // Forward waste messages to the central gateway
    send(msg, "cse$o");
}
