Using external libraries:
http://www.assimp.org/
https://glm.g-truc.net/0.9.9/index.html

Need to build the project in the root directory
In QT go to projects tab(left side of screen) 
and change debug build directory. Mine is for example
C:\......\3D-programming\build-3D-programming-MSVC2017_64bit-Debug

Deploy project for windows:
1. controlpanel -> system -> advanced system settings -> enviroment variables
2. add "<qt-dir>/<qt-version>/bin" folder to the path
3. open CMD and run "windeployqt.exe <path-to-app-binary>" from the bin folder