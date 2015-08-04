/**
* @file SerializeXml.h
* @brief xml serialize
* @author Shota Hirama
* @date 2015/08/05 doxygen
* @date 2015/08/05 create
*/


#include <iostream>
#include <fstream>
#include <string>

#include <boost\serialization\serialization.hpp>
#include <boost\serialization\nvp.hpp>
#include <boost\serialization\string.hpp>
#include <boost\archive\xml_oarchive.hpp>
#include <boost\archive\xml_iarchive.hpp>

class SerializeXml{
public:
	/**
	 * @fn コンストラクタ
	 * @breaf 値代入
	 */
	SerializeXml() :a(0), b(10), c(20), d(30){};

	/**
	 * @fn save
	 * @breaf xml保存
	 * @param filename ファイル名
	 */
	void save(const std::string &filename){
		std::ofstream ofs(filename);
		boost::archive::xml_oarchive oarchive(ofs);
		oarchive << boost::serialization::make_nvp("test", this);
	}

	/**
	 * @fn read
	 * @breaf xml読み込み
	 * @param filename ファイル名
	 */
	static SerializeXml read(const std::string &filename){
		SerializeXml serialize;
		std::ifstream ifs(filename);
		if (ifs.bad()){
			serialize.save(filename);
			return serialize;
		}
		boost::archive::xml_iarchive iarchive(ifs);
		iarchive >> boost::serialization::make_nvp("test", serialize);
		return serialize;
	}
	int a, b, c, d;
private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive& archive, unsigned int version){
		static_cast<void>(version);
		archive & BOOST_SERIALIZATION_NVP(a);
		archive & BOOST_SERIALIZATION_NVP(b);
		archive & BOOST_SERIALIZATION_NVP(c);
		archive & BOOST_SERIALIZATION_NVP(d);
	}
};