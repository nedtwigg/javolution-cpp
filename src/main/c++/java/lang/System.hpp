/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include "java/lang/String.hpp"
#include "java/lang/Class.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "iostream"

namespace java {
namespace lang {

// TODO: Move to java.io.PrintStream
class OutPrintStream: public Object {
	static const Class CLASS;
public:

	void println() const {
		synchronized(CLASS){
		std::cout << std::endl << std::flush;
	}
}

template<typename T> void print(T t) const {
	synchronized(CLASS) {
		std::cout << String::valueOf(t).toUTF8() << std::flush;
	}
}
template<typename T> void println(T t) const {
	synchronized(CLASS) {
		std::cout << String::valueOf(t).toUTF8() << std::endl << std::flush;
	}
}
};

// TODO: Move to java.io.PrintStream
class ErrPrintStream: public Object {
	static const Class CLASS;
public:

	void println() const {
		synchronized(CLASS){
		std::cerr << std::endl << std::flush;
	}
}
template<typename T> void print(T t) const {
	synchronized(CLASS) {
		std::cerr << String::valueOf(t).toUTF8() << std::flush;
	}
}
template<typename T> void println(T t) const {
	synchronized(CLASS) {
		std::cerr << String::valueOf(t).toUTF8() << std::endl << std::flush;
	}
}
};

/**
 * The System class contains several useful class fields and methods.
 *
 * @version 7.0
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/System.html">
 *       Java - System</a>
 */
class System {

	/** Utility class, cannot be instantiated. */
	System() {
	}

public:

	/** Standard output stream (UTF-8 encoding). */
	static const OutPrintStream out;

	/** Standard error stream (UTF-8 encoding). */
	static const ErrPrintStream err;

	/**
	 * Copies an array from the specified source array, beginning at the specified position, to the specified
	 * position of the destination array. This method ensures that copy constructors of the array elements (if any)
	 * are being called.
	 *
	 * @throws IndexOutOfBoundsException if <code>(srcPos+length &gt; src.length)
	 *          || (dstPos+length &gt; dst.length)</code>
	 */
	template<typename E> static void arraycopy(const Array<E>& src, int srcPos, Array<E>& dst, int dstPos, int length) {
		if ((srcPos < 0) || (dstPos < 0) || (length < 0) || (srcPos + length > src.length)
				|| (dstPos + length > dst.length))
			throw IndexOutOfBoundsException("srcPos: " + String::valueOf(srcPos) +
			        ", dstPos: " + String::valueOf(dstPos) + ", length: " + String::valueOf(length));
		for (int i = 0; i < length; ++i) {
			dst[dstPos + i] = src[srcPos + i]; // TODO: Use forEach(lambda)
		}
	}

	/** Returns the current time in milliseconds (the difference, measured in milliseconds, between the current time and
	 *  midnight, January 1, 1970 UTC). */
	static Type::int64 currentTimeMillis();

};

}
}
