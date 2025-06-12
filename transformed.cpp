#define SOUFFLE_GENERATOR_VERSION "2.4"
#define _SOUFFLE_STATS
#include "souffle/CompiledSouffle.h"
#include "souffle/SignalHandler.h"
#include "souffle/SouffleInterface.h"
#include "souffle/datastructure/BTree.h"
#include "souffle/datastructure/Nullaries.h"
#include "souffle/io/IOSystem.h"
#include "souffle/profile/Logger.h"
#include "souffle/profile/ProfileEvent.h"
#include <any>
namespace functors {
extern "C" {
}
} //namespace functors
namespace souffle::t_btree_ii__0_1__11__10 {
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
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_ii__0_1__11__10 {
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
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper, context& h) const {
t_comparator_0 comparator;
int cmp = comparator(lower, upper);
if (cmp > 0) {
    return make_range(ind_0.end(), ind_0.end());
}
return make_range(ind_0.lower_bound(lower, h.hints_0_lower), ind_0.upper_bound(upper, h.hints_0_upper));
}
range<t_ind_0::iterator> Type::lowerUpperRange_10(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_10(lower,upper,h);
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
} // namespace souffle::t_btree_ii__0_1__11__10 
namespace souffle::t_btree_iiii__0_1_2_3__1111 {
using namespace souffle;
struct Type {
static constexpr Relation::arity_type Arity = 4;
using t_tuple = Tuple<RamDomain, 4>;
struct t_comparator_0{
 int operator()(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0])) ? -1 : (ramBitCast<RamSigned>(a[0]) > ramBitCast<RamSigned>(b[0])) ? 1 :((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1])) ? -1 : (ramBitCast<RamSigned>(a[1]) > ramBitCast<RamSigned>(b[1])) ? 1 :((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2])) ? -1 : (ramBitCast<RamSigned>(a[2]) > ramBitCast<RamSigned>(b[2])) ? 1 :((ramBitCast<RamSigned>(a[3]) < ramBitCast<RamSigned>(b[3])) ? -1 : (ramBitCast<RamSigned>(a[3]) > ramBitCast<RamSigned>(b[3])) ? 1 :(0))));
 }
bool less(const t_tuple& a, const t_tuple& b) const {
  return (ramBitCast<RamSigned>(a[0]) < ramBitCast<RamSigned>(b[0]))|| ((ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0])) && ((ramBitCast<RamSigned>(a[1]) < ramBitCast<RamSigned>(b[1]))|| ((ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1])) && ((ramBitCast<RamSigned>(a[2]) < ramBitCast<RamSigned>(b[2]))|| ((ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2])) && ((ramBitCast<RamSigned>(a[3]) < ramBitCast<RamSigned>(b[3]))))))));
 }
