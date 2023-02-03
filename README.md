# Terrain Generation

This generate terrain using perlin noise from scratch (i.e putpixel). The Graphics algorithms used:
  - BLA line drawing algorithm
  - Surface filling algorithm
  - 2D clipping algorithm
  - Z-buffer algorithm

## Dependencies
  - SFML
  - cmake
  - g++ or any c++ compiler

## Building the project

```bat
git clone git@github.com:adh-aashish/terrain-generation.git
cd terrain-generation
mkdir build
cd build
cmake ../
make
cd project/src
./myproject
```

The wireframe result :<br>

![image](https://user-images.githubusercontent.com/64474508/216601931-509a3c56-8154-42ad-8ee4-617686381f64.png)

Clipping result:<br>

![image](https://user-images.githubusercontent.com/64474508/216602372-62846c17-9239-4ed3-8a78-de3c469037e7.png)
