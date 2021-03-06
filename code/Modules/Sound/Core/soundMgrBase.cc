//------------------------------------------------------------------------------
//  soundMgrBase.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "soundMgrBase.h"
#include "Sound/Core/soundEffectPool.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
soundMgrBase::soundMgrBase() :
valid(false),
effectPool(nullptr) {
    // empty
}

//------------------------------------------------------------------------------
soundMgrBase::~soundMgrBase() {
    o_assert_dbg(!this->valid);
    o_assert_dbg(nullptr == this->effectPool);
}

//------------------------------------------------------------------------------
void
soundMgrBase::setup(const SoundSetup& setup, soundEffectPool* sndEffectPool) {
    o_assert_dbg(!this->valid);
    o_assert_dbg(nullptr == this->effectPool);
    o_assert_dbg(nullptr != sndEffectPool);

    this->valid = true;
    this->effectPool = sndEffectPool;
}

//------------------------------------------------------------------------------
void
soundMgrBase::discard() {
    o_assert_dbg(this->valid);
    this->valid = false;
    this->effectPool = nullptr;
}

//------------------------------------------------------------------------------
bool
soundMgrBase::isValid() const {
    return this->valid;
}

//------------------------------------------------------------------------------
void
soundMgrBase::play(soundEffect* /*effect*/, int32 /*loopCount*/, int32 freqShift) {
    // empty
}

} // namespace _priv
} // namespace Oryol