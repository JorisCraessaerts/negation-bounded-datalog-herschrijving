#define SOUFFLE_GENERATOR_VERSION "2.4"
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
class Stratum_disconnected0_afed6794479dbd87 {
public:
 Stratum_disconnected0_afed6794479dbd87(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_disconnected0_b2add3842fe11dfe,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b);
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
t_nullaries* rel_disconnected0_b2add3842fe11dfe;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_disconnected0_afed6794479dbd87::Stratum_disconnected0_afed6794479dbd87(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_disconnected0_b2add3842fe11dfe,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b):
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
rel_disconnected0_b2add3842fe11dfe(&rel_disconnected0_b2add3842fe11dfe),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b){
}

void Stratum_disconnected0_afed6794479dbd87::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;+disconnected0; [1:1-1:1];)_",iter, [&](){return rel_disconnected0_b2add3842fe11dfe->size();});
signalHandler->setMsg(R"_(+disconnected0() :- 
   edge(_,_).
in file 3_unfolding.dl [6:1-6:23])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;+disconnected0;3_unfolding.dl [6:1-6:23];+disconnected0() :- \n   edge(_,_).;)_",iter, [&](){return rel_disconnected0_b2add3842fe11dfe->size();});
if(rel_disconnected0_b2add3842fe11dfe->empty() && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_disconnected0_b2add3842fe11dfe_op_ctxt,rel_disconnected0_b2add3842fe11dfe->createContext());
Tuple<RamDomain,0> tuple{{}};
rel_disconnected0_b2add3842fe11dfe->insert(tuple,READ_OP_CONTEXT(rel_disconnected0_b2add3842fe11dfe_op_ctxt));
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
	Logger logger(R"_(@t-relation-loadtime;edge;3_unfolding.dl [1:7-1:11];loadtime;)_",iter, [&](){return rel_edge_04d25f5060e9043b->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","."},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectory.empty()) {directiveMap["fact-dir"] = inputDirectory;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}
}
ProfileEventSingleton::instance().makeQuantityEvent( R"(@n-nonrecursive-relation;edge;3_unfolding.dl [1:7-1:11];)",rel_edge_04d25f5060e9043b->size(),iter);}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Stratum_result_positive_rewritten_cc3bb6a2ba838ebb {
public:
 Stratum_result_positive_rewritten_cc3bb6a2ba838ebb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_disconnected0_b2add3842fe11dfe,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b,t_btree_ii__0_1__11::Type& rel_result_positive_rewritten_f19b5b85867f266b);
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
t_nullaries* rel_disconnected0_b2add3842fe11dfe;
t_btree_ii__1_0__0__11__10__01::Type* rel_edge_04d25f5060e9043b;
t_btree_ii__0_1__11::Type* rel_result_positive_rewritten_f19b5b85867f266b;
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Stratum_result_positive_rewritten_cc3bb6a2ba838ebb::Stratum_result_positive_rewritten_cc3bb6a2ba838ebb(SymbolTable& symTable,RecordTable& recordTable,ConcurrentCache<std::string,std::regex>& regexCache,bool& pruneImdtRels,bool& performIO,SignalHandler*& signalHandler,std::atomic<std::size_t>& iter,std::atomic<RamDomain>& ctr,std::string& inputDirectory,std::string& outputDirectory,t_nullaries& rel_disconnected0_b2add3842fe11dfe,t_btree_ii__1_0__0__11__10__01::Type& rel_edge_04d25f5060e9043b,t_btree_ii__0_1__11::Type& rel_result_positive_rewritten_f19b5b85867f266b):
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
rel_disconnected0_b2add3842fe11dfe(&rel_disconnected0_b2add3842fe11dfe),
rel_edge_04d25f5060e9043b(&rel_edge_04d25f5060e9043b),
rel_result_positive_rewritten_f19b5b85867f266b(&rel_result_positive_rewritten_f19b5b85867f266b){
}

