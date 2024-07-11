cplusplus{{
  #include <map>
  #include <vector>
  typedef std::map<int,int> DBresult;
  typedef std::vector<omnetpp::cGate *> GateVector;
}}

class DBresult { @existingClass; };
class GateVector { @existingClass; };

message discoveryMessage{
  int queryID;  // ID assigned to QUERY

  int URI_init; // this is identifier of the very first AE generating Discovery QUERY

  int URI_route;  // this is identifier of in route CSE, sending the message to another CSE

  string feature_type;  // this is type of Resource CSE is looking for.

  int op_code;  // this can be
                // REGISTRATION (value = 0)
                // UPDATE (value = 1)
                // CANCELLATION (value = 2)
                // QUERY (value = 3)
                // RESPONSE (value = 4)
                // NOTIFY (value = 5)

  int returnCode; // It can be set to +1 or -1 respectively to add or remove the AEs from routing table.

  int delta; // It is used for notification for measuring depth of notification

  int hopCount; // It is used for notification for measuring the depth of notificaiton

  int direction;  // this will be direction where the message has been sent
                  // UP (customer to provider)
                  // DOWN (provider to customer)
                  // SIDE (sibling to sling or peer to peer)

  int initialGateIndex; // this is the index of the gate from which the request has been sent, originator gate.

  DBresult dbResult;  // this is the result obtained when looking in the local database

  GateVector gateVector;


  // realted to UPDATE
  int updateID; // ID assigned to UPDATE
  int data;
}
