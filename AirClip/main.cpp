/**
 * @file main.cpp
 * @brief Main entry point for the AirClip application.
 *
 * This file contains the main function and the application factory function for the AirClip application.
 * It uses the Wt library to create a web application.
 */

#include <Wt/WApplication.h>
#include "UI.h"

/**
 * @brief Creates and configures the AirClip application.
 *
 * This factory function creates a new instance of Wt::WApplication configured for the AirClip application.
 * It sets the title of the application and adds the main UI to the root container of the application.
 *
 * @param env The environment configuration provided by Wt.
 * @return std::unique_ptr<Wt::WApplication> A unique pointer to the created Wt::WApplication instance.
 */
std::unique_ptr<Wt::WApplication> AirClipApplication(const Wt::WEnvironment& env) {
    auto app = std::make_unique<Wt::WApplication>(env);

    app->setTitle("AirClip");  // Set the title
    // Add your UI to the root container of the application.
    app->root()->addWidget(std::make_unique<UI>());
    return app;
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, &AirClipApplication);
}
