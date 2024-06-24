#ifndef AE_H_
#define AE_H_

#include <omnetpp.h>

using namespace omnetpp;

class AE : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif /* AE_H_ */
