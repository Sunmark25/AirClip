/**
 * @class UI
 * @brief This class handles the user interface for the web application using Wt.
 *
 * The UI class is responsible for setting up and managing the graphical components
 * of the web application. It includes methods for creating the layout, handling user
 * interactions, and managing dynamic content. This class uses Wt's widgets and layouts
 * to construct a user-friendly interface.
 */

#include "UI.h"

UI::UI(const std::string& deviceID, const std::string& userID, WContainerWidget *root){
    this->deviceID = deviceID;
    this->userID = userID;
    this->root_ = root;
    setupUI();
}

/**
    * @brief Sets up the user interface of the application.
    *
    * This method constructs the main layout and widgets of the application. It includes
    * the creation and configuration of buttons, labels, input fields, and containers. It
    * also binds event handlers to the widgets for user interaction.
    */
void UI::setupUI() {
    Wt::WApplication::instance()->useStyleSheet("styles.css");



    auto vbox = std::make_unique<Wt::WVBoxLayout>();
    vbox->setContentsMargins(20, 20, 20, 20);




//    auto vbox = new Wt::WVBoxLayout();
//    vbox->setContentsMargins(20, 20, 20, 20);
//
//    Wt::WHBoxLayout* gitLayout= new Wt::WHBoxLayout();
//
//    root->setLayout(gitLayout);

    // Stores the controls (buttons, title and search bar)
    auto controlsVBox = std::make_unique<Wt::WVBoxLayout>();

    // Top horizontal box for Sign Out, Quit and clear history buttons
    auto topHBox = std::make_unique<Wt::WHBoxLayout>();
    topHBox->addStretch(1); // Add stretch to push buttons to the right

    // Clear button
    auto clearButton = std::make_unique<Wt::WPushButton>("Clear history");
    clearButton_ = topHBox->addWidget(std::move(clearButton),0,Wt::AlignmentFlag::Right);
    clearButton_->addStyleClass("button");

    // Sign Out button
//    auto signOutButton = std::make_unique<Wt::WPushButton>("Sign Out");
//    signOutButton->addStyleClass("button");
//    topHBox->addWidget(std::move(signOutButton), 0, Wt::AlignmentFlag::Right);

    // Quit button
    auto quitButton = std::make_unique<Wt::WPushButton>( "Quit");
    quitButton_ = topHBox->addWidget(std::move(quitButton),0,Wt::AlignmentFlag::Right);
    quitButton_->addStyleClass("button");

    // Add topHBox to the controls box
    controlsVBox->addLayout(std::move(topHBox));

    // "AirClip" title
    airclipLabel_ = controlsVBox->addWidget(std::make_unique<Wt::WText>("AirClip"));
    airclipLabel_->addStyleClass("title");

    // Horizontal box for search functionality
    auto searchHBox = std::make_unique<Wt::WHBoxLayout>();

    // Text Box
    textBox_ = searchHBox->addWidget(std::make_unique<Wt::WLineEdit>());
    textBox_->setPlaceholderText("Search history ");
    textBox_->addStyleClass("rounded-text-field");

    // Search button
    searchButton_= searchHBox->addWidget(std::make_unique<Wt::WPushButton>("🔍"));
    searchButton_->addStyleClass("button");
    searchButton_->setWidth("56.5px");

    // Add buttons container to the controls box
    controlsVBox->addLayout(std::move(searchHBox));

    // Dropdown button for history
    auto dropdownButton_ = controlsVBox->addWidget(std::make_unique<Wt::WPushButton>("History"));
    dropdownButton_->addStyleClass("dropdown-button");
    dropdownButton_->addStyleClass("dropdown-button-active");  // Style as active from the start

    // Create a wrapper to allow styling of the container
    auto controlsVBoxWrapper = std::make_unique<Wt::WContainerWidget>();
    controlsVBoxWrapper->setLayout(std::move(controlsVBox));
    controlsVBoxWrapper->setStyleClass("controls-container");

    // Add controls box container to the main vbox
    vbox->addWidget(std::move(controlsVBoxWrapper), 0);


    // Main container for entries with scrollbar
    auto entriesContainer = vbox->addWidget(std::make_unique<Wt::WContainerWidget>(), 1);
    entriesContainer->setOverflow(Wt::Overflow::Auto, Wt::Orientation::Vertical);
    entriesContainer->setMargin(Wt::WLength(3), Wt::Side::Top);
    entriesContainer->setMargin(Wt::WLength(10), Wt::Side::Right);
    entriesContainer->setMargin(Wt::WLength(10), Wt::Side::Left);
    entriesContainer->setMaximumSize(Wt::WLength::Auto, Wt::WLength(1000, Wt::LengthUnit::Pixel)); // Dynamic height with max limit
    entriesContainer->addStyleClass("entries-container");

    // Setup text box enter key action
    textBox_->enterPressed().connect([=, this] {
        entriesContainer->clear();

        std::vector serachClipboard = ClipboardHelper::searchClipboardEntry(textBox_->text().toUTF8());
        for (int i = 0; i < serachClipboard.size(); ++i) {
            createEntry(serachClipboard[i]->getContent(), entriesContainer);
        }
        textBox_->setText("");
    });

    std::vector clipboardEntries = ClipboardHelper::getClipboardEntries(userID);
    for (int i = 0; i < clipboardEntries.size(); ++i) {
        createEntry(clipboardEntries[i]->getContent(), entriesContainer);
    }


    // Setup Search button action
    searchButton_->clicked().connect([=, this] {
        entriesContainer->clear();

        std::vector serachClipboard = ClipboardHelper::searchClipboardEntry(textBox_->text().toUTF8());
        for (int i = 0; i < serachClipboard.size(); ++i) {
            createEntry(serachClipboard[i]->getContent(), entriesContainer);
        }
        textBox_->setText("");
    });

    // Connect the dropdown button to show/hide the content container
    dropdownButton_->clicked().connect([=] {
        if (entriesContainer->isHidden()) {
            entriesContainer->show();
            dropdownButton_->addStyleClass("dropdown-button-active");  // Highlight the button when shown
        }
        else {
            entriesContainer->hide();
            dropdownButton_->removeStyleClass("dropdown-button-active");  // Remove highlight when hidden
        }
    });

    // Back to Top button
    backToTopButton_ = entriesContainer->addWidget(std::make_unique<Wt::WPushButton>("Back to Top"));
    backToTopButton_->addStyleClass("back-to-top-button");

    entriesContainer->setId("entriesContainer");  // Assigning an ID to the main container

    // Connect signals to slots
    clearButton_->clicked().connect(this, &UI::showClearConfirmationDialog);
    quitButton_->clicked().connect(this, &UI::onQuitClicked);
    backToTopButton_->clicked().connect(this, &UI::onbackToTopClicked);

    root_->setLayout(std::move(vbox));
}

