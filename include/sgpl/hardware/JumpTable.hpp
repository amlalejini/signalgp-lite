#pragma once
#ifndef SGPL_HARDWARE_JUMPTABLE_HPP_INCLUDE
#define SGPL_HARDWARE_JUMPTABLE_HPP_INCLUDE

#include "../../../third-party/conduit/include/uitsl/math/shift_mod.hpp"

#include "../program/Program.hpp"
#include "../utility/EmptyType.hpp"

namespace sgpl {

template<typename Spec, typename Impl>
struct JumpTable {

  Impl match_bin;

  using tag_t = typename Impl::query_t;
  using library_t = typename Spec::library_t;
  using program_t = sgpl::Program<Spec>;

  inline auto MatchRaw( const tag_t & query ) {
    return match_bin.MatchRaw(query);
  }

  inline auto MatchRegulated( const tag_t & query ) {
    return match_bin.MatchRegulated(query);
  }

  inline void SetRegulator( const uid_t uid, const double set ) {
    match_bin.SetRegulator(uid, set);
  }

  inline void AdjRegulator( const uid_t uid, const double set ) {
    match_bin.AdjRegulator(uid, set);
  }

  inline double ViewRegulator(const uid_t uid) const {
    return match_bin.ViewRegulator(uid);
  }

  inline uid_t GetUid(const tag_t tag) const { return match_bin.GetUid(tag); }

  inline uid_t GetUid(const size_t pos) const { return match_bin.GetUid(pos); }

  inline auto GetVal(const uid_t uid) const { return match_bin.GetVal( uid ); }

  inline bool HasVal(const size_t pos) const { return match_bin.HasVal( pos ); }

  inline void Clear() { match_bin.Clear(); }

  inline size_t GetSize() const { return match_bin.GetSize(); }

  void InitializeLocalAnchors(const program_t& prog, const size_t start_pos) {
    Clear();
    if ( prog.empty() ) return;
    const size_t prog_len{ prog.size() };
    for (
      size_t pos = (start_pos + 1) % prog_len;
      pos != start_pos
        && !library_t::IsAnchorGlobalOpCode( prog[pos].op_code )
      ;
      ++pos %= prog_len
    ) {
      const auto& instruction = prog[pos];
      if ( library_t::IsAnchorLocalOpCode( prog[pos].op_code ) ) {
        match_bin.Put( pos, instruction.tag );
      }

    }
  }

  void InitializeGlobalAnchors(
    const sgpl::Program<Spec>& program, const size_t inclusion_mod=1
  ) {
    Clear();
    if ( program.empty() ) return;
    for (size_t pos{}; pos < program.size(); ++pos) {
      const auto& instruction = program[pos];
      if (
        library_t::IsAnchorGlobalOpCode( instruction.op_code )
        && uitsl::shift_mod(instruction.args[0], inclusion_mod) == 0
      ) {
        match_bin.Put( pos, instruction.tag );
      }
    }
  }

};


} // namespace sgpl

#endif // #ifndef SGPL_HARDWARE_JUMPTABLE_HPP_INCLUDE
