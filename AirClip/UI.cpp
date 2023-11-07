#include "UI.h"

UI::UI() {
    setupUI();
}

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

    // Title for the table of copied content
    auto tableTitle = vbox->addWidget(std::make_unique<Wt::WText>("History"));
    tableTitle->addStyleClass("title2");

    // Table for displaying copied content
    tableModel_ = std::make_shared<Wt::WStandardItemModel>(0, 1);
    tableView_ = vbox->addWidget(std::make_unique<Wt::WTableView>());
    tableView_->setModel(tableModel_);
    tableView_->addStyleClass("table-view");




    // Connect signals to slots
    copyButton_->clicked().connect(this, &UI::copyContentFromTextBox);
    clearButton_->clicked().connect(this, &UI::clearTable);
}

void UI::copyContentToTable(const std::string& content) {
    auto row = tableModel_->rowCount();
    tableModel_->insertRows(row, 1);
    auto item = std::make_unique<Wt::WStandardItem>(Wt::WString::fromUTF8(content));
    tableModel_->setItem(row, 0, std::move(item));
}

void UI::clearTable() {
    tableModel_->removeRows(0, tableModel_->rowCount());
}

void UI::copyContentFromTextBox() {
    if (!textBox_->text().empty()) {
        copyContentToTable(textBox_->text().toUTF8());
        textBox_->setText("");  // Clear the textBox after copying
    }
}
