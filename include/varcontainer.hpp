/*
 * varcontainer.hpp
 *
 *  Created on: Oct 9, 2009
 *      Author: fish
 */

#ifndef VARCONTAINER_HPP_
#define VARCONTAINER_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <map>
#ifndef _WIN32
#include <cxxabi.h>
#endif

#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "support/MuscleSupport.h"
#include "message/Message.h"

//using boost::any_cast;
using namespace boost;
using namespace std;

/* forward Dec */
class VarStorage_t;
typedef boost::shared_ptr<VarStorage_t> VarStorage;
typedef boost::variant<std::string, int, long, long long, float, boost::posix_time::ptime > HashValsVariant_t;
typedef std::map<std::string, HashValsVariant_t> HashVals;

typedef enum StoredType_t {
	ST_STRING = 1,
	ST_INT,
	ST_LONG,
	ST_LONGLONG,
	ST_FLOAT,
	ST_HASH,
	ST_BOOL,
	ST_DATETIME,
	ST_VARSTORAGE,
	ST_INVALID
} StoredType_t;

typedef struct StoredVals_r {
	/* member 'std::string StoredVals_t::<anonymouse union>::StrVal' with constructor not allowed in union */
//	union {
		std::string StrVal;
		int IntVal;
		long LongVal;
		long long LongLongVal;
		float FloatVal;
		HashVals HashVal;
		bool BoolVal;
		boost::posix_time::ptime DateTimeVal;
		VarStorage VarVal;
//	};
	StoredType_t StoredType;
} StoredVals_r;

typedef boost::shared_ptr<StoredVals_r> StoredVals_t;

typedef std::vector<StoredVals_t> Vals;
typedef std::map<std::string, Vals*> Variables_t;

class VarStorage_t {
public:
	VarStorage_t();
	VarStorage_t(muscle::MessageRef msg);
	~VarStorage_t();
	void operator()(muscle::MessageRef msg);
	int addCharValue(std::string FieldName, char *);
	int addStringValue(std::string FieldName, std::string val);
	int addIntValue(std::string FieldName, int val);
	int addLongValue(std::string FieldName, long val);
	int addLongLongValue(std::string FieldName, long long val);
	int addFloatValue(std::string FieldName, float val);
	int addHashValue(std::string Fieldname, HashVals val);
	int addBoolValue(std::string FieldName, bool val);
	int addTimeValue(std::string FieldName, boost::posix_time::ptime val);
	int addVarStorageValue(std::string Fieldname, VarStorage &val);
	int replaceCharValue(std::string FieldName, char *val, int pos);
	int replaceStringValue(std::string FieldName, std::string val, int pos = 0);
	int replaceIntValue(std::string FieldName, int val, int pos = 0);
	int replaceLongValue(std::string FieldName, long val, int pos = 0);
	int replaceLongLongValue(std::string FieldName, long long val, int pos = 0);
	int replaceFloatValue(std::string FieldName, float val, int pos = 0);
	int replaceHashValue(std::string FieldName, HashVals val, int pos = 0);
	int replaceBoolValue(std::string FieldName, bool val, int pos = 0);
	int replaceTimeValue(std::string FieldName, boost::posix_time::ptime val, int pos = 0);
	int replaceVarStorageValue(std::string FieldName, VarStorage &val, int pos = 0);
	bool getCharValue(std::string FieldName, char *value, int pos);
	bool getStringValue(std::string FieldName, std::string &value, int pos = 0);
	bool getIntValue(std::string FieldName, int &value, int pos = 0);
	bool getLongValue(std::string FieldName, long &value, int pos = 0);
	bool getLongLongValue(std::string FieldName, long long &value, int pos = 0);
	bool getFloatValue(std::string FieldName, float &value, int pos = 0);
	bool getHashValue(std::string FieldName, HashVals &value, int pos = 0);
	bool getBoolValue(std::string FieldName, bool &value, int pos = 0);
	bool getTimeValue(std::string FieldName, boost::posix_time::ptime &value, int pos = 0);
	bool getVarStorageValue(std::string FieldName, VarStorage &value, int pos = 0);
//	bool delValue(std::string FieldName, int pos = 0);
	std::vector<std::string> *getFields();
	unsigned int getSize(std::string FieldName);
	unsigned int getSize();
	void printToStream(int tab = 0);
	muscle::MessageRef toMuscle();
	void importMuscleMsg(muscle::MessageRef msg);
	bool is_empty();
	StoredType_t getType(std::string FieldName);
private:
	friend std::ostream& operator<<(std::ostream&, const VarStorage_t &);
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version);
	std::string getType(StoredVals_t SV) const;
	std::string getType(StoredType_t type) const ;
	int addValueP(std::string FieldName, StoredVals_t);
	int replaceValueP(std::string FieldName, StoredVals_t val, int pos);
	StoredVals_t getValueP(std::string FieldName, StoredType_t type, int pos);
	Variables_t Variables;
};

