/***************************************************************************
 *   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura      *
 *   Copyright (C) 2000 - 2003, Richard J. Wagner                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef LRAND_H
#define LRAND_H

// Not thread safe (unless auto-initialization is avoided and each thread has
// its own Random object)

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

namespace LINA {

/// The Mersenne Twister is an algorithm for generating random numbers.
/** It was designed with consideration of the flaws in various other generators.
    The period, 2^19937-1, and the order of equidistribution, 623 dimensions,
    are far greater.  The generator is also fast; it avoids multiplication and
    division, and it benefits from caches and pipelines.  For more information
    see the inventors' web page at http://www.math.keio.ac.jp/~matumoto/emt.html */

class Random {
// Data
public:
	typedef unsigned long uint32;  // unsigned integer type, at least 32 bits
	
	enum { N = 624 };       // length of state vector
	enum { SAVE = N + 1 };  // length of array for save()

protected:
	enum { M = 397 };  // period parameter

	uint32 state[N];   // internal state
	uint32 *pNext;     // next value to get from state
	int left;          // number of values left before reload needed


//Methods
public:
	/// Constructor.
	/** Initialize with a simple uint32. */
	Random( const uint32& oneSeed );
	/// Constructor.
	/** Initialize with an array. */
	Random( uint32 *const bigSeed, uint32 const seedLength = N );
	/// Constructor.
	/** Auto-initialize with /dev/urandom or time() and clock().*/
	Random();

	// Do NOT use for CRYPTOGRAPHY without securely hashing several returned
	// values together, otherwise the generator state can be learned after
	// reading 624 consecutive values.
	
	// Access to 32-bit random numbers
	/// Real number in [0,1]
	double Rand();
	/// Real number in [0,n]
	double Rand( const double& n );
	/// Real number in [0,1]
	double RandExc();
	/// Real number in [0,n]
	double RandExc( const double& n );
	/// Real number in [0,1]
	double RandDblExc();
	/// Real number in [0,n]
	double RandDblExc( const double& n );
	/// Integer in [0,2^32-1]
	uint32 RandInt();
	/// Integer in [0,n] for n < 2^32
	uint32 RandInt( const uint32& n );
	/// Same as Rand()
	double operator()() { return rand(); }

	/// Access to 53-bit random numbers (capacity of IEEE double precision)
	/** Real number in [0,1) */
	double Rand53();

	/// Access to nonuniform random number distributions.
	double RandNorm( const double& mean = 0.0, const double& variance = 0.0 );

	/// Re-seeding functions with same behavior as initializers
	void Seed( const uint32 oneSeed );
	/// Re-seeding functions with same behavior as initializers
	void Seed( uint32 *const bigSeed, const uint32 seedLength = N );
	/// Re-seeding functions with same behavior as initializers
	void Seed();

	/// Saving generator state.
	/** To array of size SAVE*/
	void Save( uint32* saveArray ) const;
	/// Loading generator state.
	/** From such array */
	void Load( uint32 *const loadArray );
	/// Ostream operator.
	friend std::ostream& operator<<( std::ostream& os, const Random& lrand );
	/// Istream operator.
	friend std::istream& operator>>( std::istream& is, Random& lrand );

protected:
	void Initialize( const uint32 oneSeed );
	void Reload();
	uint32 HiBit( const uint32& u ) const { return u & 0x80000000UL; }
	uint32 LoBit( const uint32& u ) const { return u & 0x00000001UL; }
	uint32 LoBits( const uint32& u ) const { return u & 0x7fffffffUL; }
	uint32 MixBits( const uint32& u, const uint32& v ) const
		{ return HiBit(u) | LoBits(v); }
	uint32 Twist( const uint32& m, const uint32& s0, const uint32& s1 ) const
		{ return m ^ (MixBits(s0,s1)>>1) ^ (-LoBit(s1) & 0x9908b0dfUL); }
	static uint32 Hash( time_t t, clock_t c );
};


