#pragma once
#ifndef TYPEINFO_H
#define TYPEINFO_H
class TypeInfo
{
public:
	explicit TypeInfo(const char * strName = 0);
	virtual ~TypeInfo();

	bool operator==(const TypeInfo & that) const;
	bool operator!=(const TypeInfo & that) const;

	const char * Name() const;
	const static TypeInfo * InvalidType; ///< Special value indicating an invalid type identifier

private:
	const char * mName; ///< Name of this class. This must point to a static const string.
};

#endif // !TYPEINFO_H