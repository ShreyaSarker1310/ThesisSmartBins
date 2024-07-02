//
// Generated file, do not edit! Created by opp_msgtool 6.0 from discoveryMessage.msg.
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
#include "discoveryMessage_m.h"

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

class DBresultDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    DBresultDescriptor();
    virtual ~DBresultDescriptor();

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

Register_ClassDescriptor(DBresultDescriptor)

DBresultDescriptor::DBresultDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DBresult)), "")
{
    propertyNames = nullptr;
}

DBresultDescriptor::~DBresultDescriptor()
{
    delete[] propertyNames;
}

bool DBresultDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DBresult *>(obj)!=nullptr;
}

const char **DBresultDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DBresultDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DBresultDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int DBresultDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *DBresultDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int DBresultDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *DBresultDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **DBresultDescriptor::getFieldPropertyNames(int field) const
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

const char *DBresultDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int DBresultDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DBresultDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DBresult'", field);
    }
}

const char *DBresultDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DBresultDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void DBresultDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DBresult'", field);
    }
}

omnetpp::cValue DBresultDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DBresult' as cValue -- field index out of range?", field);
    }
}

void DBresultDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DBresult'", field);
    }
}

const char *DBresultDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr DBresultDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DBresultDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DBresult *pp = omnetpp::fromAnyPtr<DBresult>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DBresult'", field);
    }
}

class GateVectorDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    GateVectorDescriptor();
    virtual ~GateVectorDescriptor();

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

Register_ClassDescriptor(GateVectorDescriptor)

GateVectorDescriptor::GateVectorDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GateVector)), "")
{
    propertyNames = nullptr;
}

GateVectorDescriptor::~GateVectorDescriptor()
{
    delete[] propertyNames;
}

bool GateVectorDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GateVector *>(obj)!=nullptr;
}

const char **GateVectorDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GateVectorDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GateVectorDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int GateVectorDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *GateVectorDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int GateVectorDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *GateVectorDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **GateVectorDescriptor::getFieldPropertyNames(int field) const
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

const char *GateVectorDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int GateVectorDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GateVectorDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GateVector'", field);
    }
}

const char *GateVectorDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GateVectorDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void GateVectorDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GateVector'", field);
    }
}

omnetpp::cValue GateVectorDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GateVector' as cValue -- field index out of range?", field);
    }
}

void GateVectorDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GateVector'", field);
    }
}

const char *GateVectorDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr GateVectorDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GateVectorDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GateVector *pp = omnetpp::fromAnyPtr<GateVector>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GateVector'", field);
    }
}

Register_Class(discoveryMessage)

discoveryMessage::discoveryMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

discoveryMessage::discoveryMessage(const discoveryMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

discoveryMessage::~discoveryMessage()
{
}

discoveryMessage& discoveryMessage::operator=(const discoveryMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void discoveryMessage::copy(const discoveryMessage& other)
{
    this->queryID = other.queryID;
    this->URI_init = other.URI_init;
    this->URI_route = other.URI_route;
    this->feature_type = other.feature_type;
    this->op_code = other.op_code;
    this->returnCode = other.returnCode;
    this->delta = other.delta;
    this->hopCount = other.hopCount;
    this->direction = other.direction;
    this->initialGateIndex = other.initialGateIndex;
    this->dbResult = other.dbResult;
    this->gateVector = other.gateVector;
}

void discoveryMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->queryID);
    doParsimPacking(b,this->URI_init);
    doParsimPacking(b,this->URI_route);
    doParsimPacking(b,this->feature_type);
    doParsimPacking(b,this->op_code);
    doParsimPacking(b,this->returnCode);
    doParsimPacking(b,this->delta);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->direction);
    doParsimPacking(b,this->initialGateIndex);
    doParsimPacking(b,this->dbResult);
    doParsimPacking(b,this->gateVector);
}

void discoveryMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->queryID);
    doParsimUnpacking(b,this->URI_init);
    doParsimUnpacking(b,this->URI_route);
    doParsimUnpacking(b,this->feature_type);
    doParsimUnpacking(b,this->op_code);
    doParsimUnpacking(b,this->returnCode);
    doParsimUnpacking(b,this->delta);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->direction);
    doParsimUnpacking(b,this->initialGateIndex);
    doParsimUnpacking(b,this->dbResult);
    doParsimUnpacking(b,this->gateVector);
}

