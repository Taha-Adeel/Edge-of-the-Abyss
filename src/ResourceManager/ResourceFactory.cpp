#include "ResourceFactory.h"

ResourceFactory& ResourceFactory::getResourceFactory(){
	static ResourceFactory instance;
	return instance;
}

ResourceFactory::ResourceFactory(): m_textures("png"), m_fonts("ttf"), m_sounds("wav"){}