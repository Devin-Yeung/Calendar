# User Manual


## Main Menu
The system will display a menu at the beginning for users to select. Users can select an operation sequence number based on their requirements.

Users can go back to the main menu at any time, simply by inputting `q` which means quit(expect add event).If users want to return to the main menu when entering an event title,`q!` should be inputted instead of `q`.


## Display month calendar:

Users are required to input a month (number) or the abbreviation of the month, the calendar for that month will be displayed.

`"WARNING: Invalid input! (Wrong Month)"` will be given if the month is incorrect.

If an event exists on that date, a small '+' will appear beside the date when the calendar is shown.

## Add events:

The system will ask the user to enter the month (number) or the abbreviation of the month (e.g. "1" or "Jan" or "January"), then system will ask user to input the day (number). Finally, system will ask user to input the title of event.This event will be recorded in your entered date.

`"WARNING: Invalid input! (Wrong Month)"` will be given if the month is incorrect.

`"WARNING: Invalid input! (Wrong Date)"` will be given if the day is incorrect.

`More than one day or invalid characters` will be given if you input more than one day or input some characters

After user input an event, the new event list will be displayed.

- Each event is described in no more than 127 characters in a line.

- Theoretically supports storing an unlimited number of events.

- The events in list will be displayed in a sequence.

Users can do the same operation for other dates in the same month.

## Delete events:

The system will ask the user to enter the month (number) or the abbreviation of the month (e.g. "1" or "Jan" or "January"), then system will ask user to input the day (number). 

`"WARNING: Invalid input! (Wrong Month)"` will be given if the month is incorrect.

`"WARNING: Invalid input! (Wrong Date)"` will be given if the day is incorrect.

`More than one day or invalid characters` will be given if you input more than one day or input some characters

The event(s) will be listed with index. Users can delete single or multiple events base on their requirements.

`WARNING: X is a Wrong EventID! (will be excluded)` will be given if users input a wrong index, and the system will only delete the correct index entered by users.

`No valid events to be deleted (invalid eventId)` will be given if no valid events are detected.

Users can do the same operation for other dates in the same month.

## Inquire events:

The system will ask the user to enter the month (number) or the abbreviation of the month (e.g. "1" or "Jan" or "January"), then system will ask user to input the day (number). 

`"WARNING: Invalid input! (Wrong Month)"` will be given if the month is incorrect.

`"WARNING: Invalid input! (Wrong Date)"` will be given if the day is incorrect.

`More than one day or invalid characters` will be given if you input more than one day or input some characters


A list of events on that date will be displayed.

Users can do the same operation for other dates in the same month.

## Search event:

Users can search events by entering parts of the event title instead of the whole and accurate event title.

For example, if users input event "hello", the system will match the five events whose meaning are closest to "hello" and list them with dates.

Note: Fuzzy search **DOES NOT** search events by keywords! If user only enters keywords,system may give some very strange events.


## Quit:
The system will exit and save all the data to files.



