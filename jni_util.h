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
#ifndef __d56685bc6669ab2ebf2dd186179f19f4__
#define __d56685bc6669ab2ebf2dd186179f19f4__

#if defined(__ANDROID__) || defined(USE_JNI_UTIL)

#include <jni.h>
#include <functional>
#include <string>

namespace JNI
{
	class Exception
	{
	};
}

void jniCheckException(JNIEnv * env);
void jniTryCatch(JNIEnv * env, const std::function<void()> & body);

jclass jniGetClass(JNIEnv * env, const char * name);
jclass jniGetClass(JNIEnv * env, const std::string & name);
std::string jniGetClassName(JNIEnv * env, jclass cls);

std::string jniGetStringUTFChars(JNIEnv * env, jstring string);
jstring jniNewStringUTF(JNIEnv * env, const char * str);
jstring jniNewStringUTF(JNIEnv * env, const std::string & str);

jmethodID jniGetClassMethod(JNIEnv * env, jclass cls, const char * name, const char * signature);
jmethodID jniGetObjectMethod(JNIEnv * env, jobject obj, const char * name, const char * signature);

jint jniSetException(JNIEnv * env, const char * className, const char * message) noexcept;
jint jniSetException(JNIEnv * env, const char * className, const std::string & message) noexcept;

#endif // __ANDROID__ || USE_JNI_UTIL

#endif