int discoveryMessage::getQueryID() const
{
    return this->queryID;
}

void discoveryMessage::setQueryID(int queryID)
{
    this->queryID = queryID;
}

int discoveryMessage::getURI_init() const
{
    return this->URI_init;
}

void discoveryMessage::setURI_init(int URI_init)
{
    this->URI_init = URI_init;
}

int discoveryMessage::getURI_route() const
{
    return this->URI_route;
}

void discoveryMessage::setURI_route(int URI_route)
{
    this->URI_route = URI_route;
}

const char * discoveryMessage::getFeature_type() const
{
    return this->feature_type.c_str();
}

void discoveryMessage::setFeature_type(const char * feature_type)
{
    this->feature_type = feature_type;
}

int discoveryMessage::getOp_code() const
{
    return this->op_code;
}

void discoveryMessage::setOp_code(int op_code)
{
    this->op_code = op_code;
}

int discoveryMessage::getReturnCode() const
{
    return this->returnCode;
}

void discoveryMessage::setReturnCode(int returnCode)
{
    this->returnCode = returnCode;
}

int discoveryMessage::getDelta() const
{
    return this->delta;
}

void discoveryMessage::setDelta(int delta)
{
    this->delta = delta;
}

int discoveryMessage::getHopCount() const
{
    return this->hopCount;
}

void discoveryMessage::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

int discoveryMessage::getDirection() const
{
    return this->direction;
}

void discoveryMessage::setDirection(int direction)
{
    this->direction = direction;
}

int discoveryMessage::getInitialGateIndex() const
{
    return this->initialGateIndex;
}

void discoveryMessage::setInitialGateIndex(int initialGateIndex)
{
    this->initialGateIndex = initialGateIndex;
}

const DBresult& discoveryMessage::getDbResult() const
{
    return this->dbResult;
}

void discoveryMessage::setDbResult(const DBresult& dbResult)
{
    this->dbResult = dbResult;
}

const GateVector& discoveryMessage::getGateVector() const
{
    return this->gateVector;
}

void discoveryMessage::setGateVector(const GateVector& gateVector)
{
    this->gateVector = gateVector;
}

class discoveryMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_queryID,
        FIELD_URI_init,
        FIELD_URI_route,
        FIELD_feature_type,
        FIELD_op_code,
        FIELD_returnCode,
        FIELD_delta,
        FIELD_hopCount,
        FIELD_direction,
        FIELD_initialGateIndex,
        FIELD_dbResult,
        FIELD_gateVector,
    };
  public:
    discoveryMessageDescriptor();
    virtual ~discoveryMessageDescriptor();

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

Register_ClassDescriptor(discoveryMessageDescriptor)

discoveryMessageDescriptor::discoveryMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(discoveryMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

discoveryMessageDescriptor::~discoveryMessageDescriptor()
{
    delete[] propertyNames;
}

bool discoveryMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<discoveryMessage *>(obj)!=nullptr;
}

const char **discoveryMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *discoveryMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int discoveryMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int discoveryMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_queryID
        FD_ISEDITABLE,    // FIELD_URI_init
        FD_ISEDITABLE,    // FIELD_URI_route
        FD_ISEDITABLE,    // FIELD_feature_type
        FD_ISEDITABLE,    // FIELD_op_code
        FD_ISEDITABLE,    // FIELD_returnCode
        FD_ISEDITABLE,    // FIELD_delta
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_direction
        FD_ISEDITABLE,    // FIELD_initialGateIndex
        FD_ISCOMPOUND,    // FIELD_dbResult
        FD_ISCOMPOUND,    // FIELD_gateVector
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *discoveryMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "queryID",
        "URI_init",
        "URI_route",
        "feature_type",
        "op_code",
        "returnCode",
        "delta",
        "hopCount",
        "direction",
        "initialGateIndex",
        "dbResult",
        "gateVector",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int discoveryMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "queryID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "URI_init") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "URI_route") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "feature_type") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "op_code") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "returnCode") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "delta") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "direction") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "initialGateIndex") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "dbResult") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "gateVector") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *discoveryMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_queryID
        "int",    // FIELD_URI_init
        "int",    // FIELD_URI_route
        "string",    // FIELD_feature_type
        "int",    // FIELD_op_code
        "int",    // FIELD_returnCode
        "int",    // FIELD_delta
        "int",    // FIELD_hopCount
        "int",    // FIELD_direction
        "int",    // FIELD_initialGateIndex
        "DBresult",    // FIELD_dbResult
        "GateVector",    // FIELD_gateVector
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **discoveryMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *discoveryMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int discoveryMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void discoveryMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'discoveryMessage'", field);
    }
}

