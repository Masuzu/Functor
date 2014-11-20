#ifndef __SMART_FA0NCTOR_H__
#define __SMART_FA0NCTOR_H__

#include <memory>

template<typename R>
class SmartFunctorBase
{
public:
	virtual ~SmartFunctorBase() {}
	virtual R operator()(void *, void *, void *)	const	{ return R(); };
	virtual R operator()(void *, void *)	const	{ return R(); };
	virtual R operator()(void *)	const	{ return R(); };
	virtual R operator()()	const	{ return R(); };
};

#pragma region MemberFunctions

template<typename R, typename Class, typename A0>
class MemberFunction1 : public SmartFunctorBase<R>
{
public:
	//! Member function slot type.
	typedef R(Class::*MemberFunctionType)(A0);

	MemberFunction1(MemberFunctionType func, Class* obj, A0 arg) :
		function_(func),
		object_(obj),
		arg_(arg)
	{}

	MemberFunction1(MemberFunctionType func, Class* obj) :
		function_(func),
		object_(obj)
	{}

	virtual R operator()()	const	override
	{
		return (object_->*function_)(arg_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg));
	}

private:
	MemberFunctionType function_;
	Class* object_;
	A0 arg_;
};

template<typename R, typename Class, typename A0, typename A1>
class MemberFunction2 : public SmartFunctorBase<R>
{
public:
	//! Member function slot type.
	typedef R(Class::*MemberFunctionType)(A0, A1);

	MemberFunction2(MemberFunctionType func, Class* obj) :
		function_(func),
		object_(obj)
	{}

	virtual R operator()()	const	override
	{
		return (object_->*function_)(arg1_, arg2_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg), arg2_);
	}

	virtual R operator()(void *arg1, void *arg2)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2));
	}

private:
	MemberFunctionType function_;
	Class* object_;
	A0 arg1_;
	A1 arg2_;
};

template<typename R, typename Class, typename A0, typename A1, typename A2>
class MemberFunction3 : public SmartFunctorBase<R>
{
public:
	//! Member function slot type.
	typedef R(Class::*MemberFunctionType)(A0, A1, A2);

	MemberFunction3(MemberFunctionType func, Class* obj, A0 arg1, A1 arg2, A2 arg3) :
		function_(func),
		object_(obj),
		arg1_(arg1),
		arg2_(arg2),
		arg3_(arg3)
	{}

	MemberFunction3(MemberFunctionType func, Class* obj, A0 arg1, A1 arg2) :
		function_(func),
		object_(obj),
		arg1_(arg1),
		arg2_(arg2)
	{}

	MemberFunction3(MemberFunctionType func, Class* obj, A0 arg1) :
		function_(func),
		object_(obj),
		arg1_(arg1)
	{}

	MemberFunction3(MemberFunctionType func, Class* obj) :
		function_(func),
		object_(obj)
	{}

	virtual R operator()()	const	override
	{
		return (object_->*function_)(arg1_, arg2_, arg3_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg), arg2_, arg3_);
	}

	virtual R operator()(void *arg1, void *arg2)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2), arg3_);
	}

	virtual R operator()(void *arg1, void *arg2, void *arg3)	const	override
	{
		return (object_->*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2), *reinterpret_cast<A2*>(arg3));
	}

private:
	MemberFunctionType function_;
	Class* object_;
	A0 arg1_;
	A1 arg2_;
	A2 arg3_;
};

#pragma endregion MemberFunctions

#pragma region FunctionPointers

template<typename R, typename A0>
class FunctionPointer1 : public SmartFunctorBase<R>
{
public:
	typedef R(*FunctionType)(A0);

	FunctionPointer1(FunctionType function, A0 arg) :
		function_(function),
		arg_(arg)
	{}

	FunctionPointer1(FunctionType function) :
		function_(function)
	{}

	R operator()()	const	override
	{
		return (*function_)(arg_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg));
	}

private:
	FunctionType function_;
	A0 arg_;
};

template<typename R, typename A0, typename A1>
class FunctionPointerSlot2 : public SmartFunctorBase<R>
{
public:
	typedef R(*FunctionType)(A0, A1);

	FunctionPointerSlot2(FunctionType function, A0 arg1, A1 arg2) :
		function_(function),
		arg1_(arg1),
		arg1_(arg2)
	{}

	FunctionPointerSlot2(FunctionType function, A0 arg1) :
		function_(function),
		arg1_(arg1)
	{}

	FunctionPointerSlot2(FunctionType function) :
		function_(function)
	{}

	virtual R operator()()	const	override
	{
		return (*function_)(arg1_, arg2_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg), arg2_);
	}

	virtual R operator()(void *arg1, void *arg2)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2));
	}

private:
	FunctionType function_;
	A0 arg1_;
	A1 arg2_;
};

template<typename R, typename A0, typename A1, typename A2>
class FunctionPointerSlot3 : public SmartFunctorBase<R>
{
public:
	typedef R(*FunctionType)(A0, A1, A2);

	FunctionPointerSlot3(FunctionType function, A0 arg1, A1 arg2, A2 arg3) :
		function_(function),
		arg1_(arg1),
		arg1_(arg2),
		arg3_(arg3)
	{}

