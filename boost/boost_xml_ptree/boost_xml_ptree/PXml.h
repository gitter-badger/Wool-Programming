#include <string>
#include <iostream>
#include <vector>

#include <boost\property_tree\xml_parser.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\foreach.hpp>

struct Game
{
	std::string title;
	std::string company;
	int price;
	
	Game(){}
	Game(const Game& Game) :title(Game.title), company(Game.company),price(Game.price){}
	Game(std::string title, std::string company, int price) :title(title), company(company),price(price){}
};

class PXml{
public:
	PXml(){}
	void write(std::string filename,const std::vector<Game> &Games){
		boost::property_tree::ptree pt;
		BOOST_FOREACH(const Game& Game, Games){
			boost::property_tree::ptree& child = pt.add("root.Game", "");
			child.put("title", Game.title);
			child.put("company", Game.company);
			child.put("price", Game.price);
		}

		boost::property_tree::xml_parser::write_xml(
			filename,
			pt,
			std::locale(),
			boost::property_tree::xml_parser::xml_writer_make_settings<std::string>(' ', 4)
			);
	}
};