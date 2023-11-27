#include <Wt/WApplication.h>
#include "UI.h"

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
