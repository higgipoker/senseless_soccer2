#pragma once
#include "locomotion.hpp"

namespace senseless_soccer {
class Player;
namespace locomotion {

// continue in the specified direction until stopped
class Head : public Locomotion {
 public:
  Head(Player &player);
  virtual ~Head() override = default;
  virtual void start() override;
  virtual void update(float dt) override;
  virtual void stop() override;
  virtual bool finished() override;
  std::string diagnosticParamaters() override;

  void init(const Vector3 &t);

 private:
  Vector3 direction;
};
}  // namespace locomotion
}  // namespace senseless_soccer
