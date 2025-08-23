#define SOUFFLE_GENERATOR_VERSION "2.4"
#include "souffle/CompiledSouffle.h"
#include "souffle/SignalHandler.h"
#include "souffle/SouffleInterface.h"
#include "souffle/datastructure/BTree.h"
#include "souffle/io/IOSystem.h"
#include "souffle/profile/Logger.h"
#include "souffle/profile/ProfileEvent.h"
#include <any>
namespace functors {
extern "C" {
}
} //namespace functors
namespace souffle::t_btree_ii__1_0__0__11__10__01 {
using namespace souffle;
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :((ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))|| ((ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1])) && ((ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]))&&(ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
struct t_comparator_1{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :(0);
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]));
 }
};
using t_ind_1 = btree_multiset<t_tuple,t_comparator_1>;
t_ind_1 ind_1;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
t_ind_1::operation_hints hints_1_lower;
t_ind_1::operation_hints hints_1_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_1::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_1::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
range<t_ind_0::iterator> lowerUpperRange_01(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_01(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__1_0__0__11__10__01 
namespace souffle::t_btree_ii__1_0__0__11__10__01 {
using namespace souffle;
using t_ind_0 = Type::t_ind_0;
using t_ind_1 = Type::t_ind_1;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
ind_1.insert(t, h.hints_1_lower);
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
range<t_ind_1::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_1 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_1.end(), ind_1.end());
}
return make_range(ind_1.lower_bound(lower, h.hints_1_lower), ind_1.upper_bound(upper, h.hints_1_upper));
}
range<t_ind_1::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_10(lower,upper,h);
}
range<t_ind_0::iterator> Type::lowerUpperRange_01(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_01(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_01(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
ind_1.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [1,0]\n";
ind_0.printStats(o);
o << " arity 2 direct b-tree index 1 lex-order [0]\n";
ind_1.printStats(o);
}
} // namespace souffle::t_btree_ii__1_0__0__11__10__01 
namespace souffle::t_btree_i__0__1 {
using namespace souffle;
struct Type {
static constexpr Relation::arity_type Arity = 1;
using t_tuple = Tuple<RamDomain, 1>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :(0);
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_i__0__1 
namespace souffle::t_btree_i__0__1 {
using namespace souffle;
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[1];
std::copy(ramDomain, ramDomain + 1, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0) {
RamDomain data[1] = {a0};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_0(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_1(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_1(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 1 direct b-tree index 0 lex-order [0]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_i__0__1 
namespace souffle::t_btree_iiiiii__0_1_2_3_4_5__111111 {
using namespace souffle;
struct Type {
static constexpr Relation::arity_type Arity = 6;
using t_tuple = Tuple<RamDomain, 6>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2])) ? -1 : (ramBitCast<RamSigned>(a[2]) > ramBitCast<RamSigned>(b[2])) ? 1 :((ramBitCast<RamSigned>(a[3]) < ramBitCast<RamSigned>(b[3])) ? -1 : (ramBitCast<RamSigned>(a[3]) > ramBitCast<RamSigned>(b[3])) ? 1 :((ramBitCast<RamSigned>(a[4]) < ramBitCast<RamSigned>(b[4])) ? -1 : (ramBitCast<RamSigned>(a[4]) > ramBitCast<RamSigned>(b[4])) ? 1 :((ramBitCast<RamSigned>(a[5]) < ramBitCast<RamSigned>(b[5])) ? -1 : (ramBitCast<RamSigned>(a[5]) > ramBitCast<RamSigned>(b[5])) ? 1 :(0))))));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))|| ((ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1])) && ((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2]))|| ((ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2])) && ((ramBitCast<RamSigned>(a[3]) < ramBitCast<RamSigned>(b[3]))|| ((ramBitCast<RamSigned>(a[3]) == ramBitCast<RamSigned>(b[3])) && ((ramBitCast<RamSigned>(a[4]) < ramBitCast<RamSigned>(b[4]))|| ((ramBitCast<RamSigned>(a[4]) == ramBitCast<RamSigned>(b[4])) && ((ramBitCast<RamSigned>(a[5]) < ramBitCast<RamSigned>(b[5]))))))))))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]))&&(ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2]))&&(ramBitCast<RamSigned>(a[3]) == ramBitCast<RamSigned>(b[3]))&&(ramBitCast<RamSigned>(a[4]) == ramBitCast<RamSigned>(b[4]))&&(ramBitCast<RamSigned>(a[5]) == ramBitCast<RamSigned>(b[5]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4,RamDomain a5);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_000000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_000000(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_111111(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_111111(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_iiiiii__0_1_2_3_4_5__111111 
namespace souffle::t_btree_iiiiii__0_1_2_3_4_5__111111 {
using namespace souffle;
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[6];
std::copy(ramDomain, ramDomain + 6, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3,RamDomain a4,RamDomain a5) {
RamDomain data[6] = {a0,a1,a2,a3,a4,a5};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_000000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_000000(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_111111(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_111111(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_111111(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 6 direct b-tree index 0 lex-order [0,1,2,3,4,5]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_iiiiii__0_1_2_3_4_5__111111 
namespace souffle::t_btree_ii__0_1__11 {
using namespace souffle;
struct Type {
static constexpr Relation::arity_type Arity = 2;
using t_tuple = Tuple<RamDomain, 2>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :(0));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]));
 }
};
using t_ind_0 = btree_set<t_tuple,t_comparator_0>;
t_ind_0 ind_0;
using iterator = t_ind_0::iterator;
struct context {
t_ind_0::operation_hints hints_0_lower;
t_ind_0::operation_hints hints_0_upper;
};
context createContext() { return context(); }
bool insert(const t_tuple& t);
bool insert(const t_tuple& t, context& h);
bool insert(const RamDomain* ramDomain);
bool insert(RamDomain a0,RamDomain a1);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11 
namespace souffle::t_btree_ii__0_1__11 {
using namespace souffle;
using t_ind_0 = Type::t_ind_0;
using iterator = Type::iterator;
using context = Type::context;
bool Type::insert(const t_tuple& t) {
context h;
return insert(t, h);
}
bool Type::insert(const t_tuple& t, context& h) {
if (ind_0.insert(t, h.hints_0_lower)) {
return true;
} else return false;
}
bool Type::insert(const RamDomain* ramDomain) {
RamDomain data[2];
std::copy(ramDomain, ramDomain + 2, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1) {
RamDomain data[2] = {a0,a1};
return insert(data);
}
bool Type::contains(const t_tuple& t, context& h) const {
return ind_0.contains(t, h.hints_0_lower);
}
bool Type::contains(const t_tuple& t) const {
context h;
return contains(t, h);
}
std::size_t Type::size() const {
return ind_0.size();
}
iterator Type::find(const t_tuple& t, context& h) const {
return ind_0.find(t, h.hints_0_lower);
}
iterator Type::find(const t_tuple& t) const {
context h;
return find(t, h);
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_00(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp == 0) {
    auto pos = ind_0.find(lower, h.hints_0_lower);
    auto fin = ind_0.end();
    if (pos != fin) {fin = pos; ++fin;}
    return make_range(pos, fin);
}
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_11(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_11(lower,upper,h);
}
bool Type::empty() const {
return ind_0.empty();
}
std::vector<range<iterator>> Type::partition() const {
return ind_0.getChunks(400);
}
void Type::purge() {
ind_0.clear();
}
iterator Type::begin() const {
return ind_0.begin();
}
iterator Type::end() const {
return ind_0.end();
}
void Type::printStatistics(std::ostream& o) const {
o << " arity 2 direct b-tree index 0 lex-order [0,1]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_ii__0_1__11 
namespace  souffle {
using namespace souffle;
class Stratum_T1_76f3ec8ed4d6ad63 {
public:
 Stratum_T1_76f3ec8ed4d6ad63(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T1_d16b537d059aa637,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_T1_d16b537d059aa637;
t_btree_i__0__1::Type* rel_adom_c76027b3f67642db;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_T1_76f3ec8ed4d6ad63::Stratum_T1_76f3ec8ed4d6ad63(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T1_d16b537d059aa637,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_T1_d16b537d059aa637(&rel_T1_d16b537d059aa637),
rel_adom_c76027b3f67642db(&rel_adom_c76027b3f67642db),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_T1_76f3ec8ed4d6ad63::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;T1;1_positive_rewrite_proposition_6_3_toegepast.dl [10:7-10:9];)_",iter, [&](){return rel_T1_d16b537d059aa637->size();});
signalHandler->setMsg(R"_(T1(z,x,x2,y2,x,y) :- 
   edge(x,y),
   edge(y,z),
   !edge(z,x),
   adom(x2),
   adom(y2),
   x != z,
   y != z.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [11:1-17:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T1;1_positive_rewrite_proposition_6_3_toegepast.dl [11:1-17:12];T1(z,x,x2,y2,x,y) :- \n   edge(x,y),\n   edge(y,z),\n   !edge(z,x),\n   adom(x2),\n   adom(y2),\n   x != z,\n   y != z.;)_",iter, [&](){return rel_T1_d16b537d059aa637->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt,rel_T1_d16b537d059aa637->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env1[1]),ramBitCast(env0[0]),ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T1_d16b537d059aa637->insert(tuple,READ_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T1(z,x,x2,y2,x,y) :- 
   edge(x,y),
   edge(y,z),
   !edge(z,x),
   adom(x2),
   adom(y2),
   x != z,
   z != x.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [19:1-25:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T1;1_positive_rewrite_proposition_6_3_toegepast.dl [19:1-25:12];T1(z,x,x2,y2,x,y) :- \n   edge(x,y),\n   edge(y,z),\n   !edge(z,x),\n   adom(x2),\n   adom(y2),\n   x != z,\n   z != x.;)_",iter, [&](){return rel_T1_d16b537d059aa637->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt,rel_T1_d16b537d059aa637->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env1[1]),ramBitCast(env0[0]),ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T1_d16b537d059aa637->insert(tuple,READ_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T1(z,x,x2,y2,x,y) :- 
   edge(x,y),
   edge(y,z),
   !edge(z,x),
   adom(x2),
   adom(y2),
   y != x,
   y != z.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [27:1-33:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T1;1_positive_rewrite_proposition_6_3_toegepast.dl [27:1-33:12];T1(z,x,x2,y2,x,y) :- \n   edge(x,y),\n   edge(y,z),\n   !edge(z,x),\n   adom(x2),\n   adom(y2),\n   y != x,\n   y != z.;)_",iter, [&](){return rel_T1_d16b537d059aa637->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt,rel_T1_d16b537d059aa637->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env1[1]),ramBitCast(env0[0]),ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T1_d16b537d059aa637->insert(tuple,READ_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt));
}
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T1(z,x,x2,y2,x,y) :- 
   edge(x,y),
   edge(y,z),
   !edge(z,x),
   adom(x2),
   adom(y2),
   y != x,
   z != x.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [35:1-41:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T1;1_positive_rewrite_proposition_6_3_toegepast.dl [35:1-41:12];T1(z,x,x2,y2,x,y) :- \n   edge(x,y),\n   edge(y,z),\n   !edge(z,x),\n   adom(x2),\n   adom(y2),\n   y != x,\n   z != x.;)_",iter, [&](){return rel_T1_d16b537d059aa637->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt,rel_T1_d16b537d059aa637->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env1[1]),ramBitCast(env0[0]),ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T1_d16b537d059aa637->insert(tuple,READ_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt));
}
}
}
}
}
}
}
();}
}
}
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_T2_79883c67345145b9 {
public:
 Stratum_T2_79883c67345145b9(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T2_a2eb4c083fff8b50,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_T2_a2eb4c083fff8b50;
t_btree_i__0__1::Type* rel_adom_c76027b3f67642db;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_T2_79883c67345145b9::Stratum_T2_79883c67345145b9(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T2_a2eb4c083fff8b50,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_T2_a2eb4c083fff8b50(&rel_T2_a2eb4c083fff8b50),
rel_adom_c76027b3f67642db(&rel_adom_c76027b3f67642db),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_T2_79883c67345145b9::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;T2;1_positive_rewrite_proposition_6_3_toegepast.dl [44:7-44:9];)_",iter, [&](){return rel_T2_a2eb4c083fff8b50->size();});
signalHandler->setMsg(R"_(T2(x1,y1,y,z,x,y) :- 
   edge(x,y),
   !edge(y,z),
   edge(z,x),
   adom(x1),
   adom(y1),
   x != y,
   y != z.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [45:1-51:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T2;1_positive_rewrite_proposition_6_3_toegepast.dl [45:1-51:12];T2(x1,y1,y,z,x,y) :- \n   edge(x,y),\n   !edge(y,z),\n   edge(z,x),\n   adom(x1),\n   adom(y1),\n   x != y,\n   y != z.;)_",iter, [&](){return rel_T2_a2eb4c083fff8b50->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt,rel_T2_a2eb4c083fff8b50->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[1]),ramBitCast(env1[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T2_a2eb4c083fff8b50->insert(tuple,READ_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt));
}
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T2(x1,y1,y,z,x,y) :- 
   edge(x,y),
   !edge(y,z),
   edge(z,x),
   adom(x1),
   adom(y1),
   x != y,
   z != x.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [53:1-59:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T2;1_positive_rewrite_proposition_6_3_toegepast.dl [53:1-59:12];T2(x1,y1,y,z,x,y) :- \n   edge(x,y),\n   !edge(y,z),\n   edge(z,x),\n   adom(x1),\n   adom(y1),\n   x != y,\n   z != x.;)_",iter, [&](){return rel_T2_a2eb4c083fff8b50->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt,rel_T2_a2eb4c083fff8b50->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[0]) != ramBitCast<RamDomain>(env0[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[1]),ramBitCast(env1[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T2_a2eb4c083fff8b50->insert(tuple,READ_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt));
}
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T2(x1,y1,y,z,x,y) :- 
   edge(x,y),
   !edge(y,z),
   edge(z,x),
   adom(x1),
   adom(y1),
   y != z.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [61:1-67:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T2;1_positive_rewrite_proposition_6_3_toegepast.dl [61:1-67:12];T2(x1,y1,y,z,x,y) :- \n   edge(x,y),\n   !edge(y,z),\n   edge(z,x),\n   adom(x1),\n   adom(y1),\n   y != z.;)_",iter, [&](){return rel_T2_a2eb4c083fff8b50->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt,rel_T2_a2eb4c083fff8b50->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[1]),ramBitCast(env1[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T2_a2eb4c083fff8b50->insert(tuple,READ_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt));
}
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(T2(x1,y1,y,z,x,y) :- 
   edge(x,y),
   !edge(y,z),
   edge(z,x),
   adom(x1),
   adom(y1),
   y != z,
   z != x.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [69:1-75:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;T2;1_positive_rewrite_proposition_6_3_toegepast.dl [69:1-75:12];T2(x1,y1,y,z,x,y) :- \n   edge(x,y),\n   !edge(y,z),\n   edge(z,x),\n   adom(x1),\n   adom(y1),\n   y != z,\n   z != x.;)_",iter, [&](){return rel_T2_a2eb4c083fff8b50->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt,rel_T2_a2eb4c083fff8b50->createContext());
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[0])) && (ramBitCast<RamDomain>(env1[0]) != ramBitCast<RamDomain>(env0[0])) && !(rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env0[1]),ramBitCast(env1[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env0[1]),ramBitCast(env1[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_T2_a2eb4c083fff8b50->insert(tuple,READ_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt));
}
}
}
}
}
}
();}
}
}
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_adom_e41f31085b6fd3d6 {
public:
 Stratum_adom_e41f31085b6fd3d6(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_i__0__1::Type* rel_adom_c76027b3f67642db;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_adom_e41f31085b6fd3d6::Stratum_adom_e41f31085b6fd3d6(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_adom_c76027b3f67642db(&rel_adom_c76027b3f67642db),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_adom_e41f31085b6fd3d6::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;adom;1_positive_rewrite_proposition_6_3_toegepast.dl [5:7-5:11];)_",iter, [&](){return rel_adom_c76027b3f67642db->size();});
signalHandler->setMsg(R"_(adom(x) :- 
   edge(x,_).
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [6:1-6:23])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;adom;1_positive_rewrite_proposition_6_3_toegepast.dl [6:1-6:23];adom(x) :- \n   edge(x,_).;)_",iter, [&](){return rel_adom_c76027b3f67642db->size();});
if(!(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[0])}};
rel_adom_c76027b3f67642db->insert(tuple,READ_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt));
}
}
();}
}
signalHandler->setMsg(R"_(adom(x) :- 
   edge(_,x).
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [7:1-7:23])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;adom;1_positive_rewrite_proposition_6_3_toegepast.dl [7:1-7:23];adom(x) :- \n   edge(_,x).;)_",iter, [&](){return rel_adom_c76027b3f67642db->size();});
if(!(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
Tuple<RamDomain,1> tuple{{ramBitCast(env0[1])}};
rel_adom_c76027b3f67642db->insert(tuple,READ_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt));
}
}
();}
}
}
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_edge_9543a759b165a2cb {
public:
 Stratum_edge_9543a759b165a2cb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_edge_9543a759b165a2cb::Stratum_edge_9543a759b165a2cb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_edge_9543a759b165a2cb::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-relation-loadtime;edge;1_positive_rewrite_proposition_6_3_toegepast.dl [1:7-1:11];loadtime;)_",iter, [&](){return rel_edge_04d25f5060e9043b->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","."},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectory.empty()) {directiveMap["fact-dir"] = inputDirectory;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}
}
ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;edge;1_positive_rewrite_proposition_6_3_toegepast.dl [1:7-1:11];)",rel_edge_04d25f5060e9043b->size(),iter);}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_output0_b654ad7833cb491d {
public:
 Stratum_output0_b654ad7833cb491d(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T1_d16b537d059aa637,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T2_a2eb4c083fff8b50,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_output0_8b84c88df5f1a24a);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_T1_d16b537d059aa637;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_T2_a2eb4c083fff8b50;
