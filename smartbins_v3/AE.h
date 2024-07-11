#ifndef AE_H_

#define AE_H_

#include "AEMessage_m.h"
#include "types.h"
#include "utils.h"
#include <omnetpp.h>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace omnetpp;

class AE : public cSimpleModule {
public:
  AE();
  virtual ~AE();

  BinLevelTable BinLevelDatabase;

protected:
  virtual void initialize(int stage) override;
  virtual void handleMessage(cMessage *msg) override;

  // application specific
  virtual int numInitStages() const;
  // virtual void finish() override;
  void sendAEMessage(int op_code);
  void registration();
  void deregistration();
  void sendUpdate();
  void sendQuery();
  void sendSubscribe();
  void updateData();

  // smartbin specific
  double getWasteDisposalRate(simtime_t currentTime);

private:
  AEMessage *canMsg;
  AEMessage *regMsg;
  AEMessage *queryMsg;
  AEMessage *updateMsg;
  AEMessage *subscribeMsg;

  cMessage *event = nullptr;

  long numOfFound;
  int queryIndex;
  int updateIndex;
  int URI;
  int data;
  int maxHop;

  int aeType;
  int queryType;
  std::vector<std::string> feature_types{"smartBin", "smartTruck",
                                         "smartWarehouse"};
  std::string feature_type;
  std::string query_feature_type;
};

Define_Module(AE);

#endif
