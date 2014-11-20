#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

template <typename T, T> class Functor;

template <typename R, typename Class,
	R(Class::*Member)()>
class Functor<R(Class::*)(), Member>
{
public:
	Functor(const Class& object) : object_(&object) {}
	R operator()() const { return (this->object_->*Member)(); }
private:
	Class* object_;
};

template <typename R, typename Class, typename A0,
	R(Class::*Member)(A0)>
class Functor<R(Class::*)(A0), Member>
{
public:
	Functor(Class& object) : object_(&object) {}
	R operator()(A0 a0) const { return (this->object_->*Member)(a0); }
private:
	Class* object_;
};

template <typename R, typename Class, typename A0, typename A1,
	R(Class::*Member)(A0, A1)>
class Functor<R(Class::*)(A0, A1), Member>
{
public:
	Functor(Class& object) : object_(&object) {}
	R operator()(A0 a0, A1 a1) const { return (this->object_->*Member)(a0, a1); }
private:
	Class* object_;
};

template <typename R, typename Class, typename A0, typename A1, typename A2,
	R(Class::*Member)(A0, A1)>
class Functor<R(Class::*)(A0, A1, A2), Member>
{
public:
	Functor(Class& object) : object_(&object) {}
	R operator()(A0 a0, A1 a1, A2 a2) const { return (this->object_->*Member)(a0, a1, a2); }
private:
	Class* object_;
};

#endif