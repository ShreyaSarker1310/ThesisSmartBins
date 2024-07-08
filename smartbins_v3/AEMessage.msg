message AEMessage
{
  int queryID;

  int URI;  // this is the unique identifer of the AE message
  
  string feature_type;  // this is the feature type of the resource looking for

  int data; // this is the value concerning the resource we are looking for

  int op_code;  // this can be
                // REGISTRATION (when AE register to CSE), value = 0
                // UPDATE (when AE update every x mns the CSE about the update in its values in local Database); value = 1
                // CANCELLATION (when AE wants to cancel the Resource inside CSE local Database) value = 2
                // QUERY (when AE wants to ask for resource), value = 3
                // PUT (CSE to AE: CSE gives some directive to the corresponding AE), value = 4
                // GET (CSE to AE: CSE ask some value from the corresponding AE) value = 5
                // REPLY (AE to CSE: AE reply to the CSE with a value normally in data) value = 6
                // RESPONSE (AE to CSE: AE reply to the CSE with a value normally in data) value = 7
                // NOTIFY (between CSE to notify modifications in route tables) value = 8
}