bool equal(const t_tuple& a, const t_tuple& b) const {
return (ramBitCast<RamSigned>(a[0]) == ramBitCast<RamSigned>(b[0]))&&(ramBitCast<RamSigned>(a[1]) == ramBitCast<RamSigned>(b[1]))&&(ramBitCast<RamSigned>(a[2]) == ramBitCast<RamSigned>(b[2]))&&(ramBitCast<RamSigned>(a[3]) == ramBitCast<RamSigned>(b[3]));
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
bool insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3);
bool contains(const t_tuple& t, context& h) const;
bool contains(const t_tuple& t) const;
std::size_t size() const;
iterator find(const t_tuple& t, context& h) const;
iterator find(const t_tuple& t) const;
range<iterator> lowerUpperRange_0000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const;
range<iterator> lowerUpperRange_0000(const t_tuple& /* lower */, const t_tuple& /* upper */) const;
range<t_ind_0::iterator> lowerUpperRange_1111(const t_tuple& lower, const t_tuple& upper, context& h) const;
range<t_ind_0::iterator> lowerUpperRange_1111(const t_tuple& lower, const t_tuple& upper) const;
bool empty() const;
std::vector<range<iterator>> partition() const;
void purge();
iterator begin() const;
iterator end() const;
void printStatistics(std::ostream& o) const;
};
} // namespace souffle::t_btree_iiii__0_1_2_3__1111 
namespace souffle::t_btree_iiii__0_1_2_3__1111 {
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
RamDomain data[4];
std::copy(ramDomain, ramDomain + 4, data);
const t_tuple& tuple = reinterpret_cast<const t_tuple&>(data);
context h;
return insert(tuple, h);
}
bool Type::insert(RamDomain a0,RamDomain a1,RamDomain a2,RamDomain a3) {
RamDomain data[4] = {a0,a1,a2,a3};
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
range<iterator> Type::lowerUpperRange_0000(const t_tuple& /* lower */, const t_tuple& /* upper */, context& /* h */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<iterator> Type::lowerUpperRange_0000(const t_tuple& /* lower */, const t_tuple& /* upper */) const {
return range<iterator>(ind_0.begin(),ind_0.end());
}
range<t_ind_0::iterator> Type::lowerUpperRange_1111(const t_tuple& lower, const t_tuple& upper, context& h) const {
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
range<t_ind_0::iterator> Type::lowerUpperRange_1111(const t_tuple& lower, const t_tuple& upper) const {
context h;
return lowerUpperRange_1111(lower,upper,h);
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
o << " arity 4 direct b-tree index 0 lex-order [0,1,2,3]\n";
ind_0.printStats(o);
}
} // namespace souffle::t_btree_iiii__0_1_2_3__1111 
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
class Stratum_magic_T2_bbbb__7ee48f05fac38c46 {
public:
 Stratum_magic_T2_bbbb__7ee48f05fac38c46(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiii__0_1_2_3__1111::Type& rel_magic_T2_bbbb__a52dd8127aaffaef,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f);
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
t_btree_iiii__0_1_2_3__1111::Type* rel_magic_T2_bbbb__a52dd8127aaffaef;
t_nullaries* rel_magic_result_prime_ffff__b237b896a4204d31;
t_btree_iiii__0_1_2_3__1111::Type* rel_T1_ffff__c3fb78c23a10cb3f;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_magic_T2_bbbb__7ee48f05fac38c46::Stratum_magic_T2_bbbb__7ee48f05fac38c46(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiii__0_1_2_3__1111::Type& rel_magic_T2_bbbb__a52dd8127aaffaef,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f):
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
rel_magic_T2_bbbb__a52dd8127aaffaef(&rel_magic_T2_bbbb__a52dd8127aaffaef),
rel_magic_result_prime_ffff__b237b896a4204d31(&rel_magic_result_prime_ffff__b237b896a4204d31),
rel_T1_ffff__c3fb78c23a10cb3f(&rel_T1_ffff__c3fb78c23a10cb3f){
}

void Stratum_magic_T2_bbbb__7ee48f05fac38c46::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;@magic.T2.{bbbb}; [1:1-1:1];)_",iter, [&](){return rel_magic_T2_bbbb__a52dd8127aaffaef->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(@magic.T2.{bbbb}(x,y,x2,y2) :- 
   @magic.result_prime.{ffff}(),
   T1.{ffff}(x,y,x2,y2).
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;@magic.T2.{bbbb}; [1:1-1:1];@magic.T2.{bbbb}(x,y,x2,y2) :- \n   @magic.result_prime.{ffff}(),\n   T1.{ffff}(x,y,x2,y2).;)_",iter, [&](){return rel_magic_T2_bbbb__a52dd8127aaffaef->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_T1_ffff__c3fb78c23a10cb3f->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_magic_T2_bbbb__a52dd8127aaffaef_op_ctxt,rel_magic_T2_bbbb__a52dd8127aaffaef->createContext());
CREATE_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt,rel_T1_ffff__c3fb78c23a10cb3f->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_T1_ffff__c3fb78c23a10cb3f) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_magic_T2_bbbb__a52dd8127aaffaef->insert(tuple,READ_OP_CONTEXT(rel_magic_T2_bbbb__a52dd8127aaffaef_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_magic_result_prime_ffff__3aad390435f6283d {
public:
 Stratum_magic_result_prime_ffff__3aad390435f6283d(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31);
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
t_nullaries* rel_magic_result_prime_ffff__b237b896a4204d31;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_magic_result_prime_ffff__3aad390435f6283d::Stratum_magic_result_prime_ffff__3aad390435f6283d(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31):
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
rel_magic_result_prime_ffff__b237b896a4204d31(&rel_magic_result_prime_ffff__b237b896a4204d31){
}

void Stratum_magic_result_prime_ffff__3aad390435f6283d::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;@magic.result_prime.{ffff}; [1:1-1:1];)_",iter, [&](){return rel_magic_result_prime_ffff__b237b896a4204d31->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(@magic.result_prime.{ffff}().
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;@magic.result_prime.{ffff}; [1:1-1:1];@magic.result_prime.{ffff}().;)_",iter, [&](){return rel_magic_result_prime_ffff__b237b896a4204d31->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
) {
[&](){
CREATE_OP_CONTEXT(rel_magic_result_prime_ffff__b237b896a4204d31_op_ctxt,rel_magic_result_prime_ffff__b237b896a4204d31->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,0> tuple{{}};
rel_magic_result_prime_ffff__b237b896a4204d31->insert(tuple,READ_OP_CONTEXT(rel_magic_result_prime_ffff__b237b896a4204d31_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_T1_ffff__319e895bce859217 {
public:
 Stratum_T1_ffff__319e895bce859217(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b);
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
t_nullaries* rel_magic_result_prime_ffff__b237b896a4204d31;
t_btree_iiii__0_1_2_3__1111::Type* rel_T1_ffff__c3fb78c23a10cb3f;
t_btree_ii__0_1__11__10::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_T1_ffff__319e895bce859217::Stratum_T1_ffff__319e895bce859217(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b):
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
rel_magic_result_prime_ffff__b237b896a4204d31(&rel_magic_result_prime_ffff__b237b896a4204d31),
rel_T1_ffff__c3fb78c23a10cb3f(&rel_T1_ffff__c3fb78c23a10cb3f),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_T1_ffff__319e895bce859217::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;T1.{ffff}; [1:1-1:1];)_",iter, [&](){return rel_T1_ffff__c3fb78c23a10cb3f->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(T1.{ffff}(x,y,x2,y2) :- 
   @magic.result_prime.{ffff}(),
   edge(x,y),
   edge(y,z),
   edge(x2,y2),
   z != x2.
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;T1.{ffff}; [1:1-1:1];T1.{ffff}(x,y,x2,y2) :- \n   @magic.result_prime.{ffff}(),\n   edge(x,y),\n   edge(y,z),\n   edge(x2,y2),\n   z != x2.;)_",iter, [&](){return rel_T1_ffff__c3fb78c23a10cb3f->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_edge_04d25f5060e9043b->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt,rel_T1_ffff__c3fb78c23a10cb3f->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:811 */
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env2 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1839 */
(ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
) != ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env2[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1909 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env2[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env2[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_T1_ffff__c3fb78c23a10cb3f->insert(tuple,READ_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:823 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(T1.{ffff}(x,y,x2,y2) :- 
   @magic.result_prime.{ffff}(),
   edge(x,y),
   edge(y,_),
   edge(x2,y2),
   x != y2.
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;T1.{ffff}; [1:1-1:1];T1.{ffff}(x,y,x2,y2) :- \n   @magic.result_prime.{ffff}(),\n   edge(x,y),\n   edge(y,_),\n   edge(x2,y2),\n   x != y2.;)_",iter, [&](){return rel_T1_ffff__c3fb78c23a10cb3f->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_edge_04d25f5060e9043b->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt,rel_T1_ffff__c3fb78c23a10cb3f->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
!rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)).empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1968 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env1 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1839 */
(ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
) != ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1909 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_T1_ffff__c3fb78c23a10cb3f->insert(tuple,READ_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_T2_bbbb__c35706141a28fa0c {
public:
 Stratum_T2_bbbb__c35706141a28fa0c(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiii__0_1_2_3__1111::Type& rel_magic_T2_bbbb__a52dd8127aaffaef,t_btree_iiii__0_1_2_3__1111::Type& rel_T2_bbbb__6d42374a2b7653c4,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b);
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
t_btree_iiii__0_1_2_3__1111::Type* rel_magic_T2_bbbb__a52dd8127aaffaef;
t_btree_iiii__0_1_2_3__1111::Type* rel_T2_bbbb__6d42374a2b7653c4;
t_btree_ii__0_1__11__10::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_T2_bbbb__c35706141a28fa0c::Stratum_T2_bbbb__c35706141a28fa0c(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_iiii__0_1_2_3__1111::Type& rel_magic_T2_bbbb__a52dd8127aaffaef,t_btree_iiii__0_1_2_3__1111::Type& rel_T2_bbbb__6d42374a2b7653c4,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b):
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
rel_magic_T2_bbbb__a52dd8127aaffaef(&rel_magic_T2_bbbb__a52dd8127aaffaef),
rel_T2_bbbb__6d42374a2b7653c4(&rel_T2_bbbb__6d42374a2b7653c4),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_T2_bbbb__c35706141a28fa0c::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;T2.{bbbb}; [1:1-1:1];)_",iter, [&](){return rel_T2_bbbb__6d42374a2b7653c4->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(T2.{bbbb}(x,y,x2,y2) :- 
   @magic.T2.{bbbb}(x,y,x2,y2),
   edge(y,x),
   edge(x,z),
   edge(x2,y2),
   z != y2.
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;T2.{bbbb}; [1:1-1:1];T2.{bbbb}(x,y,x2,y2) :- \n   @magic.T2.{bbbb}(x,y,x2,y2),\n   edge(y,x),\n   edge(x,z),\n   edge(x2,y2),\n   z != y2.;)_",iter, [&](){return rel_T2_bbbb__6d42374a2b7653c4->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_edge_04d25f5060e9043b->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_T2_bbbb__a52dd8127aaffaef->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_magic_T2_bbbb__a52dd8127aaffaef_op_ctxt,rel_magic_T2_bbbb__a52dd8127aaffaef->createContext());
CREATE_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt,rel_T2_bbbb__6d42374a2b7653c4->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_magic_T2_bbbb__a52dd8127aaffaef) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:991 */
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1839 */
(ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
) != ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1909 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_T2_bbbb__6d42374a2b7653c4->insert(tuple,READ_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
break;
}
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1020 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(T2.{bbbb}(x,y,x2,y2) :- 
   @magic.T2.{bbbb}(x,y,x2,y2),
   edge(y,x),
   edge(x,_),
   edge(x2,y2),
   y != x2.
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;T2.{bbbb}; [1:1-1:1];T2.{bbbb}(x,y,x2,y2) :- \n   @magic.T2.{bbbb}(x,y,x2,y2),\n   edge(y,x),\n   edge(x,_),\n   edge(x2,y2),\n   y != x2.;)_",iter, [&](){return rel_T2_bbbb__6d42374a2b7653c4->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_edge_04d25f5060e9043b->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_T2_bbbb__a52dd8127aaffaef->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_magic_T2_bbbb__a52dd8127aaffaef_op_ctxt,rel_magic_T2_bbbb__a52dd8127aaffaef->createContext());
CREATE_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt,rel_T2_bbbb__6d42374a2b7653c4->createContext());
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_magic_T2_bbbb__a52dd8127aaffaef) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1839 */
(ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
) != ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1909 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
!rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt)).empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1968 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_T2_bbbb__6d42374a2b7653c4->insert(tuple,READ_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
rel_magic_T2_bbbb__a52dd8127aaffaef->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_edge_9543a759b165a2cb {
public:
 Stratum_edge_9543a759b165a2cb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b);
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
t_btree_ii__0_1__11__10::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_edge_9543a759b165a2cb::Stratum_edge_9543a759b165a2cb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b):
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
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-relation-loadtime;edge;positive_rewrite_domain_reduction.dl [2:7-2:11];loadtime;)_",iter, [&](){return rel_edge_04d25f5060e9043b->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:335 */
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","facts"},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectory.empty()) {directiveMap["fact-dir"] = inputDirectory;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:394 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:506 */
ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;edge;positive_rewrite_domain_reduction.dl [2:7-2:11];)",rel_edge_04d25f5060e9043b->size(),iter);/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:510 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_result_positive_rewritten_cc3bb6a2ba838ebb {
public:
 Stratum_result_positive_rewritten_cc3bb6a2ba838ebb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_result_positive_rewritten_f19b5b85867f266b,t_btree_iiii__0_1_2_3__1111::Type& rel_result_prime_ffff__ef75ac9f2180b363);
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
t_btree_ii__0_1__11::Type* rel_result_positive_rewritten_f19b5b85867f266b;
t_btree_iiii__0_1_2_3__1111::Type* rel_result_prime_ffff__ef75ac9f2180b363;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_result_positive_rewritten_cc3bb6a2ba838ebb::Stratum_result_positive_rewritten_cc3bb6a2ba838ebb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_btree_ii__0_1__11::Type& rel_result_positive_rewritten_f19b5b85867f266b,t_btree_iiii__0_1_2_3__1111::Type& rel_result_prime_ffff__ef75ac9f2180b363):
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
rel_result_positive_rewritten_f19b5b85867f266b(&rel_result_positive_rewritten_f19b5b85867f266b),
rel_result_prime_ffff__ef75ac9f2180b363(&rel_result_prime_ffff__ef75ac9f2180b363){
}

