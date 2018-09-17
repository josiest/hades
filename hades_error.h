/** hades_error.h
 * Get and Set error messages.
 */

#ifndef HADES_ERROR_H
#define HADES_ERROR_H

enum {
    Hades_MaxErrorLength = 1000 /** Max buffer length for error messages */
};

/** Defined in "hades_error.h"
 * const char* Hades_GetError();
 *
 * Returns the current error message.
 */
const char* Hades_GetError();

/** Defined in "hades_error.h"
 * void Hades_SetGameError(const char* description);
 *
 * Sets a general error message that doesn't come from any subsystems
 *
 *  Parameters:
 * description - describe the error
 */
void Hades_SetGameError(const char*);

/** Defined in "hades_error.h"
 * void Hades_SetErrorSDL(const char* description);
 *
 * Sets an error message that comes from an SDL function call
 *
 *  Parameters:
 * description - describe the error
 */
void Hades_SetErrorSDL(const char*);

#endif
