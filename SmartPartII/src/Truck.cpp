#include "Truck.h"

Define_Module(Truck);

void Truck::initialize() {
    capacity = 10;  // Truck can carry waste of 10 bins
    currentLoad = 0;
}

void Truck::handleMessage(cMessage *msg) {
    if (WasteMessage *wm = dynamic_cast<WasteMessage *>(msg)) {
        processWasteMessage(wm);
    } else {
        delete msg;
    }
}

void Truck::processWasteMessage(WasteMessage *wm) {
    if (currentLoad < capacity) {
        assignTruck(wm->getBinId());
        currentLoad++;
    }
    delete wm;
}

void Truck::assignTruck(int binId) {
    TruckMessage *tm = new TruckMessage("truckMessage");
    tm->setTruckId(getIndex());
    tm->setBinId(binId);
    tm->setAccepted(true);
    send(tm, "truck$o");
    EV << "Truck " << getIndex() << " is dispatched to Bin " << binId << ".\n";  // Debug message
}