/**
     * @brief Creates a new entry in the history container.
     *
     * @param entryText The text of the new entry to be added.
     * @param entriesContainer Pointer to the container widget where the entry will be added.
     *
     * This method adds a new entry to the history section of the application. Each entry
     * includes the provided text and additional UI elements like copy and pin buttons.
     */
void UI::createEntry(const std::string& entryText, Wt::WContainerWidget* entriesContainer) {
    if (!entryText.empty()) {
        auto entryContainer = std::make_unique<Wt::WContainerWidget>();
        entryContainer->addStyleClass("entry-container");

        auto vbox = std::make_unique<Wt::WVBoxLayout>();
        auto textWidget = std::make_unique<Wt::WText>(entryText);
        textWidget->setInline(false); // Ensure the text is a block element

        // Create a unique identifier for each entry
        std::string WidgetID = "entry_" + std::to_string(rand());
        textWidget->setId(WidgetID);

        auto bottomHbox = std::make_unique<Wt::WHBoxLayout>();
        bottomHbox->addStretch(1); // Add stretch to push buttons to the right

        //copy button
        auto copyButton = std::make_unique<Wt::WPushButton>("Copy");
        copyButton->addStyleClass("copy-button");
        // copy button event handling
        copyButton->clicked().connect([=] {
            std::string jsCopyText =
                    "const textArea = document.createElement('textarea');"
                    "textArea.value = document.getElementById('" + WidgetID + "').innerText;"
                                                                              "document.body.appendChild(textArea);"
                                                                              "textArea.focus();"
                                                                              "textArea.select();"
                                                                              "try {"
                                                                              "    const successful = document.execCommand('copy');"
                                                                              "    const msg = successful ? 'successful' : 'unsuccessful';"
                                                                              "    console.log('Copy command was ' + msg);"
                                                                              "} catch (err) {"
                                                                              "    console.error('Fallback: Oops, unable to copy', err);"
                                                                              "}"
                                                                              "document.body.removeChild(textArea);";

            Wt::WApplication::instance()->doJavaScript(jsCopyText);
        });

        bottomHbox->addWidget(std::move(copyButton), 0, Wt::AlignmentFlag::Right);

        //pin button
//        auto pinButton = std::make_unique<Wt::WPushButton>("📌");
//        pinButton->addStyleClass("pin-button");
//        bottomHbox->addWidget(std::move(pinButton), 0, Wt::AlignmentFlag::Right);

        // add the buttons to entry box
        vbox->addLayout(std::move(bottomHbox));


        if (entryText.size() > 586) {
            textWidget->addStyleClass("text-collapsed"); // Apply collapsed text style
            auto expandButton = std::make_unique<Wt::WPushButton>("Show all");
            expandButton->addStyleClass("expand-button");

            // Connect the expand button to toggle function
            expandButton->clicked().connect(
                    [this, textWidget = textWidget.get(), entryContainer = entryContainer.get(), expandButton = expandButton.get()] {
                        toggleExpand(textWidget, entryContainer, expandButton);
                    });

            vbox->addWidget(std::move(expandButton));
        }

        vbox->insertWidget(0, std::move(textWidget)); // Insert text at the beginning of the vbox
        entryContainer->setLayout(std::move(vbox));
        entriesContainer->addWidget(std::move(entryContainer));

        textBox_->setText("");      // clear the text field
    }
}