const char *discoveryMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string discoveryMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: return long2string(pp->getQueryID());
        case FIELD_URI_init: return long2string(pp->getURI_init());
        case FIELD_URI_route: return long2string(pp->getURI_route());
        case FIELD_feature_type: return oppstring2string(pp->getFeature_type());
        case FIELD_op_code: return long2string(pp->getOp_code());
        case FIELD_returnCode: return long2string(pp->getReturnCode());
        case FIELD_delta: return long2string(pp->getDelta());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_direction: return long2string(pp->getDirection());
        case FIELD_initialGateIndex: return long2string(pp->getInitialGateIndex());
        case FIELD_dbResult: return "";
        case FIELD_gateVector: return "";
        default: return "";
    }
}

void discoveryMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: pp->setQueryID(string2long(value)); break;
        case FIELD_URI_init: pp->setURI_init(string2long(value)); break;
        case FIELD_URI_route: pp->setURI_route(string2long(value)); break;
        case FIELD_feature_type: pp->setFeature_type((value)); break;
        case FIELD_op_code: pp->setOp_code(string2long(value)); break;
        case FIELD_returnCode: pp->setReturnCode(string2long(value)); break;
        case FIELD_delta: pp->setDelta(string2long(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        case FIELD_direction: pp->setDirection(string2long(value)); break;
        case FIELD_initialGateIndex: pp->setInitialGateIndex(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'discoveryMessage'", field);
    }
}

omnetpp::cValue discoveryMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: return pp->getQueryID();
        case FIELD_URI_init: return pp->getURI_init();
        case FIELD_URI_route: return pp->getURI_route();
        case FIELD_feature_type: return pp->getFeature_type();
        case FIELD_op_code: return pp->getOp_code();
        case FIELD_returnCode: return pp->getReturnCode();
        case FIELD_delta: return pp->getDelta();
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_direction: return pp->getDirection();
        case FIELD_initialGateIndex: return pp->getInitialGateIndex();
        case FIELD_dbResult: return omnetpp::toAnyPtr(&pp->getDbResult()); break;
        case FIELD_gateVector: return omnetpp::toAnyPtr(&pp->getGateVector()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'discoveryMessage' as cValue -- field index out of range?", field);
    }
}

void discoveryMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        case FIELD_queryID: pp->setQueryID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_URI_init: pp->setURI_init(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_URI_route: pp->setURI_route(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_feature_type: pp->setFeature_type(value.stringValue()); break;
        case FIELD_op_code: pp->setOp_code(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_returnCode: pp->setReturnCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_delta: pp->setDelta(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_direction: pp->setDirection(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_initialGateIndex: pp->setInitialGateIndex(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'discoveryMessage'", field);
    }
}

const char *discoveryMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_dbResult: return omnetpp::opp_typename(typeid(DBresult));
        case FIELD_gateVector: return omnetpp::opp_typename(typeid(GateVector));
        default: return nullptr;
    };
}

omnetpp::any_ptr discoveryMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        case FIELD_dbResult: return omnetpp::toAnyPtr(&pp->getDbResult()); break;
        case FIELD_gateVector: return omnetpp::toAnyPtr(&pp->getGateVector()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void discoveryMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    discoveryMessage *pp = omnetpp::fromAnyPtr<discoveryMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'discoveryMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

