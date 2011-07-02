#pragma once
#include "internal/message.hpp"
#include "macros.hpp"

#include "../std/exception.hpp"
#include "../std/string.hpp"

class RootException : public exception
{
public:
  RootException(char const * what, string const & msg) : m_What(what), m_Msg(msg)
  {
  }

  virtual ~RootException() throw()
  {
  }

  virtual char const * what() const throw()
  {
    size_t const count = m_Msg.size();

    string asciiMsg;
    asciiMsg.resize(count);

    for (size_t i = 0; i < count; ++i)
    {
      if (static_cast<unsigned char>(m_Msg[i]) < 128)
        asciiMsg[i] = char(m_Msg[i]);
      else
        asciiMsg[i] = '?';
    }

    static string msg;
    msg = string(m_What) + ", \"" + asciiMsg + "\"";
    return msg.c_str();
  }

  string const & Msg() const throw()
  {
    return m_Msg;
  }

private:
  char const * m_What;
  string m_Msg;
};

#define DECLARE_EXCEPTION(exception_name, base_exception) \
  class exception_name : public base_exception \
  { \
  public: \
    exception_name(char const * what, string const & msg) : base_exception(what, msg) {} \
  }

// TODO: Use SRC_LOGGING macro.
#define MYTHROW(exception_name, msg) throw exception_name( \
  #exception_name " " __FILE__ ":" TO_STRING(__LINE__), ::my::impl::Message msg)

#define MYTHROW1(exception_name, param1, msg) throw exception_name(param1, \
  #exception_name " " __FILE__ ":" TO_STRING(__LINE__), ::my::impl::Message msg)
