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
#include <boost/shared_array.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include <boost/archive/text_oarchive.hpp>
#ifdef __clang__
#pragma clang diagnostic warning "-Wunused-parameter"
#endif
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "iHanClientDefs.hpp"
#include "support/MuscleSupport.h"
#include "message/Message.h"

//using boost::any_cast;
using namespace boost;
using namespace std;

typedef std::map<int32_t, std::string> EnumVals_t;
typedef std::map<int32_t, std::string>::const_iterator list_const_iterator;
IHANCLIENT_EXPORT_WARNINGS_OFF
class IHANCLIENT_EXPORT ListVals_t : boost::noncopyable
{
IHANCLIENT_EXPORT_WARNINGS_ON

public:
	//~ListVals_t() {//std::cout << "goodbye" << std::endl;}
	bool setSelected(int32_t);
	int32_t getSelected() const;
	bool insertValue(int32_t, std::string);
	bool removeValue(int32_t);
	std::string getValue(int32_t);
	size_t getSize();
	typedef EnumVals_t::const_iterator const_iterator;
	list_const_iterator begin() const { return this->Vals.begin(); };
	list_const_iterator end() const { return this->Vals.end(); };
	private:
	friend class boost::serialization::access;
	friend std::ostream& operator<<(std::ostream&, const ListVals_t &);


	template<class Archive>
	void serialize(Archive & ar,const unsigned int version)
	{
			(void)version;
			if (Archive::is_loading::value) {
				this->Selected = 0;
				this->Vals.clear();
			}
			ar & boost::serialization::make_nvp("Selected", this->Selected);
			ar & boost::serialization::make_nvp("Vals", this->Vals);
	}
	int32_t Selected;
	IHANCLIENT_EXPORT_WARNINGS_OFF
	EnumVals_t Vals;
	IHANCLIENT_EXPORT_WARNINGS_ON
};

typedef struct ListOptions_t {
		int32_t index;
		char desc[256];
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
				(void)version;
				//			if (Archive::is_loading::value) {
				//				g.Selected = 0;
				//				g.Vals.clear();
				//			}
				ar & boost::serialization::make_nvp("index", index);
				ar & boost::serialization::make_nvp("desc", desc);
		}

}ListOptions_t;

BOOST_IS_BITWISE_SERIALIZABLE(ListOptions_t)

#define CreateListOptions(name, size) ListOptions_t *name = new ListOptions_t[size+2]
#define AddListOptions(name, pos, indexval, descval) name[pos].index = indexval; strncpy(name[pos].desc, descval, 256)
#define FinishListOptions(name,pos) name[pos].index = -1; strncpy(name[pos].desc, "", 256)

#define ListStackPointer(w, x) boost::shared_array<ListOptions_t> x_ptr(x, &null_deleter); \
		w = x_ptr;



/* forward Dec */
class VarStorage_t;
typedef boost::shared_ptr<VarStorage_t> VarStorage;
typedef boost::shared_ptr<ListVals_t> ListVals;
typedef boost::shared_array<ListOptions_t> ListOptions;
typedef boost::variant<std::string, int, long, long long, float, boost::posix_time::ptime, ListOptions> HashValsVariant_t;
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
	ST_LIST,
	ST_INVALID = 100
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
		ListVals ListVal;

		//	};
		StoredType_t StoredType;
} StoredVals_r;

typedef boost::shared_ptr<StoredVals_r> StoredVals_t;

typedef std::vector<StoredVals_t> Vals;
typedef std::map<std::string, Vals*> Variables_t;





class IHANCLIENT_EXPORT VarStorage_t {
	public:
		VarStorage_t();
		VarStorage_t(muscle::MessageRef msg);
		VarStorage_t(VarStorage_t  const &other);
		~VarStorage_t();
		void operator()(muscle::MessageRef msg);
		uint64_t getWhat();
		void setWhat(uint64_t what);
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
		int replaceCharValue(std::string FieldName, char *val, uint8_t pos);
		int replaceStringValue(std::string FieldName, std::string val, uint8_t pos = 0);
		int replaceIntValue(std::string FieldName, int val, uint8_t pos = 0);
		int replaceLongValue(std::string FieldName, long val, uint8_t pos = 0);
		int replaceLongLongValue(std::string FieldName, long long val, uint8_t pos = 0);
		int replaceFloatValue(std::string FieldName, float val, uint8_t pos = 0);
		int replaceHashValue(std::string FieldName, HashVals val, uint8_t pos = 0);
		int replaceBoolValue(std::string FieldName, bool val, uint8_t pos = 0);
		int replaceTimeValue(std::string FieldName, boost::posix_time::ptime val, uint8_t pos = 0);
		int replaceVarStorageValue(std::string FieldName, VarStorage &val, uint8_t pos = 0);
		bool getCharValue(std::string FieldName, char *value, uint8_t pos);
		bool getStringValue(std::string FieldName, std::string &value, uint8_t pos = 0);
		bool getIntValue(std::string FieldName, int &value, uint8_t pos = 0);
		bool getLongValue(std::string FieldName, long &value, uint8_t pos = 0);
		bool getLongLongValue(std::string FieldName, long long &value, uint8_t pos = 0);
		bool getFloatValue(std::string FieldName, float &value, uint8_t pos = 0);
		bool getHashValue(std::string FieldName, HashVals &value, uint8_t pos = 0);
		bool getBoolValue(std::string FieldName, bool &value, uint8_t pos = 0);
		bool getTimeValue(std::string FieldName, boost::posix_time::ptime &value, uint8_t pos = 0);
		bool getVarStorageValue(std::string FieldName, VarStorage &value, uint8_t pos = 0);
		bool delValue(std::string FieldName, uint8_t pos);
		bool delValue(std::string FieldName);



