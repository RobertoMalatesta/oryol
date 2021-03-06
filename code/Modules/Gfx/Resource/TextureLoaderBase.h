#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::TextureLoaderBase
    @ingroup Gfx
    @brief base class for Gfx texture loaders
*/
#include "Resource/Core/ResourceLoader.h"
#include "Gfx/Setup/TextureSetup.h"

namespace Oryol {

class TextureLoaderBase : public ResourceLoader {
    OryolClassDecl(TextureLoaderBase);
public:
    /// constructor
    TextureLoaderBase(const TextureSetup& setup, int32 ioLane);
    /// return resource locator
    virtual const class Locator& Locator() const;

protected:
    TextureSetup setup;
    int32 ioLane;
};

} // namespace Oryol

