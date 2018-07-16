#pragma once

namespace Glitter {
  namespace Player {
    class Input {
    public:
        enum KEYS {
            W, A, S, D, SPACE
        };
        virtual bool pressed(KEYS k) const = 0;
    };
  }
}