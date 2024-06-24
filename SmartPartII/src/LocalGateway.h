#ifndef LOCALGATEWAY_H_
#define LOCALGATEWAY_H_

#include <omnetpp.h>
#include "WasteMessage_m.h"

using namespace omnetpp;

class LocalGateway : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
