#ifndef TYPEEXG_MATLAB_MATRIXCLASSKKH_H
#define TYPEEXG_MATLAB_MATRIXCLASSKKH_H

// Copyright (C) 2017 Kyaw Kyaw Htike @ Ali Abdul Ghafur. All rights reserved.

#include "matrix_class_KKH.h"
#include "mex.h"
#include <cstring> // for memcpy

// this namespace contains helper functions to be used only in this file (not be called from outside)
// they are all put in a namespace to avoid clashing (resulting in linker errors) with other same
// function names in other header files
namespace hpers_TEMatlabMatKKH
{
	template<class T> inline mxClassID getMatlabType() { return mxUNKNOWN_CLASS; }
	template<> inline mxClassID getMatlabType<char>()				{ return mxINT8_CLASS; }
	template<> inline mxClassID getMatlabType<unsigned char>()		{ return mxUINT8_CLASS; }
	template<> inline mxClassID getMatlabType<short>()				{ return mxINT16_CLASS; }
	template<> inline mxClassID getMatlabType<unsigned short>()		{ return mxUINT16_CLASS; }
	template<> inline mxClassID getMatlabType<int>()				{ return mxINT32_CLASS; }
	template<> inline mxClassID getMatlabType<unsigned int>()		{ return mxUINT32_CLASS; }
	template<> inline mxClassID getMatlabType<long long>()			{ return mxINT64_CLASS; }
	template<> inline mxClassID getMatlabType<unsigned long long>() { return mxUINT64_CLASS; }
	template<> inline mxClassID getMatlabType<float>()				{ return mxSINGLE_CLASS; }
	template<> inline mxClassID getMatlabType<double>()				{ return mxDOUBLE_CLASS; }
}


template <typename T>
void matKKH2matlab(const Matk<T> &matIn, mxArray* &matOut)
{
	int nrows = matIn.nrows();
	int ncols = matIn.ncols();
	int nchannels = matIn.nchannels();
	
	const mwSize ndims = 3;
	mwSize dims[ndims] = { nrows, ncols, nchannels };
	matOut = mxCreateNumericArray(ndims, dims, hpers_TEMatlabMatKKH::getMatlabType<T>(), mxREAL);
	T *dst_pointer = (T*)mxGetData(matOut);
	T *src_pointer = matIn.get_ptr();
	
	std::memcpy(dst_pointer, src_pointer, sizeof(T)*nrows*ncols*nchannels);
}

template <typename T>
void matlab2matKKH(mxArray* matIn, Matk<T> &matOut)
{
	int ndims = (int)mxGetNumberOfDimensions(matIn);
	const size_t *dims = mxGetDimensions(matIn);
	unsigned int nrows = (unsigned int) dims[0];
	unsigned int ncols = (unsigned int) dims[1];
	unsigned int nchannels = ndims == 2 ? 1 : (unsigned int)dims[2];
	
	matOut.create(nrows, ncols, nchannels);
	
	T *src_pointer = (T*)mxGetData(matIn);
	T *dst_pointer = matOut.get_ptr();

	std::memcpy(dst_pointer, src_pointer, sizeof(T)*nrows*ncols*nchannels);
}

#endif