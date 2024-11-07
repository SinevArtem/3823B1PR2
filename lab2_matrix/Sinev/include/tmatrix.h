// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if(sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size more MAX_VECTOR_SIZE");
		if (sz <= 0)
			throw out_of_range("Vector size should be greater than zero");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)  // к-ор копирования
	{
		
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);

	}
	TDynamicVector(TDynamicVector&& v) noexcept // к-ор пермещения
	{
		pMem = nullptr;
		swap(*this, v);
	}
	~TDynamicVector()
	{
		delete[]pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;
		if (v.size() != sz)
		{
			T* p = new T[v.size()];
			delete[]pMem;
			sz = v.size();
			pMem = p;
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept // перемещающее пр-е
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](int ind)
	{
		if (ind < 0 || ind >= sz) {
			throw std::out_of_range("out_of_range");
		}
		return pMem[ind];
	}
	const T& operator[](int ind) const
	{
		if (ind < 0 || ind >= sz) {
			throw std::out_of_range("out_of_range");
		}
		return pMem[ind];
	}
	// индексация с контролем
	T& at(int ind)
	{
		if (ind < 0 || ind >= sz) {
			throw std::out_of_range("out_of_range");
		}
		return pMem[ind];
	}
	const T& at(int ind) const
	{
		if (ind < 0 || ind >= sz) {
			throw std::out_of_range("out_of_range");
		}
		
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.size()) return false;
		for (size_t i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i]) return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		if (sz != v.size()) return true;
		for (size_t i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i]) return true;
		}
		return false;
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + val;
		}
		return tmp;
	}
	TDynamicVector operator-(T val)
	{

		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - val;
		}
		return tmp;
	}
	TDynamicVector operator*(T val)
	{

		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.size())
			throw "v1 size != v2";
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		}
		return tmp;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.size())
			throw "v1 size != v2";
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - v.pMem[i];
			
		}
		return tmp;
	}
	T operator*(const TDynamicVector& v)// noexcept(noexcept(T()))
	{
		if (sz != v.size())
			throw "v1 size != v2";
		T tmp = 0;
		for (size_t i = 0; i < sz; i++)
		{
			tmp += pMem[i] * v.pMem[i];
		}
		return tmp;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) //10 on 1
	{
		if (sz > MAX_MATRIX_SIZE)
			throw out_of_range("Vector size more MAX_VECTOR_SIZE");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz); //10 on 10
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		TDynamicVector<T> tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp[i] = pMem[i] * v;
		}
		return tmp;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + m.pMem[i];
		}
		return tmp;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - m.pMem[i];
		}
		return tmp;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if(m.size()!=sz)
			throw "sz != m.sz";
		TDynamicMatrix tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				for (size_t k = 0; k < sz; k++)
				{
					tmp.pMem[i][j] += pMem[i][k] * m.pMem[i][j];
				}
			}
		}
		return tmp;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		int k = v.sz;
		for (int i = 0; i < k; i++)
		{
			ostr << v[i] << endl;
		}

		return ostr;
	}

	size_t size() const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::size();
	}
};

#endif
