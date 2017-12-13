#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "TextureSampler.h"



TextureSampler::~TextureSampler()
{
}

/*
Given SamplerState fields, return GLenum value. 
*/
 GLenum TextureSampler::SamplerState_FilterEnum(SamplerState::FilterE filter, SamplerState::FilterE mipFilter)
{
	// if not using mipmaps
	if (SamplerState::FILTER_NO_MIPMAP == mipFilter)
	{
		switch (filter)
		{
		case SamplerState::FILTER_NEAREST: return GL_NEAREST; break;
		case SamplerState::FILTER_LINEAR: return GL_LINEAR; break;
		default:
			std::cout << "Input filter is not a valid filter value." << filter << std::endl;
			std::cout << "filter: " << filter << std::endl;
			std::cout << "mipFilter: " << mipFilter << std::endl;
			break;
		}
	}
	// if using mipmaps w/ nearest filtering
	else if (SamplerState::FILTER_NEAREST == mipFilter)
	{
		switch (filter)
		{
		case SamplerState::FILTER_NEAREST: return GL_NEAREST_MIPMAP_NEAREST; break;
		case SamplerState::FILTER_LINEAR: return GL_NEAREST_MIPMAP_LINEAR; break;
		default:
			std::cout << "Input filter is not a valid filter value." << std::endl;
			std::cout << "filter: " << filter << std::endl;
			std::cout << "mipFilter: " << mipFilter << std::endl;
			break;
		}
	}
	// if using mipmaps w/ linear filtering
	else if (SamplerState::FILTER_LINEAR == mipFilter)
	{
		switch (filter)
		{
		case SamplerState::FILTER_NEAREST: return GL_LINEAR_MIPMAP_NEAREST; break;
		case SamplerState::FILTER_LINEAR: return GL_LINEAR_MIPMAP_LINEAR; break;
		default:
			std::cout << "Input filter is not a valid filter value." << std::endl;
			std::cout << "filter: " << filter << std::endl;
			std::cout << "mipFilter: " << mipFilter << std::endl;
			break;
		}
	}
	return GL_NEAREST;
}

GLenum TextureSampler::SamplerState_AddressEnum(SamplerState::AddressE address)
{
	switch (address)
	{
	case SamplerState::ADDRESS_CLAMP: return GL_CLAMP_TO_EDGE; break;
	case SamplerState::ADDRESS_REPEAT: return GL_REPEAT; break;
	case SamplerState::ADDRESS_MIRROR: return GL_MIRRORED_REPEAT; break;
	default:
		std::cout << "Input address is not a valid address value." << address << std::endl;
		std::cout << "address: " << address << std::endl;
		break;
	}
	return GL_CLAMP_TO_EDGE;
}

void TextureSampler::SamplerState_Apply(const SamplerState & samplerState)
{
	{
		GLenum minFilter = SamplerState_FilterEnum(samplerState.mMinFilter, samplerState.mMipFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	}
	{
		GLenum magFilter = SamplerState_FilterEnum(samplerState.mMagFilter, SamplerState::FILTER_NO_MIPMAP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}
	{
		GLenum addressU = SamplerState_AddressEnum(samplerState.mAddressU);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, addressU);
	}
	{
		GLenum addressV = SamplerState_AddressEnum(samplerState.mAddressV);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, addressV);
	}

}
