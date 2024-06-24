//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/WasteMessage.msg.
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
#include "WasteMessage_m.h"

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

Register_Class(WasteMessage)

WasteMessage::WasteMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

WasteMessage::WasteMessage(const WasteMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

WasteMessage::~WasteMessage()
{
}

WasteMessage& WasteMessage::operator=(const WasteMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WasteMessage::copy(const WasteMessage& other)
{
    this->binId = other.binId;
    this->fillLevel = other.fillLevel;
    this->latitude = other.latitude;
    this->longitude = other.longitude;
}

void WasteMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->binId);
    doParsimPacking(b,this->fillLevel);
    doParsimPacking(b,this->latitude);
    doParsimPacking(b,this->longitude);
}

void WasteMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->binId);
    doParsimUnpacking(b,this->fillLevel);
    doParsimUnpacking(b,this->latitude);
    doParsimUnpacking(b,this->longitude);
}

int WasteMessage::getBinId() const
{
    return this->binId;
}

void WasteMessage::setBinId(int binId)
{
    this->binId = binId;
}

double WasteMessage::getFillLevel() const
{
    return this->fillLevel;
}

void WasteMessage::setFillLevel(double fillLevel)
{
    this->fillLevel = fillLevel;
}

double WasteMessage::getLatitude() const
{
    return this->latitude;
}

void WasteMessage::setLatitude(double latitude)
{
    this->latitude = latitude;
}

double WasteMessage::getLongitude() const
{
    return this->longitude;
}

void WasteMessage::setLongitude(double longitude)
{
    this->longitude = longitude;
}

class WasteMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_binId,
        FIELD_fillLevel,
        FIELD_latitude,
        FIELD_longitude,
    };
  public:
    WasteMessageDescriptor();
    virtual ~WasteMessageDescriptor();

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

Register_ClassDescriptor(WasteMessageDescriptor)

WasteMessageDescriptor::WasteMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(WasteMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

WasteMessageDescriptor::~WasteMessageDescriptor()
{
    delete[] propertyNames;
}

bool WasteMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WasteMessage *>(obj)!=nullptr;
}

const char **WasteMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *WasteMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int WasteMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int WasteMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_binId
        FD_ISEDITABLE,    // FIELD_fillLevel
        FD_ISEDITABLE,    // FIELD_latitude
        FD_ISEDITABLE,    // FIELD_longitude
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *WasteMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "binId",
        "fillLevel",
        "latitude",
        "longitude",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int WasteMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "binId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fillLevel") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "latitude") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "longitude") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *WasteMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_binId
        "double",    // FIELD_fillLevel
        "double",    // FIELD_latitude
        "double",    // FIELD_longitude
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **WasteMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WasteMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int WasteMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void WasteMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'WasteMessage'", field);
    }
}

const char *WasteMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WasteMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_binId: return long2string(pp->getBinId());
        case FIELD_fillLevel: return double2string(pp->getFillLevel());
        case FIELD_latitude: return double2string(pp->getLatitude());
        case FIELD_longitude: return double2string(pp->getLongitude());
        default: return "";
    }
}

void WasteMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_binId: pp->setBinId(string2long(value)); break;
        case FIELD_fillLevel: pp->setFillLevel(string2double(value)); break;
        case FIELD_latitude: pp->setLatitude(string2double(value)); break;
        case FIELD_longitude: pp->setLongitude(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WasteMessage'", field);
    }
}

omnetpp::cValue WasteMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_binId: return pp->getBinId();
        case FIELD_fillLevel: return pp->getFillLevel();
        case FIELD_latitude: return pp->getLatitude();
        case FIELD_longitude: return pp->getLongitude();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'WasteMessage' as cValue -- field index out of range?", field);
    }
}

void WasteMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        case FIELD_binId: pp->setBinId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_fillLevel: pp->setFillLevel(value.doubleValue()); break;
        case FIELD_latitude: pp->setLatitude(value.doubleValue()); break;
        case FIELD_longitude: pp->setLongitude(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WasteMessage'", field);
    }
}

const char *WasteMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr WasteMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void WasteMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    WasteMessage *pp = omnetpp::fromAnyPtr<WasteMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'WasteMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

