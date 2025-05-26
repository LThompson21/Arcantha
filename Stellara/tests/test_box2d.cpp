#include <Box2D/Box2D.h>
#include <iostream>

int main()
{
    // Define the gravity vector.
    b2Vec2 gravity( 0.0f, -9.8f );

    // Construct a world object, which will hold and simulate the bodies.
    b2World world( gravity );

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set( 0.0f, -10.0f );

    // Call the body factory which allocates memory for the ground body
    // and adds it to the world.
    b2Body* groundBody = world.CreateBody( &groundBodyDef );

    // Define the ground box shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox( 50.0f, 10.0f );

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture( &groundBox, 0.0f );

    std::cout << "Box2D world and ground body created successfully." << std::endl;

    // No need to step the world for a minimal test, just creation is enough.
    // The world and bodies will be destroyed when 'world' goes out of scope.

    return 0;
}