	FunctionPointerSlot3(FunctionType function, A0 arg1, A1 arg2) :
		function_(function),
		arg1_(arg1),
		arg1_(arg2)
	{}

	FunctionPointerSlot3(FunctionType function, A0 arg1) :
		function_(function),
		arg1_(arg1)
	{}

	FunctionPointerSlot3(FunctionType function) :
		function_(function)
	{}

	virtual R operator()()	const	override
	{
		return (*function_)(arg1_, arg2_, arg3_);
	}

	virtual R operator()(void *arg)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg), arg2_, arg3_);
	}

	virtual R operator()(void *arg1, void *arg2)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2), arg3_);
	}

	virtual R operator()(void *arg1, void *arg2, void *arg3)	const	override
	{
		return (*function_)(*reinterpret_cast<A0*>(arg1), *reinterpret_cast<A1*>(arg2), *reinterpret_cast<A2*>(arg3));
	}

private:
	FunctionType function_;
	A0 arg1_;
	A1 arg2_;
	A2 arg3_;
};

#pragma endregion FunctionPointers

template<typename R>
class SmartFunctor
{
private:
	// Disabled default constructor
	SmartFunctor()	{}

public:
	SmartFunctor(const SmartFunctor &foo)
	{
		functor_ = foo.functor_;
	}

	R operator()()	const
	{
		return (*functor_)();
	}

	template<typename A0>
	R operator()(A0 arg)	const
	{
		return (*functor_)(&arg);
	}

	template<typename A0, typename A1>
	R operator()(A0 arg1, A1 arg2)	const
	{
		return (*functor_)(&arg1, &arg2);
	}

	template<typename A0, typename A1, typename A2>
	R operator()(A0 arg1, A1 arg2, A2 arg3)	const
	{
		return (*functor_)(&arg1, &arg2, &arg3);
	}

	template<typename R, typename Class, typename A0, typename A1>
	SmartFunctor(R(Class::*function)(A0, A1), Class& obj, A0 arg1, A1 arg2) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction2<R, Class, A0, A1>(function, &obj, arg1, arg2)))
	{}

	template<typename R, typename Class, typename A0, typename A1>
	SmartFunctor(R(Class::*function)(A0, A1), Class& obj, A0 arg) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction2<R, Class, A0, A1>(function, &obj, arg)))
	{}

	template<typename R, typename Class, typename A0, typename A1>
	SmartFunctor(R(Class::*function)(A0, A1), Class& obj) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction2<R, Class, A0, A1>(function, &obj)))
	{}

	template<typename R, typename Class, typename A0, typename A1, typename A2>
	SmartFunctor(R(Class::*function)(A0, A1, A2), Class& obj, A0 arg1, A1 arg2, A2 arg3) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction3<R, Class, A0, A1, A2>(function, &obj, arg1, arg2, arg3)))
	{}

	template<typename R, typename Class, typename A0, typename A1, typename A2>
	SmartFunctor(R(Class::*function)(A0, A1, A2), Class& obj, A0 arg1, A1 arg2) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction3<R, Class, A0, A1, A2>(function, &obj, arg1, arg2)))
	{}

	template<typename R, typename Class, typename A0, typename A1, typename A2>
	SmartFunctor(R(Class::*function)(A0, A1, A2), Class& obj, A0 arg1) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction3<R, Class, A0, A1, A2>(function, &obj, arg1)))
	{}

	template<typename R, typename Class, typename A0, typename A1, typename A2>
	SmartFunctor(R(Class::*function)(A0, A1, A2), Class& obj) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction3<R, Class, A0, A1, A2>(function, &obj)))
	{}

	template<typename R, typename Class, typename A0>
	SmartFunctor(R(Class::*function)(A0), Class& obj, A0 arg) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction1<R, Class, A0>(function, &obj, arg)))
	{}

	template<typename R, typename Class, typename A0>
	SmartFunctor(R(Class::*function)(A0), Class& obj) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new MemberFunction1<R, Class, A0>(function, &obj)))
	{}

	template<typename R, typename A0>
	SmartFunctor(R(*function)(A0), A0 arg) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new FunctionPointer1<R, A0>(function, arg)))
	{}

	template<typename R, typename A0>
	SmartFunctor(R(*function)(A0)) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new FunctionPointer1<R, A0>(function)))
	{}

	template<typename R, typename A0, typename A1>
	SmartFunctor(R(*function)(A0, A1), A0 arg1, A1 arg2) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new FunctionPointerSlot2<R, A0, A1>(function, arg1, arg2)))
	{}

	template<typename R, typename A0, typename A1>
	SmartFunctor(R(*function)(A0, A1), A0 arg1) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new FunctionPointerSlot2<R, A0, A1>(function, arg1)))
	{}

	template<typename R, typename A0, typename A1>
	SmartFunctor(R(*function)(A0, A1)) :
		functor_(std::shared_ptr<SmartFunctorBase<R>>(new FunctionPointerSlot2<R, A0, A1>(function)))
	{}

	void __stdcall Reset()
	{
		functor_.reset();
	}

private:
	//! Points to the internal functor object to which we are bound.
	std::shared_ptr<SmartFunctorBase<R>> functor_;
};

#endif