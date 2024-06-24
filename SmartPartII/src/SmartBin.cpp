#include "SmartBin.h"

Define_Module(SmartBin);

void SmartBin::initialize() {
    fillLevel = uniform(0, 50);  // Initial fill level between 0% and 50%
    latitude = uniform(-90, 90);
    longitude = uniform(-180, 180);
    transmissionInterval = 30;  // Every 30 seconds (simulated hour)
    currentHour = 0;

    wasteDisposalRates = {0.5, 3, 7, 10, 5, 8, 4, 2, 0.5};  // Waste disposal rates for each simulated hour

    scheduleAt(simTime() + transmissionInterval, new cMessage("sendWasteMessage"));
}

void SmartBin::handleMessage(cMessage *msg) {
    if (strcmp(msg->getName(), "sendWasteMessage") == 0) {
        sendWasteMessage();
        updateFillLevel();
        scheduleAt(simTime() + transmissionInterval, msg);
    } else {
        delete msg;
    }
}

void SmartBin::sendWasteMessage() {
    if (fillLevel >= 90) {  // Send message if fill level is 90% or more
        WasteMessage *wm = new WasteMessage("wasteMessage");
        wm->setBinId(getIndex());
        wm->setFillLevel(fillLevel);
        wm->setLatitude(latitude);
        wm->setLongitude(longitude);
        send(wm, "truck$o");
        EV << "Bin " << getIndex() << " is full and requesting pickup.\n";  // Debug message
    }
}

void SmartBin::updateFillLevel() {
    // Update the fill level based on the waste disposal rate for the current hour
    fillLevel += wasteDisposalRates[currentHour];
    if (fillLevel > 100) fillLevel = 100;

    // Move to the next hour
    currentHour = (currentHour + 1) % wasteDisposalRates.size();
    EV << "Bin " << getIndex() << " fill level: " << fillLevel << "%\n";  // Debug message
}
