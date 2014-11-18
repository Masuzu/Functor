#ifndef __FUNCTOR_SLOT_H__FunctorSlotBase
#define __FUNCTOR_SLOT_H__

#include <memory>

template<typename R>
class FunctorSlotBase
{
public:
	virtual ~FunctorSlotBase() {}
	virtual R operator()(void *, void *, void *)	const = 0;
	virtual R operator()(void *, void *)	const = 0;
	virtual R operator()(void *)	const = 0;
	virtual R operator()()	const = 0;
};

template<typename R, typename T, typename U>
class MemberFunctionSlot1 : public FunctorSlotBase<R>
{
public:
	//! Member function slot type.
	typedef R(T::*MemberFunctionType)(U);

	MemberFunctionSlot1(MemberFunctionType func, T* obj, U arg) :
		d_function(func),
		d_object(obj),
		d_arg(arg)
	{}

	MemberFunctionSlot1(MemberFunctionType func, T* obj) :
		d_function(func),
		d_object(obj)
	{}

	virtual R operator()()	const
	{
		return (d_object->*d_function)(d_arg);
	}

	virtual R operator()(void *arg)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg));
	}

private:
	MemberFunctionType d_function;
	T* d_object;
	U d_arg;

	virtual R operator()(void *arg1, void *arg2)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1));
	}

	virtual R operator()(void *arg1, void *arg2, void *arg3)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1));
	}
};

template<typename R, typename T, typename U, typename V>
class MemberFunctionSlot2 : public FunctorSlotBase<R>
{
public:
	//! Member function slot type.
	typedef R(T::*MemberFunctionType)(U, V);

	MemberFunctionSlot2(MemberFunctionType func, T* obj, U arg1, V arg2) :
		d_function(func),
		d_object(obj),
		d_arg1(arg1),
		d_arg2(arg2)
	{}

	MemberFunctionSlot2(MemberFunctionType func, T* obj, U arg1) :
		d_function(func),
		d_object(obj),
		d_arg1(arg1)
	{}

	MemberFunctionSlot2(MemberFunctionType func, T* obj) :
		d_function(func),
		d_object(obj)
	{}

	virtual R operator()()	const
	{
		return (d_object->*d_function)(d_arg1, d_arg2);
	}

	virtual R operator()(void *arg)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg), d_arg2);
	}

	virtual R operator()(void *arg1, void *arg2)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1), reinterpret_cast<V>(arg2));
	}

private:
	MemberFunctionType d_function;
	T* d_object;
	U d_arg1;
	V d_arg2;

	virtual R operator()(void *arg1, void *arg2, void *arg3)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1), reinterpret_cast<V>(arg2));
	}
};

template<typename R, typename T, typename U, typename V, typename W>
class MemberFunctionSlot3 : public FunctorSlotBase<R>
{
public:
	//! Member function slot type.
	typedef R(T::*MemberFunctionType)(U, V, W);

	MemberFunctionSlot3(MemberFunctionType func, T* obj, U arg1, V arg2, W arg3) :
		d_function(func),
		d_object(obj),
		d_arg1(arg1),
		d_arg2(arg2),
		d_arg3(arg3)
	{}

	MemberFunctionSlot3(MemberFunctionType func, T* obj, U arg1, V arg2) :
		d_function(func),
		d_object(obj),
		d_arg1(arg1),
		d_arg2(arg2)
	{}

	MemberFunctionSlot3(MemberFunctionType func, T* obj, U arg1) :
		d_function(func),
		d_object(obj),
		d_arg1(arg1)
	{}

	MemberFunctionSlot3(MemberFunctionType func, T* obj) :
		d_function(func),
		d_object(obj)
	{}

	virtual R operator()()	const
	{
		return (d_object->*d_function)(d_arg1, d_arg2, d_arg3);
	}

	virtual R operator()(void *arg)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg), d_arg2, d_arg3);
	}

	virtual R operator()(void *arg1, void *arg2)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1), reinterpret_cast<V>(arg2), d_arg3);
	}

	virtual R operator()(void *arg1, void *arg2, void *arg3)	const
	{
		return (d_object->*d_function)(reinterpret_cast<U>(arg1), reinterpret_cast<V>(arg2), reinterpret_cast<W>(arg3));
	}

private:
	MemberFunctionType d_function;
	T* d_object;
	U d_arg1;
	V d_arg2;
	W d_arg3;
};

template<typename R, typename T, typename U>
class FunctionPointerSlot1 : public FunctorSlotBase<R>
{
public:
	FunctionPointerSlot1(T* function, U arg) :
		d_function(function),
		d_arg(arg)
	{}

	virtual R operator()()	const
	{
		return (*d_function)(d_arg);
	}

