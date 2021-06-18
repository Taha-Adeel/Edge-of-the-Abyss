#ifndef ASSETPOOL_H
#define ASSETPOOL_H

#include <string>
#include <unordered_map>
#include <stdexcept>

/*
	Note:- Since AssetPool is a template class, the function definitions have to be done 
	in the same file. Hence no AssetPool.cpp
*/

/**
 * @brief Template class that keeps track of assets of typename Resource.
 * 
 * AssetPool only loads a resource from a file if it hadn't loaded it in before.As processing 
 * from a file takes time and consumes more memory it is an advantage.
 * 
 * @tparam Resource The type of resource that our AssetPool holds valid for sf::Texture,sf::Font,
 * st::SoundBuffer.
 */

template<typename Resource>
class AssetPool{
public:
	//Constructor

	/**
	 * @brief Construct a new Asset Pool object 
	 * 
	 * @param extention Extension of files from which Resources are to be loaded.
	 * @param folder Folder where our assets are located default as "./assets/"
	 */

    AssetPool(const std::string& extention, const std::string& folder = "./assets/"): 
										m_folder(folder), m_extention("." + extention){}

	//public member functions
    Resource& get(const std::string& name);
	bool exists(const std::string& name) const;
    void add(const std::string& name);

private:
	//private member variables
	const std::string m_folder;/**<Folder where our resources are located>*/
    const std::string m_extention;/**<extension of our file*/
    std::unordered_map<std::string, Resource> m_resources;/**<Holds the resources that are loaded*/

	//private memeber function
	std::string getFullFilename(const std::string& name);
};



/*Function Definitions*/

/**
 * @brief Gets the resource from the file "name".
 * 
 * If the required resource is not there then get function adds it to the assetpool and returns
 *  it or if it already exists then it directly returns it.
 * 
 * @tparam Resource 
 * @param name File name relative to m_folder.
 * @return const Resource& A reference to the resource at "name"
 */

template<typename Resource>
Resource& AssetPool<Resource>::get(const std::string& name){
	if (!exists(name)){
		add(name);
	}
	return m_resources.at(name);
}

/**
 * @brief Checks whether the resource from file "name" has been loaded in before or not. 
 * 
 * @tparam Resource 
 * @param name File name relative to m_folder. 
 * @return bool 
 */

template<typename Resource>
bool AssetPool<Resource>::exists(const std::string& name) const{
	return (m_resources.find(name) != m_resources.end());
}

/**
 * @brief Loads the resource from the file and adds it to m_resources.
 * 
 * Potentially throwing(Throws std::system_error if it fails to load from the file)
 * 
 * @tparam Resource 
 * @param name File name relative to m_folder.
 */

template<typename Resource>
void AssetPool<Resource>::add(const std::string& name){
	Resource res;

	// if the resource fails to load, then throw an exeption of type std::runtime_error
	if (!res.loadFromFile(getFullFilename(name))) 
		throw std::runtime_error("Failed to open file " + getFullFilename(name));
	else
		m_resources.insert(std::make_pair(name, res));
}

/**
 * @brief Returns full file relative path along with its extension.
 * 
 * @tparam Resource 
 * @param name File name relative to m_folder.
 * @return std::string 
 */

template<typename Resource>
std::string AssetPool<Resource>::getFullFilename(const std::string& name){
	return (m_folder + name + m_extention);
}

#endif