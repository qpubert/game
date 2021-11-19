#ifndef APPLICATION_STATE_HPP
#define APPLICATION_STATE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

namespace sf {
struct Event;
}

class Application;

class ApplicationState {
  friend class ApplicationStateStack;

 public:
  ApplicationState(Application& application);
  virtual ~ApplicationState() noexcept = default;

  Application& getApplication() { return application_; }
  Application const& getApplication() const { return application_; }

  void handleEvents(std::vector<sf::Event> const& events);
  void update(sf::Time const elapsedTime);
  void render(sf::RenderTarget& target,
              sf::RenderStates states = sf::RenderStates::Default) const;

 protected:
  bool renderUnderlyingState_;

  virtual void doHandleEvents(std::vector<sf::Event> const& events) = 0;
  virtual void doUpdate(sf::Time const elapsedTime) = 0;
  virtual void doRender(sf::RenderTarget& target,
                        sf::RenderStates states) const = 0;

 private:
  Application& application_;
};

#endif  // APPLICATION_STATE_HPP