#include <iostream>
#ifndef MATRIX_H
#define MATFIX_H

#include <ostream>
#include <iterator>



/// ����� �������
template<class T>
class matrix
{
public:
	template<class T>
	class __iterator;

	/// ������������ ����������� typedef'�.
	typedef T               value_type;

	typedef value_type** pointer;
	typedef const pointer   const_pointer;

	typedef value_type& reference;
	typedef const reference const_reference;

	typedef __iterator<T>   iterator;

	typedef size_t          size_type;
	typedef ptrdiff_t       difference_type;

		/// ����������� �� ���������.
	explicit matrix() : matrix_(0), size_matrix(0)
	{
	}


	/// ����������� �����������.
	explicit matrix(const matrix& matrix__)
	{
		matrix_ = new value_type * [matrix__.size_matrix];
		for (int i = 0; i < matrix__.size_matrix; i++)
			matrix_[i] = new value_type[matrix__.size_matrix];

		for (int i = 0; i < matrix__.size_matrix; i++)
			for (int j = 0; j < matrix__.size_matrix; j++)
				matrix_[i][j] = matrix__.matrix_[i][j];

		size_matrix = matrix__.size_matrix;
	}

	///����������
	~matrix()
	{
		for (int i = 0; i < size_matrix; i++)
			delete[] matrix_[i];

		delete[] matrix_;
		std::cout << "Matrix deleted" << std::endl;
	}

	/// ���������� true, ���� ������� ������.
	bool empty() const
	{
		return size_matrix == 0;
	}

	///������� �������
	void clear()
	{
		for (int i = 0; i < size_matrix; i++)
			delete[] matrix_[i];

		delete[] matrix_;
		size_matrix = 0;
	}

	/// �������� ������������.
	matrix& operator=(matrix& matrix__)
	{
		if (size_matrix != matrix__.size_matrix) {
			for (int i = 0; i < size_matrix; i++)
				delete[] matrix_[i];

			delete[] matrix_;
			size_matrix = matrix__.size_matrix;
			matrix_ = new value_type * [size_matrix];
			for (int i = 0; i < size_matrix; i++)
				matrix_[i] = new value_type[size_matrix];
		}
		for (int i = 0; i < size_matrix; i++)
			for (int j = 0; j < size_matrix; j++)
				matrix_[i][j] = matrix__.matrix_[i][j];
	}
	
	///����� � �������
	void print_matrix()
	{
		for (int i = 0; i < size_matrix; i++)
		{
			for (int j = 0; j < size_matrix; j++)
			{
				std::cout << matrix_[i][j];
			}
			std::cout << std::endl;
		}
	}

	///���� ����������� ���������� ��� �������� ������� � �������
	reference change_connection_matrix(value_type row,value_type col)
	{
		return matrix_[row-1][col-1];
	}

	///���� ����������� ���������� ������� � �������
	const_reference view_connection_matrix(value_type row, value_type col) const
	{
		return  matrix_[row - 1][col - 1];
	}

	///���������� ������� � ����� �.�. ���������� ���������� ������� � �������� �� 1;
	void add_vertex()
	{
		value_type size___;
		size___ = size_matrix + 1;
		pointer matrix__ = new value_type * [size___];
		for (int i = 0; i < size___; i++)
			matrix__[i] = new value_type[size_matrix];

		for (int i = 0; i < size_matrix; i++)
			for (int j = 0; j < size_matrix; j++)
				matrix__[i][j] = matrix_[i][j];

		clear();
		matrix_ = matrix__;
		size_matrix = size___;
	}

	///�������� ������� � ����� �.�. ���������� ���������� ������� � �������� �� 1;
	void deletion_vertex()
	{
		value_type size___;
		size___ = size_matrix - 1;
		pointer matrix__ = new value_type * [size___];
		for (int i = 0; i < size___; i++)
			matrix__[i] = new value_type[size_matrix];

		for (int i = 0; i < size___; i++)
			for (int j = 0; j < size___; j++)
				matrix__[i][j] = matrix_[i][j];

		clear();
		matrix_ = matrix__;
		size_matrix = size___;
	}

	//1 ������� �������
	pointer begin()
	{
		return matrix_;
	}

	//��������� ������� �������	
	pointer end()
	{
		return matrix_[size_matrix][size_matrix];
	}

	//������������� ��������
	void init(pointer matrix__,size_type size__) 
	{
		size_matrix = size__;
		matrix_ = matrix__;
	}

	//����� ��������� � �������
	friend std::ostream& operator<<(std::ostream& out, iterator& a)
	{
		out << a.get_pos();
		return out;
	}

	///����� ����������
	template<class T>
	class __iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	private:

		pointer pos_;

	public:

		__iterator()
			: pos_(0)
		{
		}

		explicit __iterator(pointer pos)
			: pos_(pos)
		{
		}

		explicit __iterator(const __iterator& it)
			: pos_(it.pos_)
		{
		}

		pointer get_pos() { return pos_; }

		__iterator& operator=(const __iterator& it)
		{
			pos_ = it.pos_;
		}

		__iterator& operator++()
		{
			++pos_;
			return *this;
		}

		__iterator operator++(int)
		{
			__iterator tmp(*this);
			operator++();
			return tmp;
		}

		bool operator==(const __iterator& it)
		{
			return pos_ == it.pos_;
		}

		bool operator!=(const __iterator& it)
		{
			return pos_ != it.pos_;
		}

		reference operator*()
		{
			return *pos_;
		}

		pointer operator->()
		{
			return pos_;
		}

		__iterator& operator--()
		{
			--pos_;
			return *this;
		}

		__iterator operator--(int)
		{
			__iterator tmp(*this);
			operator--();
			return tmp;
		}

		reference operator[](const difference_type& n)
		{
			return pos_[n];
		}

		__iterator& operator+=(const difference_type& n)
		{
			pos_ += n;
			return *this;
		}

		__iterator operator+(const difference_type& n)
		{
			return __iterator(pos_ + n);
		}

		__iterator& operator-=(const difference_type& n)
		{
			pos_ -= n;
			return *this;
		}

		__iterator operator-(const difference_type& n)
		{
			return __iterator(pos_ - n);
		}

		bool operator<(const __iterator& it)
		{
			return pos_ < it.pos_;
		}

		bool operator>(const __iterator& it)
		{
			return pos_ > it.pos_;
		}

		bool operator<=(const __iterator& it)
		{
			return pos_ <= it.pos_;
		}

		bool operator>=(const __iterator& it)
		{
			return pos_ >= it.pos_;
		}
	};

private:
	pointer matrix_;//���������� ������
	size_type size_matrix;//������ �������
};

#endif
