#pragma once
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <map>

struct KeyEvent
{
    int key;
    int scancode;
    int action;
    int mods;
};

struct MouseButtonEvent
{
    int button;
    int action;
    int mods;
    double xPos, yPos;
};

struct MouseMoveEvent
{
    double xPos, yPos;
    double xDelta, yDelta;
};

struct MouseScrollEvent
{
    double xOffset, yOffset;
};

class EventDispatcher
{
public:
    std::vector<std::function<void( const KeyEvent& )>> keyListeners;
    std::vector<std::function<void( const MouseButtonEvent& )>> mouseButtonListeners;
    std::vector<std::function<void( const MouseMoveEvent& )>> mouseMoveListeners;
    std::vector<std::function<void( const MouseScrollEvent& )>> mouseScrollListeners;

    void dispatch( const KeyEvent& event ) {
        for ( const auto& listener : keyListeners ) {
            listener( event );
        }
    }

    void dispatch( const MouseButtonEvent& event ) {
        for ( const auto& listener : mouseButtonListeners ) {
            listener( event );
        }
    }

    void dispatch( const MouseMoveEvent& event ) {
        for ( const auto& listener : mouseMoveListeners ) {
            listener( event );
        }
    }

    void dispatch( const MouseScrollEvent& event ) {
        for ( const auto& listener : mouseScrollListeners ) {
            listener( event );
        }
    }
};

class InputManager
{
public:
    static InputManager& getInstance(); // Singleton access

    void init( GLFWwindow* window );
    void update();

    bool isKeyPressed( int keyCode ) const;
    bool isKeyJustPressed( int keyCode ) const;
    bool isKeyJustReleased( int keyCode ) const;

    bool isMouseButtonPressed( int button ) const;
    bool isMouseButtonJustPressed( int button ) const;
    bool isMouseButtonJustReleased( int button ) const;

    glm::vec2 getMousePosition() const;
    glm::vec2 getMouseDelta() const;
    glm::vec2 getScrollOffset() const;

    bool isMouseDragging() const;

    EventDispatcher& getEventDispatcher() { return dispatcher; }

private:
    static InputManager instance;

    InputManager(); // Private constructor for singleton
    ~InputManager() = default;
    InputManager( const InputManager& ) = delete;
    InputManager& operator=( const InputManager& ) = delete;

    std::map<int, bool> currentKeyStates;
    std::map<int, bool> lastKeyStates;
    std::map<int, bool> currentMouseButtonStates;
    std::map<int, bool> lastMouseButtonStates;

    double currentMouseX, currentMouseY;
    double lastMouseX, lastMouseY;
    double scrollXOffset, scrollYOffset;
    bool mouseDragging;

    EventDispatcher dispatcher;

    static void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
    static void glfwCursorPosCallback( GLFWwindow* window, double xPos, double yPos );
    static void glfwMouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
    static void glfwScrollCallback( GLFWwindow* window, double xOffset, double yOffset );
};