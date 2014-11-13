#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

template <typename T, T> class FunctorClass;

template <typename RC, typename Class,
	RC(Class::*Member)()>
class FunctorClass<RC(Class::*)(), Member>
{
public:
	FunctorClass(Class& object) : object_(&object) {}
	RC operator()() const { return (this->object_->*Member)(); }
private:
	Class* object_;
};

template <typename RC, typename Class, typename A0,
	RC(Class::*Member)(A0)>
class FunctorClass<RC(Class::*)(A0), Member>
{
public:
	FunctorClass(Class& object) : object_(&object) {}
	RC operator()(A0 a0) const { return (this->object_->*Member)(a0); }
private:
	Class* object_;
};

template <typename RC, typename Class, typename A0, typename A1,
	RC(Class::*Member)(A0, A1)>
class FunctorClass<RC(Class::*)(A0, A1), Member>
{
public:
	FunctorClass(Class& object) : object_(&object) {}
	RC operator()(A0 a0, A1 a1) const { return (this->object_->*Member)(a0, a1); }
private:
	Class* object_;
};

#endif