# Protocol
If a message is sent without specifying a channel or a user, it will be 
broadcasted to all channels the user is subscribed to.

### `/subscribe <channel_name> <channel_password>`
Subscribes to the specified chanel. Messages from the channel will be 
broadcasted to the user.

### `/unsubcribe <channel_name>`
Unsubcribes from the channel.

### `/list_users <channel_name>`
Lists users subscribed to the channel. Can only be used by channel subscribers.

### `/delete <channel_name>`
Deletes the specified channel. Can only be used by channel subscribers.

### `/logout`
Logs out and unauthenticates the connection.

### `#<channel_name> ...message`
Sends a message to a specific channel.

### `@<username> ...message`
Sends a message to specified user.
