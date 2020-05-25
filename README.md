<p align="center">
  <h1 align="center">CIEO</h1>
  <p align="center">
    <a href="https://github.com/LuxAter/Cieo/graphs/contributors"><img src="https://img.shields.io/github/contributors/LuxAter/Cieo.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/network/members"><img src="https://img.shields.io/github/forks/LuxAter/Cieo.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/stargazers"><img src="https://img.shields.io/github/stars/LuxAter/Cieo.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/issues"><img src="https://img.shields.io/github/issues/LuxAter/Cieo.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/blob/master/LICENSE.txt"><img src="https://img.shields.io/github/license/LuxAter/Cieo.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/releases"><img src="https://img.shields.io/github/tag/LuxAter/Cieo.svg?include_prereleases&sort=semver&style=flat-square"></a>
    <a href="https://github.com/LuxAter/Cieo/actions?query=workflows%3ADevelopment"><img src="https://img.shields.io/github/workflow/status/LuxAter/Cieo/Development.svg?include_prereleases&sort=semver&style=flat-square"></a>
    <br/>
    A C++17 Embeddable Physics simulation
    <br/>
    <a href="https://luxater.github.io/Cieo"><strong>Documentation</strong></a>
    <br/>
    <br/>
    <a href="https://github.com/LuxAter/Cieo/releases">Downloads</a>
    ·
    <a href="https://github.com/LuxAter/Cieo/issues/new?template=bug_report.md">Report Bug</a>
    ·
    <a href="https://github.com/LuxAter/Specula/issues/new?template=feature_request.md">Request Feature</a>
  </p>
</p>

## About the Project

Cieo is intended as a physics simulation, that can easily be embedded into other
applications. Thus allowing realistic physics simulations in all manor of
projects. Cieo is not intended to be a real time physics simulation, but instead
as an off-line extremely accurate simulation.

A large amount of focus is placed on the API interface, so that the library is
as easy as possible to use in other programs. And if possible, a Python API is
planed, so that the simulation can be used in python scripts.

Although Cieo is not intended as a method for rendering images, there is an
optional component for rendering out the simulation. This is primarily used for
debugging purposes. The imaging system, should be replaced by a more capable
photo realistic renderer, when possible, but for simple simulations, where the
visual quality is not of importance, then the bundled renderer should be
sufficient.


Cieo is also written with a large focus on the readability of the code, and
the documentation that is generated in addition to the code. One should be able
to read through the documentation of the library, and leave with a functional
knowledge of physics simulation that is being used.

### Built With

Cieo depends on a number of frameworks which are included in the library.
Specifically

* [Catch2](https://github.com/catchorg/Catch2)
* [fmt](https://github.com/fmtlib/fmt)
* [spdlog](https://github.com/gabime/spdlog)
* [stb](https://github.com/nothings/stb)

## Getting Started

These instructions will get you a copy of the library up and running on your
local machine for development and testing purposes.

### Prerequisites

The only prerequisites are [CMake](https://cmake.org/), and a C++ compiler
capable of C++17 (recommended to use [Clang](https://clang.llvm.org/)). Please
follow your system instructions for installing these.

### Installation

#### Prebuilt (recommended)

To get the library and the executable, goto the
[releases](https://github.com/LuxAter/Cieo/releases) and download the file
from the latest release for your system. Currently Specula is compiled for
*Linux*, *Windows*, and *MacOs*. Simply extract the zip and execute the
``install`` script. This will copy the binaries and libraries to the
appropriate directories on your system.

#### Build from source

First get the source either from the
[releases](https://github.com/LuxAter/Cieo/releases) page, or the preferred
method is to clone the repository.

```fish
git clone https://github.com/LuxAter/Cieo.git
```

Now create a build directory, and configure the code using CMake.

```fish
mkdir cmake-build-release && cd cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Finally compile and install the code using GNUMake (or an alternative build
tool).

```fish
make install
```

## Usage

The repository contains with a number of examples. Using these examples, one can
explore the capabilities of the simulation. Each example uses the built-in
renderer, to produce a sequence of images. Simply navigate to the examples
directory, and execute the available programs.

There is also an interactive interface that is shipped with the library. In the
interactive interface, initial conditions can be set, and then the simulation
can run based off of those initial conditions. The running simulation can be
previewed through a display window, so that users can stop and reset the
simulation at any point. Do note that the interactive interface will not be a
real time simulation, as the steps to calculate the simulation can take a while.

## Contributing

Contributions are what make the open source community such an amazing place to
be, learn, inspire, and create. Any contributions you make are **greatly
appreciated**.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/<my-feature>`)
3. Commit your changes (`git commit -m '<my-commit-message>'`)
4. Push to the branch (`git push origin feature/<my-feature>`)
5. Open a pull request

### Authors

For those with commit privileges to the repository we recommend the use of
[Gitflow AVH](https://github.com/petervanderdoes/gitflow-avh). Use this to
create a new work branch, and merge back to the development branch. This tool
keeps things organized, and implements a number of customized hooks, that update
versions, and prevent unwanted commits.

## License

Distributed under the MIT license. See
[`LICENSE`](https://github.com/LuxAter/Cieo/blob/development/LICENSE)
for more information.
