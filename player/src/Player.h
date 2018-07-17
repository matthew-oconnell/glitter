#pragma once

#include <Vector2d.h>
#include <Model.h>

namespace Glitter {
  namespace Player {
    class Player {
    public:
        virtual Math::Vec2d acceleration() const = 0;
        virtual float mass() const = 0;

        void setModel(std::shared_ptr<Graphics::Model> m);
        Graphics::Model* getModel();
        void render(Math::Vec2d screen_location);
        void setWorldLocation(Math::Vec2d location);
        Math::Vec2d getWorldLocation() const;
    private:
        Math::Vec2d location;
        std::shared_ptr<Graphics::Model> model = nullptr;
    };

    inline void Player::setWorldLocation(Math::Vec2d loc) {
        location = loc;
    }
    inline Math::Vec2d Player::getWorldLocation() const {
        return location;
    }
    inline void Player::setModel(std::shared_ptr<Graphics::Model> m) {
        model = m;
    }
    inline void Player::render(Math::Vec2d screen_location) {
        if(model != nullptr)
            model->render(screen_location);
    }
    inline Graphics::Model *Player::getModel() {
      if(model != nullptr)
        return model.get();
      return nullptr;
    }
  }
}