#ifndef B3_MANIPULATORS_HPP
#define B3_MANIPULATORS_HPP

#include <istream>

namespace manipulators
{
  template <typename Char, typename Traits>
  std::basic_istream<Char, Traits>& blank(std::basic_istream<Char, Traits>& input)
  {
    using istream_type = std::basic_istream<Char, Traits>;
    using streambuf_type = std::basic_streambuf<Char, Traits>;
    using int_type = typename istream_type::int_type;
    using ctype_type = std::ctype<Char>;

    const ctype_type& ct = std::use_facet<ctype_type>(input.getloc());
    const int_type eof = Traits::eof();
    streambuf_type* sb = input.rdbuf();
    int_type c = sb->sgetc();

    while (!Traits::eq_int_type(c, eof) && ct.is(std::ctype_base::blank, Traits::to_char_type(c)))
    {
      c = sb->snextc();
    }

    if (Traits::eq_int_type(c, eof))
    {
      input.setstate(std::ios_base::eofbit);
    }

    return input;
  }
}

#endif
