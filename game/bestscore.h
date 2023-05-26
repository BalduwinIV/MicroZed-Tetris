/* Tool for working with bestscore. */

#ifndef BESTSCORE_H
#define BESTSCORE_H

#define BESTSCORE_FILENAME              "bestscore.data"

/* Reads bestscore from BESTSCORE_FILENAME file and returns the value. */
unsigned int get_bestscore();

/* Sets a new value in BESTSCORE_FILENAME file. 
 * Bestscore file is binary file, so value converts to binary format at first.
 * After that writes data to BESTSCORE_FILENAME file in little-endian format. */
void set_bestscore(unsigned int value);

#endif
