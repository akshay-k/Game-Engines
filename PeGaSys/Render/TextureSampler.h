#pragma once


struct SamplerState
{
	// how to filter
	enum FilterE
	{
		FILTER_NO_MIPMAP, ///< Disable MIPmap.
		FILTER_LINEAR, ///< Linearly interpolate between samples.
		FILTER_NEAREST, ///< Use nearest sample.
	};
	//
	enum AddressE
	{
		ADDRESS_CLAMP, // Texture coordinates outside [0,1] use value at edge.
		ADDRESS_REPEAT, // Texture coordinates outside [0,1] repeat.
		ADDRESS_MIRROR // Texture coordinates outside [0,1] mirror repeat.
	};

	FilterE mMinFilter; ///< Filter mode when minimizing texture. Default is FILTER_LINEAR.
	FilterE mMagFilter; ///< Filter mode used when magnifying texture. Default is FILTER_LINEAR (Can't use mip maps here).
	FilterE mMipFilter; ///< Filter mode used with mipmaps. Default is FILTER_LINEAR.
	AddressE mAddressU;
	AddressE mAddressV;
};

class TextureSampler : public SamplerState
	{
	public:
		// set to default values
		TextureSampler()
		{
			mMinFilter = FILTER_LINEAR;
			mMagFilter = FILTER_LINEAR;
			mMipFilter = FILTER_LINEAR;
			mAddressU = ADDRESS_CLAMP;
			mAddressV = ADDRESS_CLAMP;
		}

		~TextureSampler();

		static GLenum SamplerState_FilterEnum(SamplerState::FilterE filter, SamplerState::FilterE mipFilter);
		static GLenum SamplerState_AddressEnum(SamplerState::AddressE address);
		static void SamplerState_Apply(const SamplerState & samplerState);

};