void Stratum_result_positive_rewritten_cc3bb6a2ba838ebb::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;result_positive_rewritten;positive_rewrite_domain_reduction.dl [46:7-46:32];)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   result_prime.{ffff}(x,y,_,_).
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten; [1:1-1:1];result_positive_rewritten(x,y) :- \n   result_prime.{ffff}(x,y,_,_).;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_result_prime_ffff__ef75ac9f2180b363->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
) {
[&](){
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
CREATE_OP_CONTEXT(rel_result_prime_ffff__ef75ac9f2180b363_op_ctxt,rel_result_prime_ffff__ef75ac9f2180b363->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_result_prime_ffff__ef75ac9f2180b363) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,2> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-relation-savetime;result_positive_rewritten;positive_rewrite_domain_reduction.dl [46:7-46:32];savetime;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:335 */
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_positive_rewritten"},{"operation","output"},{"output-dir","output"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (outputDirectory == "-"){directiveMap["IO"] = "stdout"; directiveMap["headers"] = "true";}
else if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:394 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
if (pruneImdtRels) rel_result_prime_ffff__ef75ac9f2180b363->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_result_prime_ffff__2db33dc5f224e5e8 {
public:
 Stratum_result_prime_ffff__2db33dc5f224e5e8(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f,t_btree_iiii__0_1_2_3__1111::Type& rel_T2_bbbb__6d42374a2b7653c4,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b,t_btree_iiii__0_1_2_3__1111::Type& rel_result_prime_ffff__ef75ac9f2180b363);
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
t_nullaries* rel_magic_result_prime_ffff__b237b896a4204d31;
t_btree_iiii__0_1_2_3__1111::Type* rel_T1_ffff__c3fb78c23a10cb3f;
t_btree_iiii__0_1_2_3__1111::Type* rel_T2_bbbb__6d42374a2b7653c4;
t_btree_ii__0_1__11__10::Type* rel_edge_04d25f5060e9043b;
t_btree_iiii__0_1_2_3__1111::Type* rel_result_prime_ffff__ef75ac9f2180b363;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_result_prime_ffff__2db33dc5f224e5e8::Stratum_result_prime_ffff__2db33dc5f224e5e8(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_magic_result_prime_ffff__b237b896a4204d31,t_btree_iiii__0_1_2_3__1111::Type& rel_T1_ffff__c3fb78c23a10cb3f,t_btree_iiii__0_1_2_3__1111::Type& rel_T2_bbbb__6d42374a2b7653c4,t_btree_ii__0_1__11__10::Type& rel_edge_04d25f5060e9043b,t_btree_iiii__0_1_2_3__1111::Type& rel_result_prime_ffff__ef75ac9f2180b363):
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
rel_magic_result_prime_ffff__b237b896a4204d31(&rel_magic_result_prime_ffff__b237b896a4204d31),
rel_T1_ffff__c3fb78c23a10cb3f(&rel_T1_ffff__c3fb78c23a10cb3f),
rel_T2_bbbb__6d42374a2b7653c4(&rel_T2_bbbb__6d42374a2b7653c4),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b),
rel_result_prime_ffff__ef75ac9f2180b363(&rel_result_prime_ffff__ef75ac9f2180b363){
}

void Stratum_result_prime_ffff__2db33dc5f224e5e8::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-relation;result_prime.{ffff}; [1:1-1:1];)_",iter, [&](){return rel_result_prime_ffff__ef75ac9f2180b363->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(result_prime.{ffff}(x,y,x2,y2) :- 
   @magic.result_prime.{ffff}(),
   edge(x,y),
   edge(y,z),
   edge(z,x),
   edge(x2,y2).
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;result_prime.{ffff}; [1:1-1:1];result_prime.{ffff}(x,y,x2,y2) :- \n   @magic.result_prime.{ffff}(),\n   edge(x,y),\n   edge(y,z),\n   edge(z,x),\n   edge(x2,y2).;)_",iter, [&](){return rel_result_prime_ffff__ef75ac9f2180b363->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_edge_04d25f5060e9043b->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_prime_ffff__ef75ac9f2180b363_op_ctxt,rel_result_prime_ffff__ef75ac9f2180b363->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:991 */
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env1[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env2 : *rel_edge_04d25f5060e9043b) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env2[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env2[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_result_prime_ffff__ef75ac9f2180b363->insert(tuple,READ_OP_CONTEXT(rel_result_prime_ffff__ef75ac9f2180b363_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
break;
}
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1020 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:644 */
signalHandler->setMsg(R"_(result_prime.{ffff}(x,y,x2,y2) :- 
   @magic.result_prime.{ffff}(),
   T1.{ffff}(x,y,x2,y2),
   T2.{bbbb}(x,y,x2,y2),
   x != y.
in file  [1:1-1:1])_");
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:607 */
{
	Logger logger(R"_(@t-nonrecursive-rule;result_prime.{ffff}; [1:1-1:1];result_prime.{ffff}(x,y,x2,y2) :- \n   @magic.result_prime.{ffff}(),\n   T1.{ffff}(x,y,x2,y2),\n   T2.{bbbb}(x,y,x2,y2),\n   x != y.;)_",iter, [&](){return rel_result_prime_ffff__ef75ac9f2180b363->size();});
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:398 */
if(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_T1_ffff__c3fb78c23a10cb3f->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_magic_result_prime_ffff__b237b896a4204d31->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1802 */
!(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1920 */
rel_T2_bbbb__6d42374a2b7653c4->empty()/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1923 */
)/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1806 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
[&](){
CREATE_OP_CONTEXT(rel_T1_ffff__c3fb78c23a10cb3f_op_ctxt,rel_T1_ffff__c3fb78c23a10cb3f->createContext());
CREATE_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt,rel_T2_bbbb__6d42374a2b7653c4->createContext());
CREATE_OP_CONTEXT(rel_result_prime_ffff__ef75ac9f2180b363_op_ctxt,rel_result_prime_ffff__ef75ac9f2180b363->createContext());
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:714 */
for(const auto& env0 : *rel_T1_ffff__c3fb78c23a10cb3f) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:666 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1702 */
if( /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1794 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1839 */
(ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
) != ramBitCast<RamDomain>(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1909 */
 && /* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1935 */
rel_T2_bbbb__6d42374a2b7653c4->contains(Tuple<RamDomain,4>{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}},READ_OP_CONTEXT(rel_T2_bbbb__6d42374a2b7653c4_op_ctxt))/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1954 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1798 */
) {
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1749 */
Tuple<RamDomain,4> tuple{{ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[0]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[1]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[2]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
),ramBitCast(/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2055 */
env0[3]/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:2057 */
)}};
rel_result_prime_ffff__ef75ac9f2180b363->insert(tuple,READ_OP_CONTEXT(rel_result_prime_ffff__ef75ac9f2180b363_op_ctxt));
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1763 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:1708 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:668 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:725 */
}
();}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:485 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:651 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:623 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
rel_magic_result_prime_ffff__b237b896a4204d31->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
if (pruneImdtRels) rel_T1_ffff__c3fb78c23a10cb3f->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
if (pruneImdtRels) rel_T2_bbbb__6d42374a2b7653c4->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:489 */
if (pruneImdtRels) rel_edge_04d25f5060e9043b->purge();
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:502 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Sf_transformed: public SouffleProgram {
public:
 Sf_transformed(std::string pf = "profile.log");
 ~Sf_transformed();
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
std::size_t freqs[103];
std::size_t reads[5];
Own<t_nullaries> rel_magic_result_prime_ffff__b237b896a4204d31;
Own<t_btree_ii__0_1__11__10::Type> rel_edge_04d25f5060e9043b;
souffle::RelationWrapper<t_btree_ii__0_1__11__10::Type> wrapper_rel_edge_04d25f5060e9043b;
Own<t_btree_iiii__0_1_2_3__1111::Type> rel_T1_ffff__c3fb78c23a10cb3f;
souffle::RelationWrapper<t_btree_iiii__0_1_2_3__1111::Type> wrapper_rel_T1_ffff__c3fb78c23a10cb3f;
Own<t_btree_iiii__0_1_2_3__1111::Type> rel_magic_T2_bbbb__a52dd8127aaffaef;
Own<t_btree_iiii__0_1_2_3__1111::Type> rel_T2_bbbb__6d42374a2b7653c4;
souffle::RelationWrapper<t_btree_iiii__0_1_2_3__1111::Type> wrapper_rel_T2_bbbb__6d42374a2b7653c4;
Own<t_btree_iiii__0_1_2_3__1111::Type> rel_result_prime_ffff__ef75ac9f2180b363;
souffle::RelationWrapper<t_btree_iiii__0_1_2_3__1111::Type> wrapper_rel_result_prime_ffff__ef75ac9f2180b363;
Own<t_btree_ii__0_1__11::Type> rel_result_positive_rewritten_f19b5b85867f266b;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_result_positive_rewritten_f19b5b85867f266b;
Stratum_magic_T2_bbbb__7ee48f05fac38c46 stratum_magic_T2_bbbb__45387d21396dd68b;
Stratum_magic_result_prime_ffff__3aad390435f6283d stratum_magic_result_prime_ffff__148a8b50ac407801;
Stratum_T1_ffff__319e895bce859217 stratum_T1_ffff__bdbab33ef428c593;
Stratum_T2_bbbb__c35706141a28fa0c stratum_T2_bbbb__07cd76e0010ec093;
Stratum_edge_9543a759b165a2cb stratum_edge_31e40d0d94fe9f7c;
Stratum_result_positive_rewritten_cc3bb6a2ba838ebb stratum_result_positive_rewritten_16ede51278f68d5b;
Stratum_result_prime_ffff__2db33dc5f224e5e8 stratum_result_prime_ffff__71983e21f12b4ff7;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Sf_transformed::Sf_transformed(std::string pf):
profiling_fname(std::move(pf)),
symTable(),
recordTable(),
regexCache(),
freqs(),
reads(),
rel_magic_result_prime_ffff__b237b896a4204d31(mk<t_nullaries>()),
rel_edge_04d25f5060e9043b(mk<t_btree_ii__0_1__11__10::Type>()),
wrapper_rel_edge_04d25f5060e9043b(0, *rel_edge_04d25f5060e9043b, *this, "edge", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_T1_ffff__c3fb78c23a10cb3f(mk<t_btree_iiii__0_1_2_3__1111::Type>()),
wrapper_rel_T1_ffff__c3fb78c23a10cb3f(1, *rel_T1_ffff__c3fb78c23a10cb3f, *this, "T1.{ffff}", std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}}, std::array<const char *,4>{{"x","y","x2","y2"}}, 0),
rel_magic_T2_bbbb__a52dd8127aaffaef(mk<t_btree_iiii__0_1_2_3__1111::Type>()),
rel_T2_bbbb__6d42374a2b7653c4(mk<t_btree_iiii__0_1_2_3__1111::Type>()),
wrapper_rel_T2_bbbb__6d42374a2b7653c4(2, *rel_T2_bbbb__6d42374a2b7653c4, *this, "T2.{bbbb}", std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}}, std::array<const char *,4>{{"x","y","x2","y2"}}, 0),
rel_result_prime_ffff__ef75ac9f2180b363(mk<t_btree_iiii__0_1_2_3__1111::Type>()),
wrapper_rel_result_prime_ffff__ef75ac9f2180b363(3, *rel_result_prime_ffff__ef75ac9f2180b363, *this, "result_prime.{ffff}", std::array<const char *,4>{{"i:number","i:number","i:number","i:number"}}, std::array<const char *,4>{{"x","y","x2","y2"}}, 0),
rel_result_positive_rewritten_f19b5b85867f266b(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_result_positive_rewritten_f19b5b85867f266b(4, *rel_result_positive_rewritten_f19b5b85867f266b, *this, "result_positive_rewritten", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
stratum_magic_T2_bbbb__45387d21396dd68b(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_magic_T2_bbbb__a52dd8127aaffaef,*rel_magic_result_prime_ffff__b237b896a4204d31,*rel_T1_ffff__c3fb78c23a10cb3f),
stratum_magic_result_prime_ffff__148a8b50ac407801(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_magic_result_prime_ffff__b237b896a4204d31),
stratum_T1_ffff__bdbab33ef428c593(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_magic_result_prime_ffff__b237b896a4204d31,*rel_T1_ffff__c3fb78c23a10cb3f,*rel_edge_04d25f5060e9043b),
stratum_T2_bbbb__07cd76e0010ec093(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_magic_T2_bbbb__a52dd8127aaffaef,*rel_T2_bbbb__6d42374a2b7653c4,*rel_edge_04d25f5060e9043b),
stratum_edge_31e40d0d94fe9f7c(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_edge_04d25f5060e9043b),
stratum_result_positive_rewritten_16ede51278f68d5b(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_result_positive_rewritten_f19b5b85867f266b,*rel_result_prime_ffff__ef75ac9f2180b363),
stratum_result_prime_ffff__71983e21f12b4ff7(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_magic_result_prime_ffff__b237b896a4204d31,*rel_T1_ffff__c3fb78c23a10cb3f,*rel_T2_bbbb__6d42374a2b7653c4,*rel_edge_04d25f5060e9043b,*rel_result_prime_ffff__ef75ac9f2180b363){
addRelation("edge", wrapper_rel_edge_04d25f5060e9043b, true, false);
addRelation("T1.{ffff}", wrapper_rel_T1_ffff__c3fb78c23a10cb3f, false, false);
addRelation("T2.{bbbb}", wrapper_rel_T2_bbbb__6d42374a2b7653c4, false, false);
addRelation("result_prime.{ffff}", wrapper_rel_result_prime_ffff__ef75ac9f2180b363, false, false);
addRelation("result_positive_rewritten", wrapper_rel_result_positive_rewritten_f19b5b85867f266b, false, true);
ProfileEventSingleton::instance().setOutputFile(profiling_fname);
}

 Sf_transformed::~Sf_transformed(){
}

void Sf_transformed::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

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
signalHandler->enableLogging();
// -- query evaluation --
ProfileEventSingleton::instance().startTimer();
ProfileEventSingleton::instance().makeTimeEvent("@time;starttime");
{
Logger logger("@runtime;", 0);
ProfileEventSingleton::instance().makeConfigRecord("relationCount", std::to_string(5));/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:627 */
{
	Logger logger(R"_(@runtime;)_",iter);
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:516 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_magic_result_prime_ffff__148a8b50ac407801.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_T1_ffff__bdbab33ef428c593.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_magic_T2_bbbb__45387d21396dd68b.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_T2_bbbb__07cd76e0010ec093.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_result_prime_ffff__71983e21f12b4ff7.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* BEGIN visit_ @/souffle/src/synthesiser/Synthesiser.cpp:597 */
{
 std::vector<RamDomain> args, ret;
stratum_result_positive_rewritten_16ede51278f68d5b.run(args, ret);
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:602 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:640 */
/* END visit_ @/souffle/src/synthesiser/Synthesiser.cpp:520 */
}
ProfileEventSingleton::instance().stopTimer();
dumpFreqs();

// -- relation hint statistics --
std::cout << "Statistics for Relation rel_magic_result_prime_ffff__b237b896a4204d31:\n";
rel_magic_result_prime_ffff__b237b896a4204d31->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_edge_04d25f5060e9043b:\n";
rel_edge_04d25f5060e9043b->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_T1_ffff__c3fb78c23a10cb3f:\n";
rel_T1_ffff__c3fb78c23a10cb3f->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_magic_T2_bbbb__a52dd8127aaffaef:\n";
rel_magic_T2_bbbb__a52dd8127aaffaef->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_T2_bbbb__6d42374a2b7653c4:\n";
rel_T2_bbbb__6d42374a2b7653c4->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_result_prime_ffff__ef75ac9f2180b363:\n";
rel_result_prime_ffff__ef75ac9f2180b363->printStatistics(std::cout);
std::cout << "\n";
std::cout << "Statistics for Relation rel_result_positive_rewritten_f19b5b85867f266b:\n";
rel_result_positive_rewritten_f19b5b85867f266b->printStatistics(std::cout);
std::cout << "\n";
signalHandler->reset();
}

void Sf_transformed::run(){
runFunction("", "", false, false);
}

void Sf_transformed::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf_transformed::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_positive_rewritten"},{"operation","output"},{"output-dir","output"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_transformed::loadAll([[maybe_unused]] std::string inputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","facts"},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectoryArg.empty()) {directiveMap["fact-dir"] = inputDirectoryArg;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}

void Sf_transformed::dumpInputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "edge";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf_transformed::dumpOutputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "result_positive_rewritten";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

SymbolTable& Sf_transformed::getSymbolTable(){
return symTable;
}

RecordTable& Sf_transformed::getRecordTable(){
return recordTable;
}

void Sf_transformed::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
regexCache.setNumLanes(getNumThreads());
}

void Sf_transformed::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
if (name == "@magic.T2.{bbbb}") {
stratum_magic_T2_bbbb__45387d21396dd68b.run(args, ret);
return;}
if (name == "@magic.result_prime.{ffff}") {
stratum_magic_result_prime_ffff__148a8b50ac407801.run(args, ret);
return;}
if (name == "T1.{ffff}") {
stratum_T1_ffff__bdbab33ef428c593.run(args, ret);
return;}
if (name == "T2.{bbbb}") {
stratum_T2_bbbb__07cd76e0010ec093.run(args, ret);
return;}
if (name == "edge") {
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
return;}
if (name == "result_positive_rewritten") {
stratum_result_positive_rewritten_16ede51278f68d5b.run(args, ret);
return;}
if (name == "result_prime.{ffff}") {
stratum_result_prime_ffff__71983e21f12b4ff7.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

void Sf_transformed::dumpFreqs(){
}

} // namespace  souffle
namespace souffle {
SouffleProgram *newInstance_transformed(){return new  souffle::Sf_transformed;}
SymbolTable *getST_transformed(SouffleProgram *p){return &reinterpret_cast<souffle::Sf_transformed*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(positive_rewrite_domain_reduction.dl)",
R"()",
R"()",
true,
R"(pos_rewrite.log)",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf_transformed obj(opt.getProfileName());
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
class factory_Sf_transformed: souffle::ProgramFactory {
public:
souffle::SouffleProgram* newInstance();
 factory_Sf_transformed();
private:
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
souffle::SouffleProgram* factory_Sf_transformed::newInstance(){
return new  souffle::Sf_transformed();
}

 factory_Sf_transformed::factory_Sf_transformed():
souffle::ProgramFactory("transformed"){
}

} // namespace  souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
souffle::factory_Sf_transformed __factory_Sf_transformed_instance;
}
#endif
} // namespace souffle

