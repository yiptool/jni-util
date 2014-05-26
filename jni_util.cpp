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
#include "jni_util.h"
#include "jni_global_ref.h"
#include "jni_int_array.h"
#include <yip-imports/cxx-util/macros.h>
#include <yip-imports/cxx-util/fmt.h>
#include <new>
#include <stdexcept>

#if defined(__ANDROID__) || defined(USE_JNI_UTIL)

void jniCheckException(JNIEnv * env)
{
	if (UNLIKELY(env->ExceptionOccurred()))
		throw JNI::Exception();
}

void jniTryCatch(JNIEnv * env, const std::function<void()> & body)
{
	try
	{
		body();
	}
	catch (const JNI::Exception &)
	{
		if (UNLIKELY(!env->ExceptionOccurred()))
			jniSetException(env, "java/lang/InternalError", "JNI::Exception");
	}
	catch (const std::bad_alloc & e)
	{
		jniSetException(env, "java/lang/OutOfMemoryError", e.what());
	}
	catch (const std::exception & e)
	{
		jniSetException(env, "java/lang/RuntimeException", e.what());
	}
	catch (...)
	{
		jniSetException(env, "java/lang/RuntimeException", "Unhandled exception in C++ code.");
	}
}

jclass jniGetClass(JNIEnv * env, const char * name)
{
	name = (name ? name : "");

	jclass cls = env->FindClass(name);
	jniCheckException(env);

	if (UNLIKELY(!cls))
	{
		jniSetException(env, "java/lang/ClassNotFoundException", name);
		throw JNI::Exception();
	}

	return cls;
}

jclass jniGetClass(JNIEnv * env, const std::string & name)
{
	return jniGetClass(env, name.c_str());
}

std::string jniGetClassName(JNIEnv * env, jclass cls)
{
	if (UNLIKELY(!cls))
		return "<null>";

	jmethodID method = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");
	jniCheckException(env);

	if (UNLIKELY(!method))
		return "???";

	jstring name = jstring(env->CallObjectMethod(cls, method));
	jniCheckException(env);

	return jniGetStringUTFChars(env, name);
}

std::string jniGetStringUTFChars(JNIEnv * env, jstring string)
{
	std::string result;

	if (!string)
		return result;

	const char * data = env->GetStringUTFChars(string, 0);
	jniCheckException(env);

	try
	{
		result = (data ? data : "");
	}
	catch (...)
	{
		env->ReleaseStringUTFChars(string, data);
		jniCheckException(env);
		throw;
	}

	env->ReleaseStringUTFChars(string, data);
	jniCheckException(env);

	return result;
}

jstring jniNewStringUTF(JNIEnv * env, const char * str)
{
	jstring result = env->NewStringUTF(str ? str : "");
	jniCheckException(env);
	return result;
}

jstring jniNewStringUTF(JNIEnv * env, const std::string & str)
{
	jstring result = env->NewStringUTF(str.c_str());
	jniCheckException(env);
	return result;
}

jmethodID jniGetClassMethod(JNIEnv * env, jclass cls, const char * name, const char * signature)
{
	name = (name ? name : "");
	signature = (signature ? signature : "");

	jmethodID method = env->GetMethodID(cls, name, signature);
	jniCheckException(env);

	if (UNLIKELY(!method))
	{
		throw std::runtime_error(fmt() << "Method '" << name << signature
			<< "' was not found in class '" << jniGetClassName(env, cls) << "'.");
	}

	return method;
}

jmethodID jniGetObjectMethod(JNIEnv * env, jobject obj, const char * name, const char * signature)
{
	jclass cls = env->GetObjectClass(obj);
	jniCheckException(env);

	return jniGetClassMethod(env, cls, name, signature);
}

jint jniSetException(JNIEnv * env, const char * className, const char * message) noexcept
{
	className = (className ? className : "");
	message = (message ? message : "");

	jclass cls = env->FindClass(className);
	jniCheckException(env);

	if (LIKELY(cls))
		return env->ThrowNew(cls, message);

	return env->ThrowNew(env->FindClass("java/lang/ClassNotFoundException"), className);
}

jint jniSetException(JNIEnv * env, const char * className, const std::string & message) noexcept
{
	return jniSetException(env, className, message.c_str());
}

#endif // __ANDROID__ || USE_JNI_UTIL
