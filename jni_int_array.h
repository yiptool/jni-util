/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#ifndef __e127d5650c2f556326ee823a3ba9ea40__
#define __e127d5650c2f556326ee823a3ba9ea40__

#include "jni_global_ref.h"

#if defined(__ANDROID__) || defined(USE_JNI_UTIL)

namespace JNI
{
	class IntArray : public GlobalRef<jintArray>
	{
	public:
		inline IntArray(JNIEnv * env, jintArray array)
			: GlobalRef<jintArray>(env, array)
		{
			m_Data = env->GetIntArrayElements(array, 0);
		}

		inline ~IntArray()
		{
			jniEnv()->ReleaseIntArrayElements(jintArray(*this), m_Data, 0);
		}

		inline jint & operator[](jint index) const noexcept
		{
			return m_Data[index];
		}

		inline operator jint * () const noexcept
		{
			return m_Data;
		}

	private:
		jint * m_Data;

		IntArray(const IntArray &) = delete;
		IntArray & operator=(const IntArray &) = delete;
	};
}

#endif // __ANDROID__ || USE_JNI_UTIL

#endif
