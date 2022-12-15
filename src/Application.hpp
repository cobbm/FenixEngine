#pragma once

#include <memory>
#include "FenixPlatform.hpp"

#include "Renderer.hpp"

#ifdef PSP
#include "../common/psphdr.hpp"
#include "PSPRenderer.hpp"

bool platformShouldQuit();
#else
#error "Cannot build for target other than PSP"
#endif

namespace Fenix
{
    class ApplicationBase
    {
    public:
        ApplicationBase() : m_renderer(std::unique_ptr<Renderer>(new PlatformRenderer())) {}
        virtual ~ApplicationBase() = default;

        virtual void run() = 0;

        virtual bool shouldQuit()
        {
            return platformShouldQuit() || exitRequested;
        }

    protected:
        void quit()
        {
            exitRequested = true;
        }

        std::unique_ptr<Renderer> m_renderer;
        bool exitRequested = false;

    private:
    };

} // namespace Fenix

// #ifdef PSP
// #include "PSPApplication.hpp"
// #else
// #error "Cannot build for target other than PSP"
// #endif
