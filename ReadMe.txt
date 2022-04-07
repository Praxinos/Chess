This project is a UE4.27.2 project
To make it work properly, you just have to do two things in the UE editor when launching this project:

1) Select ChessGameMode as default game mode in Blueprints/ProjectSettings
2) Create a collisions preset in ProjectSettings/Collisions, named Chess, with all components set to blocked, except the static one, which should be set to overlap