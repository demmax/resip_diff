/* C++ code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf -D -E -L C++ -t -k '*' --compare-strncmp -Z ParameterHash ParameterHash.gperf  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "ParameterHash.gperf"

#include <string.h>
#include <ctype.h>
#include "resip/stack/ParameterTypes.hxx"
namespace resip {
using namespace std;
#line 8 "ParameterHash.gperf"
struct params { const char *name; ParameterTypes::Type type; };
/* maximum key range = 313, duplicates = 0 */

class ParameterHash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static struct params *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
ParameterHash::hash (register const char *str, register unsigned int len)
{
  static unsigned short asso_values[] =
    {
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318,  10, 318,   5,   5, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318,   0,  85,   0,
       15,   5,  60,  40,  15,   0,   0,   0,  20,   0,
        5,   0,  35, 100,   0,  20,   0,   5,  45,   0,
       85,  35,  25, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318, 318, 318, 318, 318,
      318, 318, 318, 318, 318, 318
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)tolower(str[12])];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)tolower(str[11])];
      /*FALLTHROUGH*/
      case 11:
        hval += asso_values[(unsigned char)tolower(str[10])];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)tolower(str[9])];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)tolower(str[8])];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)tolower(str[7])];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)tolower(str[6])];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)tolower(str[5])];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)tolower(str[4])];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)tolower(str[3])];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)tolower(str[2])];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)tolower(str[1])];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)tolower(str[0])];
        break;
    }
  return hval;
}

