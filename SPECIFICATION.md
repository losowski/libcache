# SPECIFICATION

## Concept
- Cache service library to contain keys and expire them


## Process
- Construct with templated types
- Set expiry time on constructor
- Set refresh time on constructor (to refresh expiry on access)
- Housekeeping interval on constructor
- Set housekeeping first run time
- Adding to map
	< key, object>
	- Sets expiry object
	- If time, then perform housekeeping
- Accessing
	- If time, then perform housekeeping
- Deletion (not implemented)
	- Delete entry
	- If time, then perform housekeeping
- Housekeeping
	- When run sets a time in the future (now + housekeeping interval)
	- Any usage will get current time and compare to housekeeping time
		- If due to run will runm cleanup and set next housekeeping
