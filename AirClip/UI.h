#ifndef UI_H
#define UI_H

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTableView.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WLayout.h>
#include <Wt/WAnchor.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLength.h>
#include <Wt/WFlags.h>

#include <memory>
#include "ClipboardHelper.h"


class UI : public Wt::WContainerWidget {
public:
    DatabaseController *dbc; // Store a reference to the database controller singleton

    // Constructor
    UI() {
        dbc = DatabaseController::getInstance("");

        setupUI();
    }

    virtual ~UI() = default; // Virtual destructor for proper cleanup

    void setupUI(); // Sets up the user interface

private:
    std::string userId = "1";

    // Widgets and model pointers
    Wt::WLineEdit* textBox_;
    Wt::WPushButton* copyButton_;
    Wt::WPushButton* clearButton_;
    Wt::WTableView* tableView_; // To display copied contents
    Wt::WText* airclipLabel_;   // "airclip" label
    Wt::WPushButton* deleteButton_;
    Wt::WPushButton* exportButton_;
    Wt::WAnchor* downloadLink_;

    std::shared_ptr<Wt::WStandardItemModel> tableModel_; // Model for the tableView

    // Helper functions for actions
    void updateTable();
    void clearTable();
    void copyContentFromTextBox();
};

#endif // UI_H
