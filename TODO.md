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

## Should do

- Improve API routes (use auth)
- Update the UI on new change
- Handle potential errors (with try catches)
- Add any missing SQL injection protection


- Use a daemon to run the server
- Fix UI for multi user
- Allow user to set ip and login credentials

## Future

- Make history have a dropdown arrow
- Make an icon

## Optional

- Don't remove search string on enter?
