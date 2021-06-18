#include "ResourceFactory"

/**
 * @brief Returns a reference to the ResourceFactory.
 * 
 * Creates a new ResourceFactory first time it is called and returns that
 * instance whenever it is called again.
 * 
 * @return ResourceFactory& 
 */

ResourceFactory& ResourceFactory::getResourceFactory(){
	static ResourceFactory instance;
	return instance;
}

/**
 * @brief ResourceFactory constructor that initializes its internal AssetPools.
 * 
 * The AssetPools are initialized to search for the assets in "./assets/" folder(Default parameter),
 * and with their respective extensions.
 * 
 */

ResourceFactory::ResourceFactory(): textures("png"), fonts("ttf"), sounds("wav"){}