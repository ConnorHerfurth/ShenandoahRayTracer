# Shenandoah Ray Tracer
This project is intended to be a light-weight modular ray tracer.  The
main goal of Shenandoah is to allow for the implementation of new rendering
algorithms and techniques with the minimal amount of code change by
abstracting as many concepts as possible, while still maintaining certain
low-level concepts to increase efficiency.  It is designed to be used for
both CPU and GPU rendering, as well as allowing importing and loading from
popular tools.

The project is currently very new, and so these 'mission statements' have
yet to be implemented.

## Architecture
Shenandoah is designed around the concept of 'handlers', each of which
control a specific part of the code and are defined as abstract classes.
The implementation of each handler is dependent on the use case and 
preference of the user; however, multiple implementations are created
in this code to allow for ease of use and facilitate open source
collaboration.

Although not all handlers have been defined, an example handler might be
the RenderHandler, which handles the rendering process.  The RenderHandler
interface could be implemented multiple times, each for specific ray
tracing algorithms.

## Installation Instructions
In order to install and run the program yourself, please clone the repository
and load the solution file in Visual Studio.  The project was created
in Visual Studio 2019, and so may not be compatible with later versions.

Compiling is as simple as using the built-in Visual Studio C++ compiler,
which is what is used for all builds during testing.

## How To Use
Currently, the program has no way of loading scenes or rendering, as those
features have yet to be implemented (this is very early in development).
However, code will not be pushed to the master branch unless it is able
to compile, so pulling from master and running will provide you a glimpse
into how the code is currently operating.

## Collaboration
Since the project is in such early stages, code is currently not accepted
from others (in addition, this project was to practice my skills, so
having others work on it defeats the point).  However, architectural ideas
are more than welcome.  If you have ideas for how the program should be
designed, please let me know through the GitHub issues page.

## License
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.