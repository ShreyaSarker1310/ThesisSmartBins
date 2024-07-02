//
// Generated file, do not edit! Created by opp_msgtool 6.0 from AEMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "AEMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(AEMessage)

AEMessage::AEMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

AEMessage::AEMessage(const AEMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

AEMessage::~AEMessage()
{
}

AEMessage& AEMessage::operator=(const AEMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void AEMessage::copy(const AEMessage& other)
{
    this->queryID = other.queryID;
    this->URI = other.URI;
    this->feature_type = other.feature_type;
    this->data = other.data;
    this->op_code = other.op_code;
}

void AEMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->queryID);
    doParsimPacking(b,this->URI);
    doParsimPacking(b,this->feature_type);
    doParsimPacking(b,this->data);
    doParsimPacking(b,this->op_code);
}

void AEMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->queryID);
    doParsimUnpacking(b,this->URI);
    doParsimUnpacking(b,this->feature_type);
    doParsimUnpacking(b,this->data);
    doParsimUnpacking(b,this->op_code);
}

int AEMessage::getQueryID() const
{
    return this->queryID;
}

void AEMessage::setQueryID(int queryID)
{
    this->queryID = queryID;
}

int AEMessage::getURI() const
{
    return this->URI;
}

void AEMessage::setURI(int URI)
{
    this->URI = URI;
}

const char * AEMessage::getFeature_type() const
{
    return this->feature_type.c_str();
}

void AEMessage::setFeature_type(const char * feature_type)
{
    this->feature_type = feature_type;
}

int AEMessage::getData() const
{
    return this->data;
}

void AEMessage::setData(int data)
{
    this->data = data;
}

int AEMessage::getOp_code() const
{
    return this->op_code;
}

void AEMessage::setOp_code(int op_code)
{
    this->op_code = op_code;
}

class AEMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_queryID,
        FIELD_URI,
        FIELD_feature_type,
        FIELD_data,
        FIELD_op_code,
    };
  public:
    AEMessageDescriptor();
    virtual ~AEMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AEMessageDescriptor)

AEMessageDescriptor::AEMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AEMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

AEMessageDescriptor::~AEMessageDescriptor()
{
    delete[] propertyNames;
}

bool AEMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AEMessage *>(obj)!=nullptr;
}

const char **AEMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AEMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AEMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int AEMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_queryID
        FD_ISEDITABLE,    // FIELD_URI
        FD_ISEDITABLE,    // FIELD_feature_type
        FD_ISEDITABLE,    // FIELD_data
        FD_ISEDITABLE,    // FIELD_op_code
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *AEMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "queryID",
        "URI",
        "feature_type",
        "data",
        "op_code",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int AEMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "queryID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "URI") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "feature_type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "op_code") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *AEMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_queryID
        "int",    // FIELD_URI
        "string",    // FIELD_feature_type
        "int",    // FIELD_data
        "int",    // FIELD_op_code
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **AEMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AEMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AEMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AEMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AEMessage'", field);
    }
}

const char *AEMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AEMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: return long2string(pp->getQueryID());
        case FIELD_URI: return long2string(pp->getURI());
        case FIELD_feature_type: return oppstring2string(pp->getFeature_type());
        case FIELD_data: return long2string(pp->getData());
        case FIELD_op_code: return long2string(pp->getOp_code());
        default: return "";
    }
}

void AEMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: pp->setQueryID(string2long(value)); break;
        case FIELD_URI: pp->setURI(string2long(value)); break;
        case FIELD_feature_type: pp->setFeature_type((value)); break;
        case FIELD_data: pp->setData(string2long(value)); break;
        case FIELD_op_code: pp->setOp_code(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AEMessage'", field);
    }
}

omnetpp::cValue AEMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: return pp->getQueryID();
        case FIELD_URI: return pp->getURI();
        case FIELD_feature_type: return pp->getFeature_type();
        case FIELD_data: return pp->getData();
        case FIELD_op_code: return pp->getOp_code();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AEMessage' as cValue -- field index out of range?", field);
    }
}

void AEMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: pp->setQueryID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_URI: pp->setURI(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_feature_type: pp->setFeature_type(value.stringValue()); break;
        case FIELD_data: pp->setData(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_op_code: pp->setOp_code(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AEMessage'", field);
    }
}

const char *AEMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AEMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AEMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AEMessage *pp = omnetpp::fromAnyPtr<AEMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AEMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

