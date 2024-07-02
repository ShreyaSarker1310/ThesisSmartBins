#ifndef TYPES_H_
#define TYPES_H_

using namespace omnetpp;


typedef int URI;  // luigi suggestion

typedef std::pair<URI, int> queryKey;

//Routing Entry
/*
 * Routing entry represents single entry in semantic routing table.
 * In contains mappings with number of AEs by link type.
 * */

struct RoutingEntryStruct {
    // URIs of AEs which are directly connected to the CSE.
    std::map<URI,int> database;
    // don't forget to take into account filter criteria
    std::map<URI,int> CSECustomer;
    // key is the CSE_URI Customer
    // value is the number of AE feature type
    // e.g. (URI_CSE,#23),...
    std::map<URI,int> CSEProvider;
    // the same but CSE_URI Providers
    std::map<URI,int> CSESibling;
    // the same but CSE_URI Sibling
    std::map<URI,int> CSEPeer;
    // the same but CSE_URI Peer
    std::map<URI,int> CSEBucket;
    // key is the CSE_URI
    // value is the % of successful query result
};

typedef struct RoutingEntryStruct RoutingEntry;

/*
 * Semantic routing table model.
 *
 * Represents full routing table model, with mapping by AE type.
 *
 * */
typedef std::map<std::string, RoutingEntry> RoutingTable;


typedef std::map<URI, std::pair<std::string, int>> GateMapping;

#endif
