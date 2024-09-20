# First Year CS Project - Matrix solver (Fast Sorting Algorithms)

1. [Overview](#overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Setup and Running](#setup-and-running)
5. [Important Notes](#important-notes)
6. [License](#license)

## Overview
The goal was to implement an efficient matrix solver capable of finding the determinant of a matrix as well as its inverse. I developed a console application that can be run in a console or an integrated development environment such as VS Code. Users can input matrices, solve them, and perform file handling.

## Features
- **Matrix-solving algorithms**: Supports finding the determinant of a matrix in several ways depending on its size..
- **Matrix input**: Users can enter arrays manually, generate random arrays with specified size and range, and load a matrix from a text file.
- **Save results**: Ability to save the calculation results in a text file ..

# Getting Started

## Requirements

- **VS Code**: Follow the instructions on the [VS Code website](https://code.visualstudio.com/download) to install VS Code.

## Setup and Running

### Step 1: Clone the Repository
```sh
git clone https://github.com/piddubnamariia/MatrixSolver.git
cd MatrixSolver
```

### Step 2: Run VS Code:
1. Launch VcXsrv from the Start menu.
2. Configure the display settings:
   1. Multiple windows
   2. Display number: 0
   3. Start no client
   4. Check 'Disable access control'

### Step 3: Configure X Server
Set DISPLAY Environment Variable:
```sh
$env:DISPLAY="host.docker.internal:0.0"
```

### Step 4: Run Docker Engine

### Step 5: Build the Docker Image
```sh
docker build -t first_year_cs_coursework .
```

### Step 6: Run the Docker Container
```sh
docker run -it --rm -e DISPLAY=host.docker.internal:0.0 -v /tmp/.X11-unix:/tmp/.X11-unix first_year_cs_coursework
```
or if you prefer using Docker Compose you can run
```sh
docker-compose up --build
```

## Important Notes
- Ensure VcXsrv is running before starting the Docker container.
- The DISPLAY environment variable and Docker volume for X11 are necessary for GUI display.
- Remember that when you are saving metrics, it will be saved inside docker container.

## License
This project is licensed under MIT License. Check LICENSE for details.
