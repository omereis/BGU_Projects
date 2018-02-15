//---------------------------------------------------------------------------

#ifndef Encode64H
#define Encode64H
//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
String base64_encode_str (unsigned char const *sz, unsigned int len);
String base64_decode_str (const String &s);
#endif
