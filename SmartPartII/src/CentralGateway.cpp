#include "CentralGateway.h"

Define_Module(CentralGateway);

void CentralGateway::initialize() {
    // Initialization code here
    EV << "Central Gateway initialized.\n";  // Debug message
}

void CentralGateway::handleMessage(cMessage *msg) {
    // Forward waste messages to trucks
    send(msg, "truck$o");
    EV << "Central Gateway received a message and forwarded it to trucks.\n";  // Debug message
}
