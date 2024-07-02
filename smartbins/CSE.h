#ifndef CSE_H_
#define CSE_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "discoveryMessage_m.h"
#include "AEMessage_m.h"
#include <list>
#include "utils.h"
#include "types.h"

using namespace omnetpp;

class CSE: public cSimpleModule {

public:
    CSE();
    virtual ~CSE();

    RoutingTable SemanticRoutingTable;

protected:
    // by default in omnet methods
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    // application specific  method
    virtual discoveryMessage *generateMessage(int op_code);
private:

    discoveryMessage *queryMsg;
    discoveryMessage *ResMsg;
    discoveryMessage *NotifMsg;

    int notif;
    bool seenQuery(discoveryMessage *msg);
    // application specific for exploring and updating the local database
    URI DBLookup(discoveryMessage *msg);
    void localDBLookup(AEMessage *msg);
    void generateDiscoveryMessage(AEMessage *msg);
    void generateResponseMessage(discoveryMessage *discoveryMsg, ResultCode result = ResultCode::SUCCESS);

    // not yet implemented
    // TODO this function organize the map by value-ordering
//    void orderingMap(std::map<int, int>);

    // Routing table update
    void cancelationAndNotification(AEMessage *msg);
    void registrationAndNotification(AEMessage *msg);
    RoutingEntry mustGetRoutingEntry(std::string feature_type);
    void registerAE(std::string feature_type, URI uri);
    void deregisterAE(std::string feature_type, URI uri);
    void updatingRoutingTableAndNotify(discoveryMessage *msg);
    void notifyCSE(std::string feature_type, int delta);
    void notifyNeighbors(discoveryMessage *msg);
    bool multicast(std::string gateName, discoveryMessage *msg, int maxMessages = INT_MAX);
    void broadcast(std::string gateName, discoveryMessage *msg);
    // Save AE data
//    void saveAEData(std::string feature_type, URI uri, int data);

    //Messages handling
    void handleAEMessage(cMessage *msg);
    void handleDiscoveryMessage(cMessage *msg);
    void handleQuery(discoveryMessage *msg);
    void fallbackRouteQuery(discoveryMessage *msg);
    void processQuery(discoveryMessage *msg);
    void returnResponse(discoveryMessage * msg);
//    std::vector<URI> routeQuery(discoveryMessage *msg);
//    std::vector<URI> UpdateBucket(discoveryMessage*msg);

    std::map<URI, std::tuple<int, simtime_t, int>> schedulerMap;

    GateMapping Gates;

    URI Uri;

    // How many times to retransmit `Notify`
    int NotificationDepth;

    // Alpha - is the multicast parameter for customer;
    int multicastAlpha;
    // Beta - is the multicast parameter for provider
    int multicastBeta;
    // Gamma - is the multicast parameter for sibling
    int multicastGamma;
    // Delta - is the multicast parameter for peer
    int multicastDelta;

    // Max hops for message/query
    int maxHops;

    simtime_t queryBufferTTL;

    std::map<queryKey, int64_t> processedQueries;

    simtime_t delay;

};
Define_Module(CSE);

#endif