struct params *
ParameterHash::in_word_set (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 95,
      MIN_WORD_LENGTH = 1,
      MAX_WORD_LENGTH = 13,
      MIN_HASH_VALUE = 5,
      MAX_HASH_VALUE = 317
    };

  static struct params wordlist[] =
    {
#line 23 "ParameterHash.gperf"
      {"actor", ParameterTypes::actor},
#line 58 "ParameterHash.gperf"
      {"nc", ParameterTypes::nc},
#line 67 "ParameterHash.gperf"
      {"uri", ParameterTypes::uri},
#line 101 "ParameterHash.gperf"
      {"cterm", ParameterTypes::cterm},
#line 32 "ParameterHash.gperf"
      {"name", ParameterTypes::name},
#line 56 "ParameterHash.gperf"
      {"id", ParameterTypes::id},
#line 10 "ParameterHash.gperf"
      {"data", ParameterTypes::data},
#line 57 "ParameterHash.gperf"
      {"nonce", ParameterTypes::nonce},
#line 54 "ParameterHash.gperf"
      {"cnonce", ParameterTypes::cnonce},
#line 39 "ParameterHash.gperf"
      {"lr", ParameterTypes::lr},
#line 37 "ParameterHash.gperf"
      {"ttl", ParameterTypes::ttl},
#line 83 "ParameterHash.gperf"
      {"mode", ParameterTypes::mode},
#line 55 "ParameterHash.gperf"
      {"domain", ParameterTypes::domain},
#line 95 "ParameterHash.gperf"
      {"url", ParameterTypes::url},
#line 81 "ParameterHash.gperf"
      {"site", ParameterTypes::site},
#line 60 "ParameterHash.gperf"
      {"realm", ParameterTypes::realm},
#line 99 "ParameterHash.gperf"
      {"joined", ParameterTypes::joined},
#line 11 "ParameterHash.gperf"
      {"control", ParameterTypes::control},
#line 44 "ParameterHash.gperf"
      {"duration", ParameterTypes::duration},
#line 34 "ParameterHash.gperf"
      {"user", ParameterTypes::user},
#line 38 "ParameterHash.gperf"
      {"maddr", ParameterTypes::maddr},
#line 69 "ParameterHash.gperf"
      {"reason", ParameterTypes::reason},
#line 92 "ParameterHash.gperf"
      {"document", ParameterTypes::document},
#line 51 "ParameterHash.gperf"
      {"comp", ParameterTypes::comp},
#line 52 "ParameterHash.gperf"
      {"rport", ParameterTypes::rport},
#line 36 "ParameterHash.gperf"
      {"method", ParameterTypes::method},
#line 29 "ParameterHash.gperf"
      {"gr", ParameterTypes::gr},
#line 47 "ParameterHash.gperf"
      {"tag", ParameterTypes::tag},
#line 50 "ParameterHash.gperf"
      {"rinstance", ParameterTypes::rinstance},
#line 89 "ParameterHash.gperf"
      {"model", ParameterTypes::model},
#line 85 "ParameterHash.gperf"
      {"charset", ParameterTypes::charset},
#line 63 "ParameterHash.gperf"
      {"username", ParameterTypes::username},
#line 103 "ParameterHash.gperf"
      {"hadd", ParameterTypes::hadd},
#line 62 "ParameterHash.gperf"
      {"stale", ParameterTypes::stale},
#line 42 "ParameterHash.gperf"
      {"to-tag", ParameterTypes::toTag},
#line 79 "ParameterHash.gperf"
      {"size", ParameterTypes::size},
#line 94 "ParameterHash.gperf"
      {"network-user", ParameterTypes::networkUser},
#line 104 "ParameterHash.gperf"
      {"hdel", ParameterTypes::hdel},
#line 16 "ParameterHash.gperf"
      {"methods", ParameterTypes::methods},
#line 75 "ParameterHash.gperf"
      {"protocol", ParameterTypes::protocol},
#line 82 "ParameterHash.gperf"
      {"directory", ParameterTypes::directory},
#line 76 "ParameterHash.gperf"
      {"micalg", ParameterTypes::micalg},
#line 33 "ParameterHash.gperf"
      {"transport", ParameterTypes::transport},
#line 19 "ParameterHash.gperf"
      {"video", ParameterTypes::video},
#line 27 "ParameterHash.gperf"
      {"reg-id", ParameterTypes::regid},
#line 17 "ParameterHash.gperf"
      {"schemes", ParameterTypes::schemes},
#line 72 "ParameterHash.gperf"
      {"d-ver", ParameterTypes::dVer},
#line 88 "ParameterHash.gperf"
      {"vendor", ParameterTypes::vendor},
#line 15 "ParameterHash.gperf"
      {"priority", ParameterTypes::priority},
#line 21 "ParameterHash.gperf"
      {"type", ParameterTypes::type},
#line 102 "ParameterHash.gperf"
      {"ctype", ParameterTypes::ctype},
#line 84 "ParameterHash.gperf"
      {"server", ParameterTypes::server},
#line 90 "ParameterHash.gperf"
      {"version", ParameterTypes::version},
#line 49 "ParameterHash.gperf"
      {"received", ParameterTypes::received},
#line 53 "ParameterHash.gperf"
      {"algorithm", ParameterTypes::algorithm},
#line 70 "ParameterHash.gperf"
      {"d-alg", ParameterTypes::dAlg},
#line 14 "ParameterHash.gperf"
      {"events", ParameterTypes::events},
#line 28 "ParameterHash.gperf"
      {"ob", ParameterTypes::ob},
#line 100 "ParameterHash.gperf"
      {"left", ParameterTypes::left},
#line 98 "ParameterHash.gperf"
      {"orbit", ParameterTypes::orbit},
#line 13 "ParameterHash.gperf"
      {"description", ParameterTypes::description},
#line 35 "ParameterHash.gperf"
      {"ext", ParameterTypes::extension},
#line 24 "ParameterHash.gperf"
      {"text", ParameterTypes::text},
#line 80 "ParameterHash.gperf"
      {"permission", ParameterTypes::permission},
#line 93 "ParameterHash.gperf"
      {"app-id", ParameterTypes::appId},
#line 61 "ParameterHash.gperf"
      {"response", ParameterTypes::response},
#line 40 "ParameterHash.gperf"
      {"q", ParameterTypes::q},
#line 97 "ParameterHash.gperf"
      {"addtransport", ParameterTypes::addTransport},
#line 74 "ParameterHash.gperf"
      {"filename", ParameterTypes::filename},
#line 31 "ParameterHash.gperf"
      {"temp-gruu", ParameterTypes::tempGruu},
#line 18 "ParameterHash.gperf"
      {"application", ParameterTypes::application},
#line 41 "ParameterHash.gperf"
      {"purpose", ParameterTypes::purpose},
#line 46 "ParameterHash.gperf"
      {"handling", ParameterTypes::handling},
#line 48 "ParameterHash.gperf"
      {"branch", ParameterTypes::branch},
#line 22 "ParameterHash.gperf"
      {"isfocus", ParameterTypes::isFocus},
#line 43 "ParameterHash.gperf"
      {"from-tag", ParameterTypes::fromTag},
#line 73 "ParameterHash.gperf"
      {"smime-type", ParameterTypes::smimeType},
#line 26 "ParameterHash.gperf"
      {"+sip.instance", ParameterTypes::Instance},
#line 65 "ParameterHash.gperf"
      {"refresher", ParameterTypes::refresher},
#line 68 "ParameterHash.gperf"
      {"retry-after", ParameterTypes::retryAfter},
#line 20 "ParameterHash.gperf"
      {"language", ParameterTypes::language},
#line 96 "ParameterHash.gperf"
      {"sigcomp-id", ParameterTypes::sigcompId},
#line 64 "ParameterHash.gperf"
      {"early-only", ParameterTypes::earlyOnly},
#line 86 "ParameterHash.gperf"
      {"access-type", ParameterTypes::accessType},
#line 66 "ParameterHash.gperf"
      {"qop", ParameterTypes::qop},
#line 78 "ParameterHash.gperf"
      {"expiration", ParameterTypes::expiration},
#line 12 "ParameterHash.gperf"
      {"mobility", ParameterTypes::mobility},
#line 59 "ParameterHash.gperf"
      {"opaque", ParameterTypes::opaque},
#line 77 "ParameterHash.gperf"
      {"boundary", ParameterTypes::boundary},
#line 25 "ParameterHash.gperf"
      {"extensions", ParameterTypes::extensions},
#line 45 "ParameterHash.gperf"
      {"expires", ParameterTypes::expires},
#line 71 "ParameterHash.gperf"
      {"d-qop", ParameterTypes::dQop},
#line 30 "ParameterHash.gperf"
      {"pub-gruu", ParameterTypes::pubGruu},
#line 87 "ParameterHash.gperf"
      {"profile-type", ParameterTypes::profileType},
#line 91 "ParameterHash.gperf"
      {"effective-by", ParameterTypes::effectiveBy}
    };

  static signed char lookup[] =
    {
      -1, -1, -1, -1, -1,  0, -1,  1,  2, -1,  3, -1, -1, -1,
       4, -1, -1,  5, -1,  6,  7,  8,  9, 10, 11, -1, 12, -1,
      13, 14, 15, 16, 17, 18, 19, 20, 21, -1, 22, 23, 24, 25,
      26, 27, 28, 29, -1, 30, 31, 32, 33, 34, -1, -1, 35, -1,
      -1, 36, -1, 37, -1, -1, 38, 39, 40, -1, 41, -1, -1, 42,
      43, 44, 45, -1, -1, 46, 47, -1, 48, 49, 50, 51, 52, 53,
      54, 55, 56, 57, -1, 58, 59, 60, -1, 61, 62, 63, 64, -1,
      65, -1, -1, 66, 67, 68, 69, -1, 70, 71, 72, -1, -1, 73,
      74, 75, -1, 76, -1, -1, 77, 78, -1, 79, -1, 80, -1, 81,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, 82, 83, -1, 84, -1,
      85, -1, -1, -1, -1, -1, -1, -1, 86, -1, -1, 87, -1, 88,
      -1, 89, -1, 90, -1, -1, 91, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, 92, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
      -1, -1, -1, -1, -1, -1, -1, -1, -1, 94
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (tolower(*str) == *s && !strncasecmp (str + 1, s + 1, len - 1) && s[len] == '\0')
                return &wordlist[index];
            }
        }
    }
  return 0;
}
#line 105 "ParameterHash.gperf"

}
