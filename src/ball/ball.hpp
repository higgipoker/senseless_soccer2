#pragma once
#include <gamelib2/game/entity.hpp>
namespace senseless_soccer {

class Ball : public gamelib2::Entity{
public:
  // construct with an entity name
  Ball(std::string in_name);
  virtual ~Ball();

  // main update
  void update(float dt) override;
};

}// namespace