inline Random::Random( const uint32& oneSeed )
	{ Seed(oneSeed); }

inline Random::Random( uint32 *const bigSeed, const uint32 seedLength )
	{ Seed(bigSeed,seedLength); }

inline Random::Random()
	{ Seed(); }

inline double Random::Rand()
	{ return double(RandInt()) * (1.0/4294967295.0); }

inline double Random::Rand( const double& n )
	{ return Rand() * n; }

inline double Random::RandExc()
	{ return double(RandInt()) * (1.0/4294967296.0); }

inline double Random::RandExc( const double& n )
	{ return RandExc() * n; }

inline double Random::RandDblExc()
	{ return ( double(RandInt()) + 0.5 ) * (1.0/4294967296.0); }

inline double Random::RandDblExc( const double& n )
	{ return RandDblExc() * n; }

inline double Random::Rand53()
{
	uint32 a = RandInt() >> 5, b = RandInt() >> 6;
	return ( a * 67108864.0 + b ) * (1.0/9007199254740992.0);  // by Isaku Wada
}

inline double Random::RandNorm( const double& mean, const double& variance )
{
	// Return a real number from a normal (Gaussian) distribution with given
	// mean and variance by Box-Muller method
	double r = sqrt( -2.0 * log( 1.0-RandDblExc()) ) * variance;
	double phi = 2.0 * 3.14159265358979323846264338328 * RandExc();
	return mean + r * cos(phi);
}

inline Random::uint32 Random::RandInt()
{
	// Pull a 32-bit integer from the generator state
	// Every other access function simply transforms the numbers extracted here
	
	if( left == 0 ) Reload();
	--left;
		
	register uint32 s1;
	s1 = *pNext++;
	s1 ^= (s1 >> 11);
	s1 ^= (s1 <<  7) & 0x9d2c5680UL;
	s1 ^= (s1 << 15) & 0xefc60000UL;
	return ( s1 ^ (s1 >> 18) );
}

inline Random::uint32 Random::RandInt( const uint32& n )
{
	// Find which bits are used in n
	// Optimized by Magnus Jonsson (magnus@smartelectronix.com)
	uint32 used = n;
	used |= used >> 1;
	used |= used >> 2;
	used |= used >> 4;
	used |= used >> 8;
	used |= used >> 16;
	
	// Draw numbers until one is found in [0,n]
	uint32 i;
	do
		i = RandInt() & used;  // toss unused bits to shorten search
	while( i > n );
	return i;
}


inline void Random::Seed( const uint32 oneSeed )
{
	// Seed the generator with a simple uint32
	Initialize(oneSeed);
	Reload();
}


inline void Random::Seed( uint32 *const bigSeed, const uint32 seedLength )
{
	// Seed the generator with an array of uint32's
	// There are 2^19937-1 possible initial states.  This function allows
	// all of those to be accessed by providing at least 19937 bits (with a
	// default seed length of N = 624 uint32's).  Any bits above the lower 32
	// in each element are discarded.
	// Just call seed() if you want to get array from /dev/urandom
	Initialize(19650218UL);
	register int i = 1;
	register uint32 j = 0;
	register int k = ( N > seedLength ? N : seedLength );
	for( ; k; --k )
	{
		state[i] =
			state[i] ^ ( (state[i-1] ^ (state[i-1] >> 30)) * 1664525UL );
		state[i] += ( bigSeed[j] & 0xffffffffUL ) + j;
		state[i] &= 0xffffffffUL;
		++i;  ++j;
		if( i >= N ) { state[0] = state[N-1];  i = 1; }
		if( j >= seedLength ) j = 0;
	}
	for( k = N - 1; k; --k )
	{
		state[i] =
			state[i] ^ ( (state[i-1] ^ (state[i-1] >> 30)) * 1566083941UL );
		state[i] -= i;
		state[i] &= 0xffffffffUL;
		++i;
		if( i >= N ) { state[0] = state[N-1];  i = 1; }
	}
	state[0] = 0x80000000UL;  // MSB is 1, assuring non-zero initial array
	Reload();
}