#define VarContainerFactory(x) VarStorage x(new VarStorage_t());

std::ostream& operator<<(std::ostream&, const VarStorage_t &);
std::ostream& operator<<(std::ostream &os, const VarStorage &ptr) {
	os << *ptr.get();
	return os;
}
template<class Archive> void VarStorage_t::serialize(Archive & ar, const unsigned int version) {
	ar & boost::serialization::make_nvp("VarContainer", this->Variables);
}

#ifdef Q_OBJECT
Q_DECLARE_METATYPE(VarStorage_t);
//Q_DECLARE_METATYPE(VarStorage);
Q_DECLARE_METATYPE(boost::shared_ptr<VarStorage_t>);
Q_DECLARE_METATYPE(HashVals);
#endif


namespace boost {
namespace serialization {
#if 0
template<class Archive>
inline void serialize(
    Archive & ar,
    StoredVals_t & t,
    const unsigned int file_version
){
    split_free(ar, t, file_version);
}
#endif


template<class Archive>
void serialize(Archive & ar, StoredVals_t & g, const unsigned int version)
{
	if (Archive::is_loading::value) g.reset(new StoredVals_r);
	ar & make_nvp("StoredType", g->StoredType);
	switch (g->StoredType) {
		case ST_STRING:
			ar & make_nvp("String", g->StrVal);
			break;
		case ST_INT:
			ar & make_nvp("Int", g->IntVal);
			break;
		case ST_LONG:
			ar & make_nvp("Long", g->LongVal);
			break;
		case ST_LONGLONG:
			ar & make_nvp("LongLong", g->LongLongVal);
			break;
		case ST_FLOAT:
			ar & make_nvp("Float", g->FloatVal);
			break;
		case ST_HASH:
			ar & make_nvp("Hash", g->HashVal);
			break;
		case ST_BOOL:
			ar & make_nvp("Bool", g->BoolVal);
			break;
		case ST_DATETIME:
			ar & make_nvp("DateTime", g->DateTimeVal);
			break;
		case ST_VARSTORAGE:
			ar & make_nvp("VarStorage_t", g->VarVal);
			break;
		case ST_INVALID:
			break;
	}
}
#if 0
template<class Archive>
void load(Archive & ar, StoredVals_t & g, const unsigned int version)
{
	cout << version;
	ar >> make_nvp("StoredType", g->StoredType);
	switch (g->StoredType) {
		case ST_STRING:
			ar >> make_nvp("String", g->StrVal);
			break;
		case ST_INT:
			ar >> make_nvp("Int", g->IntVal);
			break;
		case ST_LONG:
			ar >> make_nvp("Long", g->LongVal);
			break;
		case ST_LONGLONG:
			ar >> make_nvp("LongLong", g->LongLongVal);
			break;
		case ST_FLOAT:
			ar >> make_nvp("Float", g->FloatVal);
			break;
		case ST_HASH:
			ar >> make_nvp("Hash", g->HashVal);
			break;
		case ST_BOOL:
			ar >> make_nvp("Bool", g->BoolVal);
			break;
		case ST_DATETIME:
			ar >> make_nvp("DateTime", g->DateTimeVal);
			break;
		case ST_VARSTORAGE:
			ar >> make_nvp("VarStorage_t", g->VarVal);
			break;
	}
}

#endif


} // namespace serialization
} // namespace boost

#endif /* VARCONTAINER_HPP_ */
