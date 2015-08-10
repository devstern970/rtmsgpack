#include <msgpack.hpp>

#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <list>
#include <limits>

#include "test_allocator.hpp"

#include <gtest/gtest.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


using namespace std;

const unsigned int kLoop = 1000;
const unsigned int kElements = 100;

// strong typedefs
namespace test {

template <class Key>
struct equal_to : std::equal_to<Key> {
};

template <class Key>
struct less : std::less<Key> {
};

} // namespace test

TEST(MSGPACK_STL, simple_buffer_vector)
{
    typedef vector<int, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.push_back(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        EXPECT_EQ(ret.get().type, msgpack::type::ARRAY);
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_vector_char)
{
    typedef vector<char, test::allocator<char> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.push_back(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        EXPECT_EQ(ret.get().type, msgpack::type::BIN);
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_vector_bool)
{
    typedef vector<bool, test::allocator<bool> > type;
    type val1;
    for (unsigned int i = 0; i < kElements; i++)
        val1.push_back(i % 2 ? false : true);
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, val1);
    msgpack::unpacked ret;
    msgpack::unpack(ret, sbuf.data(), sbuf.size());
    EXPECT_EQ(ret.get().type, msgpack::type::ARRAY);
    type const& val2 = ret.get().as<type>();
    EXPECT_EQ(val1.size(), val2.size());
    EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
}


TEST(MSGPACK_STL, simple_buffer_assoc_vector)
{
    typedef msgpack::type::assoc_vector<int, int, test::less<int>, test::allocator<std::pair<int, int> > >type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        val1.push_back(std::make_pair(1, 2));
        val1.push_back(std::make_pair(3, 4));
        val1.push_back(std::make_pair(5, 6));
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_map)
{
    typedef map<int, int, test::less<int>, test::allocator<std::pair<int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1[rand()] = rand();
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_deque)
{
    typedef deque<int, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.push_back(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_list)
{
    typedef list<int, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.push_back(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type const& val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_set)
{
    typedef set<int, test::less<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_TRUE(equal(val1.begin(), val1.end(), val2.begin()));
    }
}

TEST(MSGPACK_STL, simple_buffer_pair)
{
    for (unsigned int k = 0; k < kLoop; k++) {
        pair<int, int> val1 = make_pair(rand(), rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        pair<int, int> val2 = ret.get().as<pair<int, int> >();
        EXPECT_EQ(val1.first, val2.first);
        EXPECT_EQ(val1.second, val2.second);
    }
}

TEST(MSGPACK_STL, simple_buffer_multimap)
{
    typedef multimap<int, int, test::less<int>, test::allocator<std::pair<int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++) {
            int i1 = rand();
            val1.insert(make_pair(i1, rand()));
            val1.insert(make_pair(i1, rand()));
        }
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<pair<int, int> > v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(make_pair(it->first, it->second));
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(make_pair(it->first, it->second));
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}

TEST(MSGPACK_STL, simple_buffer_multiset)
{
    typedef multiset<int, test::less<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<int> v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(*it);
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(*it);
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}

TEST(MSGPACK_TUPLE, simple_tuple)
{
    msgpack::sbuffer sbuf;
    msgpack::type::tuple<bool, std::string, double> val1(true, "kzk", 12.3);
    msgpack::pack(sbuf, val1);
    msgpack::unpacked ret;
    msgpack::unpack(ret, sbuf.data(), sbuf.size());
    msgpack::type::tuple<bool, std::string, double> val2
        = ret.get().as<msgpack::type::tuple<bool, std::string, double> >();
    EXPECT_EQ(ret.get().via.array.size, 3u);
    EXPECT_EQ(val1.get<0>(), val2.get<0>());
    EXPECT_EQ(val1.get<1>(), val2.get<1>());
    EXPECT_EQ(val1.get<2>(), val2.get<2>());
}

TEST(MSGPACK_TUPLE, simple_tuple_empty)
{
    msgpack::sbuffer sbuf;
    msgpack::type::tuple<> val1;
    msgpack::pack(sbuf, val1);
    msgpack::unpacked ret;
    msgpack::unpack(ret, sbuf.data(), sbuf.size());
    ret.get().as<msgpack::type::tuple<> >();
    EXPECT_EQ(ret.get().via.array.size, 0u);
}


// TR1

#if defined(MSGPACK_HAS_STD_TR1_UNORDERED_MAP) || defined(MSGPACK_HAS_STD_TR1_UNORDERED_SET)

#include <tr1/functional>

namespace test {

template <class Key>
struct tr1_hash : std::tr1::hash<Key> {
};

} // namespace test

#endif // defined(MSGPACK_HAS_STD_TR1_UNORDERED_MAP) || defined(MSGPACK_HAS_STD_TR1_UNORDERED_SET)

#ifdef MSGPACK_HAS_STD_TR1_UNORDERED_MAP
#include <tr1/unordered_map>
#include "msgpack/adaptor/tr1/unordered_map.hpp"
TEST(MSGPACK_TR1, simple_buffer_tr1_unordered_map)
{
    typedef tr1::unordered_map<int, int, test::tr1_hash<int>, test::equal_to<int>, test::allocator<std::pair<const int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1[rand()] = rand();
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it) {
            EXPECT_TRUE(val2.find(it->first) != val2.end());
            EXPECT_EQ(it->second, val2.find(it->first)->second);
        }
    }
}

