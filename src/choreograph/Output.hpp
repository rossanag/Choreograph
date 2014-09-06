/*
 * Copyright (c) 2014 David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

namespace choreograph
{

//! Safe type for Choreograph outputs.
//! Disconnects applied Animation on destruction so you don't accidentally modify stale pointers.
template<typename T>
class Output
{
public:
	~Output()
	{
		disconnect();
	}

	//! Removes self from parent Animation.
	void disconnect()
	{
		if( mParent ) {
			mParent->removeOutput( this );
		}
	}

	Output<T>& operator= ( T value ) { mValue = value; return *this }

	//! Returns value.
	const T& 	value() const { return mValue; }

	//! Returns value.
	const T& 	operator() () const { return mValue; }
	//! Returns value.
	T&				operator() () { return mValue; }

	//! Cast to value type.
	operator const T&()	{ return mValue; }

	//! Returns pointer to value.
	const T* 	ptr() const { return &mValue; }
	//! Returns pointer to value.
	T*				ptr() const { return &mValue; }

private:
	T				mValue;
	Motion	*mInput;
};

} // namespace choreograph
