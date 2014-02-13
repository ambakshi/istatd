
#if !defined (istat_test_h)
#define istat_test_h

#include <cmath>
#include <sstream>
#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>

namespace istat
{
    int test(void (*func)(), int argc, char const *argv[]);
    void test_init_path(std::string const &path);

    void test_asserttrue(char const *file, int line, char const *expr, bool b);
    #define assert_true(x) istat::test_asserttrue(__FILE__, __LINE__, #x, x)
    void test_assertfalse(char const *file, int line, char const *expr, bool b);
    #define assert_false(x) istat::test_assertfalse(__FILE__, __LINE__, #x, x)
    void test_assertequal(char const *file, int line, char const *xa, char const *xb, char const *fail);
    void test_assertnotequal(char const *file, int line, char const *xa, char const *xb, char const *fail);
    void test_assertcontains(char const *file, int line, std::string const &haystack, std::string const &needle, std::string const &fail);
    #define assert_contains(h,n) istat::test_assertcontains(__FILE__, __LINE__, (h), (n), (std::string(#h) + " does not contain " + #n).c_str())
    void test_assert_does_not_contain(char const *file, int line, std::string const &haystack, std::string const &needle, std::string const &fail);
    #define assert_does_not_contain(h,n) istat::test_assert_does_not_contain(__FILE__, __LINE__, (h), (n), (std::string(#h) + " contains " + #n).c_str())
    std::string quote(std::string const &str);
    template<typename A, typename B> inline void test_assertequal(char const *file, int line, char const *xa, char const *xb, A const &a, B const &b)
    {
        std::stringstream ss;
        ss << quote(boost::lexical_cast<std::string>(a)) << " doesn't equal " <<
            quote(boost::lexical_cast<std::string>(b));
        test_assertequal(file, line, xa, xb, ss.str().c_str());
    }
    #define assert_equal(a,b) if ((a)==(b)) {} else { istat::test_assertequal(__FILE__, __LINE__, #a, #b, a, b); }
    template<typename A, typename B> inline void test_assertnotequal(char const *file, int line, char const *xa, char const *xb, A const &a, B const &b)
    {
        std::stringstream ss;
        ss << quote(boost::lexical_cast<std::string>(a)) << " equals " <<
            quote(boost::lexical_cast<std::string>(b));
        test_assertnotequal(file, line, xa, xb, ss.str().c_str());
    }
    #define assert_not_equal(a,b) if ((a)!=(b)) {} else { istat::test_assertnotequal(__FILE__, __LINE__, #a, #b, a, b); }

    void test_assertless(char const *file, int line, char const *xa, char const *xb, char const *fail);
    template<typename A, typename B> inline void test_assertless(char const *file, int line, char const *xa, char const *xb, A const &a, B const &b)
    {
        std::stringstream ss;
        ss << quote(boost::lexical_cast<std::string>(a)) << " not less than " <<
            quote(boost::lexical_cast<std::string>(b));
        test_assertless(file, line, xa, xb, ss.str().c_str());
    }
    #define assert_less_than(a,b) if ((a)<(b)) {} else { istat::test_assertless(__FILE__, __LINE__, #a, #b, a, b); }

    void test_assertgreater(char const *file, int line, char const *xa, char const *xb, char const *fail);
    template<typename A, typename B> inline void test_assertgreater(char const *file, int line, char const *xa, char const *xb, A const &a, B const &b)
    {
        std::stringstream ss;
        ss << quote(boost::lexical_cast<std::string>(a)) << " not greater than " <<
            quote(boost::lexical_cast<std::string>(b));
        test_assertgreater(file, line, xa, xb, ss.str().c_str());
    }
    #define assert_greater_than(a,b) if ((a)>(b)) {} else { istat::test_assertgreater(__FILE__, __LINE__, #a, #b, a, b); }

    void test_assertwithin(char const *file, int line, char const *xa, char const *xb, char const *fail);
    template<typename A, typename B, typename Dist> inline void test_assertwithin(char const *file, int line, char const *xa, char const *xb, const char *xdist, A const &a, B const &b, Dist const &dist)
    {
        std::stringstream ss;
        ss << quote(boost::lexical_cast<std::string>(a))
            << " not within " << dist << " of " <<
            quote(boost::lexical_cast<std::string>(b))
            << " (distance = " <<
            fabs(a - b)
            << ")";
        test_assertwithin(file, line, xa, xb, ss.str().c_str());
    }
    #define assert_within(a, b, dist) if (fabs((b) - (a)) < (dist)) {} else { istat::test_assertwithin(__FILE__, __LINE__, #a, #b, #dist, a, b, dist); }

    class CallCounter
    {
    public:
        CallCounter() : count_(0), value_(0), ret_(false) {}
        CallCounter(bool ret) : count_(0), value_(0), ret_(ret) {}
        void reset() { count_ = 0; value_ = 0; str_ = ""; ret_ = false; }
        mutable int64_t count_;
        mutable int64_t value_;
        mutable bool ret_;
        mutable std::string str_;
        bool operator()() const { call(); return ret_;} 
        void call() const { ++count_; }
        bool operator()(int64_t v) const { call(v); return ret_;}
        void call(int64_t v) const { ++count_; value_ += v; }
        bool operator()(std::string const &str) const { call(str); return ret_;}
        void call(std::string const &str) const { ++count_; str_ += str; }
    };
}

#endif  //  istat_test_h