	virtual R operator()(void *arg)	const
	{
		return (*d_function)(reinterpret_cast<U>(arg));
	}

private:
	T* d_function;
	U d_arg;
};

template<typename R>
class Functor
{
public:
	Functor()
	{
	}

	Functor(const Functor &foo)
	{
		d_functor_impl = foo.d_functor_impl;
	}

	R operator()()	const
	{
		return (*d_functor_impl)();
	}

	template<typename U>
	R operator()(U arg)	const
	{
		return (*d_functor_impl)(arg);
	}

	template<typename U, typename V>
	R operator()(U arg1, V arg2)	const
	{
		return (*d_functor_impl)(arg1, arg2);
	}

	template<typename U, typename V, typename W>
	R operator()(U arg1, V arg2, W arg3)	const
	{
		return (*d_functor_impl)(arg1, arg2, arg3);
	}

	template<typename R, typename T, typename U, typename V>
	Functor(R(T::*function)(U, V), T* obj, U arg1, V arg2) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot2<R, T, U, V>(function, obj, arg1, arg2)))
	{}

	template<typename R, typename T, typename U, typename V>
	Functor(R(T::*function)(U, V), T* obj, U arg) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot2<R, T, U, V>(function, obj, arg)))
	{}

	template<typename R, typename T, typename U, typename V>
	Functor(R(T::*function)(U, V), T* obj) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot2<R, T, U, V>(function, obj)))
	{}

	template<typename R, typename T, typename U, typename V, typename W>
	Functor(R(T::*function)(U, V, W), T* obj, U arg1, V arg2, W arg3) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot3<R, T, U, V, W>(function, obj, arg1, arg2, arg3)))
	{}

	template<typename R, typename T, typename U, typename V, typename W>
	Functor(R(T::*function)(U, V, W), T* obj, U arg1, V arg2) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot3<R, T, U, V, W>(function, obj, arg1, arg2)))
	{}

	template<typename R, typename T, typename U, typename V, typename W>
	Functor(R(T::*function)(U, V, W), T* obj, U arg1) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot3<R, T, U, V, W>(function, obj, arg1)))
	{}

	template<typename R, typename T, typename U, typename V, typename W>
	Functor(R(T::*function)(U, V, W), T* obj) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot3<R, T, U, V, W>(function, obj)))
	{}

	template<typename R, typename T, typename U>
	Functor(R(T::*function)(U), T* obj, U arg) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot1<R, T, U>(function, obj, arg)))
	{}

	template<typename R, typename T, typename U>
	Functor(R(T::*function)(U), T* obj) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new MemberFunctionSlot1<R, T, U>(function, obj)))
	{}

	template<typename R, typename T, typename U>
	Functor(T* function, U arg) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new FunctionPointerSlot1<R, T, U>(function, arg)))
	{}

	template<typename R, typename T, typename U>
	Functor(T* function) :
		d_functor_impl(std::shared_ptr<FunctorSlotBase<R>>(new FunctionPointerSlot1<R, T, U>(function)))
	{}

	void __stdcall Reset()
	{
		d_functor_impl.reset();
	}

private:
	//! Points to the internal functor object to which we are bound.
	std::shared_ptr<FunctorSlotBase<R>> d_functor_impl;
};

template<typename T>	class MyFunctor;

template<typename Class, typename RC, typename A0>
class MyFunctor <RC(Class::*)(A0)>
{
	typedef RC(Class::*MemberFunction)(A0);

public:
	MyFunctor(RC(Class::*fn)(A0), Class &object) : fn_(fn), object_(&object)	{}
	RC operator()(A0 a0)	const{ return (object_->*fn_)(a0); }
private:
	MemberFunction fn_;
	Class *object_;
};

template<typename Class, typename RC, typename A0, typename A1>
class MyFunctor <RC(Class::*)(A0, A1)>
{
	typedef RC(Class::*MemberFunction)(A0, A1);

public:
	MyFunctor(RC(Class::*fn)(A0, A1), Class &object) : fn_(fn), object_(&object)	{}
	RC operator()(A0 a0, A1 a1)	const{ return (object_->*fn_)(a0, a1); }
private:
	MemberFunction fn_;
	Class *object_;
};

template<typename Class, typename RC, typename A0, typename A1, typename A2>
class MyFunctor <RC(Class::*)(A0, A1, A2)>
{
	typedef RC(Class::*MemberFunction)(A0, A1, A2);

public:
	MyFunctor(RC(Class::*fn)(A0, A1, A2), Class &object) : fn_(fn), object_(&object)	{}
	RC operator()(A0 a0, A1 a1, A2 a2)	const{ return (object_->*fn_)(a0, a1, a2); }
private:
	MemberFunction fn_;
	Class *object_;
};

#endif