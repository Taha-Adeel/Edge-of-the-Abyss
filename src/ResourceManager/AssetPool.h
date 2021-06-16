#ifndef ASSETPOOL_H
#define ASSETPOOL_H

#include <string>
#include <unordered_map>
#include <system_error>

/*
	Note:- Since AssetPool is a template class, the function definitions have to be done 
	in the same file. Hence no AssetPool.cpp
*/

template<typename Resource>
class AssetPool{
public:
	//Constructor
    AssetPool(const std::string& extention, const std::string& folder = "../assets/"): 
										m_folder(folder), m_extention("." + extention){}

	//public member functions
	const Resource& get(const std::string& name);
	bool exists(const std::string& name) const;
	void add(const std::string& name);

private:
	//private member variables
	const std::string m_folder;
    const std::string m_extention;
    std::unordered_map<std::string, Resource> m_resources;

	//private memeber function
	std::string getFullFilename(const std::string& name);
};



/*Function Definitions*/

template<typename Resource>
const Resource& AssetPool<Resource>::get(const std::string& name){
	if (!exists(name)){
		add(name);
	}
	return m_resources.at(name);
}

template<typename Resource>
bool AssetPool<Resource>::exists(const std::string& name) const{
	return (m_resources.find(name) != m_resources.end());
}

template<typename Resource>
void AssetPool<Resource>::add(const std::string& name){
	Resource res;

	// if the resource fails to load, then throw an exeption of type std::system_error
	if (!res.loadFromFile(getFullFilename(name))) 
		throw std::system_error("Failed to open file " + getFullFilename(name));
	else
		m_resources.insert(std::make_pair(name, res));
}

template<typename Resource>
std::string AssetPool<Resource>::getFullFilename(const std::string& name){
	return (m_folder + name + m_extention);
}

#endif