#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include <memory>
#include <scmdr/canvas.hpp>
#include <scmdr/texture.hpp>

using namespace std;

namespace components {
struct position {
  float x, y;
};
struct size {
  float w, h;
};
struct solid {};
struct velocity {
  float vx = 0, vy = 0;
};
struct acceleration {
  float ax = 0, ay = 0;
};
struct texture {
  unique_ptr<Texture> ptr;
};
} // namespace components

namespace systems {
void rendering(entt::registry &registry, Canvas &canvas) {
  auto view =
      registry.view<const components::position, const components::texture>();
  for (auto [entity, position, texture] : view.each()) {
    canvas.draw(*texture.ptr, {(int)position.x, (int)position.y});
  }
}
void movement(entt::registry &registry, double dt) {
  auto view = registry.view<components::position, components::velocity>();
  for (auto [entity, position, velocity] : view.each()) {
    auto acceleration =
        registry.try_get<const components::acceleration>(entity);
    if (acceleration) {
      velocity.vx += .5 * acceleration->ax * dt;
      velocity.vy += .5 * acceleration->ay * dt;
      position.x += velocity.vx * dt;
      position.y += velocity.vy * dt;
      velocity.vx += .5 * acceleration->ax * dt;
      velocity.vy += .5 * acceleration->ay * dt;
    } else {
      position.x += velocity.vx * dt;
      position.y += velocity.vy * dt;
    }
  }
}
} // namespace systems

entt::entity create_player(entt::registry &registry) {
  auto player = registry.create();
  registry.emplace<components::position>(player, 5., 5.);
  registry.emplace<components::velocity>(player);
  registry.emplace<components::acceleration>(player, 0., 100.);
  registry.emplace<components::texture>(
      player,
      make_unique<Texture>(Texture::solidColor({255, 0, 0, 255}, {2, 6})));
  registry.emplace<components::solid>(player);
  return player;
}

int main() {
  entt::registry registry;
  Canvas canvas;
  auto player = create_player(registry);
  while (true) {
    canvas.fill({255, 255, 255, 255});
    systems::movement(registry, canvas.deltaTime.get());
    systems::rendering(registry, canvas);
    canvas.refresh_simple();
  }
}