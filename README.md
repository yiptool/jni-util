
JNI Util
========

This is the small library of convenient C++ wrappers for Java Native Interface.

By default this library is meaningful only on Android. To use it on other platforms,
define the USE_JNI_UTIL preprocessor directive in your `Yipfile`.


Compiling this library
----------------------

This library is not intended to be built directly. Instead it is supposed
to be included into projects using the [Yip](https://github.com/yiptool/yip.git).

Use the `import jni-util` directive in your `Yipfile` to use this library.


License
=======

Copyright © 2014 Nikolay Zapolnov (zapolnov@gmail.com).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
