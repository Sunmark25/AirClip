#include "UI.h"

void UI::setupUI() {
    auto vbox = setLayout(std::make_unique<Wt::WVBoxLayout>());
    Wt::WApplication::instance()->useStyleSheet("styles.css");

    // "AirClip" title
    airclipLabel_ = vbox->addWidget(std::make_unique<Wt::WText>("AirClip"));
    airclipLabel_->addStyleClass("title");

    // Text Box
    textBox_ = vbox->addWidget(std::make_unique<Wt::WLineEdit>());
    textBox_->setPlaceholderText("Input here...");
    textBox_->addStyleClass("largeTextBox");

    // Buttons container
    auto buttonsContainer = std::make_unique<Wt::WContainerWidget>();
    auto hbox = buttonsContainer->setLayout(std::make_unique<Wt::WHBoxLayout>());

    // Copy button
    copyButton_ = hbox->addWidget(std::make_unique<Wt::WPushButton>("Copy"));
    copyButton_->addStyleClass("button");
    // Enable the 'Enter' key to trigger the copy action
    textBox_->enterPressed().connect(this, &UI::copyContentFromTextBox);

    // Clear button
    clearButton_ = hbox->addWidget(std::make_unique<Wt::WPushButton>("Clear"));
    clearButton_->addStyleClass("button");

    // Add buttons container to the main vbox
    vbox->addWidget(std::move(buttonsContainer));

    // Dropdown button for history
    auto dropdownButton = vbox->addWidget(std::make_unique<Wt::WPushButton>("History"));
    dropdownButton->addStyleClass("dropdown-button");

    // Container for the table view, initially hidden
    auto tableContainer = vbox->addWidget(std::make_unique<Wt::WContainerWidget>());
    tableContainer->hide();

    // Table for displaying copied content
    tableModel_ = std::make_shared<Wt::WStandardItemModel>(0, 1);
    tableView_ = tableContainer->addWidget(std::make_unique<Wt::WTableView>());
    tableView_->setModel(tableModel_);
    tableView_->addStyleClass("table-view");

    // Connect the dropdown button to show/hide the table container
    dropdownButton->clicked().connect([=] {
        if (tableContainer->isHidden()) {
            tableContainer->show();
            dropdownButton->addStyleClass("dropdown-button-active");  // Highlight the button when shown
        }
        else {
            tableContainer->hide();
            dropdownButton->removeStyleClass("dropdown-button-active");  // Remove highlight when hidden
        }
    });

    // Define the query to get all the clipboard entries for a user using their userID
    std::string query = "SELECT * FROM CLIPBOARDENTRY WHERE userID ='" + userId + "';";

    // Look for the fullName matching the userID
    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    for (int i = 0; i < tableData.size(); i++) {
        updateTable();
    }

    // Connect signals to slots
    copyButton_->clicked().connect(this, &UI::copyContentFromTextBox);
    clearButton_->clicked().connect(this, &UI::clearTable);
}

void UI::updateTable() {
    auto row = tableModel_->rowCount();
    tableModel_->insertRows(row, 1);

    auto clipboardEntry = ClipboardHelper::getClipboardEntry(userId, row);

    auto item = std::make_unique<Wt::WStandardItem>(Wt::WString::fromUTF8(clipboardEntry->getContent()));
    tableModel_->setItem(row, 0, std::move(item));
}

void UI::clearTable() {
    tableModel_->removeRows(0, tableModel_->rowCount());

    std::string deleteSQL = ClipboardHelper::generateClipboardEntryDeleteSQL(userId);

    dbc->deleteSQL(deleteSQL);
}

void UI::copyContentFromTextBox() {
    if (!textBox_->text().empty()) {
        std::string content = textBox_->text().toUTF8();

        std::string insertSQL = ClipboardHelper::generateClipboardEntryInsertSQL(content, "", Type::Text, userId);
        dbc->insertSQL(insertSQL);

        textBox_->setText("");  // Clear the textBox after copying

        updateTable();
    }
}
