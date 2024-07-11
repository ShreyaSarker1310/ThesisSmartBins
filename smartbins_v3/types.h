#ifndef TYPES_H_

#define TYPES_H_

using namespace omnetpp;

typedef int URI;
typedef std::pair<URI, int> queryKey;

/*
 * Routing Entry
 *
 * Routing entry represents single entry in semantic routing table.
 * In contains mappings with number of AEs by link type.
 */

struct RoutingEntryStruct {
  // URIs of AEs which are directly connected to the CSE
  std::map<URI, int> database;

  // key is the CSE_URI Customer
  // value is the number of AE feature type
  std::map<URI, int> CSECustomer;

  // key is the CSE_URI Provider
  // value is the number of AE feature type
  std::map<URI, int> CSEProvider;

  // key is the CSE_URI Sibling
  // value is the number of AE feature type
  std::map<URI, int> CSESibling;

  // key is the CSE_URI Peer
  // value is the number of AE feature type
  std::map<URI, int> CSEPeer;

  // key is the CSE_URI
  // value is the % of successful query result
  std::map<URI, int> CSEBucket;
};

/*
 * Sematic routing table model
 *
 * Represents full routing table model, whith mapping by AE type.
 *
 */
typedef struct RoutingEntryStruct RoutingEntry;

typedef std::map<std::string, RoutingEntry> RoutingTable;

typedef std::map<URI, std::pair<std::string, int>> GateMapping;

struct SubscribeEntryStruct {
  std::map<URI, cGate *> subscribers;
};

typedef struct SubscribeEntryStruct SubscribeEntry;

typedef std::map<std::string, SubscribeEntry> SubscribeTable;

typedef std::map<URI, int> BinLevelTable;

#endif