/**
     * @brief Shows a confirmation dialog for clearing history.
     *
     * This method displays a JavaScript-based confirmation dialog to the user. If the user
     * confirms, it will emit a signal to clear the history. This is a placeholder for
     * future implementation of actual history clearing functionality.
     */
void UI::showClearConfirmationDialog() {
    std::string jsCode =
            "if (confirm('Are you sure you want to clear the history? This action cannot be undone.')) {"
            "    Wt.emit('" + this->id() + "', 'clearConfirmed');"
                                           "} else {"
                                           "    console.log('Clear cancelled');"
                                           "}";


    //std::string deleteAllClipboardEntry = "DELETE * FROM ClipboardEntry JOIN Device ON ClipboardEntry.deviceID = Device.deviceID WHERE Device.userID = '" + userID + "';";
    std::string deleteAllClipboardEntry = "DELETE FROM ClipboardEntry WHERE deviceID IN ( SELECT deviceID FROM Device WHERE userID = '" +  userID + "');";
    DatabaseController *dbc = DatabaseController::getInstance();
    dbc->sqlOperation(deleteAllClipboardEntry);
    Wt::WApplication::instance()->doJavaScript(jsCode);
    setupUI();
}

/**
 * @brief Handles the 'Quit' button click event.
 *
 * This method is bound to the 'Quit' button. When invoked, it executes JavaScript
 * to close the browser window, effectively quitting the application.
 */
void UI::onQuitClicked() {
    Wt::WApplication::instance()->doJavaScript("window.close();");     // Close the browser window
}

/**
     * @brief Scrolls the entries container and the page to the top.
     *
     * This method is connected to the 'Back to Top' button. It uses JavaScript to scroll
     * both the entries container and the entire web page back to the top, providing a
     * quick way for users to navigate back to the start of the content.
     */
void UI::onbackToTopClicked() {
    // JavaScript to scroll the entriesContainer to the top
    std::string scriptEntriesContainer = "document.getElementById('entriesContainer').scrollTop = 0;";
    Wt::WApplication::instance()->doJavaScript(scriptEntriesContainer);

    // JavaScript to scroll the entire page to the top
    std::string scriptPage = "window.scrollTo(0, 0);";
    Wt::WApplication::instance()->doJavaScript(scriptPage);
}

/**
     * @brief Toggles the expansion of a text entry.
     *
     * @param textWidget Pointer to the text widget that needs to be expanded or collapsed.
     * @param entryContainer Pointer to the container of the entry.
     * @param expandButton Pointer to the button controlling the expand/collapse action.
     *
     * This method is used to expand or collapse a text entry in the history section.
     * It changes the style class of the text widget and the text of the expand/collapse
     * button to reflect the current state (expanded or collapsed).
     */
void UI::toggleExpand(Wt::WText *textWidget, Wt::WContainerWidget *entryContainer,Wt::WPushButton *expandButton) {
    if (textWidget->hasStyleClass("text-collapsed")) {
        textWidget->removeStyleClass("text-collapsed");
        textWidget->addStyleClass("text-expanded");
        entryContainer->addStyleClass("entry-container-expanded");
        expandButton->setText("Show less");
    } else {
        textWidget->removeStyleClass("text-expanded");
        textWidget->addStyleClass("text-collapsed");
        expandButton->setText("Show all");
    }
}
