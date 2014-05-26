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
#ifndef __a6dabed02e9d7664cb8057c70020235e__
#define __a6dabed02e9d7664cb8057c70020235e__

#if defined(__ANDROID__) || defined(USE_JNI_UTIL)

#include <jni.h>

namespace JNI
{
	template <class TYPE> class GlobalRef
	{
	public:
		inline GlobalRef()
			: m_Env(nullptr),
			  m_Ref(0)
		{
		}

		inline GlobalRef(JNIEnv * env, TYPE value)
		{
			acquire(env, value);
		}

		inline GlobalRef(const GlobalRef & src)
		{
			acquire(src.m_Env, src.m_Ref);
		}

		inline ~GlobalRef()
		{
			release();
		}

		inline GlobalRef & operator=(const GlobalRef & src)
		{
			release();
			acquire(src.m_Env, src.m_Ref);
			return *this;
		}

		inline JNIEnv * jniEnv() const noexcept
		{
			return m_Env;
		}

		inline operator TYPE() const noexcept
		{
			return m_Ref;
		}

	private:
		JNIEnv * m_Env;
		TYPE m_Ref;

		void acquire(JNIEnv * env, TYPE value)
		{
			m_Env = nullptr;
			m_Ref = 0;

			if (env && value)
			{
				TYPE ref = TYPE(env->NewGlobalRef(value));
				jniCheckException(env);

				if (ref)
				{
					m_Env = env;
					m_Ref = ref;
				}
			}
		}

		void release()
		{
			if (m_Env && m_Ref)
			{
				JNIEnv * env = m_Env;
				env->DeleteGlobalRef(m_Ref);
				m_Env = nullptr;
				m_Ref = 0;
				jniCheckException(env);
			}
		}
	};
}

#endif // __ANDROID__ || USE_JNI_UTIL

#endif
