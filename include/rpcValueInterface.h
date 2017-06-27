/**
* @file			rpcValueInterface.h  
* @brief		rpc数据读取接口
* @author		fanqiang
* @date			2017-6-21 
* @version		A001 
* @copyright	ford                                                              
*/

#ifndef RPCVALUEINTERFACE_H
#define RPCVALUEINTERFACE_H

#include <string>

class rpcValueInterface
{
public:
	/** 
	 * 判断是否存在某个字段
	 * @param[in]	key		字段名，空字符结尾
	 * @return		如果对象具有指定字段名的成员，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isMember(const char* key) const = 0;

	/** 
	 * 通过基于零的索引访问数组元素
	 * @param[in]	index		文件名长度
	 * @return		rpcValueInterface& rpc数据结构
	 * @ref			
	 * @see			
	 * @note		在数组大小为索引+ 1，如果数组包含元素数小于索引，则会返回null
	 */ 
	virtual  rpcValueInterface& operator[](int index) = 0;

	/** 
	 * 通过基于零的索引访问数组元素
	 * @param[in]	index		文件名长度
	 * @return		rpcValueInterface& rpc数据结构
	 * @ref			
	 * @see			
	 * @note		在数组大小为索引+ 1，如果数组包含元素数小于索引，则会返回null，返回值不能修改
	 */ 
	virtual  const rpcValueInterface& operator[](int index) const = 0;

	/** 
	 * 通过字段关键字访问对象元素
	 * @param[in]	key		字段关键字字符串
	 * @return		rpcValueInterface& rpc数据结构
	 * @ref			
	 * @see			
	 * @note		如果不存在，则创建空成员，关键字被限制为2^30-1个字符，超过该值将导致异常
	 */ 
	virtual  rpcValueInterface& operator[](const char* key) = 0;

	/** 
	 * 通过字段关键字访问对象元素
	 * @param[in]	key		字段关键字字符串
	 * @return		rpcValueInterface& rpc数据结构
	 * @ref			
	 * @see			
	 * @note		如果不存在，则创建空成员，关键字被限制为2^30-1个字符，超过该值将导致异常，返回值不能修改
	 */ 
	virtual  const rpcValueInterface& operator[](const char* key) const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为int类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  int asInt() const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为unsigned int类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  unsigned int asUInt() const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为float类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  float asFloat() const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为double类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  double asDouble() const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为bool类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool asBool() const = 0;

	/** 
	 * 将当前rpcValueInterface对象转换为std::string类型
	 * @return		rpcValueInterface数据值
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  std::string asString() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为空类型
	 * @return		为空类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isNull() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为bool类型
	 * @return		为bool类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isBool() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为int类型
	 * @return		为int类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isInt() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为64位int类型
	 * @return		为64位int类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isInt64() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为unsigned int类型
	 * @return		为unsigned int类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isUInt() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为64位unsigned int类型
	 * @return		为64位unsigned int类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isUInt64() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为整数类型
	 * @return		为整数类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isIntegral() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为double类型
	 * @return		为double类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isDouble() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为数字类型
	 * @return		为数字类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */
	virtual  bool isNumeric() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为字符串类型
	 * @return		为字符串类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */  
	virtual  bool isString() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为数组类型
	 * @return		为数组类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isArray() const = 0;

	/** 
	 * 判断当前rpcValueInterface对象是否为对象类型
	 * @return		为对象类型，则返回true
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  bool isObject() const = 0;

	/** 
	 * 获取对象或数组的元素个数
	 * @return		对象或数组的元素个数
	 * @ref			
	 * @see			
	 * @note		
	 */ 
	virtual  unsigned int size() const = 0;
};

#endif // RPCVALUEINTERFACE_H
