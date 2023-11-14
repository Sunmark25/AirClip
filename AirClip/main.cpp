#include <Wt/WApplication.h>
#include "UI.h"
#include "DatabaseController.h"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    auto app = std::make_unique<Wt::WApplication>(env);

    app->setTitle("AirClip");  // Set the title
    // Add your UI to the root container of the application.
    app->root()->addWidget(std::make_unique<UI>());

    app->useStyleSheet("styles.css"); // This assumes "styles.css" is directly in the document_root.

    return app;
}

int main(int argc, char **argv) {
    DatabaseController::getInstance("../../AirClip.sqlite");
    return Wt::WRun(argc, argv, &createApplication);
}