		bool addListValue(std::string Filename, uint32_t index, std::string val, uint8_t pos = 0);
		bool delListValue(std::string Filename, uint32_t index, uint8_t pos = 0);
		bool getListValue(std::string Filename, uint32_t index, std::string &value, uint8_t pos = 0);
		bool setListSelectedValue(std::string Filename, uint32_t index, uint8_t pos = 0);
		bool getListSelectedValue(std::string Filename, uint32_t &value, uint8_t pos = 0);
		list_const_iterator getListIterBegin(std::string Fieldname, uint8_t pos = 0);
		list_const_iterator getListIterEnd(std::string Fieldname, uint8_t pos = 0);
		uint32_t getListSize(std::string Filename, uint8_t pos = 0);
		int addListValue_p(std::string Filename, ListVals val);
		int replaceListValue_p(std::string FieldName, ListVals val, uint8_t pos = 0);
		bool getListValue_p(std::string FieldName, ListVals &value, uint8_t pos = 0);



		std::vector<std::string> *getFields();
		unsigned int getSize(std::string FieldName);
		unsigned int getSize();
		void printToStream(int tab = 0);
		muscle::MessageRef toMuscle();
		void importMuscleMsg(muscle::MessageRef msg);
		bool is_empty();
		StoredType_t getType(std::string FieldName);
	private:
		friend IHANCLIENT_EXPORT std::ostream& operator<<(std::ostream&, const VarStorage_t &);
		friend class boost::serialization::access;
		friend IHANCLIENT_EXPORT void copyVarStorageFields(VarStorage src, VarStorage dst, std::string fieldName);
		template<class Archive> void serialize(Archive & ar, const unsigned int version);
		std::string getType(StoredVals_t SV) const;
		std::string getType(StoredType_t type) const ;
		int addValueP(std::string FieldName, StoredVals_t);
		int replaceValueP(std::string FieldName, StoredVals_t val, uint8_t pos);


		StoredVals_t getValueP(std::string FieldName, StoredType_t type, uint8_t pos);
		IHANCLIENT_EXPORT_WARNINGS_OFF
		uint32_t m_what;
		Variables_t Variables;
		IHANCLIENT_EXPORT_WARNINGS_ON
};

#define VarContainerFactory(x) VarStorage x(new VarStorage_t());
#define VarContainerCopy(x, y) VarStorage x(new VarStorage_t(*y.get()));

IHANCLIENT_EXPORT std::ostream& operator<<(std::ostream&, const VarStorage_t &);
IHANCLIENT_EXPORT std::ostream& operator<<(std::ostream &os, const VarStorage &ptr);
template<class Archive> void VarStorage_t::serialize(Archive & ar, const unsigned int version) {
		(void)version;
		ar & boost::serialization::make_nvp("VarContainer", this->Variables);
		ar & boost::serialization::make_nvp("What", this->m_what);
}

IHANCLIENT_EXPORT void copyVarStorageFields(VarStorage src, VarStorage dst, std::string fieldName);


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
				(void)version;
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
					case ST_LIST:
						ar & make_nvp("ListVals_t", g->ListVal);
						break;
					case ST_INVALID:
						break;
				}
		}
		template<class Archive>
		inline void save(
				Archive & ar,
				const boost::shared_array<ListOptions_t> &t,
				const unsigned int /* file_version */
		){
				// The most common cause of trapping here would be serializing
				// something like shared_ptr<int>.  This occurs because int
				// is never tracked by default.  Wrap int in a trackable type
				BOOST_STATIC_ASSERT((tracking_level< boost::shared_array<ListOptions_t> >::value != track_never));
				const  ListOptions_t* t_ptr = t.get();
				int size = 0;
				do {
					size++;
					t_ptr++;
				} while (strlen(t_ptr->desc) > 0);
				ar << boost::serialization::make_nvp("size", size);
				for (int i = 0; i < size; i++) {
					ar << boost::serialization::make_nvp("px", t[i]);
				}
		}
		template<class Archive>
		inline void load(
				Archive & ar,
				boost::shared_array<ListOptions_t> &t,
				const unsigned int /*file_version*/
		){
				// The most common cause of trapping here would be serializing
				// something like shared_ptr<int>.  This occurs because int
				// is never tracked by default.  Wrap int in a trackable type
				BOOST_STATIC_ASSERT((tracking_level< boost::shared_array<ListOptions_t> >::value != track_never));
				int size;
				ar >> boost::serialization::make_nvp("size", size);
				ListOptions_t* r = new ListOptions_t[size];
				for (int i = 0; i < size; i++) {
					ar >> boost::serialization::make_nvp("px", r[i]);
				}
				t.reset(r);
		}

		template<class Archive>
		inline void serialize(
				Archive & ar,
				boost::shared_array<ListOptions_t> &t,
				const unsigned int file_version
		){
				// correct shared_ptr serialization depends upon object tracking
				// being used.
				BOOST_STATIC_ASSERT(
						boost::serialization::tracking_level< boost::shared_array<ListOptions_t> >::value
						!= boost::serialization::track_never
				);
				boost::serialization::split_free(ar, t, file_version);
		}


#if 0
		template<class Archive>
		void serialize(Archive & ar, ListVals & g, const unsigned int version)
		{
				if (Archive::is_loading::value) {
					g.Selected = 0;
					g.Vals.clear();
				}
				ar & make_nvp("Selected", g.Selected);
				ar & make_nvp("Vals", g.Vals);
		}
#endif

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
