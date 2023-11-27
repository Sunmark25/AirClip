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
    UI(); // Constructor
    ~UI() override = default; // Virtual destructor for proper cleanup

    void setupUI(); // Sets up the user interface

private:
    // Helper functions for actions

//    void clearEntriesContainer();
    void onQuitClicked();       //Slots for handling the Quit button click
    void onbackToTopClicked();
    void createEntry(const std::string &entryText, WContainerWidget *container);
    void toggleExpand(Wt::WText *textWidget, Wt::WContainerWidget *entryContainer,Wt::WPushButton *expandButton);
    void showClearConfirmationDialog();

    // Widgets and model pointers
    Wt::WLineEdit* textBox_;

    Wt::WPushButton* searchButton_;
    Wt::WPushButton* clearButton_;
//    Wt::WPushButton* signOutButton_;        // sign out button
    Wt::WPushButton* quitButton_;
    Wt::WPushButton* backToTopButton_;

    //   Wt::WPushButton* moveToTopButton_;

    Wt::WText* airclipLabel_;       // "Airclip" label

};

#endif // UI_H
