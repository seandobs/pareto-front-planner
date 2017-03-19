#ifndef MERGE_AND_SHRINK_MERGE_AND_SHRINK_HEURISTIC_H
#define MERGE_AND_SHRINK_MERGE_AND_SHRINK_HEURISTIC_H

#include "../heuristic.h"

#include <memory>

namespace utils {
class Timer;
}

namespace merge_and_shrink {
class FactoredTransitionSystem;
class LabelReduction;
class MergeAndShrinkRepresentation;
class MergeStrategyFactory;
class ShrinkStrategy;
class TransitionSystem;
enum class Verbosity;

class MergeAndShrinkHeuristic : public Heuristic {
    // TODO: when the option parser supports it, the following should become
    // unique pointers.
    std::shared_ptr<MergeStrategyFactory> merge_strategy_factory;
    std::shared_ptr<ShrinkStrategy> shrink_strategy;
    std::shared_ptr<LabelReduction> label_reduction;

    // Options for shrinking
    // Hard limit: the maximum size of a transition system at any point.
    const int max_states;
    // Hard limit: the maximum size of a transition system before being merged.
    const int max_states_before_merge;
    /* A soft limit for triggering shrinking even if the hard limits
       max_states and max_states_before_merge are not violated. */
    const int shrink_threshold_before_merge;

    const int bound;

    const Verbosity verbosity;
    long starting_peak_memory;
    // The final merge-and-shrink representation, storing goal distances.
    std::unique_ptr<MergeAndShrinkRepresentation> mas_representation;

    std::pair<bool, bool> shrink_before_merge(
        FactoredTransitionSystem &fts, int index1, int index2);
    void build(const utils::Timer &timer);

    void report_peak_memory_delta(bool final = false) const;
    void dump_options() const;
    void warn_on_unusual_options() const;
protected:
    virtual int compute_heuristic(const GlobalState &global_state) override;
    virtual int compute_heuristic(const GlobalState &global_state, int g, int bound, int u=-1) override;
public:
    explicit MergeAndShrinkHeuristic(const options::Options &opts);
    virtual ~MergeAndShrinkHeuristic() override = default;
    static void add_shrink_limit_options_to_parser(options::OptionParser &parser);
    static void handle_shrink_limit_options_defaults(options::Options &opts);
    
    virtual bool dead_ends_are_reliable() const override {
      // Dead ends for bounded-cost problems depend on g-level,
      // so dead ends are only reliable if the search algorithm/open list
      // doesn't cache dead ends.
      return true;
    }
};
}

#endif