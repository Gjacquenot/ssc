/*
 * YamlParser.hpp
 *
 * \date 27 ao�t 2012, 13:05:23
 *  \author cec
 */

#ifndef YAMLPARSER_HPP_
#define YAMLPARSER_HPP_

#include "yaml.h"

class YamlParser
{
	public:
	virtual ~YamlParser() {}
	YamlParser(const std::string& contents_to_parse);


	protected:
		YAML::Node& convert_stream_to_yaml_node(const std::string& input_data, YAML::Node& node) const;
		YamlParser();
		std::string contents;
};


#endif /* YAMLPARSER_HPP_ */
