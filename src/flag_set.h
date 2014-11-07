/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef X64ASM_SRC_FLAG_SET_H
#define X64ASM_SRC_FLAG_SET_H

#include "src/flag.h"

/** A compact representation of cpuid feature flag sets. */
namespace x64asm {

class FlagSet {
  public:
    /** Creates an empty flag set. */
    constexpr FlagSet() : mask_(0) {}
    /** Creates a flag set with a single element. */
    constexpr FlagSet(Flag f) : mask_((uint64_t)f) {}

    /** Creates an empty flag set. */
    static constexpr FlagSet empty() {
			return FlagSet();
		}
    /** Creates a full flag set. */
    static constexpr FlagSet universe() {
			return FlagSet((Flag)-1);
		}

    /** Inserts a flag into this set. */
    constexpr FlagSet operator+(Flag f) {
			return FlagSet((Flag)(mask_ | (uint64_t)f));
		}
    /** Removes a flag from this set. */
    constexpr FlagSet operator-(Flag f) {
  		return FlagSet((Flag)(mask_ & ~(uint64_t)f));
		}

    /** Inserts a flag into this set. */
		FlagSet& operator+=(Flag f) {
			mask_ |= (uint64_t)f;
			return *this;
		}
    /** Removes a flag from this set. */
		FlagSet& operator-=(Flag f) {
			mask_ &= ~(uint64_t)f;
			return *this;
		}

    /** Does this set contain a flag? */
		constexpr bool contains(Flag f) {
			return ((uint64_t)f & mask_) == (uint64_t)f;
		}
    /** Does this set subsume another set? */
		constexpr bool contains(FlagSet fs) {
			return ((uint64_t)fs.mask_ & mask_) == (uint64_t)fs.mask_;
		}

    /** Equality based on underlying bit mask. */
    constexpr bool operator==(FlagSet rhs) {
			return mask_ == rhs.mask_;
		}
    /** Equality based on underlying bit mask. */
    constexpr bool operator!=(FlagSet rhs) {
			return mask_ != rhs.mask_;
		}
    /** Equality based on underlying bit mask. */
    constexpr bool operator<(FlagSet rhs) {
			return mask_ < rhs.mask_;
		}

    /** STL compliant hash. */
		constexpr size_t hash() {
			return mask_;
		}
    /** STL compliant swap. */
    void swap(FlagSet rhs) {
			std::swap(mask_, rhs.mask_);
		}

  private:
    /** Underlying bitmask. */
    uint64_t mask_;  
};

} // namespace x64asm

namespace std {

/** STL hash specialization. */
template <>
struct hash<x64asm::FlagSet> {
  size_t operator()(const x64asm::FlagSet& fs) const {
  	return fs.hash();
	}
};

/** STL swap overload. */
inline void swap(x64asm::FlagSet& lhs, x64asm::FlagSet& rhs) {
  lhs.swap(rhs);
}

} // namespace std

#endif
