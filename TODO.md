# To Do

## Required

- ~~Push received content to clipboard~~ ~~-- Just need to polish up~~
- ~~Connect server API methods to database (right now it just outputs or gives set values)~~
- Link Qt and c++ code together
    - This means in general just running the normal c++ code when the UI opens
    - But also linking the user login to the login methods (this involves sending json to an api path currently)
        - Implement methods in the client for login and register
        - Store username and deviceID on client
- ~~Improve API routes (use http params like username?=test)~~
- ~~Fix crash after clearing history (I think it happens when client requests it)~~
- Stop user from refreshing the Wt UI page
- Fix big that clearing history will work if you click cancel
- ~~Fix bug with special characters in content (mainly quotes I think)~~
- Fix timezone bug (convert to UTC-0 before sending) - convert client side?

## Should do

- Improve API routes (use auth)
- Update the UI on new change
- Handle potential errors (with try catches)
- Add any missing SQL injection protections
    - Device, and user


- Use a daemon to run the server (this should be done by running the program)
    - Running the program again should require a command like killing, stopping or resuming the program
- Fix UI for multi user
- Allow user to set ip and login credentials
- Fix not being able to copy from Wt UI on iOS
- Fix iOS scaling
- Fix scroll bar missing in Wt UI on iOS
- The order of items in the UI should be newest to oldest
    - Alternatively there should be a way to change it
- Show time stamps of the items on the UI

## Future

- Make history have a dropdown arrow
- Make an icon

## Optional

- Don't remove search string on enter?
- Change from allowing the textbox to expand to just having a scroll view for long content
    - Both could also be combined to make it even easier to view
    - Another option is to have a more information button that shows a modal view of all details about the entry and is
      a scroll view
