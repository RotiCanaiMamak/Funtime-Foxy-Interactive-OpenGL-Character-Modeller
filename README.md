# Funtime Foxy OpenGL Model

An interactive 3D Funtime Foxy character model created with C++ and legacy OpenGL for the **Graphics Programming** assignment.

The project uses custom geometry, lighting, textures, hierarchical transformations, and keyboard/mouse controls to render and manipulate the model.

## Features

- Textured 3D Funtime Foxy model
- Custom-built head, body, hands, legs, feet, and tail
- OpenGL lighting and depth testing
- BMP texture loading for metal, plastic, eyes, teeth, limbs, and other details
- Mouse-controlled camera rotation
- Orthographic and perspective camera views
- Adjustable light position
- Articulated limb controls
- Animated opening face panels
- Optional outer-shell visibility

## Built With

- C++
- Win32 API
- OpenGL
- GLU
- Microsoft Visual Studio 2022

## Requirements

- Windows
- Visual Studio 2022 with the **Desktop development with C++** workload
- Windows SDK
- OpenGL libraries included with Windows (`OpenGL32.lib` and `GLU32.lib`)

## How to Run

1. Clone or download this repository.
2. Open `Test1.sln` in Visual Studio.
3. Select either the `Debug` or `Release` build configuration.
4. Build and run the project with `Ctrl + F5` or `F5`.

> Keep the BMP texture files in the `Test1` folder. The application loads these files at runtime.

## Controls

| Control | Action |
| --- | --- |
| Left mouse drag | Rotate the camera |
| Arrow keys | Rotate the view |
| `W` / `S` | Move camera vertically |
| `A` / `D` | Move camera horizontally |
| `Q` / `E` | Move camera forward / backward |
| `X` | Toggle orthographic and perspective view |
| `G` / `H` / `J` | Move light position positively on the X, Y, and Z axes |
| `C` / `V` / `B` | Move light position negatively on the X, Y, and Z axes |
| `Y` | Open or close the face panels |
| `Z` | Show or hide the outer head shell |
| `I` / `U` | Adjust eye blink / facial movement |
| `F` / `T` | Adjust face-shell rotation |
| `1`–`8` | Select an articulated joint |
| `P` / `O` | Rotate selected joint on the X axis |
| `K` / `L` | Rotate selected joint on the Y axis |
| `M` / `N` | Rotate selected arm joint on the Z axis |
| `Esc` | Exit the application |

## Project Structure

```text
Test1/
├── Test1.sln               # Visual Studio solution
├── Test1/
│   ├── test1.cpp           # Main application and rendering code
│   ├── Test1.vcxproj       # Visual Studio C++ project file
│   ├── metal.bmp           # Metal texture
│   ├── white.bmp           # White texture
│   ├── teeth.bmp           # Teeth texture
│   ├── plastic.bmp         # Plastic texture
│   ├── eye.bmp             # Eye texture
│   ├── hand.bmp            # Hand texture
│   ├── leg.bmp             # Leg texture
│   ├── foot.bmp            # Foot texture
│   └── blackdc.bmp         # Dark texture
└── .gitignore
```

## Technical Highlights

- Hierarchical modelling is used to position and rotate separate character components.
- The model combines primitive shapes such as spheres, cylinders, cones, cubes, disks, and custom curved meshes.
- Textures are loaded from BMP files using the Win32 API.
- Lighting uses `GL_LIGHT0` with ambient and diffuse material properties.
- The camera supports both orthographic and perspective projections.