void Stratum_result_positive_rewritten_cc3bb6a2ba838ebb::run([[maybe_unused]] const std::vector<RamDomain>& args,[[maybe_unused]] std::vector<RamDomain>& ret){
{
	Logger logger(R"_(@t-nonrecursive-relation;result_positive_rewritten;3_unfolding.dl [10:7-10:32];)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z),
   edge(z,x).
in file 3_unfolding.dl [16:1-19:16])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [16:1-19:16];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z),\n   edge(z,x).;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( rel_edge_04d25f5060e9043b->contains(Tuple<RamDomain,2>{{ramBitCast(env1[1]),ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   x != y,
   y != z2.
in file 3_unfolding.dl [31:1-33:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [31:1-33:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   y != z2.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   x != y,
   z2 != x.
in file 3_unfolding.dl [34:1-36:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [34:1-36:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   z2 != x.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   y != z2,
   z2 != x,
   x != y.
in file 3_unfolding.dl [40:1-42:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [40:1-42:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   y != z2,\n   z2 != x,\n   x != y.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   x != y,
   y != z2.
in file 3_unfolding.dl [45:1-47:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [45:1-47:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   y != z2.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   x != y,
   z2 != x.
in file 3_unfolding.dl [48:1-50:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [48:1-50:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   z2 != x.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   x != z1,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   y != z2,
   z2 != x,
   x != y.
in file 3_unfolding.dl [54:1-56:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [54:1-56:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   x != z1,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   y != z2,\n   z2 != x,\n   x != y.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   x != y,
   y != z2.
in file 3_unfolding.dl [59:1-61:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [59:1-61:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   y != z2.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   x != y,
   z2 != x.
in file 3_unfolding.dl [62:1-64:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [62:1-64:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   z2 != x.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   y != z1,
   edge(z2,x),
   +disconnected0(),
   y != z2,
   z2 != x,
   x != y.
in file 3_unfolding.dl [68:1-70:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [68:1-70:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   y != z1,\n   edge(z2,x),\n   +disconnected0(),\n   y != z2,\n   z2 != x,\n   x != y.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env1[1]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   x != y,
   y != z2.
in file 3_unfolding.dl [73:1-75:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [73:1-75:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   y != z2.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   x != y,
   z2 != x.
in file 3_unfolding.dl [76:1-78:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [76:1-78:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   x != y,\n   z2 != x.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
signalHandler->setMsg(R"_(result_positive_rewritten(x,y) :- 
   edge(x,y),
   edge(y,z1),
   y != x,
   z1 != x,
   edge(z2,x),
   +disconnected0(),
   y != z2,
   z2 != x,
   x != y.
in file 3_unfolding.dl [82:1-84:41])_");
{
	Logger logger(R"_(@t-nonrecursive-rule;result_positive_rewritten;3_unfolding.dl [82:1-84:41];result_positive_rewritten(x,y) :- \n   edge(x,y),\n   edge(y,z1),\n   y != x,\n   z1 != x,\n   edge(z2,x),\n   +disconnected0(),\n   y != z2,\n   z2 != x,\n   x != y.;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if(!(rel_disconnected0_b2add3842fe11dfe->empty()) && !(rel_edge_04d25f5060e9043b->empty())) {
[&](){
CREATE_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt,rel_edge_04d25f5060e9043b->createContext());
CREATE_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt,rel_result_positive_rewritten_f19b5b85867f266b->createContext());
for(const auto& env0 : *rel_edge_04d25f5060e9043b) {
if( (ramBitCast<RamDomain>(env0[0]) != ramBitCast<RamDomain>(env0[1])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_10(Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MIN_RAM_SIGNED)}},Tuple<RamDomain,2>{{ramBitCast(env0[1]), ramBitCast<RamDomain>(MAX_RAM_SIGNED)}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env1 : range) {
if( (ramBitCast<RamDomain>(env1[1]) != ramBitCast<RamDomain>(env0[0]))) {
auto range = rel_edge_04d25f5060e9043b->lowerUpperRange_01(Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MIN_RAM_SIGNED), ramBitCast(env0[0])}},Tuple<RamDomain,2>{{ramBitCast<RamDomain>(MAX_RAM_SIGNED), ramBitCast(env0[0])}},READ_OP_CONTEXT(rel_edge_04d25f5060e9043b_op_ctxt));
for(const auto& env2 : range) {
if( (ramBitCast<RamDomain>(env2[0]) != ramBitCast<RamDomain>(env0[0])) && (ramBitCast<RamDomain>(env0[1]) != ramBitCast<RamDomain>(env2[0]))) {
Tuple<RamDomain,2> tuple{{ramBitCast(env0[0]),ramBitCast(env0[1])}};
rel_result_positive_rewritten_f19b5b85867f266b->insert(tuple,READ_OP_CONTEXT(rel_result_positive_rewritten_f19b5b85867f266b_op_ctxt));
break;
}
}
break;
}
}
}
}
}
();}
}
}
{
	Logger logger(R"_(@t-relation-savetime;result_positive_rewritten;3_unfolding.dl [10:7-10:32];savetime;)_",iter, [&](){return rel_result_positive_rewritten_f19b5b85867f266b->size();});
if (performIO) {
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_positive_rewritten"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (outputDirectory == "-"){directiveMap["IO"] = "stdout"; directiveMap["headers"] = "true";}
else if (!outputDirectory.empty()) {directiveMap["output-dir"] = outputDirectory;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}
}
if (pruneImdtRels) rel_disconnected0_b2add3842fe11dfe->purge();
if (pruneImdtRels) rel_edge_04d25f5060e9043b->purge();
}

} // namespace  souffle

namespace  souffle {
using namespace souffle;
class Sf___unfolding__noopt: public SouffleProgram {
public:
 Sf___unfolding__noopt(std::string pf = "profile.log");
 ~Sf___unfolding__noopt();
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
std::size_t freqs[78];
std::size_t reads[3];
Own<t_btree_ii__1_0__0__11__10__01::Type> rel_edge_04d25f5060e9043b;
souffle::RelationWrapper<t_btree_ii__1_0__0__11__10__01::Type> wrapper_rel_edge_04d25f5060e9043b;
Own<t_nullaries> rel_disconnected0_b2add3842fe11dfe;
souffle::RelationWrapper<t_nullaries> wrapper_rel_disconnected0_b2add3842fe11dfe;
Own<t_btree_ii__0_1__11::Type> rel_result_positive_rewritten_f19b5b85867f266b;
souffle::RelationWrapper<t_btree_ii__0_1__11::Type> wrapper_rel_result_positive_rewritten_f19b5b85867f266b;
Stratum_disconnected0_afed6794479dbd87 stratum_disconnected0_f9c4672e8cd1a89c;
Stratum_edge_9543a759b165a2cb stratum_edge_31e40d0d94fe9f7c;
Stratum_result_positive_rewritten_cc3bb6a2ba838ebb stratum_result_positive_rewritten_16ede51278f68d5b;
std::string inputDirectory;
std::string outputDirectory;
SignalHandler* signalHandler{SignalHandler::instance()};
std::atomic<RamDomain> ctr{};
std::atomic<std::size_t> iter{};
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
 Sf___unfolding__noopt::Sf___unfolding__noopt(std::string pf):
profiling_fname(std::move(pf)),
symTable(),
recordTable(),
regexCache(),
freqs(),
reads(),
rel_edge_04d25f5060e9043b(mk<t_btree_ii__1_0__0__11__10__01::Type>()),
wrapper_rel_edge_04d25f5060e9043b(0, *rel_edge_04d25f5060e9043b, *this, "edge", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
rel_disconnected0_b2add3842fe11dfe(mk<t_nullaries>()),
wrapper_rel_disconnected0_b2add3842fe11dfe(1, *rel_disconnected0_b2add3842fe11dfe, *this, "+disconnected0", std::array<const char *,0>{{}}, std::array<const char *,0>{{}}, 0),
rel_result_positive_rewritten_f19b5b85867f266b(mk<t_btree_ii__0_1__11::Type>()),
wrapper_rel_result_positive_rewritten_f19b5b85867f266b(2, *rel_result_positive_rewritten_f19b5b85867f266b, *this, "result_positive_rewritten", std::array<const char *,2>{{"i:number","i:number"}}, std::array<const char *,2>{{"x","y"}}, 0),
stratum_disconnected0_f9c4672e8cd1a89c(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_disconnected0_b2add3842fe11dfe,*rel_edge_04d25f5060e9043b),
stratum_edge_31e40d0d94fe9f7c(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_edge_04d25f5060e9043b),
stratum_result_positive_rewritten_16ede51278f68d5b(symTable,recordTable,regexCache,pruneImdtRels,performIO,signalHandler,iter,ctr,inputDirectory,outputDirectory,*rel_disconnected0_b2add3842fe11dfe,*rel_edge_04d25f5060e9043b,*rel_result_positive_rewritten_f19b5b85867f266b){
addRelation("edge", wrapper_rel_edge_04d25f5060e9043b, true, false);
addRelation("+disconnected0", wrapper_rel_disconnected0_b2add3842fe11dfe, false, false);
addRelation("result_positive_rewritten", wrapper_rel_result_positive_rewritten_f19b5b85867f266b, false, true);
ProfileEventSingleton::instance().setOutputFile(profiling_fname);
}

 Sf___unfolding__noopt::~Sf___unfolding__noopt(){
}

void Sf___unfolding__noopt::runFunction(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){

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
ProfileEventSingleton::instance().makeConfigRecord("relationCount", std::to_string(3));{
	Logger logger(R"_(@runtime;)_",iter);
{
 std::vector<RamDomain> args, ret;
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_disconnected0_f9c4672e8cd1a89c.run(args, ret);
}
{
 std::vector<RamDomain> args, ret;
stratum_result_positive_rewritten_16ede51278f68d5b.run(args, ret);
}
}
}
ProfileEventSingleton::instance().stopTimer();
dumpFreqs();

// -- relation hint statistics --
signalHandler->reset();
}

void Sf___unfolding__noopt::run(){
runFunction("", "", false, false);
}

void Sf___unfolding__noopt::runAll(std::string inputDirectoryArg,std::string outputDirectoryArg,bool performIOArg,bool pruneImdtRelsArg){
runFunction(inputDirectoryArg, outputDirectoryArg, performIOArg, pruneImdtRelsArg);
}

void Sf___unfolding__noopt::printAll([[maybe_unused]] std::string outputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"name","result_positive_rewritten"},{"operation","output"},{"output-dir","."},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!outputDirectoryArg.empty()) {directiveMap["output-dir"] = outputDirectoryArg;}
IOSystem::getInstance().getWriter(directiveMap, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf___unfolding__noopt::loadAll([[maybe_unused]] std::string inputDirectoryArg){
try {std::map<std::string, std::string> directiveMap({{"IO","file"},{"attributeNames","x\ty"},{"auxArity","0"},{"fact-dir","."},{"name","edge"},{"operation","input"},{"params","{\"records\": {}, \"relation\": {\"arity\": 2, \"params\": [\"x\", \"y\"]}}"},{"types","{\"ADTs\": {}, \"records\": {}, \"relation\": {\"arity\": 2, \"types\": [\"i:number\", \"i:number\"]}}"}});
if (!inputDirectoryArg.empty()) {directiveMap["fact-dir"] = inputDirectoryArg;}
IOSystem::getInstance().getReader(directiveMap, symTable, recordTable)->readAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << "Error loading edge data: " << e.what() << '\n';
exit(1);
}
}

void Sf___unfolding__noopt::dumpInputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "edge";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_edge_04d25f5060e9043b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

void Sf___unfolding__noopt::dumpOutputs(){
try {std::map<std::string, std::string> rwOperation;
rwOperation["IO"] = "stdout";
rwOperation["name"] = "result_positive_rewritten";
rwOperation["types"] = "{\"relation\": {\"arity\": 2, \"auxArity\": 0, \"types\": [\"i:number\", \"i:number\"]}}";
IOSystem::getInstance().getWriter(rwOperation, symTable, recordTable)->writeAll(*rel_result_positive_rewritten_f19b5b85867f266b);
} catch (std::exception& e) {std::cerr << e.what();exit(1);}
}

SymbolTable& Sf___unfolding__noopt::getSymbolTable(){
return symTable;
}

RecordTable& Sf___unfolding__noopt::getRecordTable(){
return recordTable;
}

void Sf___unfolding__noopt::setNumThreads(std::size_t numThreadsValue){
SouffleProgram::setNumThreads(numThreadsValue);
symTable.setNumLanes(getNumThreads());
recordTable.setNumLanes(getNumThreads());
regexCache.setNumLanes(getNumThreads());
}

void Sf___unfolding__noopt::executeSubroutine(std::string name,const std::vector<RamDomain>& args,std::vector<RamDomain>& ret){
if (name == "+disconnected0") {
stratum_disconnected0_f9c4672e8cd1a89c.run(args, ret);
return;}
if (name == "edge") {
stratum_edge_31e40d0d94fe9f7c.run(args, ret);
return;}
if (name == "result_positive_rewritten") {
stratum_result_positive_rewritten_16ede51278f68d5b.run(args, ret);
return;}
fatal(("unknown subroutine " + name).c_str());
}

void Sf___unfolding__noopt::dumpFreqs(){
}

} // namespace  souffle
namespace souffle {
SouffleProgram *newInstance___unfolding__noopt(){return new  souffle::Sf___unfolding__noopt;}
SymbolTable *getST___unfolding__noopt(SouffleProgram *p){return &reinterpret_cast<souffle::Sf___unfolding__noopt*>(p)->getSymbolTable();}
} // namespace souffle

#ifndef __EMBEDDED_SOUFFLE__
#include "souffle/CompiledOptions.h"
int main(int argc, char** argv)
{
try{
souffle::CmdOptions opt(R"(3_unfolding.dl)",
R"()",
R"()",
true,
R"(/dev/null)",
1);
if (!opt.parse(argc,argv)) return 1;
souffle::Sf___unfolding__noopt obj(opt.getProfileName());
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
class factory_Sf___unfolding__noopt: souffle::ProgramFactory {
public:
souffle::SouffleProgram* newInstance();
 factory_Sf___unfolding__noopt();
private:
};
} // namespace  souffle
namespace  souffle {
using namespace souffle;
souffle::SouffleProgram* factory_Sf___unfolding__noopt::newInstance(){
return new  souffle::Sf___unfolding__noopt();
}

 factory_Sf___unfolding__noopt::factory_Sf___unfolding__noopt():
souffle::ProgramFactory("__unfolding__noopt"){
}

} // namespace  souffle
namespace souffle {

#ifdef __EMBEDDED_SOUFFLE__
extern "C" {
souffle::factory_Sf___unfolding__noopt __factory_Sf___unfolding__noopt_instance;
}
#endif
} // namespace souffle

