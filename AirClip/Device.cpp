#include <fstream>
#include "Device.h"
#include "ClipboardEntry.h"

bool Device::connectToServer() {
}

void Device::syncClipboardToDevice(const ClipboardEntry& content) {

}

ClipboardEntry Device::syncClipboardFromDevice() {
}

bool Device::downloadFile(int clipboardEntryId) {
}

bool Device::sendToServer(std::ifstream file) {
}

void Device::addDevice() {

}

void Device::removeDevice() {

}

std::thread Device::createThread() {
}

void Device::performActions() {

}

void Device::notifyUI() {

}

void Device::listenToUI() {

}
