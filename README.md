# SimEngine
A personal project which seeks to make a simple game engine and some games using OpenGL and other open source, multiplatform tools.

A personal project which seeks to make a simple game engine and some games using OpenGL and other open source, multiplatform tools.

This engine uses an Entity Component System approach. GameObject is the Entity, anything that inherits from IComponent is a Component. GameObjects update their Components, and when a GameObject is deleted all it's Components are too.

Have a look at the GameObjectFactory class to see how to construct 3D and 2D GameObjects.

Currently only OBJ files are supported for 3D models, and these must be run through the ModelConstructor in Offline Tools to be used in the game. Alternatively functions exist to load them in from the raw obj file, but this will be much slower.

There are States and a StateManager for all your state based needs.

The Application class is where everything is run from, so I would start there.
