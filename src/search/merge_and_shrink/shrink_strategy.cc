#include "shrink_strategy.h"

#include "factored_transition_system.h"
#include "transition_system.h"

#include "../plugin.h"

#include <iostream>

using namespace std;

namespace merge_and_shrink {
bool ShrinkStrategy::shrink_fts(
    FactoredTransitionSystem &fts,
    int index,
    const StateEquivalenceRelation &equivalence_relation,
    Verbosity verbosity) const {
    // TODO: We currently violate this; see issue250
    //assert(equivalence_relation.size() <= new_size);
    return fts.apply_abstraction(index, equivalence_relation, verbosity);
}

void ShrinkStrategy::dump_options() const {
    cout << "Shrink strategy options: " << endl;
    cout << "Type: " << name() << endl;
    dump_strategy_specific_options();
}

string ShrinkStrategy::get_name() const {
    return name();
}

static PluginTypePlugin<ShrinkStrategy> _type_plugin(
    "ShrinkStrategy",
    "This page describes the various shrink strategies supported "
    "by the planner.");
}