inline void Random::Seed()
{
	// Seed the generator with an array from /dev/urandom if available
	// Otherwise use a hash of time() and clock() values
	
	// First try getting an array from /dev/urandom
	FILE* urandom = fopen( "/dev/urandom", "rb" );
	if( urandom )
	{
		uint32 bigSeed[N];
		register uint32 *s = bigSeed;
		register int i = N;
		register bool success = true;
		while( success && i-- )
			success = fread( s++, sizeof(uint32), 1, urandom );
		fclose(urandom);
		if( success ) { Seed( bigSeed, N );  return; }
	}
	
	// Was not successful, so use time() and clock() instead
	Seed( Hash( time(NULL), clock() ) );
}


inline void Random::Initialize( const uint32 seed )
{
	// Initialize generator state with seed
	// See Knuth TAOCP Vol 2, 3rd Ed, p.106 for multiplier.
	// In previous versions, most significant bits (MSBs) of the seed affect
	// only MSBs of the state array.  Modified 9 Jan 2002 by Makoto Matsumoto.
	register uint32 *s = state;
	register uint32 *r = state;
	register int i = 1;
	*s++ = seed & 0xffffffffUL;
	for( ; i < N; ++i )
	{
		*s++ = ( 1812433253UL * ( *r ^ (*r >> 30) ) + i ) & 0xffffffffUL;
		r++;
	}
}


inline void Random::Reload()
{
	// Generate N new values in state
	// Made clearer and faster by Matthew Bellew (matthew.bellew@home.com)
	register uint32 *p = state;
	register int i;
	for( i = N - M; i--; ++p )
		*p = Twist( p[M], p[0], p[1] );
	for( i = M; --i; ++p )
		*p = Twist( p[M-N], p[0], p[1] );
	*p = Twist( p[M-N], p[0], state[0] );

	left = N, pNext = state;
}


inline Random::uint32 Random::Hash( time_t t, clock_t c )
{
	// Get a uint32 from t and c
	// Better than uint32(x) in case x is floating point in [0,1]
	// Based on code by Lawrence Kirby (fred@genesis.demon.co.uk)

	static uint32 differ = 0;  // guarantee time-based seeds will change

	uint32 h1 = 0;
	unsigned char *p = (unsigned char *) &t;
	for( size_t i = 0; i < sizeof(t); ++i )
	{
		h1 *= UCHAR_MAX + 2U;
		h1 += p[i];
	}
	uint32 h2 = 0;
	p = (unsigned char *) &c;
	for( size_t j = 0; j < sizeof(c); ++j )
	{
		h2 *= UCHAR_MAX + 2U;
		h2 += p[j];
	}
	return ( h1 + differ++ ) ^ h2;
}


inline void Random::Save( uint32* saveArray ) const
{
	register uint32 *sa = saveArray;
	register const uint32 *s = state;
	register int i = N;
	for( ; i--; *sa++ = *s++ ) {}
	*sa = left;
}


inline void Random::Load( uint32 *const loadArray )
{
	register uint32 *s = state;
	register uint32 *la = loadArray;
	register int i = N;
	for( ; i--; *s++ = *la++ ) {}
	left = *la;
	pNext = &state[N-left];
}


inline std::ostream& operator<<( std::ostream& os, const Random& lrand )
{
	register const Random::uint32 *s = lrand.state;
	register int i = lrand.N;
	for( ; i--; os << *s++ << "\t" ) {}
	return os << lrand.left;
}


inline std::istream& operator>>( std::istream& is, Random& lrand )
{
	register Random::uint32 *s = lrand.state;
	register int i = lrand.N;
	for( ; i--; is >> *s++ ) {}
	is >> lrand.left;
	lrand.pNext = &lrand.state[lrand.N-lrand.left];
	return is;
}

} // end LINA namespace

#endif  // LRAND_H
