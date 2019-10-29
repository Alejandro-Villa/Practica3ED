#ifndef VDinclude
#define VDinclude

#include<iostream>

template <class T>
class VD {
	private:
		T* datos;
		int nelementos;
	public:
		VD(int n=0);
		VD(const VD& original);
		~VD();

		unsigned size() const;
		T& operator[](int i);
		const T& operator[](int i) const;
		void add(T nuevo);
		void resize(int n);
		VD<T>& operator= (const VD<T>& original);
};

#include "VD.cpp"

#endif