t_btree_i__0__1::Type* rel_adom_c76027b3f67642db;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_output0_8b84c88df5f1a24a;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_output0_b654ad7833cb491d::Stratum_output0_b654ad7833cb491d(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T1_d16b537d059aa637,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_T2_a2eb4c083fff8b50,t_btree_i__0__1::Type& rel_adom_c76027b3f67642db,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_output0_8b84c88df5f1a24a):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_T1_d16b537d059aa637(&rel_T1_d16b537d059aa637),
rel_T2_a2eb4c083fff8b50(&rel_T2_a2eb4c083fff8b50),
rel_adom_c76027b3f67642db(&rel_adom_c76027b3f67642db),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b),
rel_output0_8b84c88df5f1a24a(&rel_output0_8b84c88df5f1a24a){
}

void Stratum_output0_b654ad7833cb491d::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;output0;1_positive_rewrite_proposition_6_3_toegepast.dl [78:7-78:14];)_",iter, [&](){return rel_output0_8b84c88df5f1a24a->size();});
signalHandler->setMsg(R"_(output0(x1,y1,x2,y2,x,y) :- 
   edge(x,y),
   edge(y,z),
   edge(z,x),
   adom(x1),
   adom(y1),
   adom(x2),
   adom(y2).
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [79:1-84:24])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;output0;1_positive_rewrite_proposition_6_3_toegepast.dl [79:1-84:24];output0(x1,y1,x2,y2,x,y) :- \n   edge(x,y),\n   edge(y,z),\n   edge(z,x),\n   adom(x1),\n   adom(y1),\n   adom(x2),\n   adom(y2).;)_",iter, [&](){return rel_output0_8b84c88df5f1a24a->size();});
if(!(rel_adom_c76027b3f67642db->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_adom_c76027b3f67642db_op_ctxt,rel_adom_c76027b3f67642db->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_output0_8b84c88df5f1a24a_op_ctxt,rel_output0_8b84c88df5f1a24a->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))) {
for(const auto& env2 : *rel_adom_c76027b3f67642db) {
for(const auto& env3 : *rel_adom_c76027b3f67642db) {
for(const auto& env4 : *rel_adom_c76027b3f67642db) {
for(const auto& env5 : *rel_adom_c76027b3f67642db) {
Tuple<RamDomain,6> tuple{{ramBitCast(env2[0]),ramBitCast(env3[0]),ramBitCast(env4[0]),ramBitCast(env5[0]),ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_output0_8b84c88df5f1a24a->insert(tuple,READ_OP_CONTEXT(rel_output0_8b84c88df5f1a24a_op_ctxt));
}
}
}
}
break;
}
}
}
}
();}
}
signalHandler->setMsg(R"_(output0(x1,y1,x2,y2,x,y) :- 
   T2(x1,y1,x2,y2,x,y),
   T1(x1,y1,x2,y2,x,y),
   x != y.
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [87:1-90:12])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;output0;1_positive_rewrite_proposition_6_3_toegepast.dl [87:1-90:12];output0(x1,y1,x2,y2,x,y) :- \n   T2(x1,y1,x2,y2,x,y),\n   T1(x1,y1,x2,y2,x,y),\n   x != y.;)_",iter, [&](){return rel_output0_8b84c88df5f1a24a->size();});
if(!(rel_T2_a2eb4c083fff8b50->empty()) && !(rel_T1_d16b537d059aa637->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt,rel_T1_d16b537d059aa637->createContext());
CREATE_OP_CONTEXT(rel_T2_a2eb4c083fff8b50_op_ctxt,rel_T2_a2eb4c083fff8b50->createContext());
CREATE_OP_CONTEXT(rel_output0_8b84c88df5f1a24a_op_ctxt,rel_output0_8b84c88df5f1a24a->createContext());
for(const auto& env0 : *rel_T2_a2eb4c083fff8b50) {
if( (ramBitCast<RamDomain>(env0[4]) != ramBitCast<RamDomain>(env0[5])) && rel_T1_d16b537d059aa637->contains(Tuple<RamDomain,6>{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3]),ramBitCast(env0[4]),ramBitCast(env0[5])}},READ_OP_CONTEXT(rel_T1_d16b537d059aa637_op_ctxt))) {
Tuple<RamDomain,6> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1]),ramBitCast(env0[2]),ramBitCast(env0[3]),ramBitCast(env0[4]),ramBitCast(env0[5])}};
rel_output0_8b84c88df5f1a24a->insert(tuple,READ_OP_CONTEXT(rel_output0_8b84c88df5f1a24a_op_ctxt));
}
}
}
();}
}
}
if (pruneImdtRels) rel_T1_d16b537d059aa637->purge();
if (pruneImdtRels) rel_T2_a2eb4c083fff8b50->purge();
if (pruneImdtRels) rel_adom_c76027b3f67642db->purge();
if (pruneImdtRels) rel_edge_04d25f5060e9043b->purge();
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_result_conflict_free_daa1077469ffc61b {
public:
 Stratum_result_conflict_free_daa1077469ffc61b(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_output0_8b84c88df5f1a24a,t_btree_ii__0_1__11::Type& rel_result_conflict_free_05673b16b868496c);
void run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret);
private:
SymbolTable& symTable;
RecordTable& recordTable;
ConcurrentCache<std::string,std::regex>& regexCache;
bool& pruneImdtRels;
bool& performIO;
SignalHandler*& signalHandler;
std::atomic<std::size_t>& iter;
std::atomic<RamDomain>& ctr;
std::string& inputDirectory;
std::string& outputDirectory;
t_btree_iiiiii__0_1_2_3_4_5__111111::Type* rel_output0_8b84c88df5f1a24a;
t_btree_ii__0_1__11::Type* rel_result_conflict_free_05673b16b868496c;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_result_conflict_free_daa1077469ffc61b::Stratum_result_conflict_free_daa1077469ffc61b(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiiiii__0_1_2_3_4_5__111111::Type& rel_output0_8b84c88df5f1a24a,t_btree_ii__0_1__11::Type& rel_result_conflict_free_05673b16b868496c):
symTable(symTable),
recordTable(recordTable),
regexCache(regexCache),
pruneImdtRels(pruneImdtRels),
performIO(performIO),
signalHandler(signalHandler),
iter(iter),
ctr(ctr),
inputDirectory(inputDirectory),
outputDirectory(outputDirectory),
rel_output0_8b84c88df5f1a24a(&rel_output0_8b84c88df5f1a24a),
rel_result_conflict_free_05673b16b868496c(&rel_result_conflict_free_05673b16b868496c){
}

