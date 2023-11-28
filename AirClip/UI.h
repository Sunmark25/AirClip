#ifndef UI_H
#define UI_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTableView.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WText.h>
#include <Wt/WLayout.h>
#include <Wt/WAnchor.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WLength.h>
#include <Wt/WFlags.h>
#include <Wt/WDialog.h>
#include <Wt/WLabel.h>

#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <memory>

#include <chrono>
#include <sstream>

struct Entry {
    std::string content;
    std::string uniqueId; // Unique identifier for each entry
};

class UI : public Wt::WContainerWidget {
public:
    /**
     * @brief Constructor for the UI class.
     *
     * Initializes a new instance of the UI class, setting up the basic components of the user interface.
     */
    UI();

    /**
     * @brief Virtual destructor for proper cleanup.
     *
     * Ensures that resources allocated by the UI class are properly released when the object is destroyed.
     */
    ~UI() override = default;

    /**
     * @brief Sets up the user interface components.
     *
     * This method initializes and arranges various UI components such as buttons, text boxes, and labels.
     */
    void setupUI();

private:
    // Private Helper Methods
    void onQuitClicked(); ///< Handles the Quit button click event.
    void onbackToTopClicked(); ///< Handles the Back to Top button click event.
    void createEntry(const std::string &entryText, WContainerWidget *container); ///< Creates a new entry in the UI.
    void toggleExpand(Wt::WText *textWidget, Wt::WContainerWidget *entryContainer, Wt::WPushButton *expandButton); ///< Toggles the expansion state of an entry.
    void showClearConfirmationDialog(); ///< Displays a confirmation dialog for clearing entries.
//    void clearEntriesContainer();

    // Widgets and Model Pointers
    Wt::WLineEdit* textBox_; ///< Text box for input.

    Wt::WPushButton* searchButton_; ///< Button for initiating a search.
    Wt::WPushButton* clearButton_; ///< Button for clearing the UI.
    Wt::WPushButton* quitButton_; ///< Button for quitting the application.
    Wt::WPushButton* backToTopButton_; ///< Button for returning to the top of the UI.
//    Wt::WPushButton* signOutButton_;        // sign out button
//   Wt::WPushButton* moveToTopButton_;

    Wt::WText* airclipLabel_; ///< Label displaying "Airclip".
};


#endif // UI_H
