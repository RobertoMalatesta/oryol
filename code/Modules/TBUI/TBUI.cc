//-----------------------------------------------------------------------------
//  TBUI.cc
//-----------------------------------------------------------------------------
#include "Pre.h"
#include "TBUI.h"
#include "Core/Assertion.h"
#include "Core/Memory/Memory.h"

namespace Oryol {

TBUI::_state* TBUI::state = nullptr;

//-----------------------------------------------------------------------------
void
TBUI::Setup(const TBUISetup& setup) {
    o_assert_dbg(!IsValid());
    state = Memory::New<_state>();
    state->setup = setup;
    state->resourceContainer.setup(setup);
}

//-----------------------------------------------------------------------------
void
TBUI::Discard() {
    o_assert_dbg(IsValid());
    state->resourceContainer.discard();
    state->mgr.Discard();
    Memory::Delete(state);
    state = nullptr;
}

//-----------------------------------------------------------------------------
TBUIResourceContainer&
TBUI::Resource() {
    o_assert_dbg(IsValid());
    return state->resourceContainer;
}

//-----------------------------------------------------------------------------
void
TBUI::InitTurboBadger() {
    o_assert_dbg(IsValid());
    state->mgr.Setup(state->setup);
}

} // namespace Oryol