void Stratum_result_conflict_free_daa1077469ffc61b::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;result_conflict_free;1_positive_rewrite_proposition_6_3_toegepast.dl [93:7-93:27];)_",iter, [&](){return rel_result_conflict_free_05673b16b868496c->size();});
signalHandler->setMsg(R"_(result_conflict_free(x,y) :- 
   output0(_,_,_,_,x,y).
in file 1_positive_rewrite_proposition_6_3_toegepast.dl [95:1-95:57])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_conflict_free;1_positive_rewrite_proposition_6_3_toegepast.dl [95:1-95:57];result_conflict_free(x,y) :- \n   output0(_,_,_,_,x,y).;)_",iter, [&](){return rel_result_conflict_free_05673b16b868496c->size();});
if(!(rel_output0_8b84c88df5f1a24a->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_output0_8b84c88df5f1a24a_op_ctxt,rel_output0_8b84c88df5f1a24a->createContext());
CREATE_OP_CONTEXT(rel_result_conflict_free_05673b16b868496c_op_ctxt,rel_result_conflict_free_05673b16b868496c->createContext());
for(const auto& env0 : *rel_output0_8b84c88df5f1a24a) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[4]),ramBitCast(env0[5])}};
rel_result_conflict_free_05673b16b868496c->insert(tuple,READ_OP_CONTEXT(rel_result_conflict_free_05673b16b868496c_op_ctxt));
}
}
();}
}
}
{
	Logger logger(R"_(@t-relation-savetime;result_conflict_free;1_positive_rewrite_proposition_6_3_toegepast.dl [93:7-93:27];savetime;)_",iter, [&](){return rel_result_conflict_free_05673b16b868496c->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_conflict_free"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (outputDirectory == "-"){directiveMap["IO"] = "stdout"; directiveMap["headers"] = "true";}
else if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_conflict_free_05673b16b868496c);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}
if (pruneImdtRels) rel_output0_8b84c88df5f1a24a->purge();
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Sf___positive_rewrite_proposition_6_3_toegepast__noopt: public SouffleProgram {
public:
 Sf___positive_rewrite_proposition_6_3_toegepast__noopt(std::string pf = "profile.log");
 ~Sf___positive_rewrite_proposition_6_3_toegepast__noopt();
void run();
void runAll(std::string inputDirectoryArg = "",std::string outputDirectoryArg = "",bool performIOArg = true,bool pruneImdtRelsArg = true);
void printAll([[maybe_unused]] std::string outputDirectoryArg = "");
void loadAll([[maybe_unused]] std::string inputDirectoryArg = "");
void dumpInputs();
void dumpOutputs();
SymbolTable& getSymbolTable();
RecordTable& getRecordTable();
void setNumThreads(std::size_t numThreadsValue);
void executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret);
std::string profiling_fname;
private:
void runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg);
void dumpFreqs();
SymbolTableImpl symTable;
SpecializedRecordTable<0> recordTable;
ConcurrentCache<std::string,std::regex> regexCache;
std::size_t freqs[105];
std::size_t reads[6];
Own<t_btree_ii__1_0__0__11__10__01::Type> rel_edge_04d25f5060e9043b;
souffle::RelationWrapper<t_btree_ii__1_0__0__11__10__01::Type> wrapper_rel_edge_04d25f5060e9043b;
Own<t_btree_i__0__1::Type> rel_adom_c76027b3f67642db;
souffle::RelationWrapper<t_btree_i__0__1::Type> wrapper_rel_adom_c76027b3f67642db;
Own<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> rel_T1_d16b537d059aa637;
souffle::RelationWrapper<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> wrapper_rel_T1_d16b537d059aa637;
Own<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> rel_T2_a2eb4c083fff8b50;
souffle::RelationWrapper<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> wrapper_rel_T2_a2eb4c083fff8b50;
Own<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> rel_output0_8b84c88df5f1a24a;
souffle::RelationWrapper<t_btree_iiiiii__0_1_2_3_4_5__111111::Type> wrapper_rel_output0_8b84c88df5f1a24a;
Own<t_btree_ii__0_1__11::Type> rel_result_conflict_free_05673b16b868496c;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_result_conflict_free_05673b16b868496c;
Stratum_T1_76f3ec8ed4d6ad63 stratum_T1_5c3ab2c64a54be91;
Stratum_T2_79883c67345145b9 stratum_T2_55c519d79b356f03;
Stratum_adom_e41f31085b6fd3d6 stratum_adom_2dcfa675c8564488;
Stratum_edge_9543a759b165a2cb stratum_edge_31e40d0d94fe9f7c;
Stratum_output0_b654ad7833cb491d stratum_output0_84e2aabb419d0022;
Stratum_result_conflict_free_daa1077469ffc61b stratum_result_conflict_free_48a4862607b8a5c8;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Sf___positive_rewrite_proposition_6_3_toegepast__noopt::Sf___positive_rewrite_proposition_6_3_toegepast__noopt(std::string pf):
profiling_fname(std::move(pf)),
symTable(),
recordTable(),
regexCache(),
freqs(),
reads(),
rel_edge_04d25f5060e9043b(mk<t_btree_ii__1_0__0__11__10__01::Type>()),
wrapper_rel_edge_04d25f5060e9043b(0, *rel_edge_04d25f5060e9043b, *this, "edge", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_adom_c76027b3f67642db(mk<t_btree_i__0__1::Type>()),
wrapper_rel_adom_c76027b3f67642db(1, *rel_adom_c76027b3f67642db, *this, "adom", std::array<const char *,1>{{"i:number"}}, std::array<const char *,1>{{"x"}}, 0),
rel_T1_d16b537d059aa637(mk<t_btree_iiiiii__0_1_2_3_4_5__111111::Type>()),
wrapper_rel_T1_d16b537d059aa637(2, *rel_T1_d16b537d059aa637, *this, "T1", std::array<const char *,6>{{"i:number","i:number","i:number","i:number","i:number","i:number"}}, std::array<const char *,6>{{"p_z","p_x","p_x2","p_y2","original_x","original_y"}}, 0),
rel_T2_a2eb4c083fff8b50(mk<t_btree_iiiiii__0_1_2_3_4_5__111111::Type>()),
wrapper_rel_T2_a2eb4c083fff8b50(3, *rel_T2_a2eb4c083fff8b50, *this, "T2", std::array<const char *,6>{{"i:number","i:number","i:number","i:number","i:number","i:number"}}, std::array<const char *,6>{{"p_x1","p_y1","p_y","p_z","original_x","original_y"}}, 0),
rel_output0_8b84c88df5f1a24a(mk<t_btree_iiiiii__0_1_2_3_4_5__111111::Type>()),
wrapper_rel_output0_8b84c88df5f1a24a(4, *rel_output0_8b84c88df5f1a24a, *this, "output0", std::array<const char *,6>{{"i:number","i:number","i:number","i:number","i:number","i:number"}}, std::array<const char *,6>{{"p_x1","p_y1","p_x2","p_y2","x","y"}}, 0),
rel_result_conflict_free_05673b16b868496c(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_result_conflict_free_05673b16b868496c(5, *rel_result_conflict_free_05673b16b868496c, *this, "result_conflict_free", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
stratum_T1_5c3ab2c64a54be91(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_T1_d16b537d059aa637,*rel_adom_c76027b3f67642db,*rel_edge_04d25f5060e9043b),
stratum_T2_55c519d79b356f03(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_T2_a2eb4c083fff8b50,*rel_adom_c76027b3f67642db,*rel_edge_04d25f5060e9043b),
stratum_adom_2dcfa675c8564488(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_adom_c76027b3f67642db,*rel_edge_04d25f5060e9043b),
stratum_edge_31e40d0d94fe9f7c(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_edge_04d25f5060e9043b),
stratum_output0_84e2aabb419d0022(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_T1_d16b537d059aa637,*rel_T2_a2eb4c083fff8b50,*rel_adom_c76027b3f67642db,*rel_edge_04d25f5060e9043b,*rel_output0_8b84c88df5f1a24a),
stratum_result_conflict_free_48a4862607b8a5c8(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_output0_8b84c88df5f1a24a,*rel_result_conflict_free_05673b16b868496c){
addRelation("edge", wrapper_rel_edge_04d25f5060e9043b, true, false);
addRelation("adom", wrapper_rel_adom_c76027b3f67642db, false, false);
addRelation("T1", wrapper_rel_T1_d16b537d059aa637, false, false);
addRelation("T2", wrapper_rel_T2_a2eb4c083fff8b50, false, false);
addRelation("output0", wrapper_rel_output0_8b84c88df5f1a24a, false, false);
addRelation("result_conflict_free", wrapper_rel_result_conflict_free_05673b16b868496c, false, true);
ProfileEventSingleton::instance().setOutputFile(profiling_fname);
}

 Sf___positive_rewrite_proposition_6_3_toegepast__noopt::~Sf___positive_rewrite_proposition_6_3_toegepast__noopt(){
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

    this->inputDirectory  = std::move(inputDirectoryArg);
    this->outputDirectory = std::move(outputDirectoryArg);
    this->performIO       = performIOArg;
    this->pruneImdtRels   = pruneImdtRelsArg;

    // set default threads (in embedded mode)
    // if this is not set, and omp is used, the default omp setting of number of cores is used.
#if defined(_OPENMP)
    if (0 < getNumThreads()) { omp_set_num_threads(static_cast<int>(getNumThreads())); }
#endif

    signalHandler->set();
// -- query evaluation --
ProfileEventSingleton::instance().startTimer();
ProfileEventSingleton::instance().makeTimeEvent("@time;starttime");
{
Logger logger("@runtime;", 0);
ProfileEventSingleton::instance().makeConfigRecord("relationCount", std::to_string(6));{
	Logger logger(R"_(@runtime;)_",iter);
{
 std::vector<RamDomain> args, ret;
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_adom_2dcfa675c8564488.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_T1_5c3ab2c64a54be91.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_T2_55c519d79b356f03.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_output0_84e2aabb419d0022.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_result_conflict_free_48a4862607b8a5c8.run(args, ret);
}
}
}
ProfileEventSingleton::instance().stopTimer();
dumpFreqs();

// -- relation hint statistics --
signalHandler->reset();
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::run(){
runFunction("", "", false, false);
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_conflict_free"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_conflict_free_05673b16b868496c);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::loadAll([[maybe_unused]] std::string inputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","."},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectoryArg.empty()) {directiveMap["fact-dir"] = inputDirectoryArg;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::dumpInputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "edge";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::dumpOutputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "result_conflict_free";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_result_conflict_free_05673b16b868496c);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

SymbolTable& Sf___positive_rewrite_proposition_6_3_toegepast__noopt::getSymbolTable(){
return symTable;
}

RecordTable& Sf___positive_rewrite_proposition_6_3_toegepast__noopt::getRecordTable(){
return recordTable;
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
regexCache.setNumLanes(getNumThreads());
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
if (name == "T1") {
stratum_T1_5c3ab2c64a54be91.run(args, ret);
return;}
if (name == "T2") {
stratum_T2_55c519d79b356f03.run(args, ret);
return;}
if (name == "adom") {
stratum_adom_2dcfa675c8564488.run(args, ret);
return;}
if (name == "edge") {
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
return;}
if (name == "output0") {
stratum_output0_84e2aabb419d0022.run(args, ret);
return;}
if (name == "result_conflict_free") {
stratum_result_conflict_free_48a4862607b8a5c8.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

void Sf___positive_rewrite_proposition_6_3_toegepast__noopt::dumpFreqs(){
}

} // namespace  souffle
namespace souffle {
SouffleProgram *newInstance___positive_rewrite_proposition_6_3_toegepast__noopt(){return new  souffle::Sf___positive_rewrite_proposition_6_3_toegepast__noopt;}
SymbolTable *getST___positive_rewrite_proposition_6_3_toegepast__noopt(SouffleProgram *p){return &reinterpret_cast<souffle::Sf___positive_rewrite_proposition_6_3_toegepast__noopt*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(1_positive_rewrite_proposition_6_3_toegepast.dl)",
R"()",
R"()",
true,
R"(/dev/null)",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf___positive_rewrite_proposition_6_3_toegepast__noopt obj(opt.getProfileName());
#if defined(_OPENMP) 
obj.setNumThreads(opt.getNumJobs());

#endif
souffle::ProfileEventSingleton::instance().makeConfigRecord("", opt.getSourceFileName());
souffle::ProfileEventSingleton::instance().makeConfigRecord("fact-dir", opt.getInputFileDir());
souffle::ProfileEventSingleton::instance().makeConfigRecord("jobs", std::to_string(opt.getNumJobs()));
souffle::ProfileEventSingleton::instance().makeConfigRecord("output-dir", opt.getOutputFileDir());
souffle::ProfileEventSingleton::instance().makeConfigRecord("version", "2.4");
obj.runAll(opt.getInputFileDir(), opt.getOutputFileDir());
return 0;
} catch(std::exception &e) { souffle::SignalHandler::instance()->error(e.what());}
}
#endif

namespace  souffle {
using namespace souffle;
class factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt: souffle::ProgramFactory {
public:
souffle::SouffleProgram* newInstance();
 factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt();
private:
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
souffle::SouffleProgram* factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt::newInstance(){
return new  souffle::Sf___positive_rewrite_proposition_6_3_toegepast__noopt();
}

 factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt::factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt():
souffle::ProgramFactory("__positive_rewrite_proposition_6_3_toegepast__noopt"){
}

} // namespace  souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
souffle::factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt __factory_Sf___positive_rewrite_proposition_6_3_toegepast__noopt_instance;
}
#endif
} // namespace souffle

