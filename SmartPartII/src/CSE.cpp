#include "CentralGateway.h"

Define_Module(CentralGateway);

void CentralGateway::initialize() {
    // Initialization code here
}

void CentralGateway::handleMessage(cMessage *msg) {
    // Forward waste messages to trucks
    send(msg, "truck$o");
}
