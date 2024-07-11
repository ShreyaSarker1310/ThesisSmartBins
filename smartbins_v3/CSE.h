#ifndef CSE_H_

#define CSE_H_

#include "AEMessage_m.h"
#include "discoveryMessage_m.h"
#include "types.h"
#include "utils.h"
#include <list>
#include <omnetpp.h>
#include <stdio.h>
#include <string.h>

using namespace omnetpp;

class CSE : public cSimpleModule {
public:
  CSE();
  virtual ~CSE();

  RoutingTable SemanticRoutingTable;
  SubscribeTable SubscribersTable;

protected:
  // default omnet methods
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;

  // application specific method
  virtual discoveryMessage *generateMessage(int op_code);

private:
  discoveryMessage *ResMsg;
  discoveryMessage *queryMsg;
  discoveryMessage *NotifMsg;
  discoveryMessage *updateMsg;

  int notif;
  bool seenQuery(discoveryMessage *msg);

  std::map<URI, std::tuple<int, simtime_t, int>> schedulerMap;
  GateMapping Gates;
  URI Uri;

  int NotificationDepth; // how many times to retransmit 'Notify'
  int multicastAlpha;    // Alpha - is the multicast parameter for customer
  int multicastBeta;     // Beta - is the multicast parameter for provider
  int multicastGamma;    // Gamma - is the multicast parameter for sibling
  int multicastDelta;    // Delta - is the multicast parameter for peer
  int maxHops;           // Max hops for message / query

  simtime_t queryBufferTTL;
  simtime_t delay;
  std::map<queryKey, int64_t> processedQueries;
  std::map<queryKey, int64_t> processedUpdates;

  // application specific for exploring and updating the local database
  URI DBLookup(discoveryMessage *msg);
  void localDBLookup(AEMessage *msg);
  void generateDiscoveryMessage(AEMessage *msg);
  void generateResponseMessage(discoveryMessage *discoveryMsg,
                               ResultCode result = ResultCode::SUCCESS);

  // Routing table update
  void cancelationAndNotification(AEMessage *msg);
  void registrationAndNotification(AEMessage *msg);
  void saveAEData();
  void registerAE(std::string feature_type, URI uri, int data);
  void deregisterAE(std::string feature_type, URI uri);
  void updatingRoutingTableAndNotify(discoveryMessage *msg);
  void notifyCSE(std::string feature_type, int delta);
  void notifyNeighbors(discoveryMessage *msg);
  bool multicast(std::string gateName, discoveryMessage *msg,
                 int maxMessages = INT_MAX);
  void broadcast(std::string gateName, discoveryMessage *msg);

  // Messages handling
  void handleAEMessage(cMessage *msg);
  void handleCSEMessage(cMessage *msg);
  void handleDiscoveryMessage(cMessage *msg);
  void handleQuery(discoveryMessage *msg);
  void fallbackRouteQuery(discoveryMessage *msg);
  void processQuery(discoveryMessage *msg);
  void returnResponse(discoveryMessage *msg);
  void saveAEData(std::string feature_type, URI uri, int data);

  // UPDATE handling
  void updateData(AEMessage *msg);
  void localSubscriberLookup(AEMessage *msg);
  void generateUpdateMessage(AEMessage *msg);
  void processUpdate(discoveryMessage *msg);
  void handleUpdate(discoveryMessage *msg);
  bool seenUpdate(discoveryMessage *msg);
  URI SubscriberLookup(discoveryMessage *msg);
  void registerSubscriber(AEMessage *msg);
};

Define_Module(CSE);

#endif