TEST(MSGPACK_TR1, simple_buffer_tr1_unordered_multimap)
{
    typedef tr1::unordered_multimap<int, int, test::tr1_hash<int>, test::equal_to<int>, test::allocator<std::pair<int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++) {
            int i1 = rand();
            val1.insert(make_pair(i1, rand()));
            val1.insert(make_pair(i1, rand()));
        }
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<pair<int, int> > v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(make_pair(it->first, it->second));
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(make_pair(it->first, it->second));
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}
#endif

#ifdef MSGPACK_HAS_STD_TR1_UNORDERED_SET
#include <tr1/unordered_set>
#include "msgpack/adaptor/tr1/unordered_set.hpp"
TEST(MSGPACK_TR1, simple_buffer_tr1_unordered_set)
{
    typedef tr1::unordered_set<int, test::tr1_hash<int>, test::equal_to<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            EXPECT_TRUE(val2.find(*it) != val2.end());
    }
}

TEST(MSGPACK_TR1, simple_buffer_tr1_unordered_multiset)
{
    typedef tr1::unordered_multiset<int, test::tr1_hash<int>, test::equal_to<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<int> v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(*it);
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(*it);
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}
#endif

#if defined (MSGPACK_HAS_STD_UNORDERED_MAP) || defined (MSGPACK_HAS_STD_UNORDERED_SET)

#include <functional>

namespace test {

template <class Key>
struct hash : std::hash<Key> {
};

} // namespace test

#endif // defined (MSGPACK_HAS_STD_UNORDERED_MAP) || defined (MSGPACK_HAS_STD_UNORDERED_SET)

#ifdef MSGPACK_HAS_STD_UNORDERED_MAP
#include <unordered_map>
#include "msgpack/adaptor/tr1/unordered_map.hpp"
TEST(MSGPACK_TR1, simple_buffer_unordered_map)
{
    typedef unordered_map<int, int, test::hash<int>, test::equal_to<int>, test::allocator<std::pair<const int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1[rand()] = rand();
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it) {
            EXPECT_TRUE(val2.find(it->first) != val2.end());
            EXPECT_EQ(it->second, val2.find(it->first)->second);
        }
    }
}

TEST(MSGPACK_TR1, simple_buffer_unordered_multimap)
{
    typedef unordered_multimap<int, int, test::hash<int>, test::equal_to<int>, test::allocator<std::pair<const int, int> > > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++) {
            int i1 = rand();
            val1.insert(make_pair(i1, rand()));
            val1.insert(make_pair(i1, rand()));
        }
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<pair<int, int> > v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(make_pair(it->first, it->second));
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(make_pair(it->first, it->second));
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}
#endif

#ifdef MSGPACK_HAS_STD_UNORDERED_SET

#include <unordered_set>
#include "msgpack/adaptor/tr1/unordered_set.hpp"
TEST(MSGPACK_TR1, simple_buffer_unordered_set)
{
    typedef unordered_set<int, test::hash<int>, test::equal_to<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();
        EXPECT_EQ(val1.size(), val2.size());
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            EXPECT_TRUE(val2.find(*it) != val2.end());
    }
}

TEST(MSGPACK_TR1, simple_buffer_unordered_multiset)
{
    typedef unordered_multiset<int, test::hash<int>, test::equal_to<int>, test::allocator<int> > type;
    for (unsigned int k = 0; k < kLoop; k++) {
        type val1;
        for (unsigned int i = 0; i < kElements; i++)
            val1.insert(rand());
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, val1);
        msgpack::unpacked ret;
        msgpack::unpack(ret, sbuf.data(), sbuf.size());
        type val2 = ret.get().as<type>();

        vector<int> v1, v2;
        type::const_iterator it;
        for (it = val1.begin(); it != val1.end(); ++it)
            v1.push_back(*it);
        for (it = val2.begin(); it != val2.end(); ++it)
            v2.push_back(*it);
        EXPECT_EQ(val1.size(), val2.size());
        EXPECT_EQ(v1.size(), v2.size());
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        EXPECT_TRUE(v1 == v2);
    }
}
#endif
