#include "visualizer.h"

int main(int argc, char *argv[])
{
    visualizer::VisualizerApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}