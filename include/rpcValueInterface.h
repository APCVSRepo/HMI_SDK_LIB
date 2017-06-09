#ifndef RPCVALUEINTERFACE_H
#define RPCVALUEINTERFACE_H

#include <string>

class rpcValueInterface
{
public:
	/// Return true if the object has a member named key.
	/// \note 'key' must be null-terminated.
	virtual  bool isMember(const char* key) const = 0;
	/// Return true if the object has a member named key.
	/// \param key may contain embedded nulls.
	//virtual  bool isMember(const JSONCPP_STRING& key) const = 0;
	/// Same as isMember(JSONCPP_STRING const& key)const
	virtual  bool isMember(const char* begin, const char* end) const = 0;

	/// Access an array element (zero based index ).
	/// If the array contains less than index element, then null value are
	/// inserted
	/// in the array so that its size is index+1.
	/// (You may need to say 'value[0u]' to get your compiler to distinguish
	///  this from the operator[] which takes a string.)
	virtual  rpcValueInterface& operator[](int index) = 0;

	/// Access an array element (zero based index )
	/// (You may need to say 'value[0u]' to get your compiler to distinguish
	///  this from the operator[] which takes a string.)
	virtual  const rpcValueInterface& operator[](int index) const = 0;

	/// Access an object value by name, create a null member if it does not exist.
	/// \note Because of our implementation, keys are limited to 2^30 -1 chars.
	///  Exceeding that will cause an exception.

	virtual  rpcValueInterface& operator[](const char* key) = 0;
	/// Access an object value by name, returns null if there is no member with
	/// that name.
	virtual  const rpcValueInterface& operator[](const char* key) const = 0;

	virtual  int asInt() const = 0;
	virtual  unsigned int asUInt() const = 0;
	virtual  float asFloat() const = 0;
	virtual  double asDouble() const = 0;
	virtual  bool asBool() const = 0;
	virtual  std::string asString() const = 0;

	virtual  bool isNull() const = 0;
	virtual  bool isBool() const = 0;
	virtual  bool isInt() const = 0;
	virtual  bool isInt64() const = 0;
	virtual  bool isUInt() const = 0;
	virtual  bool isUInt64() const = 0;
	virtual  bool isIntegral() const = 0;
	virtual  bool isDouble() const = 0;
	virtual  bool isNumeric() const = 0;
	virtual  bool isString() const = 0;
	virtual  bool isArray() const = 0;
	virtual  bool isObject() const = 0;

	/// Number of values in array or object
	virtual  unsigned int size() const = 0;

};

#endif // RPCVALUEINTERFACE_H
