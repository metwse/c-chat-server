/*!
 * Chat server protocol definitions/enumerations.
 */

#ifndef PROTOCOL
#define PROTOCOL

/**
 * Represents the type of response.
 */
enum command_response_type {
    /// Authenticates the connection with user credentials.
    AUTHENTICATE_CONNECTION,
    /// Logs out user from.
    UNAUTHENTICATE_CONNECTION,
    /// Is returned if something went wrong during signup.
    USER_CREATION_FAILED,
    /// Error that is returned cannot log into account.
    LOGIN_FAILED,

    CHANNEL_NOT_FOUND,
    USER_NOT_FOUND,
    INVALID_CHANNEL_PASSWORD,
    
    /// Returned when a user does not have permission to run the command,  
    /// such as removing a channel without being subscribed to it.
    UNAUTHENTICATED,

    ALERT,
    CLOSURE_ALERT,
};

/**
 * Response for commands.
 */
struct command_response {
    enum command_response_type *type;
    void *response;
};

#endif
