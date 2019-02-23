// Copyright 2019: Julian Domingo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "constants.h"
#include "window.h"

using namespace std;
using namespace Constants::Application;

int main(int argc, char *argv[])
{
    Window *window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Keep showing frames until user force quits window
    while (!window->ShouldClose()) {
        // Obtain + handle user input events
        glfwPollEvents();

        // Swap to the next frame to display
        window->Refresh();
    }

    return 0;
}
