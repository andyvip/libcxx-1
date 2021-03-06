//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03

// <experimental/filesystem>

// class path

// path& replace_filename()

#include "filesystem_include.hpp"
#include <type_traits>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"
#include "count_new.hpp"
#include "filesystem_test_helper.hpp"


struct ReplaceFilenameTestcase {
  const char* value;
  const char* expect;
  const char* filename;
};

const ReplaceFilenameTestcase TestCases[] =
  {
      {"/foo", "/bar", "bar"}
    , {"/foo", "/", ""}
    , {"foo", "bar", "bar"}
    , {"/", "bar", "bar"}
    , {"\\", "bar", "bar"}
    , {"///", "bar", "bar"}
    , {"\\\\", "bar", "bar"}
    , {"\\/\\", "\\/bar", "bar"}
    , {".", "bar", "bar"}
    , {"..", "bar", "bar"}
    , {"/foo\\baz/bong/", "/foo\\baz/bong/bar", "bar"}
    , {"/foo\\baz/bong", "/foo\\baz/bar", "bar"}
  };

int main()
{
  using namespace fs;
  for (auto const & TC : TestCases) {
    path p(TC.value);
    assert(p == TC.value);
    path& Ref = (p.replace_filename(TC.filename));
    assert(p == TC.expect);
    assert(&Ref == &p);
    // Tests Effects "as-if": remove_filename() append(filename)
    {
      path p2(TC.value);
      path replace(TC.filename);
      p2.remove_filename();
      p2 /= replace;
      assert(p2 == p);
    }
  }
}
